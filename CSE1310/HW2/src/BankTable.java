import java.util.Scanner;
/*
Ethan Chase
This program: Lets the user enter a starting amount for their bank account and 2 transactions from that amount,
outputting the data in a formatted table
 */
public class BankTable {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);

        //Input for the starting amount
        System.out.printf("This program will simulate 2 bank transactions. %n");
        System.out.printf("Enter the original amount of money in the bank: ");
        double startAmount = myScan.nextDouble();

        //Input for the 2 transactions
        System.out.printf("Enter the 1st transaction: ");
        double firstTran = myScan.nextDouble();
        System.out.printf("Enter the 2nd transaction: ");
        double secTran = myScan.nextDouble();

        //Creation of the actual table
        System.out.printf(  "---------------------------%n" +
                            "| Transaction |  Account  |%n" +
                            "|             |  %7.2f  |%n" +
                            "|    %7.2f  |  %7.2f  |%n" +
                            "|    %7.2f  |  %7.2f  |%n" +
                            "---------------------------", startAmount, firstTran, (startAmount + firstTran), secTran, (startAmount + firstTran + secTran));
    }
}