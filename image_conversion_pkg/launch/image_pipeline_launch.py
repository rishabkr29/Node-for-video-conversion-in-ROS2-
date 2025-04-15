from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='dummy_usb_cam',
            executable='dummy_usb_cam_node',
            name='dummy_usb_cam_node',
            output='screen',
            parameters=[{
                "video_device": "/dev/video0",  # You can adjust this
                "image_width": 640,
                "image_height": 480,
                "framerate": 30,
            }],
        ),
        Node(
            package='image_conversion_pkg',
            executable='image_conversion_node',
            name='image_conversion_node',
            output='screen',
        )
    ])
