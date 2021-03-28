import java.util.Scanner;

/**
 * @author Ethan Chase
 * This program repeatedly asks the user for a word and will generate
 * all the substrings of a given word, in increasing order of substring length.
 */


public class HW6_Substrings {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        //Introduction
        System.out.printf("This program will generate all the substrings of a "
                + "given word, in increasing order of substring length.\n");

        //Infinite loop to continue asking for a user inputted word, and method calls to print substrings
        System.out.printf("\nPlease enter a word or q to quit: ");
        String userWord = in.nextLine();
        for ( ; !userWord.equals("q") ; ){
            //printSubstrings_a(userWord);  // method for part a)
            printSubstrings_b(userWord);  // method for part b
            //printSubstringsExtra2(userWord);
            System.out.printf("\n\nPlease enter a word or q to quit: ");
            userWord = in.nextLine();
        }
        System.out.println("\n\nBye\n");
    }

    //Method that prints substrings with a comma between them
    public static void printSubstrings_a(String word){
        int len = word.length();

        //For loop to print and differentiate substrings
        for(int y = 1; y <= len; y++){
            for(int x = 0; (x + y) <= len; x++){
                String rowSpace = "";
                int dif = (y-x);
                //Calculating amount of required spaces
                while (dif < len){
                    rowSpace += " ";
                    dif++;
                }
                //Printing substrings in the given format
                System.out.printf("%s%s",word.substring(x,(x+y)),rowSpace + ", ");
            }
            System.out.printf("\n");
        }
    }

    //Method that prints all possible substrings for a word in a formatted manner
    public static void printSubstrings_b(String word){
        int len = word.length();

        //Calculates each possible row with correct spacing
        for(int y = 1; y <= len; y++){
            String row = "";
            for(int x = 0; (x + y) <= len; x++){
                String rowSpace = "";
                int dif = (y-x);
                String close = "";

                //Calculating spacing
                while (dif < len){
                    rowSpace += " ";
                    dif++;
                }
                //Deciding the spacing needs a | at the end to close a statement
                if((x + y) == len)
                    close = "|";
                else
                    close = "";

                row += ("| "+ word.substring(x,(x+y)) + rowSpace + " " +  close);
            }

            //Defining the dashed line
            String dash = "";
            for(int i = 0; i < row.length(); i++){
                dash += "-";
            }
            //Making the special case for the first dashed line
            if(y == 1) {
                System.out.printf("%s\n", dash);
            }

            //Printing output of both the rows, then the dashed line
            System.out.printf("%s\n", row);
            System.out.printf("%s\n", dash);
        }
    }
}