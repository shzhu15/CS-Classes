import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

//Q4B Assignment
//Author: Sharon Zhu
//Date:   Apr 19, 2017
//Class:  CS163
//Email:  shzhu@rams.colostate.edu

public class Q4B implements IQ4B {


	@Override
	public String addStars(ArrayList<Character> str) {
		return addStars(str, 0, "");
	}

	public String addStars(ArrayList<Character> s, int size, String output) {
		if(size >  s.size())
			return output;
		if(s.isEmpty())
			return output;
		output += s.get(0) +"*";
		s.remove(0);
		return addStars(s, size + 1, output);
	}
	
	@Override
	public int[] readFile(String fileName) {
	
		try {
			File input = new File(filename);
			Scanner scan = new Scanner(input);
			
			String temp = "";
			int row = scan.nextInt();
			int column = scan.nextInt();
			scan.nextLine();
			int[] field = new int[column];

			for (int i = 0; i < row; i++) {
				if(scan.hasNextLine())
					temp = scan.nextLine();
				for (int j = 0; j < column; j++) {
					field[j] = temp.charAt(j);
					}										
			}
			scan.close();
			return field;

			} catch (IOException e) {
				System.out.println("Error: cannot read input file");
			}
			
		return null;
		}

	

	public static void main(String[] args) {
		Q4B test = new Q4B();
		ArrayList<Character> str = new ArrayList();
		str.add('a');
		str.add('b');
		str.add('c');
		System.out.println(test.addStars(str));
		System.out.println(test.readFile("data.txt"));
	}

}
