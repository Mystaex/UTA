import java.util.Scanner;
/*
Ethan Chase
This program collects company names and the amount they have donated towards two causes and computes the values given
 */
public class HW3_Donations {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);
        String topComp;

        //Collecting the company names
        System.out.printf("Enter the first company: ");
        String compOne = myScan.nextLine();
        System.out.printf("Enter the second company: ");
        String compTwo = myScan.nextLine();

        //Collecting the Christmas donations amounts
        System.out.printf("Enter how much each company donated for Christmas gifts: \n");
        System.out.printf("%s donated: ", compOne);
        int christOne = myScan.nextInt();
        System.out.printf("%s donated: ", compTwo);
        int christTwo = myScan.nextInt();

        //Collecting the school support donations amounts
        System.out.printf("Enter how much each company donated for school support: \n");
        System.out.printf("%s donated: ", compOne);
        int schoolOne = myScan.nextInt();
        System.out.printf("%s donated: ", compTwo);
        int schoolTwo = myScan.nextInt();

        //Outputting the total christmas and school support donations
        System.out.printf("Total Christmas donations: %d\n", (christOne + christTwo));
        System.out.printf("Total school support donations: %d\n", (schoolOne + schoolTwo));

        //Deciding which company donated more and then outputting the company name
        if((christOne + schoolOne) > (christTwo + schoolTwo)){
            topComp = compOne;
        }
        else{
            topComp = compTwo;
        }
        System.out.printf("The company that donated the most is: %s\n", topComp);
        System.out.printf("Bye");
    }
}
