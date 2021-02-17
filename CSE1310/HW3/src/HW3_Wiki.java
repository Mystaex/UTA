import java.util.Scanner;
/*
Ethan Chase
This program Outputs the subject of a given wikipedia link
 */
public class HW3_Wiki {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);

        //Defines the standard for a wiki page, and collects the inputted webpage
        String wikiDef = "https://en.wikipedia.org/wiki/";
        System.out.printf("This program will extract the topic from a valid Wikipedia webpage address.\n");
        System.out.printf("Enter a web address: ");
        String webPage = myScan.nextLine();

        //Decides if the input was a wiki page and if it is, Outputs the topic
        if(webPage.substring(0, 30).equals(wikiDef)){
            String topic = webPage.substring((webPage.indexOf("wiki/") + 5));
            System.out.printf("Topic: %s", topic);
        }
        else{
            System.out.printf("Not a valid wikipedia webpage address");
        }
        System.out.printf("\nBye");
    }
}
