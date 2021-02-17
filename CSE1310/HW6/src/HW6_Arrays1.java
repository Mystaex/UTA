import java.util.Scanner;
import java.util.Random;
/*
Ethan Chase
This program creates grades for the amount of user inputted students in the class, then outputs them in a formatted
manner and classifies amount of each letter grade.
 */
public class HW6_Arrays1 {

    public static void main(String[] args) {
        //Variable declaration and user input section
        Scanner kb = new Scanner(System.in);
        int[] grades;
        int N;
        int aCount = 0, bCount = 0, cCount = 0, dCount = 0, fCount = 0;
        System.out.print("Enter the number of students in the class: ");
        N = kb.nextInt();
        grades = getGrades(N);

        //Output for the called grades
        System.out.println("The grades are:");
        for(int i = 0; i < N; i++){
            System.out.printf("%d\n", grades[i]);
        }

        //Going through the grades to decide the proper letter grade, and adding up count for each letter grade.
        System.out.println("Grade | letter");
        for(int i = 0; i < N; i++){
            String letter = "filler";
            if(grades[i] >= 90){
                letter = "A";
                aCount++;
            }
            else if(grades[i] >= 80){
                letter = "B";
                bCount++;
            }
            else if(grades[i] >= 70){
                letter = "C";
                cCount++;
            }
            else if(grades[i] >= 60){
                letter = "D";
                dCount++;
            }
            else{
                letter = "F";
                fCount++;
            }

            //Outputting grade with proper letter grade in a given format
            System.out.printf("  %3d | %S\n", grades[i], letter);
        }

        //Outputting count for each letter grade
        System.out.println("Grade counts:");
        System.out.printf(  "A: %d\n" +
                            "B: %d\n" +
                            "C: %d\n" +
                            "D: %d\n" +
                            "F: %d\n", aCount, bCount, cCount, dCount, fCount);
    }

    //Method to generate an array of random grades between 0 and 100 in a given seed
    public static int[] getGrades(int N){
        Random rGen = new Random(0);
        int i;
        int arr[] = new int[N];
        for(i = 0; i<N; i++){
            arr[i] = rGen.nextInt(101); // returns a random integer in range[0,100]
        }
        return arr;
    }

}