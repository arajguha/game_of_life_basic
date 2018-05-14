# game_of_life_basic

#purpose : to demonstrate the ease of simulating simple C.A based models

#This project has been coded in C. Change system("cls") statement at the end of the code
to system("cls") to run in unix os.

This project typically runs in the terminal. '#' character has been used in place of black pixels. " " (whitespace)
has been used in place of white pixels

//no implementation of threads
//eqivalent java code to be uploaded later
//from java it can be use in processing or p5.js for more in depth computations and visualisations

compilation and execution : (use full screen mode for visualisation)
in windows :
open command prompt(note:https://sourceforge.net/projects/tdm-gcc/ --> link for tdm gcc compiler)
1. type wmic and press enter
2. make command prompt fullscreen
3. type quit and press enter
4. gcc game_mod.c -o <outputfile_name>
5. <output_file_name> [NO_OF_ROWS] [NO_OF_COLS]

for unix os :
open terminal
1. gcc game_mod.c -o <outputfile_name>
2. ./<output_file_name> [NO_OF_ROWS] [NO_OF_COLS]
