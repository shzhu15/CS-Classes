
public class B extends A{

	B(double x, double y) {
		super(x, y);
		System.out.println( "Constructor: B");
		
	}
	
	public double power() {
		return Math.pow(x, y);
	}
	
	
	
	
	
	
	
}
