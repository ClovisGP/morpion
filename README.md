# my_morpion
## Description
Hello, this project was carried out as part of my year in Ireland at Dublin City University, as part of the course 2022/2023 CA644 System Software. The goal was to make a small C program using several concepts seen during the first semester such as sockets.
For my part, I chose to create a multiplayer crag (or tik tak toe) where each player can connect and play, or watch the game that is in progress.
This project was completed in 5 days.

## Setting up:
For setting up the project, go at the same level thant the *Makefile* and run the following command:
```
make
```
If you run the following command, it is going to clean the project and recompile it.
```
make re
```
And when you are done, you can run this last command for cleanning the all project.
```
make fclean
```

## Launch the project
After setting up the project, you can run this command for launch the server. Carefull, the port and size arguments are both mandatory despite the fact that if the game board size is unvailable, the size is going to be set to the default size of 3 case.
Finally, the port number has to be between 1 and 9999. And the size, between 3 and 10.
```
./my_morpion port-[portNumber] size-[gameBoardSize]
```


Clovis GILLES 15/11/2022