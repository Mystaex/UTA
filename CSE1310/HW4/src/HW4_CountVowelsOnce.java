import java.util.Scanner;
/*
Ethan Chase
This program counts out many distinct and total vowels are in a user inputted phrase
 */
public class HW4_CountVowelsOnce {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);
        String inString;
        int aBool = 0, eBool = 0, oBool = 0, uBool = 0, iBool = 0, yBool = 0, totNum = 0;

        //User input
        System.out.printf("Enter a phrase. I will count the vowels\n");
        inString = myScan.nextLine();

        //Processing for vowels. (ie. aBool = 1 if there is one or more 'A's in the string, therefore can only be 1 or 0)
        //totNum adds up all vowels
        for(int i = 0; i < inString.length(); i++){
            if(inString.charAt(i) == 'A' || inString.charAt(i) == 'a'){
                aBool = 1;
                totNum++;
            }
            if(inString.charAt(i) == 'E' || inString.charAt(i) == 'e'){
                eBool = 1;
                totNum++;
            }
            if(inString.charAt(i) == 'O' || inString.charAt(i) == 'o'){
                oBool = 1;
                totNum++;
            }
            if(inString.charAt(i) == 'U' || inString.charAt(i) == 'u'){
                uBool = 1;
                totNum++;
            }
            if(inString.charAt(i) == 'I' || inString.charAt(i) == 'i'){
                iBool = 1;
                totNum++;
            }
            if(inString.charAt(i) == 'Y' || inString.charAt(i) == 'y'){
                yBool = 1;
                totNum++;
            }
        }

        //Output for distinct and total number of vowels. Add up 'Bool' int values to decide how many distinct
        System.out.printf("There are %d distinct vowels in \"%s\".\n", (aBool + eBool + oBool + uBool + iBool + yBool), inString);
        System.out.printf("There are %d total vowels in \"%s\".\n", totNum, inString);
        System.out.printf("Bye");
    }
}