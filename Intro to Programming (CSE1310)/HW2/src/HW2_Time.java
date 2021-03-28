import java.util.Scanner;
/*
Ethan Chase
This program: Lets the user enter distance and speed and outputs the travel time in 2 formats
 */
public class HW2_Time {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);

        //User input of distance and speed
        System.out.printf("This program will compute the travel time.%n");
        System.out.printf("Enter the distance (miles): ");
        int dist = myScan.nextInt();
        System.out.printf("Enter the car speed (miles/hour): ");
        int speed = myScan.nextInt();

        //All the math to compute the amount of travel time
        double time = (double)dist/(double)speed;
        int orMin = (int)((time%1)*60);
        int orHour = (int)(time/1);

        //The final output of travel time in 2 formats
        System.out.printf("Travel time: %.2f", time);
        System.out.printf("%nor: %d hour(s) and %d minutes", orHour, orMin);

    }
}
