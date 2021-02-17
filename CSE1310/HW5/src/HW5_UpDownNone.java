import java.util.Scanner;
/*
Ethan Chase
This program decides if 2 sets of 3 user inputted ints are in a specific order, and compares both orders to see if they are the same or different
 */
public class HW5_UpDownNone {

    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);
        int inOne, inTwo, inThree;
        String res1, res2;

        //Input for the first 3 numbers
        System.out.printf("Enter three integers separated by spaces: ");
        inOne = myScan.nextInt();
        inTwo = myScan.nextInt();
        inThree = myScan.nextInt();

        //output for the second 3 numbers
        res1 = upDown(inOne, inTwo, inThree);
        System.out.printf("These numbers are in order: %s", res1);

        //Input for the second 3 numbers
        System.out.printf("\nEnter three integers separated by spaces: ");
        inOne = myScan.nextInt();
        inTwo = myScan.nextInt();
        inThree = myScan.nextInt();

        //Output for the second 3 numbers
        res2 = upDown(inOne, inTwo, inThree);
        System.out.printf("These numbers are in order: %s", res2);

        //Comparison for result of int sets
        if(res1.equals(res2)){
            System.out.printf("\nsame");
        }
        else{
            System.out.printf("\ndifferent");
        }
    }

    //Method to decide if there is an order for a set of ints
    public static String upDown(int a, int b, int c){
        String order = "";
        //If statement for decreasing of 3 ints
        if(a > b){
            if(b > c){
                order = "decreasing";
            }
            else{
                order = "none";
            }
        }
        //If statement for increasing 3 ints
        else if(c > b){
            if(b > a){
                order = "increasing";
            }
            else{
                order = "none";
            }
        }
        //if the first one is neither
        else{
            order = "none";
        }
        return order;
    }
}
