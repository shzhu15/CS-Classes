
public class Main{

	  public static void main(String[] args) {
	// Instantiate and test A
	A a = new A(2.0, 4.0);
	System.out.printf("x: %.1f, y: %.1f\n", a.getX(), a.getY());
	System.out.printf("a: %s\n", a);
	System.out.println(a.toString("A class: "));
	System.out.printf("a.sum: %.1f\n", a.sum());
	System.out.printf("a.product: %.1f\n", a.product());
	//System.out.println("a.power: " + a.power());
	System.out.println("\n");
	
	// Instantiate and test B
	B b = new B(3.0, 5.0);
	System.out.printf("b: %s\n", b);
	System.out.println(b.toString("B class: "));
	System.out.printf("b.sum: %.1f\n", b.sum());
	System.out.printf("b.product: %.1f\n", b.product());
	System.out.printf("b.power: %.1f\n", b.power());
	System.out.println("\n");

	/* Why does the super class constructor have to come before any other code?
	 *	so the compile knows where to look
	*/

	/* x and y were declared in class A. Why can you use x and y for the power method in class B?
	 * cause B is a subclass of A
	*/

	/* What changes in the code would cause B to not have the member variables x and y?
	 * delete the extends A part
	*/

	/* What happens when you uncomment the call to a.power?
	 *a error since there is no a.power
	 *
	 * Why can't you call the power method using an instance of class A?
	 * cause the call is in B
	*/
	
	// Instantiate and test C
	C c = new C(2.0, 3.0, 4.0);
	System.out.println("c: " + c);
	System.out.println(c.toString("C class: "));
	System.out.println("c.sum: " + c.sum());
	System.out.println("c.product: " + c.product());
	System.out.println("c.power: " + c.power());
	System.out.println("\n");
	
	/* When the code calls the overloaded toString(String) on the C instance,
	 * in which classes does it run code? HINT: use the debugger with "step into"
	 * to observe what classes are called. Be specific.
	 *B, A
	 * When the code calls the  original toString() on the C instance,
	 * in which classes does it run code?
	 *C
	 * How does Java determine which version of a method to use in an inheritance hierarchy?
	 *	it will use the subclass and then the superclass if called
	 */
	
	
	
	  }
}
