import java.util.Scanner;
/*
Ethan Chase
This program: Lets the user enter 3 grades and outputs the highest and lowest of the 3
 */
public class HW2_MaxMin {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);

        //input of the grades
        System.out.println("This program will compute the smallest and highest of 3 grades entered by the user.");
        System.out.print("Please input 3 grades separated by a space: ");
        double gradeOne = myScan.nextDouble();
        double gradeTwo = myScan.nextDouble();
        double gradeThree = myScan.nextDouble();

        //output of the highest and lowest
        System.out.println("Smallest : " + Math.min(gradeOne, Math.min(gradeTwo, gradeThree)));
        System.out.println("Highest : " + Math.max(gradeOne, Math.max(gradeTwo, gradeThree)));

        System.out.println("Bye");
    }
}
