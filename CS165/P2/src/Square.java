
public class Square extends Primitive {

	private int x;
	private int y;
	private int height;
	private int width;
	private boolean filled;
	private int color;
	
	public Square(int x, int y, int size) {
		this.x = x;
		this.y = y;
		this.height = size;
		this.width = size;
		
	}
	
	public void setColor(int color) {
		this.color = color;
	}
	
	public void setFilled(boolean isFilled) {
		this.filled = isFilled;
	}
	
	public void draw(UserInterface ui) {
		ui.fillColor(color);
		ui.lineColor(color);
		ui.textColor(color);
		ui.drawRectangle(x, y, width, height, filled);
			

	}

}
