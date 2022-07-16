// Parser.java - supplied code for expression parser
// Author: ?????
// Date:   ?????
// Class:  CS165
// Email:  ?????

import java.util.*;
import java.util.stream.Collectors;

/**
 * The Lexer has several different versions of a parsing method for expressions.
 * <p>
 * The first method is called {@code scannerLexer}, and is based on using a {@link Scanner}. <br>
 * The second method is called {@code splitLexer}, which uses {@link String#split(String)}. <br>
 * The third method is call {@code tokenizerLexer} and is based on an object called {@link StringTokenizer}. <br>
 * <p>
 * created by Chris Wilcox Spring17 <br>
 * modified by {@code rbecwar} and {@code garethhalladay} Fall17
 */
public class Lexer {

    /**
     * Lex a String using an instance of Scanner.
     * <p>
     * Initialize a {@code Scanner} object with a {@code String} argument containing the expression.
     * Using the {@link Scanner#hasNext()} and {@link Scanner#next()} methods:
     * <ol>
     *     <li> Parse the {@code String} (using whitespace as your delimiter)
     *     <li> Add each element to the {@code ArrayList}
     * </ol>
     * <p>
     * After implementing this approach, examine the results.
     * <p>
     * This approach seems to have trouble unless there is white space between every token.
     * Is this fixable or is the Scanner approach not a good idea?
     * @param expr a String in the form of an expression
     * @return a list of tokens
     */
    public static List<String> scannerLexer(String expr) {
        // Allocate list
        ArrayList<String> tokens = new ArrayList<>();
        // YOUR CODE HERE
        Scanner scan = new Scanner(expr);
        while(scan.hasNext()) {
        	tokens.add(scan.next());
        }
        scan.close();
        return tokens;
    }

    //

    /**
     * Parse a String using {@link String#split(String)}.
     * <p>
     * Invoke the {@code String.split(String)} method on the String containing the expression.
     * Remember that split returns an array of strings that you must iterate.
     * Note that the method takes a regular expression, which we have not studied yet. As an introduction,
     * you should check out the provided links and try to understand what the following expressions are
     * matching.
     * <p>
     * Try the regular expression {@code "[-+*()/]"} to see what happens. <br>
     * It seems to match everything, but it removes the operators and parentheses. <br>
     * Is the {@code String.split(String)} approach fixable?
     * <p>
     * Hint: Try this regular expression: {@code "(?<=[-+*()/])|(?=[-+*()/])"}.
     *       What is this doing and why does it work?
     *
     * Use the {@link String#trim()} method to remove whitespace in each token.
     * 
     * @param expr a string in the form of an expression
     * @return a list of tokens
     * @see String#split(String)
     */
    public static List<String> splitLexer(String expr) {
        // Allocate list
        List<String> tokens = new ArrayList<>();
        // YOUR CODE HERE
        String[] temp = new String[20];
        temp = expr.split("(?<=[-+*()/])|(?=[-+*()/])");
        
        for(int i = 0; i < temp.length; i++) {
        	tokens.add(temp[i].trim());
        }

        return tokens;
    }

    /**
     * Lexer method (StringTokenizer)
     * <p>
     * Using a {@code StringTokenizer}.
     * The tokenizer has methods named {@link StringTokenizer#hasMoreTokens()} and
     * {@link StringTokenizer#nextToken()}, which operate in the similar fashion to
     * the associated methods in iterators and Scanners.
     * <p>
     * Create the tokenizer with the String containing the expression, and
     * the characters you want as delimiters, in a string. Is there a way
     * to make StringTokenizer keep the delimiters as tokens instead of discarding them?
     *
     * Use the {@link String#trim()} method to remove whitespace in each token.
     *
     * @param expr a string in the form of an expression
     * @return a list of tokens
     * @see StringTokenizer
     */
    public static List<String> tokenizerLex(String expr) {
        // Allocate list
        List<String> tokens = new ArrayList<>();
        // YOUR CODE HERE
        StringTokenizer temp = new StringTokenizer(expr, "-+*()/", true);
        while(temp.hasMoreTokens()) {
        	tokens.add(temp.nextToken().trim());
        }
        
       
        

        return tokens;
    }

    /*
    Answer the following questions about the regular expression below to complete the recitation:
    (?<=[-+*()/])|(?=[-+*()/])
		Look immediately ahead for this group of operators or look immediately behind for this group of operators to match
    1) What do the characters "[" "]" represent?
	 	They represent groups that we use to match strings/expressions.
    2) What roles do lookbehind (?<=...) and lookahead (?=...) play in this expression?
		They look to the left or right of the string for the characters in the group from the expression.
    3) Why does the expression using lookahead and lookbehind keep the
       operators in its output, while the expression "[-+*()/]" discards them?
		Because the lookahead expression looks for the operators to use as delim, while the other expression uses operators as the delim.
    */
}
