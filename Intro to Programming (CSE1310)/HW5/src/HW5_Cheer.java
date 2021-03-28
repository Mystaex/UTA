import java.util.Scanner;

/*
Ethan Chase
This program prints a user inputted cheer x(user inputted repetitions) times with both static horizontal position and diagonally
 */

//Beginning of provided code
public class HW5_Cheer {
    public static void main(String[] args) {
        Scanner kb = new Scanner(System.in);
        String banner, text;
        int reps = 4;
        System.out.print("Enter your cheer: ");
        text = kb.nextLine();
        System.out.print("Enter the number of repetitions: ");
        reps = kb.nextInt();
        System.out.println("Calling printCheer");
        printCheer(text, reps);
        System.out.println("Calling printCheerDiag");
        printCheerDiag(text, reps);
    }

    public static void printCheer(String cheer, int N){
        int i;
        for(i = 0; i < N; i++){
            System.out.println(cheer);
        }
    }
    //End of provided code

    //Method for diagonal cheering
    public static void printCheerDiag(String cheer, int N){
        int i;
        String extent = "";
        for(i = 0; i < N; i++){
            System.out.println(extent + cheer);
            //Adding horizontal varity
            extent += " ";
        }
    }
}