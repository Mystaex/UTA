import java.util.Scanner;
/*
Ethan Chase
This program outputs the divisors of a user inputted interval of [start, end] in a formatted manner with a horizontal
line splitting the numbers of the interval that is a user defined length.
 */
public class HW6_DivisorsA2B {
    public static void main(String args[]){
        //Variable declaration
        Scanner myScan = new Scanner(System.in);
        String line = "";

        //User input into variable declaration
        System.out.println("This program will print the divisors of each number in the [A,B].");
        System.out.printf("Enter A:");
        int a = myScan.nextInt();
        System.out.printf("Enter B:");
        int b = myScan.nextInt();
        System.out.printf("Enter length of horizontal line:");
        int lineLen = myScan.nextInt();
        System.out.println(""); //Empty line

        //Processing for the line, making it modular to user input
        for(int i = 0; i < lineLen ; i++){
            line = line + "-";
        }

        //Insuring the program can run
        if((b-a) >= 0){
            for(int x = a; x <= b; x++){
                String divisors = "";
                for(int test = 2; test <= b; test++){
                    //Testing to see if a number in the interval is divisible by [2,b]
                    if(x % test == 0){
                        //Adding divisible numbers with a comma and space
                        divisors = divisors + test + ", ";
                    }
                }
                //Output the dashed line then number in interval with all divisors
                System.out.printf("%s\n",line);
                System.out.printf("%d : %s\n", x, divisors);
            }
        }
        //Ending code.
        System.out.printf("%s\n", line);
        System.out.printf("Bye");
    }
}
