#include <sstream>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <std_msgs/msg/string.hpp>

#include "canopen_interface.hpp"
#include "conversion_utils.hpp"
#include "constants.hpp"

class CanopenBridgeNode : public rclcpp::Node {
public:
    CanopenBridgeNode() : Node("canopen_bridge_node") {
        cmd_vel_sub_ = create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_velocity", QOS_DEPTH,
            [this](const geometry_msgs::msg::Twist::SharedPtr msg) { cmd_vel_callback(msg); });

        device_state_pub_ = create_publisher<std_msgs::msg::String>("/device_state", QOS_DEPTH);

        poll_timer_ = create_wall_timer(
            std::chrono::milliseconds(TIMER_RATE_MS),
            [this]() { poll_canopen(); });

        last_successful_read_ = now();
        last_cmd_vel_time_    = now();

        RCLCPP_INFO(get_logger(), LOG_NODE_STARTED);
    }

private:
    void send_rpdo(uint16_t index, uint8_t subindex, int value) {
        try {
            canopen_.sendRPDO(index, subindex, value);
        } catch (const std::exception & e) {
            RCLCPP_ERROR(get_logger(), LOG_RPDO_SEND_FAILED, e.what());
        }
    }

    void cmd_vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg) {
        last_cmd_vel_time_ = now();
        int16_t can_vel = to_canopen_velocity(msg->linear.x);
        send_rpdo(VELOCITY_INDEX, VELOCITY_SUBINDEX, can_vel);
        RCLCPP_INFO(get_logger(), LOG_VELOCITY_CMD, msg->linear.x, can_vel);
    }

    void poll_canopen() {
        bool cmd_stale = (now() - last_cmd_vel_time_) >
                         rclcpp::Duration(std::chrono::milliseconds(COMM_TIMEOUT_MS));
        if (cmd_stale) {
            send_rpdo(VELOCITY_INDEX, VELOCITY_SUBINDEX, DEFAULT_VELOCITY);
        }

        try {
            int status_raw  = canopen_.readTPDO(TPDO_INDEX, SUB_STATUS);
            int vel_raw     = canopen_.readTPDO(TPDO_INDEX, SUB_VELOCITY);
            int error_code  = canopen_.readTPDO(TPDO_INDEX, SUB_ERROR_CODE);

            last_successful_read_ = now();

            double velocity      = from_canopen_velocity(static_cast<int16_t>(vel_raw));
            const char * status  = (cmd_stale || status_raw != STATUS_OK) ? STATUS_FAULT_STR : STATUS_OK_STR;

            publish_device_state(status, velocity, error_code);

            if (status_raw != STATUS_OK) {
                RCLCPP_ERROR(get_logger(), LOG_DEVICE_FAULT, error_code);
            }
        } catch (const std::exception & e) {
            rclcpp::Duration elapsed = now() - last_successful_read_;
            if (elapsed > rclcpp::Duration(std::chrono::milliseconds(COMM_TIMEOUT_MS))) {
                RCLCPP_ERROR(get_logger(), LOG_COMM_TIMEOUT, elapsed.seconds(), e.what());
                publish_device_state(STATUS_TIMEOUT_STR, DEFAULT_VELOCITY, STATUS_TIMEOUT);
            } else {
                RCLCPP_ERROR(get_logger(), LOG_TPDO_READ_FAILED, e.what());
            }
        }
    }

    void publish_device_state(const char * status, double velocity, int error_code) {
        std::ostringstream ss;
        ss << "{\"status\": \"" << status << "\", "
           << "\"velocity\": " << velocity << ", "
           << "\"error_code\": " << error_code << "}";

        std_msgs::msg::String out;
        out.data = ss.str();
        device_state_pub_->publish(out);
    }

    CanopenInterface canopen_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr device_state_pub_;
    rclcpp::TimerBase::SharedPtr poll_timer_;
    rclcpp::Time last_successful_read_;
    rclcpp::Time last_cmd_vel_time_;
};

int main(int argc, char ** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CanopenBridgeNode>());
    rclcpp::shutdown();
    return 0;
}
