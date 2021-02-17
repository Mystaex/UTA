import java.util.Scanner;
/*
Ethan Chase
This program outputs a rectangle of asterisks that is 3 wide and n tall.
 */
public class HW4_Rectangle {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);

        //User input for height of rectangle
        System.out.printf("Enter N: ");
        int n = myScan.nextInt();

        //Processing and output of rectangle
        for(int i = 0; i < n; i++){
            System.out.printf("***\n");
        }
        System.out.printf("Bye");
    }
}
