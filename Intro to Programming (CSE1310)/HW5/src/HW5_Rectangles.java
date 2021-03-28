import java.util.Scanner;
/*
Ethan Chase
This program outputs a complete rectangle of x width and y height with a outline of a rectangle that is the same size to the right of it
 */
public class HW5_Rectangles {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);
        int inNum = 0;

        //Intro and x/y input
        System.out.printf("This program will display a full and an empty square given the side length.\n");
        System.out.printf("Enter the side length: ");
        inNum = myScan.nextInt();

        //Method call to print the rectangles
        printRectangles(inNum);
        System.out.printf("Bye");
    }

    //Method to print rectangles and define rows
    public static void printRectangles(int height){
        String space = " ";
        String asterisk = "*";
        String lengthBody = "";
        String lengthEdge = "";

        //Defines each row for rectangles
        for(int i = 0; i < ((height*2) +2); i++){
            if((i < height) || (i == (height + 2)) || (i == ((height * 2) + 1))){
                lengthBody += asterisk;
            }
            else{
                lengthBody += space;
            }
            if((i < height) || (i > height + 1)){
                lengthEdge += asterisk;
            }
            else{
                lengthEdge += space;
            }
        }
        //Outputs rows of rectangles in formatted manner
        for(int h = 0; h < height; h++){
            if ((h == 0) || (h == (height-1))){
                System.out.printf("%s\n", lengthEdge);
            }
            else{
                System.out.printf("%s\n", lengthBody);
            }
        }
    }
}
