# project_angry_birds

Motivation
-------------
Building the popular Angry Birds video game with OpenGL igraphics GUI using C Programming Language.


Brief Description of Gameplay
--------------------------------
• Main Mechanism

The main mechanism of the game is dragging a bird from a slinger and releasing it at a certain angle and velocity. The angle creates from the initial point and the releasing point of the bird. The velocity of bird depends on the distance released from the initial point.
To implement this projectile logic there are three main functions. Functions are lanuchAngle( ), launchVelocity( ), projectileMotion( ). When the bird is released imouse( ) gets the coordinate of the releasing point and passes it to the launchAngle( ) and launchVelocity( ) function. They calculate the angle and velocity then pass them to projectileMotion( ). The projectile motion is frequently called by iSetTimer to update the coordinates of the bird. The bird is shown using iShowBMP2 with changing coordinates.

• Projectile Prediction

There is a dot line prediction of projectile before launching the bird that helps player to target obstacles. The logic of dot prediction is also made with same logic of projectile motion, and it constantly takes coordinates from imousemove to show prediction.

• Sound

There is background music for the game. When buttons are clicked there is a sound. Also, when the bird is released, and a collision happens then there is a sound. All sound and music can be on/off using the sound button. For that a Boolean musicOn is declared to be true and all sounds initially conditioned with true, when musicOn is false all sounds are off.

• Leaderboard Update

There is a leaderboard that stores scores and names in a text file. Whenever a new game is played the name, and score gets updated. The text file is then sorted according to the scores in descending order.

• Regeneration of Obstacles

When the game is over and a new game is started or the back button is clicked then all birds, pigs and obstacles are regenerated. This is done with a restart( ) function that sets all the declared values to initial values.

• Game Over and New Game

When all the pigs die then the game is over display show a button to play a new game. The new game starts with regeneration of all the obstacles and birds.

• Check Collision

To detect the collision, coordinates of bird are compared frequently after launching the bird. When the coordinates match there will be a collision and then set a condition to remove the image of that obstacle.


Algorithm used in gameplay
-----------------------------
The gameplay mainly uses projectile motion to launch the birds and hit obstacles. The velocity and angle are calculated with functions.
The algorithm used in gameplay is shown in the following flowchart.
Calculate angle,velocrty then call projectile.
Check coordinate with obstacle to check collision,set bird initial.


Challenges
-------------
• To make the projectile motion there is a need to set a timer that calls projectile function at a certain interval of time. In igraphics the iSetTimer function can be called maximum of 10 times after the game built.
• The yellow bird’s speed is increased when clicking in the air. But the coordinates change with large distance. That can make the collision hard to detect.
• When checking collision for the blue bird all three birds should check collision individually otherwise when one of the birds collide the other two will not check the collision.
• While switching from one menu to another, gameState variable is used. But when two or more coordinates are the same then the mouse click is true for all conditions and menus may be skipped. For that we should use else if condition.


Attachments
--------------
This is the you tube link for video demonstration of Angry Birds game:

https://www.youtube.com/watch?v=Ola-ENVe5Aw
