/**
 * Created by garethhalladay on 8/27/17
 */
public class Rating {
	
	private int cScore;
	private int cNum;
	private int aScore;
	private int aNum;

	public Rating() {
		
	}
	
	public Rating(int criticScore, int numCritics, int audienceScore, int numAudience) {
		this.cScore = criticScore;
		this.cNum = numCritics;
		this.aScore = audienceScore;
		this.aNum = numAudience;
	}
	
	public int getAudienceScore() {
		return aScore;
	}
	
	public int getNumAudience() {
		return aNum;
	}
	
	public int getCriticScore() {
		return cScore;
	}
	
	public int getNumCritics() {
		return cNum;
	}
	
	public String toString() {
		return "Critics Score: " + getCriticScore() + " Critic Count: " + getNumCritics() +
				" Audience Score: " + getAudienceScore() + " Audience Count: " + getNumAudience();
	}
	
		
    public static void main(String [] args){
    	System.out.println("The Rating class:");
    	Rating noargs = new Rating();
    	Rating rating1 = new Rating(30, 10, 45, 100);
    	System.out.printf("Critic Score: %d\nNumber of Critics: %d\nAudience Score: %d\nNumber of people: %d\n",
    	                   rating1.getCriticScore(), rating1.getNumCritics(), rating1.getAudienceScore(), rating1.getNumCritics());
    	System.out.println(noargs);
    	System.out.println(rating1);

    }
}
