package main;
import java.util.Scanner;

public class BoardController {

	private BoardModel model;
	

	
	public BoardController(BoardModel.Difficulty difficulty, int seed)
	{
		model = new BoardModel(difficulty, seed);
	}
	
	public BoardController()
	{
		this(BoardModel.Difficulty.BEGINNER, 42);
	}

	
	public void displayVisible()
	{
		int numRows = model.rows();
		int numCols = model.columns();
		
		System.out.print(" ");
		for (int x = 0; x < numCols; x++) {
			System.out.printf("%4s", x);
		}
		System.out.println();
		
		for (int i = 0; i < numRows; i++) {
            System.out.printf("%2s", i);
			for (int j = 0; j < numCols; j++) {
				System.out.print("|");
				
				if (model.isFlagged(i, j)) {
					System.out.print(" F ");
				} else if (model.isUnknown(i,j)) {
					System.out.print(" ? ");
				} else if (model.isCleared(i, j)) {
                    int count = model.adjacentMineCount(i, j);
                    if (count == 0) {
                        System.out.print("   ");
                    }else{
						System.out.printf("%2s ", count);
					}
				}
			}
			System.out.println("|");
		}
	}
	
	public void displayAll()
	{
		int numRows = model.rows();
		int numCols = model.columns();
		
		System.out.print(" ");
		for (int x = 0; x < numCols; x++) {
			System.out.printf("%4s", x );
		}
		System.out.println();
		
		for (int i = 0; i < numRows; i++) {
			System.out.printf("%2s", i);
			for (int j = 0; j < numCols; j++) {
				System.out.print("|");

				if (model.isMined(i, j) && model.isFlagged(i, j)) {
					System.out.print(" X ");
				} else if (model.isMined(i, j)) {
					System.out.print(" M ");
				} else if (!model.isMined(i, j)) {
					System.out.print("   ");
				}
			}
			System.out.println("|");
		}
	}
	
	public static void main(String[] args)
	{

        Scanner userInput = new Scanner(System.in);
	    System.out.print("What mode do you want to play in beginner, intermediate, or expert (b, i, e)? ");
        BoardModel.Difficulty level = null;
        do{
            String input = userInput.next();
            switch(input){
                case "beginner":
                case "b":
                    level = BoardModel.Difficulty.BEGINNER;
                    break;
                case "intermediate":
                case"i":
                    level = BoardModel.Difficulty.INTERMEDIATE;
                    break;
                case "expert":
                case "e":
                    level = BoardModel.Difficulty.EXPERT;
            }
        }while(level == null);

		BoardController game = new BoardController(level, 42);

        label:
        do {
            int row, col;
            String cmd;

            game.displayVisible();
            System.out.println("Flags Remaining: " + game.model.flagsRemaining());

            System.out.print("> ");

            cmd = userInput.next();
            switch (cmd) {
                case "q":
                case "quit":
                case "exit":
                    System.out.println("Thanks for playing!");
                    break label;
                case "reset":
                    System.out.println("Resetting the game board.");
                    game.model.resetBoard();
                    break;
                case "r":
                case "f":

                    row = userInput.nextInt();
                    col = userInput.nextInt();

                    if (cmd.equals("r")) {
                        if (!game.model.reveal(row, col) && !game.model.lost()) {
                            System.out.printf("Unable to reveal [%d, %d]\n", row, col);
                        }
                    } else {
                        if (!game.model.flag(row, col)) {
                            System.out.printf("Unable to flag [%d, %d]\n", row, col);
                        }
                    }

                    if (game.model.won()) {
                        game.displayAll();
                        System.out.println("YOU WIN!");
                        break label;
                    } else if (game.model.lost()) {
                        game.displayAll();
                        System.out.println("GAME OVER");
                        break label;
                    }

                    break;
                default:
                    System.out.println("unrecognized command: \"" + cmd + "\"");
                    break;
            }
        } while (true);
	}



}
