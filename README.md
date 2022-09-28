# wall_following_Turtlebot3

The wall following behavior is a behavior that makes the robot follow along the wall on its right hand side. This means that the robot must be moving forward at a 30cm distance from the wall, having the wall on its right hand side, the entire time.

To achieve this behavior in the robot, you need to do two things:

## Subscribe to the laser topic of the robot

You need to subscribe to the laser topic and capture the rays. Select the ray on the right (the one that makes a 90º angle to the right with the front of the robot) and use it to measure the robot's distance to the wall.

NOTE: The topics for different simulations most likely will not be named the same. So make sure that you are using the correct name. For example, you used /kobuki/laser/scan during the course. The laser topic in this simulation is /scan

## Publish to the velocity topic of the robot

* If the ray distance is bigger than 0.3m, you need to make the robot approach the wall a little, by adding some rotational speed to the robot
* If the ray distance is smaller than 0.2m, you need to move the robot away from the wall, by adding rotational speed in the opposite direction
* If the ray distance is between 0.2m and 0.3m, just keep the robot moving forward

### IMPORTANT

When the robot is moving along a wall, it can reach the next wall crossing its way. At that point in time, you should include a behavior that progressively transitions the robot from following the current wall to the next one.

For that, we recommend that you use the front laser ray. If the distance measured by that ray is shorter than 0.5m, then make the robot turn fast to the left (moving forward at the same time).

The result of this behavior must be that the robot moves along the whole environment (see video below).
![Alt Text](https://github.com/khaledgabr77/wall_following_Turtlebot3/blob/master/wall_follow_long.gif)
