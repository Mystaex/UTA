import java.util.Scanner;
/*
Ethan Chase
This program creates and outputs a square of x length and r repeat in a given pattern.
 */
public class HW6_Pattern2 {
    public static void main(String args[]){
        //Variable declaration
        Scanner myScan = new Scanner(System.in);
        int len = 0, repeat = 0;
        String line = "";
        String pattern[][];

        //Intro and user input
        System.out.printf("This program will print a len X len pattern\n");
        System.out.printf("Enter len: ");
        len = myScan.nextInt();
        System.out.printf("Enter repeat: ");
        repeat = myScan.nextInt();

        //Loop that defines each property in the pattern array with the given pattern and desired length.
        pattern = new String[len][len];
        for(int x = 0; x < len; x++){
            for(int y = 0; y < len; y++){
                if(((x + y)%repeat == 0) || ((x + y) == 0)){
                    pattern[x][y] = "\\";
                }
                else{
                    pattern[x][y] = "-";
                }
                System.out.printf("%s", pattern[x][y]);
            }
            System.out.printf("\n");
        }
        //Ending
        System.out.printf("Bye");
    }
}