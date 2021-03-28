import java.util.Scanner;
/*
Ethan Chase
This program creates a chess board with user defined dimensions. Then asks the user to select other actions regarding
the queen. It interprets the possible moves that every queen on the board can make, and prints them in a formatted manner.
 */
public class HW8_PlaceQueens {
    public static void main(String args[]){
        Scanner myScan = new Scanner(System.in);
        String board[][] = null;
        int side = 0;

        while(true){
            //Printing out the menu and requesting a choice from the user
            System.out.printf(  "q - quit\n" +
                                "r - reset,\n" +
                                "m - make,\n" +
                                "a - add queen,\n" +
                                "d - delete queen,\n" +
                                "c - count queen,\n" +
                                "p - print board\n\n");
            System.out.printf("Enter option: ");
            String option = myScan.next();

            //If statement block for interpreting the user's menu choice
            if(option.toLowerCase().equals("q")){
                break;
            }
            //Insuring that for the below options, the board has already been made
            else if(option.toLowerCase().equals("m")){
                System.out.printf("Enter board size: ");
                side = myScan.nextInt();

                board = makeBoard(side,side);
                printBoard(board);
            }
            else if(option.toLowerCase().equals("a")){
                System.out.printf("Enter row and column (1-N): ");
                int row = myScan.nextInt();
                int column = myScan.nextInt();
                if(row <= side && column <= side)
                    addQueen(row,column,board);
            }
            else if(option.toLowerCase().equals("d")){
                System.out.printf("Enter row and column (1-N): ");
                int row = myScan.nextInt();
                int column = myScan.nextInt();
                if(row <= side && column <= side)
                    board = removeQueen(row,column,board);
            }
            else if(option.toLowerCase().equals("c")){
                countQueen(board);
            }
            else if(option.toLowerCase().equals("p")){
                printBoard(board);
            }
            else if(option.toLowerCase().equals("r")){
                board = resetBoard(board);
            }
        }
    }

    //Method to make the board
    public static String[][] makeBoard(int row, int column){
        String board[][] = new String[row][column];

        //Setting all values of the board to a space so that it isn't null
        for(int x = 0; x < column; x++){
            for(int y = 0; y < row; y++){
                board[x][y] = " ";
            }
        }
        return board;
    }

    //Method to reset the board
    public static String[][] resetBoard(String board[][]){
        //Looping through the board and setting all values to a space
        if(board != null){
            for(int y = 0; y < board[0].length; y++){
                for(int x = 0; x < board.length; x++){
                    board[x][y] = " ";
                }
            }
        }
        else{
            System.out.printf("Not a valid board. Could not be reset.\n");
        }
        printBoard(board);
        return board;
    }

    //Method to print the board
    public static void printBoard(String board[][]) {
        String rowSpacing = "---";

        if(board != null){
            for(int y = 0; y < board[0].length; y++){
                if(y == 0) {
                    System.out.printf("  |");
                    //Identifying the length of the line in between rows, and printing x axis
                    for(int i = 0; i < board.length; i++){
                        rowSpacing += "----";
                        System.out.printf("%3d|", (i + 1));
                    }
                    System.out.printf("\n%s\n",rowSpacing);
                }
                //Printing y axis and values of board in a formatted manner
                System.out.printf("%2d|", (y+1));
                for(int x = 0; x < board.length; x++){
                    System.out.printf(" %s |", board[x][y]);
                }
                System.out.printf("\n%s\n", rowSpacing);
            }
        }
        //Printing an error code
        else{
            System.out.println("Not a valid board. Cannot be printed.\n");
        }
    }
    public static String[][] removeQueen(int row, int column, String board[][]){
        row--;
        column--;
        //Removing the queen if it is valid
        if(row < board.length && column < board.length){
            if(board[column][row].equals("Q")){
                board[column][row] = " ";
                //removing all possible moves to re-evaluate with updated queens
                for(int y = 0; y < board[0].length; y++){
                    for(int x = 0; x < board.length; x++){
                        if(board[x][y].equals("*")){
                            board[x][y] = " ";
                        }
                    }
                }
            }
            else{
                System.out.println("Not a valid queen");
            }
            //re-evaluating possible moves
            board = possibleMoves(board);
            printBoard(board);
        }
        else{
            System.out.printf("Invalid row or column.\n");
        }
        return board;
    }

    public static void countQueen(String board[][]){
        int count = 0;

        //Loop through the board looking for queens and counting them
        for(int y = 0; y < board[0].length; y++){
            for(int x = 0; x < board.length; x++){
                if(board[x][y].equals("Q")){
                    count++;
                }
            }
        }

        System.out.printf("Counted queens on the board: %d\n",count);
    }

    //Method to add a queen to the board
    public static String[][] addQueen(int row, int column, String board[][]){
        row --;
        column --;

        if(row < board.length && column < board.length){
            //Add a queen, then find possible moves
            board[column][row] = "Q";
            board = possibleMoves(board);
        }
        else{
            System.out.printf("Invalid row or column.\n");
        }

        printBoard(board);
        return board;
    }

    //Method to identify all possible moves for the queens on the board
    public static String[][] possibleMoves(String board[][]){
        //Loop through the board looking for queens
        for(int y = 0; y < board[0].length; y++){
            for(int x = 0; x < board.length; x++){
                //Once it finds a queen, check for all possible moves
                if(board[x][y].equals("Q")){
                    for(int yt = 0; yt < board[0].length; yt++){
                        for(int xt = 0; xt < board.length; xt++){
                            if(x == xt && y == yt){
                                board[xt][yt] = "Q";
                            }
                            //Placing the asterisks down for possible moves
                            else if(!board[xt][yt].equals("Q")){
                                if((x == xt || y == yt) || ((x+y == xt+yt) || ((xt-yt) == (x-y)))){
                                    board[xt][yt] = "*";
                                }
                            }
                        }
                    }
                }
            }
        }
        return board;
    }
}