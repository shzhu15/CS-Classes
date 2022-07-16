
public class Oval extends Primitive  {
	private int x;
	private int y;
	private int width;
	private int height;
	private boolean filled;
	private int color;
	
	public Oval(int x, int y, int width, int height) {
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
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
