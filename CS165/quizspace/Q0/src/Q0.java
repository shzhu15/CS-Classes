import java.util.Scanner;

//Name: Sharon Zhu
//Assignment: Q0
//Date: 2/1/2017

public class Q0 {

	public static void main(String[] args) {
		double assign0, assign1, assign2, assign3, assignAverage;
		
		Scanner input = new Scanner (System.in);
		
		System.out.print("First assignment: ");
		assign0 = input.nextDouble();
		System.out.print("Second assignment: ");
		assign1 = input.nextDouble();
		System.out.print("Third assignment: ");
		assign2 = input.nextDouble();
		System.out.print("Fourth assignment: ");
		assign3 = input.nextDouble();
		
		assignAverage = (assign0 + assign1 + assign2 + assign3) / 4;
		
		System.out.printf("Assignment average: %.2f\n", assignAverage);
		
		input.close();
		
	}

}
