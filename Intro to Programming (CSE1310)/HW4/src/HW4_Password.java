import java.util.Scanner;
/*
Ethan Chase
This program compares user inputs to a hardcoded case sensitive password
 */
public class HW4_Password {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);
        String password = "CSE1310";
        String inString;

        //Input for password attempts. Given 5 times
        for(int i = 0; i < 5; i++){
            System.out.printf("Enter your password: ");
            inString = myScan.nextLine();

            //Ends for loop if gets the password right
            if(inString.equals(password)){
                System.out.printf("Correct! You're in!\n");
                break;
            }
            else{
                System.out.printf("Wrong\n");
                //If the user takes all 5 tries, then they get locked out
                if(i == 4){
                    System.out.printf("You are locked out!\n");
                }
            }
        }
        System.out.printf("Bye");
    }
}
