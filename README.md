# README #

## Controls ##

* A - left;
* D - right;
* Z - shoot;
* R - reload;
* Q - exit;
* 1 - laser
* 2 - machinegun

## Libraries ##

* SOIL;
* GLEW;
* Freeglut;
* Assimp;
* glm 


## What implemented ##
* Battlefield with height field based on a texture;
* Water shader;
* FPS counter;
* Collisions: enemy vs bullets, enemy vs spaceship (but have some problems and commented);
* 3D Model loading (enemies are quads because in the case of loading model on my laptop FPS going to be very small - model is high poly);
* Per pixel shading ("sun");
* Environment mapping and a skybox;
* Scoring system;
* Gameplay;
* Particle (but do not use in game);
* other stuff


## Gameplay ##
The player starting the game can control the spaceship (moving right and left, changing weapon, shooting and reloading). The player has 2 different types of weapons: Laser, which is more condensed but has less damage and Machinegun, which has more delay between shots, but more damage. Enemies has only Machinegun. Killing the enemies adds the score and the frequency of appearing of enemies. If enemy hits the player, it takes away the health or armor. The game finishes when the player does not have any armor and health. In the end the player sees the statistics of game.

## Video ##


## Binaries ##

## Screenshots ##
![Capture.PNG](https://bitbucket.org/repo/MrgdBdr/images/3850406829-Capture.PNG)
Process of game


![Capture2.PNG](https://bitbucket.org/repo/MrgdBdr/images/841858776-Capture2.PNG)
End of game