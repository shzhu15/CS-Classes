
public class Triangle extends Primitive {
	
	private int[] x = new int[3];
	private int[] y = new int [3];
	private int color;
	private boolean isFilled;
	
	Triangle(int x0, int y0, int x1, int y1, int x2, int y2) {
		this.x[0] = x0;
		this.x[1] = x1;
		this.x[2] = x2;
		this.y[0] = y0;
		this.y[1] = y1;
		this.y[2] = y2;
	}
	
	public void setColor(int color) {
		this.color = color;
	}
	
	public void setFilled(boolean isFilled) {
		this.isFilled = isFilled;
	}
	
	public void draw(UserInterface ui) {
		ui.fillColor(color);
		ui.lineColor(color);
		ui.textColor(color);
		ui.drawPolygon(x, y, isFilled);
	}
	
}
