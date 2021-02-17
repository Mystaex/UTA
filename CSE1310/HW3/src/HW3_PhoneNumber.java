import java.util.Scanner;
/*
Ethan Chase
This program formats any 10 length string, that the user inputs, as a phone number
 */
public class HW3_PhoneNumber {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);

        //Collects string/phone number from user
        System.out.printf("This program will format a string as a phone number.\n");
        System.out.printf("Enter the number: ");
        String inNum = myScan.nextLine();

        //Decides if inputted string is 10 char in length, and if it is, formats it as a phone number
        if(inNum.length() == 10) {
            System.out.printf("Formatted number: (%s)%s-%s", inNum.substring(0,3), inNum.substring(3,6), inNum.substring(6));
        }
        else {
            //Gives the user a second chance to enter a 10 length string
            System.out.printf("Not a valid number. Please enter another one: ");
            inNum = myScan.nextLine();

            if(inNum.length() == 10){
                System.out.printf("Formatted number: (%s)%s-%s", inNum.substring(0,3), inNum.substring(3,6), inNum.substring(6));
            }
            else
            {
                System.out.printf("You missed your second try! No more chances!");
            }
        }
        System.out.printf("\nBye.");
    }
}
