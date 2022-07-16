import java.util.*;
import java.util.stream.Collectors;

/**
 * Created by garethhalladay on 8/24/17.
 */
public class Movie {

	private final String title;
	private final int year;
	private final List<String> actors;
	private List<String> genres;
	private Rating rate;
	private List<KeyWord> word;

	
	Movie(String title, int year, List<String> actors) {
		this.title = title;
		this.year = year;
		this.actors = actors;
	}
	
	Movie(String title, int year, List<String> actors, List<String> genres, Rating rating, List<KeyWord> keywords) {
		this.title = title;
		this.year = year;
		this.actors = actors;
		this.genres = genres;
		this.rate = rating;
		this.word = keywords;
	}
	
	public String getTitle() {
		return title;
	}
	
	public int getYear() {
		return year;
	}
	
	public List<String> getActors() {
		return actors;
	}
	
	public List<String> getGenres() {
		return genres;
	}
	
	public Rating getRating() {
		return rate;
	}
	
	public List<KeyWord> getKeyWords() {
		return word;
	}
	
	
    /**
     * Helper method to compare lists. Ignores order and case.
     * @param one first list
     * @param two second list
     * @return true if the two lists are equal
     */
    public static boolean equalsIgnoresOrder(List<String> one, List<String> two){
        if (one == null && two == null){
            return true;
        }
        if(one == null || two == null || one.size() != two.size()){
            return false;
        }

        // Collections.sort will mutate the original lists so if order matters,
        // we need to create new temporary lists. We can do this at the same time as
        // converting to lower case because streams are monads (shout out to Haskell!)
        // and monads are magical things. But you can know that these
        // functions will not mutate the original lists.
        one = one.stream().map(String::toLowerCase).sorted().collect(Collectors.toList());
        two = two.stream().map(String::toLowerCase).sorted().collect(Collectors.toList());
        return one.equals(two);
    }
    
    public String toString() {
    	return "Title: " + getTitle() + " Year: " + getYear() + " Actors: " + formatActors(actors);
    }
    
    public boolean equals(Object o) {
    	if(o == this)
    		return true;
    	if(!(o instanceof Movie))
    			return false;
    	Movie check = (Movie) o;
    	return check.getTitle().equals(this.title) && check.getYear() == this.year && 
    			equalsIgnoresOrder(check.getActors(), this.actors);
    	

    }
    
    
    
    

    /**
     * Helper method to format actors, 5 per line.
     * @param actors
     * @return a String of actors
     */
    private static String formatActors(List<String> actors){
        String result = String.format("%s\n", String.join(", ", actors.subList(0, 5 < actors.size() ? 5 : actors.size() )));
        for(int i = 5; i < actors.size(); i+=5){
            int end = (i+5 < actors.size()) ? i+5 : actors.size();
            result += String.format("%5s\n" ,String.join(", ", actors.subList(i, end)));
        }
        return result;
    }

    /**
     * When you override the equals method, you should override the hashCode.
     * If two objects are equal (as per equals method) then their hashcode (integer value) MUST be the equal.
     */
    @Override
    public int hashCode(){
        return getTitle().hashCode() +
               getYear() +
               this.getActors().stream().map(String::toLowerCase).sorted().collect(Collectors.toList()).hashCode();
    }

    public static void main(String [] args){
    	Movie movie1 = new Movie("Spirited Away", 2001,
                Arrays.asList("Rumi Hiiragi", "Miyu Irino", "Mari Natsuki",
                              "Takashi Naito", "Yasuko Sawaguchi", "Tatsuya Gashuin"));
Movie movie2 = new Movie("Spirited Away", 2001,
                Arrays.asList("Rumi Hiiragi", "Miyu Irino", "Yasuko Sawaguchi",
                              "Takashi Naito", "Mari Natsuki", "Tatsuya Gashuin"),
                Arrays.asList("Animation", "Adventure", "Family"),
                new Rating(97, 180, 96, 334759),
                Arrays.asList(new KeyWord("spirit", 5),
                              new KeyWord("f rated", 20),
                              new KeyWord("female protagonist", 32),
                              new KeyWord("surprise ending", 10)) );

Movie movie3 = new Movie("Coco", 2017,
                Arrays.asList("Alanna Ubach", "Benjamin Bratt", "Edward James Olmos",
                              "Gael Garcia Bernal", "Cheech Marin", "Gabriel Iglesias"),
                Arrays.asList("Animation", "Adventure", "Comedy"),
                new Rating(),
                Arrays.asList(new KeyWord("afterlifet", 1),
                              new KeyWord("disney", 1)));


System.out.printf("Testing the Getters:\n" +
                 "movie2.getTitle() %s\n" +
                 "movie2.getYear() %d\n" +
                 "movie2.getActors() %s\n" +
                 "movie2.getGenres() %s\n" +
                 "movie2.getRating() %s\n" +
                 "movie2.getKeyWords() %s\n",
         movie2.getTitle(), movie2.getYear(), movie2.getActors(),
         movie2.getGenres(), movie2.getRating(), movie2.getKeyWords());
System.out.println("\nTesting the toString method:\n" + movie1);
System.out.printf("movie1 and movie2 should be equal (true) -> %b\n", movie1.equals(movie2));
System.out.printf("movie1 and movie3 should be not be equal (false) -> %b\n\n", movie1.equals(movie3));

System.out.println("hashCode should always be changed along with the equals method.");
System.out.println(movie1.hashCode());
System.out.println(movie2.hashCode());
System.out.println(movie3.hashCode() + "\n");

try {
movie2.actors.add("Yumi Tamai");
System.err.println("FAILURE. Check to make sure that actors is an unmodifiable list.");
}catch(UnsupportedOperationException e){
System.out.println("SUCCESS. Used an unmodifiable list for actors.");
}

    }
}
