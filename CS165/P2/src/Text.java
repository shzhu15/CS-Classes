
public class Text extends Primitive {

	private int x;
	private int y;
	private String text;
	private int color;
	private String fontName;
	private int fontSize;
	
	Text(int x, int y, String text) {
		this.x = x;
		this.y = y;
		this.text = text;
	}
	
	public void setColor(int color) {
		this.color = color;
	}
	
	public void setFont(String name, int size) {
		this.fontName = name;
		this.fontSize = size;
	}
	
	public void draw(UserInterface ui) {
		ui.fillColor(color);
		ui.lineColor(color);
		ui.textColor(color);
		ui.setFont(fontName, fontSize);
		ui.drawText(x, y, text);
	}
}
