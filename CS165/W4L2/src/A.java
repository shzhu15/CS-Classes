
public class A extends Main{
	protected double x;
	protected double y;

	
	A(double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	public double getX() {
		return this.x;
	}
	
	public double getY() {
		return this.y;
	}
	
	public String toString() {
		return "(" + getX() + ", " + getY() + ")";
	}
	
	public String toString(String message) {
		return message + toString();
	}
	
	public double sum() {
		return this.x + this.y;
	}
	
	public double product() {
		return this.x * this.y;
	}
}
