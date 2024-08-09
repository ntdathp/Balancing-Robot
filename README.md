# Balancing-Robot
Design a two-wheeled self-balancing robot with DC motor from scratch with Fuzzy logic controller, using a complementary filter to determine the tilt angle of the robot with an IMU.

#Fuzzy logic implement
The robot system has two input variables: tilt angle and tilt rate, with the output being the motor rotation speed.

![Robot system](img/Robot_Fuzzy.png)


Based on that, I designed fuzzy control rules for the robot system.

![example](ing/example.png)

Linguistic values of input and output variables.

![variables](ing/Fuzzy_logic.png)

Fuzzy control rule table for the robot:

![example](ing/Rule_table.png)
