README
**************
Ethan Chase
1001457646 | EGC7646
**************
File(s) included: money.cpp
**************
This program takes in the name of a 2 word currency exchange office and the first name of the manager. It then continuously asks the traveler for the part of the airport they're in
and puts them in contact with the correct exchange office. It will then ask for the currency they want to exchange and the amount. The amount in dollars will be output and added to 
the "Total dollars given out" pile which outputs when the user exits the program.
**************
Compilation instructions:
->This is built in a Lubuntu virtual machine
->In terminal:g++ money.cpp
    ./a.out
**************
Enter name of exchange office and manager: ABC Conversions Fadiah
Enter name of exchange office and manager: DEF Conversions Ethan

********
Hello traveler! Where are you in the airport? North
********

Welcome to ABC Conversions. Please contact the manager Fadiah if you have any complaints. What currency are you converting to dollars and how much? 200 yen  
Here you go: $1.9

********
Hello traveler! Where are you in the airport? West
********

Welcome to DEF Conversions. Please contact the manager Ethan if you have any complaints. What currency are you converting to dollars and how much? 300 dinar
We do not convert the dinar currency here. Sorry.

********
Hello traveler! Where are you in the airport? West
********

Welcome to DEF Conversions. Please contact the manager Ethan if you have any complaints. What currency are you converting to dollars and how much? 300 pesos
Here you go: $15
********
Hello traveler! Where are you in the airport? exit
********

$$$Total dollars given out: $16.9
Exiting...
**************
Notes:
Directions (North, South, East, West) must be capitalised, while exit must be lowercase.
exit to leave the program.

ABC Conversions and DEF Conversions are the only 2 acceptable currency offices for XYZ airport, as stated in the HW2 documents. 
Directional control will not work for any other currency offices.

2 currencies:
yen
pesos