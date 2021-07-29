======================================
Program:
    substring_thread.c
======================================
Included files:
    substring_thread.c
    tests/hamlet.txt
    tests/shakespeare.txt
    tests/test1.txt
======================================
Compilation:
    gcc -o substring substring_thread.c -lpthread

Example run:
    ./substring tests/hamlet.txt
======================================
Description:
    Like substring.c, substring_thread.c loops through a given string of N1 characters 
    checking the substring at that spot and beyond from that spot, x, to x+N2 (number 
    of characters in given substring, S2). In this threaded version of substring.c, S1 is 
    split into an equal number of threads to run simultaneously, hopefully speeding up the process.
    I designed my multithreaded adapted program under the assumption that the number of threads 
    used will satisfy the given conditions (Let T be the number of threads):
    - N1%T == 0
    - N1/T > N2
======================================
Notes:
    Made for Ubuntu Linux
    
    In the input files, S1 is taken from the first line of the .txt file and S2 is taken from 
    the second. ie.
    "abzzzzabzab
    ab"
    S1 = "abzzzzabzab" ; S2 = "ab";

    To change the number of threads for a given compilation of the program, change the 
    global constant "NUM_THREADS".
