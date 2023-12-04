import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from ei_interfaces.msg import EIClassification
from ei_interfaces.msg import EIResult
from geometry_msgs.msg import PoseStamped, Point, Quaternion

class GoalPosePubSub(Node):
    def __init__(self):
        super().__init__('goal_pose_pub_sub')
        self.publisher_ = self.create_publisher(PoseStamped, '/goal_pose', 10)
        self.subscription = self.create_subscription(EIResult, '/wakeword_publisher', self.listener_callback, 10)

        self.pose_dict = {
            'kitchen': PoseStamped(),
            'living_room': PoseStamped(),
            'office': PoseStamped(),
            'bedroom': PoseStamped()
        }

        # Predefined pose data for different locations
        self.pose_dict['office'].pose.position = Point(x=-3.5909152030944824, y=-3.2075748443603516, z=0.0)
        self.pose_dict['office'].pose.orientation = Quaternion(x=0.0, y=0.0, z=1.5, w=1.0)

        self.pose_dict['living_room'].pose.position = Point(x=-6.732161521911621, y=0.7128251194953918, z=0.0)
        self.pose_dict['living_room'].pose.orientation = Quaternion(x=0.0, y=0.0, z=-0.6987532750001173, w=1.0)

        self.pose_dict['kitchen'].pose.position = Point(x=-8.503005027770996, y=-1.9668318033218384, z=0.0)
        self.pose_dict['kitchen'].pose.orientation = Quaternion(x=0.0, y=0.0, z=0.5494003685647514, w=1.0)

        self.pose_dict['bedroom'].pose.position = Point(x=-2.9972314834594727, y=1.2094670534133911, z=0.0)
        self.pose_dict['bedroom'].pose.orientation = Quaternion(x=0.0, y=0.0, z=-0.9409409053266997, w=1.0)

    def listener_callback(self, msg):
        most_likely_label = 'background'
        highest_probability = 0

        for classification in range(0, len(msg.result)):
            if msg.result[classification].value > highest_probability and msg.result[classification].value > 0.96:
                highest_probability = msg.result[classification].value
                most_likely_label = msg.result[classification].label

        goal_name = most_likely_label
        print(goal_name)

        if goal_name in self.pose_dict:
            goal_pose = self.pose_dict[goal_name]
            goal_pose.header.stamp = self.get_clock().now().to_msg()
            goal_pose.header.frame_id = "map"
            self.publisher_.publish(goal_pose)
            # self.get_logger().info('Published goal pose: %s' % goal_name)
        else:
            pass

def main(args=None):
    rclpy.init(args=args)
    goal_pose_pub_sub = GoalPosePubSub()
    rclpy.spin(goal_pose_pub_sub)

    goal_pose_pub_sub.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
