import java.util.Scanner;
/*
Ethan Chase
This program asks the user to input a start, end, and step values, then increments by the step value from the start to
end values while asking the user to input the expected result
 */
public class HW4_VerifyCountBy {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);
        int start, end, step, inNum;

        //Opening statements
        System.out.printf("This program will be counting by a certain step.\n");
        System.out.printf("Enter what you want the start, end and step values to be.\n");

        //User inputs for start, end, and step
        System.out.printf("start is: ");
        start = myScan.nextInt();
        System.out.printf("end is: ");
        end = myScan.nextInt();
        System.out.printf("step is: ");
        step = myScan.nextInt();

        //User inputs and processing for the series of numbers
        System.out.printf("Enter the numbers (starting with %d):\n", start);
        for(int i = start; i <= end; i += step){
            System.out.printf("Enter your answer: ");
            inNum = myScan.nextInt();

            //If the inputted number is correct
            if(inNum == i){
                System.out.printf("Correct\n");
            }
            else{
                System.out.printf("Wrong. The correct answer was: %d\n", i);
            }
        }
        System.out.printf("Bye");
    }
}
