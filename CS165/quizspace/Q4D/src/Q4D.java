import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

//Q4D Assignment
//Author: Sharon Zhu
//Date:   Apr 28, 2017
//Class:  CS163
//Email:  shzhu@rams.colostate.edu

public class Q4D implements IQ4D {

	@Override
	public int sumOfCubes(ArrayList<Integer> num) {
		return sumOfCubes(num, 0);
	}

	public int sumOfCubes(ArrayList<Integer> num, int count) {
		if(count <  num.size()) {
			num.add(count, (num.get(count) * num.get(count) * num.get(count)));
			return sumOfCubes(num, count + 2);
		}
		return 0;
	}

	
	@Override
	public double[] readFile(String fileName) {
		try {
			File input = new File(fileName);
			Scanner scan = new Scanner(input);
			int line = 0;

			double[] field = new double[6];

			for(int i = 0; i < 6; i++) {
				if(scan.hasNext())
					field[i] = scan.nextDouble();
			}
			scan.close();
			return field;

			} catch (IOException e) {
				System.out.println("Error: cannot read input file");
			}
			
		return null;
		}
	
	public static void main(String[] args) {
		Q4D test = new Q4D();
		ArrayList<Integer> num = new ArrayList();
		num.add(1);
		num.add(2);
		num.add(3);
		
		System.out.println(test.sumOfCubes(num));
		double[] d = test.readFile("input.txt");
		System.out.println(d.toString());
	
	}
}
