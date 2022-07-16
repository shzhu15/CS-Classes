import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * Created by garethhalladay on 8/24/17
 */
public class MovieLibrary {
	List<Movie> movies;
	List<Movie> moviesR;
	public MovieLibrary() {
		
	}
	
	public void addMovie(Movie movie) {
		movies.add(movie);
	}
	
	public List<Movie> getMovies() {
		return movies;
	}
	
	public List<Movie> getMoviesByRating(int lowestRating, int highestRating, boolean criticsOrAudience) {
		
		if(criticsOrAudience = true) {
			for(int i = 0; i < movies.size(); i++) {
				if(movies.get(i).getRating().getCriticScore() >= lowestRating || movies.get(i).getRating().getCriticScore() <= highestRating)
					moviesR.add(movies.get(i));
			}
		}
		else {
			for(int i = 0; i < movies.size(); i++) {
				if(movies.get(i).getRating().getAudienceScore() >= lowestRating || movies.get(i).getRating().getAudienceScore()  <= highestRating)
					moviesR.add(movies.get(i));
			}
		}
		return moviesR;
	}
	
	public List<Movie> getMoviesByRating(int lowestRating, boolean criticsOrAudience) {
		if(criticsOrAudience = true) {
			for(int i = 0; i < movies.size(); i++) {
				if(movies.get(i).getRating().getCriticScore() >= lowestRating)
					moviesR.add(movies.get(i));
			}
		}
		else {
			for(int i = 0; i < movies.size(); i++) {
				if(movies.get(i).getRating().getAudienceScore() >= lowestRating)
					moviesR.add(movies.get(i));
			}
		}
		return moviesR;
	}
	
	public static String getDescriptions(List<Movie> movies) {
		String print = "";
		for(int i = 0; i < movies.size(); i++) {
			print += movies.get(i).getTitle() + "/n" + movies.get(i).getGenres() + "/n" + 
					formatKeyWords(movies.get(i).getKeyWords());
		}
		return print;
	}
	
	public static String formatMovies(List<Movie> movies) {
		return movies.toString();
	}
	
	
	
	
    /**
     * A Helper method to format KeyWords, 5 per line.
     * @param keywords a list of keywords describing a movie
     * @return A formatted String with 5 keywords per line.
     */
    public static String formatKeyWords(List<KeyWord> keywords){
        if(Objects.isNull(keywords))
            return "";
        String result = keywords.get(0).toString() + ((keywords.size() == 1) ?  "\n" : ", ");

        int count = 1;
        for(KeyWord k : keywords.subList(1,keywords.size())){
            if (count % 5 == 0 || count == keywords.size()-1){
                result += k.toString() + "\n";
            }
            else{
                result += k.toString() + ", ";
            }
            count++;
        }
        return result;
    }

    public static void main(String [] args) throws FileNotFoundException {
    	FileParser fileParser = new FileParser();
    	System.out.println(args[0]);
    	MovieLibrary movieLibrary = fileParser.getAllMovies(args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
    
    	System.out.println("The MovieLibrary class:");
    	// 1. How many movies are there in total?
    		System.out.println("65133");
    	// 2. How many movies did the audience rate 95% or above?

    	// 3. How many movies did the critics rate 0% to 5%?

    	// 4. Some movies don't have KeyWords. Explain how you could change
    	//   the getDescription method to only print movies that have keywords.
    		System.out.println("check if there is keywords for the movie and print those that have words");
    	// 5. How would you sort the KeyWords by frequency? What class/classes would you modify?
    	// How would you deal with keywords that have the same frequency?
    		System.out.println("sort by low to high, modifying movielibrary, print both");
    	
    }
}
