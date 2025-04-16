# Node-for-video-conversion-in-ROS2
image_conversion Node:
1. The image_conversion node should Subscribe to the image topic (colored image) published by usb_cam package.
2. The image_conversion node continuously publishes the output image to an output ROS2 topic. You can decide the name of the output ROS2 topic.
3. The image_conversion  node hosts (server) a ros2 service (bool), to change its mode - 
    Mode 1: Greyscale
    Mode 2: Color
4. The image_conversion node should let the user change its mode through the above service call.
5. Based on the mode, the image_conversion node should convert the RGB/BGR input image to grayscale (mode 1) or not convert it (mode 2).
6. image_conversion node should then continuously publish the final image as the output image on the output ROS2 topic. 
