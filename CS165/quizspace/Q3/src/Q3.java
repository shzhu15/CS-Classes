// Q3 Assignment
// Author: Sharon Zhu
// Date:   April 3, 2017
// Class:  CS163
// Email:  Your Email

public class Q3 {

	/*
	 * Method: fillArray
	 */
	public char[] fillArray(String var){
		char[] words = new char[var.length()];
		for(int i = 0; i < var.length(); i++) {
			words[i] = var.charAt(i);
		}
		return words;
	}

	/*
	 * Method: stringArray
	 */
	public String stringArray(char[] chArray) {
		String s0 = "";	
		if(chArray.length == 0)
			return s0;
		if(chArray == null)
			return s0;
		for(int i = 0; i < chArray.length; i++) {
			s0 += chArray[i];
		}
		return s0;
	}

	/*
	 * Method: productMatrix
	 */
	public int[][] productMatrix(int n){
		int[][] table = new int[n][n];
		if(0 < n && n <= 100) {
			for(int i = 0; i < n; i++){
				for(int j = 0; j < n; j++){
					table[i][j] = i * j;
				}
			}
		}
		else
			return null;
		return table;
	}

	/*
	 * Method: sumOfSquares
	 */
	public long sumOfSquares (int[] intArray) {
		long sum = 0;
		if(intArray.length == 0)
			return 0;
		if(intArray == null)
			return 0;
		if(intArray.length < 0) {
			for(int i = 0; i < intArray.length; i++) {
				sum += intArray[i] * intArray[i];
			}	
		}
		return sum;
	}

	/*
	 * Method: incPosArray
	 */
	public void incPosArray (int[] intArray) {
		if(intArray.length == 0)
			return;
		if(intArray == null)
			return;
		if(intArray.length < 0) {
			for(int i = 0; i < intArray.length; i++) {
				if(intArray[i] > 0) {
					intArray[i] = intArray[i] + 1;
				}
			}
		}
		
		return;
	}


	public static void main (String[] args) {
		Q3 q3 = new Q3();
		int[] i0 = {1,2,3,4,5,6,-6,-7,0};
		//Put your test code here
		System.out.println(q3.fillArray("Well Done!"));
		System.out.println(q3.stringArray(q3.fillArray("Done!")));
		System.out.println(q3.productMatrix(5));
		q3.incPosArray(i0);
		System.out.println();
		
	}
}