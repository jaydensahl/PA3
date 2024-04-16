@mainpage ELEC 331 Programming Assignment 3

@author Jayden Sahl (jaydensahl)
@author Yousaf Nazari (yousafnazari)

Status of the project: 
- Calculates the link utilization rate and writes it to "output.txt"
  based on the input parameters provided by the input file

How to run:

Method 1:
- in a WSL program, 'make' binaries
- from src folder, run ./csma inputFileName
- inputFileName is named according to the input file provided

Method 2 (using VS Code terminal):
- in VS Code open a new terminal
- navigate to src folder
- compile by entering the following command in terminal: 'gcc -o csma csma.c'
- run the csma.c file using the following command while still in the src directory: './csma inputfilename'

To run test functions:
- simply uncomment test function calls in main and perform the same steps above in 'How to run'