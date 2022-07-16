package main;
import main.BoardModel.Difficulty;

import org.junit.Test;
import static org.junit.Assert.*;

public class TestBoardModel {
	
	BoardModel board;
	int seed = 1024;
	
	private void setup() {
		try{
			board = new BoardModel(Difficulty.BEGINNER, seed);
		} catch (Exception e) {
			fail("BoardModel failed to create");
		}
	}
	
	@Test
	public void testInstanceCreation() {
		setup();
	}

	@Test
	public void testRevealBounds() {
		setup();
		assertFalse("Cannot reveal a space with a negitive row", board.reveal(-1, 0));
		assertFalse("Cannot reveal a space with a negitive column", board.reveal(0, -1));
		assertFalse("Cannot reveal a space with a row greater then the maximum rows", board.reveal(board.rows()+1, 0));
		assertFalse("Cannot reveal a space with a column greater then the maximum columns", board.reveal(0, board.columns()));
		assertTrue("Should be able to reveal a valid space", board.reveal(0, 0));
		assertFalse("Cannot do a outbounds moves", board.reveal(-1, 0));
		assetFalse("Cannot reveal a space outbounds", board.reveal(-1, 0));

	}
	public void testMines() {
		setup();
		assertNull("Cannot reveal a space with a null mines", board.isMined(3, 3));	
		assertTrue("number of mines should be equal", board.flagsRemaining());
	}
	public void testFlags() {
		setup();
		assetFalse("should there be flag there?", board.flag(3, 3));
	}
}
