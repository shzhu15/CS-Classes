package main;

public class BoardSpace {

	private boolean visible;
	private boolean mined;
	private boolean flagged;
	private int adjacentMines;
	
	
	public BoardSpace() {
		visible = true;
	}
	
	public void reset() {
		visible = false;
		mined = false;
		flagged = false;
		adjacentMines = -1;
	}
	
	boolean isVisible() {
		return visible;
	}
	
	void setVisibility() {
		visible = true;
	}
	
	boolean isMined() {
		return mined;
	}
	
	void setMined() {
		mined = true;
	}
	
	int adjacentMineCount() {
		return adjacentMines;
	}
	
	void setAdjacentMineCount(int count) {
		adjacentMines = count;
	}
	
	boolean isFlagged() {
		return flagged;
	}
	
	void setFlagged(boolean flagged) {
		this.flagged = flagged;
	}
}
