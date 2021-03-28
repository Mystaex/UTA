import java.util.Scanner;
/*
Ethan Chase
This program uses a method to output complete rectangles of asterisks that is x in height until x is 0
 */
public class HW5_RectangleFull {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);
        int inNum;
        System.out.printf("This program will repeatedly get an integer from the user and print a rectangle of that height.\n");

        //Continuously requests new height until input is 0, then ends program
        while(true){
            System.out.printf("Enter height: ");
            inNum = myScan.nextInt();
            //Breaks infinite loop
            if(inNum == 0){
                break;
            }
            else{
                printRectangleFull(inNum);
            }
        }
        System.out.printf("Bye");
    }

    //Method to print rectangle of x height
    public static void printRectangleFull(int height){
        for(int i = 0; i < height; i++){
            System.out.printf("***\n");
        }
    }
}
