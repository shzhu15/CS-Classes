// Hasher.java - code for hashing class
// Author: ?????
// Date:   ?????
// Class:  CS165
// Email:  ?????

@FunctionalInterface
interface HashFunction {
    int hash(String key);
}


public class Hasher {

    // Hashing algorithms, see specification

    /**
     * Hashing algorithms, see provided documentation in assignment
     * @param hashFunction FIRST, SUM, PRIME, OR JAVA
     * @return the corresponding HashFunction
     */
    public static HashFunction make(String hashFunction) {
        switch (hashFunction) {
        case "FIRST":
            // YOUR CODE HERE
        	return new HashFunction() {
				@Override
				public int hash(String key) {
					int r = key.charAt(0);
					r = Math.abs(r);
					return r;
				}
			};
            
        case "SUM":
            // YOUR CODE HERE
            return new HashFunction() {
				@Override
				public int hash(String key) {
					int value = 0;
					for(int i = 0; i < key.length()-1; i++) {
						value += key.charAt(i);
					}
					value = Math.abs(value);
					return value;
				}
			};

        case "PRIME":
            // YOUR CODE HERE
            return new HashFunction() {
				@Override
				public int hash(String key) {
					int value = 7;
					for(int i = 0; i < key.length()-1; i++) {
						value = value * 31 + key.charAt(i);
					}
					value = Math.abs(value);
					return value;
				}
			};

        case "JAVA":
            // YOUR CODE HERE
            return new HashFunction() {
				@Override
				public int hash(String key) {
					int value = key.hashCode();
					value = Math.abs(value);
					return value;
				}
			};

        default:
            usage();
        }
        return null;
    }


    // Usage message
    private static void usage() {
        System.err.println("Usage: java Hasher <FIRST|SUM|PRIME|JAVA> <word>");
        System.exit(1);
    }



    // Test code for hasher
    public static void main(String[] args) {
        args = Debug.init(args);
        if (args.length != 2)
            usage();

        HashFunction sh = make(args[0]);
        int hashCode = sh != null ? sh.hash(args[1]) : 0;
        System.out.printf("'%s' hashes to %d using %s\n", args[1], hashCode, args[0]);
    }
}
