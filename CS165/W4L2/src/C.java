
public class C extends B{

	double z;
	
	C(double x, double y, double z) {
		super(x, y);
		this.z = z;
	}
	
	public double product() {
		double result = super.product();
		result = result * z;
		return result;
	}
	
	public double power() {
		double result = super.power();
		result = Math.pow(z, result);
		return result;
	}
	
	public String toString() {
		return "(" + super.getX() + ", " + super.getY() + ", " + this.z + ")";
	}
	
}
