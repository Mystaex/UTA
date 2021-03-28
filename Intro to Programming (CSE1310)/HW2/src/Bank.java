import java.util.Scanner;
/*
Ethan Chase
This program: Lets the user enter a starting amount for their bank account and 2 transactions from that amount,
outputting the data after each input
 */
public class Bank {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);

        //Input for the starting amount
        System.out.printf("This program will simulate 2 bank transactions. %n");
        System.out.printf("Enter the original amount of money in the bank: ");
        double startAmount = myScan.nextDouble();

        //First transaction
        System.out.printf("Enter the 1st transaction: ");
        double firstTran = myScan.nextDouble();
        System.out.printf("Current amount: %.2f%n", (startAmount + firstTran));

        //Second transaction
        System.out.printf("Enter the 2nd transaction: ");
        double secTran = myScan.nextDouble();
        System.out.printf("Current amount: %.2f%n", (startAmount + firstTran + secTran));

        //Output of the original amount
        System.out.printf("The original amount was: %.2f", startAmount);
    }
}
