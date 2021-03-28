import java.util.Scanner;
/*
Ethan Chase
This program: Lets the user enter a number of 3 digits and outputs the digits in reverse order on separate lines
 */
public class HW2_Digits {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);

        //Input for the original 3 digit number
        System.out.printf("Enter an integer of exactly 3 digits(e.g. 538): ");
        int totNum = myScan.nextInt();

        //Math calculations to separate the digits
        int hunNum = (totNum/100);
        int tenNum = ((totNum/10)%10);
        int oneNum = (totNum%10);

        //Final output of the separated numbers
        System.out.printf("%d%n%d%n%d", oneNum, tenNum, hunNum);
    }
}
