import java.io.*;
import java.util.*;
import java.lang.*;
/*
Ethan Chase
This program takes in a file of a specific format and calculates grade averages for n amount of students
it then creates 2 text files, one that prints the calculated data in a formatted manner, and one that prints
in an unformatted manner. Finally, it prints the grade of each student in order of letter grade to the console.
 */

public class HW9_Grades {
    public static void main(String[] args){
        //Variable declaration
        Scanner input = new Scanner(System.in);
        ArrayList<String> nameGrade = new ArrayList<>();

        //User input
        System.out.printf("Please enter the name of the input file: ");
        String input_name = input.nextLine();
        System.out.printf("Please enter the name of the output CSV file: ");
        String out_name = input.nextLine();
        System.out.printf("Please enter the name of the output pretty-print file: ");
        String pretty_name = input.nextLine();

        //Creating the text files to write to
        PrintWriter out = null;
        PrintWriter pretty = null;
        try{
            out = new PrintWriter(out_name);
        }
        catch (FileNotFoundException e){
            System.out.printf("ERROR: Cannot create file with name %s\n",out_name);
            System.exit(0);
        }
        try{
            pretty = new PrintWriter(pretty_name);
        }
        catch (FileNotFoundException e){
            System.out.printf("ERROR: Cannot create file with name %s\n",pretty_name);
            System.exit(0);
        }

        //Reading the data from the file
        ArrayList<String> fileData = readFromFile(input_name);

        //For loop to process each line of data from the input
        for(int x = 1; x < fileData.size(); x++){
            float avgExam = 0;
            float avgHmw = 0;
            float minGrade = 0;
            String grade = " ";
            String data[] = fileData.get(x).split(",");

            //Calculating averages
            avgExam = (Float.parseFloat(data[2]) + Float.parseFloat(data[3]) + Float.parseFloat(data[4]))/3;
            for(int y = 5; y < 12; y++){
                avgHmw += Float.parseFloat(data[y]);
            }
            avgHmw = avgHmw/7;
            minGrade = Math.min(avgExam,avgHmw);
            //Declaring letter grade
            if(minGrade >= 90){
                grade = "A";
            }
            else if(minGrade >= 80){
                grade = "B";
            }
            else if(minGrade >= 70){
                grade = "C";
            }
            else if(minGrade >= 60){
                grade = "D";
            }
            else{
                grade = "F";
            }

            //Outputting to unformatted and formatted text files
            if(x == 1)
            {
                pretty.printf("%20s: %10s, %8s, %9s, %s\r\n", "name", "exam score", "hw score", "min score", "grade");
                out.printf("name,exam score,hw score,min score,grade\r\n");
            }
            pretty.printf("%20s: %10.2f, %8.2f, %9.2f, %s\r\n", data[0] + " " + data[1], avgExam, avgHmw, minGrade, grade);

            out.printf("%s,%2.6f,%2.6f,%2.6f,%s\r\n",data[0]+ " " + data[1],avgExam,avgHmw,minGrade,grade);
            //Creating output list for letter grade
            nameGrade.add(grade + " " + data[0] + " " + data[1]);
        }
        out.close();
        pretty.close();

        //Output names in order of letter grade
        System.out.println("\nNames in order of letter grade:");
        for(int i = 0; i < nameGrade.size(); i++){
            if(nameGrade.get(i).substring(0,1).equals("A")){
                System.out.println(nameGrade.get(i));
            }
        }
        for(int i = 0; i < nameGrade.size(); i++){
            if(nameGrade.get(i).substring(0,1).equals("B")){
                System.out.println(nameGrade.get(i));
            }
        }
        for(int i = 0; i < nameGrade.size(); i++){
            if(nameGrade.get(i).substring(0,1).equals("C")){
                System.out.println(nameGrade.get(i));
            }
        }
        for(int i = 0; i < nameGrade.size(); i++){
            if(nameGrade.get(i).substring(0,1).equals("D")){
                System.out.println(nameGrade.get(i));
            }
        }
        for(int i = 0; i < nameGrade.size(); i++){
            if(nameGrade.get(i).substring(0,1).equals("F")){
                System.out.println(nameGrade.get(i));
            }
        }
        System.out.printf("\n\nExiting...");
    }

    //Method to read data from a file
    public static ArrayList<String> readFromFile(String fname) {
        Scanner inputFile;
        try {
            inputFile = new Scanner( new File(fname) );
        }
        catch (FileNotFoundException badThing) {
            System.out.println("Could not open file " + fname);
            return null;
        }
        ArrayList<String> fileData = new ArrayList<>();
        //Add each line from the file to the data list
        while( inputFile.hasNextLine() ){
            String line = inputFile.nextLine();
            fileData.add(line);
        }
        inputFile.close();
        return fileData;
    }
}