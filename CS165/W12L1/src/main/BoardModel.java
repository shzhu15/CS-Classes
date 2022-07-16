package main;
import java.util.Random;

public class BoardModel {

	private BoardSpace[][] board;
	private int numMines;
	private int numFlags;
	private Random rdm;
	
	private boolean isFirstTurn;
	private boolean won;
	private boolean lost;
	
	//difficulty values to pass to constructor
    public enum Difficulty {BEGINNER, INTERMEDIATE, EXPERT}

    /**
     * Depending on the level of difficulty, sets number of rows, columns, and mines for the game.
     * After the level of difficulty has been set, the constructor sets up the game in the following manner:
     * <ol>
     *     <li> Instantiates the board as a 2D array of BoardSpaces.
     *     <li> Assigns each element in the array with a now BoardSpace object.
     *     <li> Calls the {@code resetBoard} method
     *     <li> Initializes the Random instance which deals with where to lay down mines.
     * </ol>
     * @param level difficulty level
     */
	public BoardModel(Difficulty level){
        int rows, cols;
        switch (level) {
            case BEGINNER:
                rows = cols = 8;
                numMines = numFlags = 10;
                break;

            case INTERMEDIATE:
                rows = cols = 16;
                numMines = numFlags = 40;
                break;

            case EXPERT:
            default:
                rows = 16;
                cols = 30;
                numMines = numFlags = 99;
        }
        BoardSpace newSpace = new BoardSpace();
        board = new BoardSpace[rows][cols];
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                board[r][c] = newSpace;
            }
        }
        resetBoard();
        rdm = new Random();
    }

    /**
     * Calls the one argument constructor and then assigns the random
     * object with a new instance that sets the
     * seed. This is mostly for testing purposes
     * @param level the difficulty level
     * @param seed used to create reproducible results
     */
	public BoardModel(Difficulty level, int seed) {
        this(level);
	    rdm = new Random(seed);
	}


    /**
     * Responsible initializing the remaining pieces of game state.
     * <p>
     * resetBoard() assumes that the 2D board array has been initialized so that it may "reset"
     * each individual BoardSpace via their reset() methods.
     *
     * Then, since a new game has been started, isFirstTurn should be set to true. Similarly, since
     * the player has not yet taken a turn, the game has not yet been won or lost. resetBoard() must
     * initialize the remainingMines ArrayList to keep track of mines that have not yet been flagged
     * by the player. Mines are only laid when the player takes their first turn.
     */
    void resetBoard()
	{
        for (BoardSpace[] row : board) {
			for (BoardSpace square : row) {
				square.reset();
			}
		}
		isFirstTurn = true;
		won = lost = false;
	}

    /**
     * Removes a flag from the board position (row, col) and increments the corresponding flag variable.
     * If there was a mine, increment the mine variable.
     * <p>
     * Note: this method is only called if boundaries are already checked and the square
     * has been previously flagged.
     * @param row the current row
     * @param col the current column
     */
	private void unflag(int row, int col)
	{
        board[row][col].setFlagged(false);
        if (board[row][col].isMined()) {
            ++numMines;
            ++numFlags;
        }
	}

    /**
     * Either "flags" or "unflags" a board space as a possible mine if:
     * <ul>
     *     <li> (row, col) represents a valid move
     *     <li> the player has flags left
     *     <li> the board space has not been previously cleared
     * </ul>
     * The player wins if they are able to flag every mine.
     * <p>
     * Note that because there are exactly numMines flags, there is no room for error
     * on the player's part. Players may also undo a flag placement by invoking
     * {@link #unflag(int, int)} on a position that already contains a flag.
     * @param row the current row
     * @param col the current col
     * @return true if the board was successfully flagged or unflagged
     */
	public boolean flag(int row, int col)
	{
		
		board[row][col].setFlagged(true);
		if (board[row][col].isMined()) {
			--numMines;
		}
		--numFlags;
		return true;
	}

	public int flagsRemaining()
	{
		return numFlags;
	}

    /**
     * Exposes the board space specified by (row, col) if it would be a valid move.
     * <p>
     * If it is the player's first turn, the reveal method is also responsible for
     * calling {@link #layMines(int, int)}.
     * <p>
     * The player immediately loses the game if they select a board space that contains a mine
     * (the lost instance variable is set to true and later detected by BoardController).
     * <p>
     * If the player's move does not result in losing the game,
     * the reveal method invokes explore(row, col) to perform the work of actually exposing
     * board spaces. Afterwards, the reveal method checks if every board space that does not
     * contain a mine has been explored. If so, the game immediately ends in victory for the
     * player (won is set to true and detected by BoardController). The {@link #onlyMinesRemain()}
     * method should be used to determine if this event has occurred.
     * @param row the current row
     * @param col the current col
     * @return true if a valid move was selected
     */
    boolean reveal(int row, int col) {
        if (isFirstTurn) {
            layMines(row, col);
            isFirstTurn = false;
        }
		if (!isValidMove(row, col)) {
			return false;
		}
		explore(row, col);
		return true;
	}
	
	private boolean onlyMinesRemain() {
		//check if only hidden spaces are mines
		boolean onlyMinesRemain = true;
        for (BoardSpace[] aBoard : board) {
            for (int c = 0; c < board[0].length-1; c++) {
                if (!aBoard[c].isVisible() && !aBoard[c].isMined()) {
                    onlyMinesRemain = false;
                    break;
                }
            }
        }
		return onlyMinesRemain;
	}

    /**
     * the work horse of BoardModel. The explore method makes the
     * board space specified by (row, col) visible and recursively explores each of its eight
     * neighbors that are not adjacent to a mine. In other words, a neighboring space is only
     * explored if adjacentMineCount(r, c) is 0.
     * <p>
     * Otherwise, the neighbor is only made visible to prevent accidentally exploring a space
     * containing a mine. In general, the explore method does not visit board spaces that have
     * been marked as visible.
     * <p>
     * You should pay special attention to how it chooses neighboring spaces to visit. In other
     * words, you may need to win or lose a game to see the problem.)
     * @param row the current row being explored
     * @param col the current column being explored
     */
	private void explore(int row, int col) {
		if (board[row][col].isVisible()) {
			return;
		}
		board[row][col].setVisibility();
		if (board[row][col].adjacentMineCount() > 0) {
			return;
		}
		for (int r = row-1; r <= row+1; r++) {
			for (int c = col-1; c <= col+1; c++) {
				if (isValidMove(r, c)){
					int mineCount = adjacentMineCount(row, col);
					if (mineCount == 0) {
						explore(r, c);
					} else if (mineCount > 0) {
						board[r][c].setVisibility();
					}
				}
			}
		}
	}

    /**
     * Lay mines except for current position (row, col) to enhance playability. Number of
     * mines based on difficulty setting.
     * <p>
     * Places exactly numMines mines within the boundaries of the board.
     * Each board space may contain at most 1 mine. In order to enhance playability, the layMines
     * method does not place a mine at the board space specified by (row, col). layMines also computes
     * the number of mines adjacent to each board space. This information is displayed to user when
     * the space is actually revealed/explored. We are only concerned with adjacency counts for spaces
     * that are not mines since mined spaces cannot be explored without losing the game.
     * @param row the current row
     * @param col the current column
     */
	private void layMines(int row, int col) {
		for (int i = 0; i < numMines; i++) {
			int r, c;
			do { 
				r = rdm.nextInt(board.length);
				c = rdm.nextInt(board[0].length);
			} while (r == row && c == col);
			board[r][c].setMined();
		}
        for (int r = 0; r < board.length-1; r++) {
            for (int c = 0; c < board[0].length-1; c++) {
				if (!board[r][c].isMined()) {
					int count = calculateAdjacentMineCount(r, c);
					board[r][c].setAdjacentMineCount(count);
				}
			}
		}
	}


	int calculateAdjacentMineCount(int row, int col) {
		int mineCount = 0;
		for (int r = row-1; r <= row+1; r++) {
			for (int c = col-1; c <= col+1; c++) {
				if (isValidMove(r, c) && isMined(r, c)) {
					mineCount++;
				}
			}
		}
		return mineCount;
	}
	
	int adjacentMineCount(int row, int col)
	{
		return board[row][col].adjacentMineCount();
	}

    /**
     * determines if the board space specified by (row, col) is a
     * valid move for the player to make. The player may only choose board spaces that currently
     * hidden (unexplored) and (row, column) must be within the board's boundaries.
     * @param row the row being checked
     * @param col the col being checked
     * @return true if the move is valid
     */
	private boolean isValidMove(int row, int col) {
         return row > 0 || row < board.length || col < board[0].length;
	}

	int rows() {
		return board.length;
	}
	
	int columns() {
		return board[0].length;
	}

	boolean isUnknown(int row, int col) {
		return !board[row][col].isVisible();
	}

	boolean isCleared(int row, int col) {
		return board[row][col].isVisible();
	}
	
	boolean isFlagged(int row, int col) {
		return board[row][col].isFlagged();
	}
	
	boolean isMined(int row, int col) {
		return board[row][col].isMined();
	}
	
	boolean won() {
		return won;
	}
	
	boolean lost() {
		return lost;
	}

}
