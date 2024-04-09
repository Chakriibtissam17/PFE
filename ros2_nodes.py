import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Range
from geometry_msgs.msg import Twist

class KS0523RobotNode(Node):
    def _init_(self):
        super()._init_('ks0523_robot_node')
        # Publisher for sending commands to the robot's motors
        self.cmd_vel_publisher_ = self.create_publisher(Twist, 'cmd_vel', 10)
        # Subscriber for receiving data from ultrasonic sensors
        self.ultrasonic_subscriber_ = self.create_subscription(Range, 'ultrasonic', self.ultrasonic_callback, 10)
        # Timer for periodic tasks (e.g., checking sensor data)
        timer_period = 0.1  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def ultrasonic_callback(self, msg):
        # Process ultrasonic sensor data
        if msg.range < 0.2:  # If an obstacle is closer than 20cm
            self.stop_robot()  # Stop the robot

    def timer_callback(self):
        # Periodic tasks (e.g., sending keep-alive signals)
        pass

    def stop_robot(self):
        # Stop the robot by publishing zero velocities
        stop_msg = Twist()
        stop_msg.linear.x = 0.0
        stop_msg.angular.z = 0.0
        self.cmd_vel_publisher_.publish(stop_msg)
        self.get_logger().info('Stopping the robot due to an obstacle.')

def main(args=None):
    rclpy.init(args=args)
    node = KS0523RobotNode()
    rclpy.spin(node)
    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    node.destroy_node()
    rclpy.shutdown()

if _name_ == '_main_':
    main()
