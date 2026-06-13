Build:

```bash
source /opt/ros/$ROS_DISTRO/setup.bash
cd ros2_ws
colcon build
source install/setup.bash
```

Run:

```bash
ros2 run canopen_bridge canopen_bridge_node
```

Test the command path by publishing a velocity command:

```bash
ros2 topic pub /cmd_velocity geometry_msgs/msg/Twist "{linear: {x: 1.5}}"
```

Monitor device state feedback:

```bash
ros2 topic echo /device_state
```

AI usage:

1. Finish the mock canopen interface in [@canopen_interface.cpp] according to specifications in the pdf.

I ended up removing unnecessary headers that the agent added. Also wrote a constants.hpp where I moved some hardcoded variables. Converted static constexpr to precompiler constants.
The agent wrote a very bloated logger which I removed.

2. Create a ros2 workspace for the project.

The agent created the workspace with corresponding CMakeLists.txt and package.xml files.
For some reason it also decided to implement canopen_bridge_node.cpp without me asking for it.
I ended up mostly rewriting the node class while keeping the original class structure.
The agent also added unnecessary subdirectories which I removed.

3. Add build and run instructions to [@README.md]

Changed the ros distro to be parametric.

4. Replace all usage of auto with the proper datatypes.

5. Move message creation and publication into a dedicated function in [@canopen_bridge_node.cpp]

6. Replace all hardcoded status strings with the precompiler constants defined in [@constants.hpp]

I also asked the agent to write comprehensive unit tests for the bridge node 
but ended up reverting them because testing required too many changes to the
base classes and the specification didn't ask for unit tests.
