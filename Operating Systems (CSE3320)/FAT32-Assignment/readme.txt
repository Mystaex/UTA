README
**************
Ethan Chase
1001457646 | EGC7646
**************
File(s) included: mfs.c
                  fat32.img (FAT32 image file)
**************
Description:
This program reads a given FAT32 image file byte-by-byte and allows the user to perform a variety of functions with the files and information by utilizing fseek().
**************
Compilation instructions:
->This is built in a Ubuntu virtual machine
->In terminal: gcc mfs.c -o mfs

Run Instructions:
     ./mfs
     open fat32.img
**************
***Commands***

open <filename>
This command shall open a fat32 image. Filenames of fat32 images shall not contain spaces and
shall be limited to 100 characters.

close
This command shall close the fat32 image.

info
This command shall print out information about the file system in both hexadecimal and base 10:
• BPB_BytesPerSec
• BPB_SecPerClus
• BPB_RsvdSecCnt
• BPB_NumFATS
• BPB_FATSz32

stat <filename> or <directory name>
This command shall print the attributes and starting cluster number of the file or directory name.
If the parameter is a directory name then the size shall be 0.

get <filename>
This command shall retrieve the file from the FAT 32 image and place it in your current workingdirectory. 

cd <directory>
This command shall change the current working directory to the given directory. Does not support absolute or relative paths.

ls
Lists the directory contents.

read <filename> <position> <number of bytes>
Reads from the given file at the position for the given number of bytes
**************
Notes:
Made for Ubuntu Linux
