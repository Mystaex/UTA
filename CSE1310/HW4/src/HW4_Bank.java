import java.util.Scanner;
/*
Ethan Chase
This program will continuously add transactions to an inputted balance in a formatted way until the user inputs a transaction of 0.
 */
public class HW4_Bank {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);
        double balance = 0, start = 0, tran = 1;

        //Introductory message and section for input of starting balance
        System.out.printf("This program simulates transactions in a bank account.\n");
        System.out.printf("Enter your current balance (money in your account): ");
        start = myScan.nextDouble();
        balance = start;

        //Looping of transactions until transaction is 0
        while (tran != 0){
            //Input for transaction and reprocessing of balance with regard to new transaction
            System.out.printf("Enter transaction: ");
            tran = myScan.nextDouble();
            balance = balance + tran;
            //Leaving the loop if transaction is 0
            if(tran == 0) {
                break;
            }

            //Outputting of the formatted bank table
            System.out.printf("|transaction|    balance|\n");
            System.out.printf("|%11.2f|%11.2f|\n", tran, balance);
        }

        //Outputting if the user made or lost money. Comparison for original vs new balance
        if(balance >= start){
            System.out.printf("You made money or have the same as when you started.\n");
        }
        else{
            System.out.printf("You lost money.\n");
        }
        System.out.printf("Bye");
    }
}
