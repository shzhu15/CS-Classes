
public class Rectangle extends Primitive {
	private int x;
	private int y;
	private int height;
	private int width;
	private boolean filled;
	private int color;
	
	public Rectangle(int x, int y, int width, int height) {
		this.x = x;
		this.y = y;
		this.height = height;
		this.width = width;
		
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
