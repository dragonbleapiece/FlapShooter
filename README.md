# FlapShooter 
### 2D arcade game in OpenGL

The goal of this project was to create a 2D arcade game, halfway between a FLAPPY BIRD and a SPACE SHOOTER using the OpenGL library.
Our realization, named "Flap Shooter", features an angry rabbit flying on a plane in a pixelated horizontal set. With his carrot thrower, he has to fight flying rats while avoiding obstacles and recovering bonuses.

## Compile and launch the game

To compile the game, use the makefile file directly in the program folder:
```
make
```
N.B. The SDL 1.2 library must be installed before.

If the game configuration has been changed (file /includes/settings.h), it's recommended to delete all the already compiled files:
```
make clean
```

Finally, to start the game, simply run the command:
```
./bin/FlapShooter
```

## Commands

The rabbit can move horizontally and vertically on the screen using the directional keys and shoot with the space key. In addition, the F12 key allows to put the game in full screen (or reduce it if necessary).

### A 2d arcade game created by Nicolas CUSUMANO and Nicolas SENECAL
