/**
 * Created by garethhalladay 08/2017 for a recitation in CS165 at Colorado State University to increase
 * the understanding of Objects and OO concepts in Java. <br> <br>
 *
 * The KeyWord class consists of a word that describes a movie and the frequency of that word.
 * At this point, the class just accepts data parsed from a file but could be extended to increment the count of
 * frequency if the user wanted to collect new data.
 */
public class KeyWord {
	private String word;
	private int freq;
	
	KeyWord(String label, int frequency) {
		this.word = label;
		this.freq = frequency;
	}
	
	public String getLabel() {
		return word;
	}
	
	public int getFrequency() {
		return freq;
	}
	
	public String toString() {
		return word;
	}
	
    public static void main(String[] args){
    	System.out.println("The KeyWord class:");
    	KeyWord one = new KeyWord("magical", 20);
    	KeyWord two = new KeyWord("waste of time", 3);

    	System.out.printf("label: %s, frequency: %d\n", one.getLabel(), two.getFrequency());
    	System.out.println(one);
    	System.out.println(two);

    }
}
