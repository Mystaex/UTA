import java.util.Scanner;
/*
Ethan Chase
This program accepts user input for 2 christmas present lists on one line. It then returns the 2 lists in a formatted manner
 */
public class HW8_RobotSanta {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);
        String presents[];
        String AliceArr[];
        String BobArr[];

        //User input and splitting into a mass presents array
        System.out.printf("Enter the presents:");
        presents = myScan.nextLine().split(";");

        //Combining all presents for each person together into one string
        String bobPres = "";
        String aliPres = "";
        for(int i = 0; i < presents.length; i++){
            if(presents[i].substring(0,1).equals("A")){
                aliPres += presents[i].substring(2) + ";";
            }
            else if(presents[i].substring(0,1).equals("B")){
                bobPres += presents[i].substring(2) + ";";
            }
        }
        //Splitting up the present lists
        AliceArr = aliPres.split(";");
        BobArr = bobPres.split(";");

        //Outputting the present lists
        System.out.printf("\nAlice gets:\n");
        for(int a = 0; a < AliceArr.length; a++){
            System.out.println(AliceArr[a]);
        }
        System.out.printf("\nBob gets:\n");
        for(int a = 0; a < BobArr.length; a++){
            System.out.println(BobArr[a]);
        }
    }
}