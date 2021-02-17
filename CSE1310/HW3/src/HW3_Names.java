import java.util.Scanner;
/*
Ethan Chase
This program collects the first and last name of someone, then outputs their name and initials
 */
public class HW3_Names {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);

        //Collects full name
        System.out.printf("Please enter your first and last name: ");
        String fullName = myScan.nextLine();

        //Separates name into first and last name
        String firstName = fullName.substring(0, fullName.indexOf(" "));
        String lastName = fullName.substring(fullName.indexOf(" ") + 1);

        //separates name into first letters of name, and the rest
        String irstName = firstName.substring(1);
        String astName = lastName.substring(1);
        String fName = firstName.substring(0,1);
        String lName = lastName.substring(0,1);

        //Outputs the name in a specific format
        System.out.printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        System.out.printf("|%S%-14s|%S%-14s|%S.%S.|\n", fName, irstName, lName, astName, fName, lName);
        System.out.printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }
}
