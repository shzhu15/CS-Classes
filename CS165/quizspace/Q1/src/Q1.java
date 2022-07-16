import java.util.Scanner;

public class Q1 {

	public static void main(String[] args) {
		String testString;
		
		Scanner input = new Scanner(System.in);
		
		System.out.print("Enter a String: ");
			testString = input.nextLine();
		System.out.println(testString);
		System.out.println(testString.length());
		System.out.println(testString.indexOf('a'));
		System.out.println(testString.charAt(2));
		System.out.println(testString.toUpperCase());
		
		input.close();
	}

}
