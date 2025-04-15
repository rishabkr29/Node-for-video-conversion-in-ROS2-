from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='image_conversion_pkg',
            executable='image_conversion_node',
            name='image_conversion_node',
            output='screen'
        )
    ])
