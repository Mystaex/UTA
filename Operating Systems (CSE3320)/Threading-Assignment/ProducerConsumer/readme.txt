======================================
Program:
    procon.c
======================================
Included files:
    procon.c
    message.txt
    message2.txt
    message3.txt
======================================
Compilation:
    gcc -o procon procon.c -lpthread

Example run:
    ./procon
======================================
Description:
    Create a producer-consumer algorithm-based program that reads in a text file one char at a
    time into a circular queue, and outputs them in the same order.
======================================
Notes:
    Made for Ubuntu Linux
    
    I chose to only output the result from the consumer thread, as to make the message continuous.
    I found that if the producer also outputted when a char was read, then the message 
    became obscure.

    If you wish to change the input text file, simply change the global char[] filename. 
    
    In case you would like to watch the code in an incremental manner, include unistd and add 
    sleep(1); to the producer or consumer function. 
