import java.util.Scanner;


/* HW1_Avg
 * CSE 1310 Section
 * @author Ethan Chase
 * A program intended to produce the average of 3 user-inputted grades
 */
public class HW1_Avg {
    public static void main(String args[])
    {
        Scanner myScan = new Scanner(System.in);

        System.out.println("Enter Grade 1: ");
        int gradeOne = myScan.nextInt();
        System.out.println("Enter Grade 2: ");
        int gradeTwo = myScan.nextInt();
        System.out.println("Enter Grade 3: ");
        int gradeThree = myScan.nextInt();

        //Averaging the 3 inputted ints
        double avg = ((gradeOne + gradeTwo + gradeThree) / 3);

        System.out.println(avg);
    }
}
