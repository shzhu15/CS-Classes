
public class Circle extends Primitive {
	
	private int x;
	private int y;
	private int width;
	private int height;
	private boolean filled;
	private int color;
	
	public Circle(int x, int y, int radius) {
		this.x = x;
		this.y = y;
		this.width = radius;
		this.height = radius;
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
		ui.drawOval(x, y, width, height, filled);
	}
}
