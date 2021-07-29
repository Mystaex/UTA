README
**************
Ethan Chase
1001457646 | EGC7646
**************
File(s) included: msh.c
**************
Description:
This program recreates the bash shell with some popular commands heavily utilizing the exec() family of functions along with forking.
**************
Compilation instructions:
->This is built in a Ubuntu virtual machine
->In terminal: gcc msh.c -o msh

Run Instructions:
     ./msh
**************
***Commands***
quit
exit
ls <directory>
cd <directory>
mkdir <directory>
listpids (Lists the pids of the past 0 to 15 pids used for forking)
history (Lists the past 0 to 15 commands used)
[Any other command supported by exec()]

**************
Notes:
Made for Ubuntu Linux
All commands should support parameters that are supported via bash shell ie. "ls -la"

!n is currently not functional. Change is required.
