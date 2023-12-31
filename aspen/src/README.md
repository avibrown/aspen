## aspen-3

This directory tracks my ongoing efforts in building a differential drive SLAM robot. The goal of this project is to familiarize myself with SLAM concepts and the Nav2 stack, as well as to provide a platform for demonstrating the use of TinyML + micro-ROS driven smart components (as per my [talk](https://vimeo.com/showcase/9954564/video/767140724) at ROSCon '22)

I am slowly organizing this project in such a way that I hope others will be able to learn from it and apply parts of it to their own projects. I have lots of people to thank for the educational resources and open source code that made this project possible, namely:
- Josh Newans of [Articulad Robotics](https://articulatedrobotics.xyz/) -- He has a great [course](https://www.youtube.com/watch?v=OWeLUSzxMsw&list=PLunhqkrRNRhYAffV8JDiFOatQXuU-NnxT) on YouTube that helped me a lot with getting my robot running
- Steve Macenski for developing [Nav2](https://navigation.ros.org/) and the [Slam Toolbox](https://github.com/SteveMacenski/slam_toolbox)
- The folks at Factor Robotics for developing the [ODrive ROS 2 Control](https://github.com/Factor-Robotics/odrive_ros2_control) package

<img src='https://user-images.githubusercontent.com/63222803/231443613-5480641b-1625-46fa-b7fb-392498462427.png' width='400'>

---

### Hardware details
- Raspberry Pi 4 8GB
  - Handles ROS 2 control, LiDAR, SLAM...
- rplidar
- ODrive v3.6 24V motor controller
- 2 x brushless "[RoboWheel](https://skysedge.com/robotics/robowheel170/index.html)" hub motors
- Luxonis OAK-D camera
  - Still deciding whether to keep this or not...
- 18V Makita battery
- Arduino Mega
  - Handles manual control over UART <> ODrive: Intentionally isolated from the Pi for safety. 
- Arduino Portenta H7 + Vision Shield
  - This is my TinyML testing device. Currently I have it running a word recognition model that allows me to sent the robot to different rooms around the house with a voice command!
