import java.util.Scanner;
/*
Ethan Chase
This program counts the number of vowels in 2 user inputted strings and a hardcoded string then outputs
 */
public class HW5_VowelCount {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);
        String inString, stringOne, stringTwo, hard = "I love coffee";

        System.out.printf("This program rreads two strings and then calls a method to count how many vowels are in each one of them.\n");

        //User input
        System.out.printf("Enter a string: ");
        stringOne = myScan.nextLine();
        System.out.printf("Enter a string: ");
        stringTwo = myScan.nextLine();

        //Output of vowel counting
        System.out.printf("Number of vowels in the string %s : %d\n", stringOne, vowelsCt(stringOne));
        System.out.printf("Number of vowels in the string %s : %d\n", stringTwo, vowelsCt(stringTwo));
        System.out.printf("Number of vowels in the string \"%s\" : %d", hard, vowelsCt(hard));

    }

    public static int vowelsCt(String word){
        int vowelCount = 0;

        //Processing for vowels.
        //vowelCount adds up all vowels
        for(int i = 0; i < word.length(); i++){
            if(word.charAt(i) == 'A' ||word.charAt(i) == 'a'){
                vowelCount++;
            }
            if(word.charAt(i) == 'E' || word.charAt(i) == 'e'){
                vowelCount++;
            }
            if(word.charAt(i) == 'O' || word.charAt(i) == 'o'){
                vowelCount++;
            }
            if(word.charAt(i) == 'U' || word.charAt(i) == 'u'){
                vowelCount++;
            }
            if(word.charAt(i) == 'I' || word.charAt(i) == 'i'){
                vowelCount++;
            }
            if(word.charAt(i) == 'Y' || word.charAt(i) == 'y'){
                vowelCount++;
            }
        }
        return vowelCount;
    }
}


