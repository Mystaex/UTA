import java.util.Scanner;


/* HW1_Div
 * CSE 1310 Section
 * @author Ethan Chase
 * A program intended to divide 1 user-inputted number by a 2nd user-inputted number and output the answer
 */
public class HW1_Div{
    public static void main(String[] args){
        int num1;
        int num2;
        Scanner in = new Scanner(System.in);
        System.out.print("Enter the first number: ");
        num1 = in.nextInt();
        System.out.print("Enter the second number: ");
        num2 = in.nextInt();

        //outputting the equation to divide the 2 inputted numbers
        System.out.println(num1 + " / " + num2 + " = " + (num1/num2));

    }
}