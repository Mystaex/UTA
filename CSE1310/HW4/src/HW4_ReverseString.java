import java.util.Scanner;
/*
Ethan Chase
This program reverses any user inputted string
 */
public class HW4_ReverseString {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);

        //Section to input string
        System.out.printf("This program will create a string with letters in reversed order.\n");
        System.out.printf("Enter a string: ");
        String word = myScan.nextLine();

        //Section to output and process the reversed string
        System.out.printf("The reversed string is: ");
        for(int i = (word.length() - 1); i > -1; i--){
            System.out.printf("%s", word.charAt(i));
        }
        System.out.printf("\nBye");
    }
}
