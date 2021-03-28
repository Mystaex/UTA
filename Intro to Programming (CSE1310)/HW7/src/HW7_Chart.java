import java.util.Scanner;
/*
 * Author: Ethan Chase
 * CSE 1310 - 001
 * This program is meant to collect a user defined amount of items and their names. Then, print out horizontal charts
 * regarding the count of each item, and their percentage of all items added together. The user is then prompted to
 * update the program, and given an option to continue.
 */
public class HW7_Chart {
    public static Scanner myScan = new Scanner(System.in);

    public static void main(String args[]) {
        String items[];
        int counts[];
        int updateCount = 0;
        String updateItem = "";
        int cont = 0;

        //Infinite look until the user provides the stop code
        while (true) {
            items = readItems();
            counts = readCounts();
            printHorizChart(counts, items);                                         //Printing normal chart
            System.out.printf(itemMaxCount(counts, items));                         //Printing highest count item
            System.out.printf("Compute and print percentages chart \n");
            printHorizChart((getPercentages(counts)), items);                       //Printing percentages
            System.out.printf("Enter item and value to update the counts: ");
            updateItem = myScan.next();
            updateCount = myScan.nextInt();
            updateCounts(counts, items, updateItem, updateCount);                   //Updating counts
            printHorizChart(counts, items);                                         //Printing new normal chart
            //Optional stopcode point
            System.out.printf("Do you want to repeat these steps? (0-No/1-Yes): ");
            cont = myScan.nextInt();
            if (cont == 0) {
                break;
            }
        }
    }

    //Method to print the necessary horizontal charts from 0 - 100 given the items and counts
    public static void printHorizChart(int[] counts, String[] items) {
        //Insures the arrays are of equal length
        if (items.length == counts.length) {
            //maxLength is 2 so that no matter what, it fits "ct"
            int maxLength = 2;
            //Finding the item with the longest character length
            for(int x = 0; x < items.length; x++){
                if(items[x].length() > maxLength){
                    maxLength = items[x].length();
                }
            }

            //Printing counts with respective items
            for (int i = 0; i < items.length; i++) {
                //Defines amount of spaces necessary for each item in the chart
                int spaceCount = maxLength;
                spaceCount = spaceCount - items[i].length();
                String space = "";
                //Adds up necessary spaces
                for (int s = 0; s < spaceCount; s++) {
                    space += " ";
                }
                System.out.printf("%s%s|", items[i], space);
                //Prints a asterisk for the amount of counts each item has
                for (int c = 0; c < counts[i]; c++) {
                    System.out.printf("   *");
                }
                System.out.printf("\n");
            }

            //Defining the amount of spaces for the count label
            int spaceCount = maxLength;
            spaceCount = spaceCount - "ct".length();
            String space = "";
            for(int s = 0; s < spaceCount; s++){
                space += " ";
            }
            //Listing out the count axis
            System.out.printf("ct%s|",space);
            for (int n = 1; n < 101; n++) {
                System.out.printf("%4d", n);
            }
            System.out.printf("\n");
        }
        //Error code if the arrays don't match in length
        else {
            System.out.printf("\tError in printHorizChart: arrays do not have the same number of items\n");
        }
    }

    //Method to find the item with the highest count. If 2 counts are equal, the first checked will we used
    public static String itemMaxCount(int[] counts, String[] items) {
        String maxItem = "";
        int maxCount = 0;
        //Insures the arrays are of equal length
        if (items.length == counts.length) {
            //Runs through every count and retains the highest value
            for (int i = 0; i < counts.length; i++) {
                if (counts[i] > maxCount) {
                    maxCount = counts[i];
                    maxItem = items[i];
                }
            }
            return ("Item with largest count: " + maxItem + "\n\n");
        }
        //Error code if array lengths dont match
        else {
            return ("\tError in itemMaxCount: arrays do not have the same number of items\n");
        }
    }

    //Method to calculate the percentages of each item out of the total amount
    public static int[] getPercentages(int[] counts) {
        int[] percent = new int[counts.length];
        int total = 0;

        //Defining sum of all counts for the items
        for (int i = 0; i < counts.length; i++) {
            total += counts[i];
        }

        //Calculating each percentage
        for (int i = 0; i < counts.length; i++) {
            percent[i] = (counts[i] * 100 / total);
        }

        return percent;
    }

    //Method to read the counts of each item given by the user
    public static int[] readCounts() {
        System.out.printf("Enter the data for the counts array in format (N count1 count2 ... countN): ");
        int count = myScan.nextInt();
        int counts[] = new int[count];
        //Defines the counts array with count number of inputted ints
        for (int i = 0; i < count; i++) {
            counts[i] = myScan.nextInt();
        }
        System.out.printf("Reading the items finished.\n");

        return counts;
    }

    //Method to read the items given by the user
    public static String[] readItems() {
        System.out.printf("Enter the number of items and their names (N item1 item2 ... itemN): ");
        int count = myScan.nextInt();
        String items[] = new String[count];
        //Defines the items array with count number of inputted Strings
        for (int i = 0; i < count; i++) {
            items[i] = myScan.next();
        }
        System.out.printf("Reading the items finished.\n");

        return items;
    }

    //Method to update the count for an item if applicable
    public static void updateCounts(int[] counts, String[] items, String givenItem, int value) {
        boolean valid = false;
        //Insures the arrays are of equal length
        if (counts.length == items.length) {
            //Checking to see if the given item is the same as any of the items in the array
            for (int i = 0; i < items.length; i++) {
                if (givenItem.equals(items[i])) {
                    valid = true;
                    counts[i] = value;
                }
            }
            if (!valid) {
                System.out.printf("\tError. No update will be made. Not found in items: %s\n", givenItem);
            }
        }
        //Error code if the arrays arent equal in length
        else {
            System.out.printf("\tError in UpdateCounts: arrays do not have the same number of items\n");
        }
    }
}