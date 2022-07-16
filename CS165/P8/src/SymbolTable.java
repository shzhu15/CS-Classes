import java.io.ObjectInputStream.GetField;
import java.util.*;

import javax.management.RuntimeErrorException;

/**
 * Created by garethhalladay on 10/23/17
 */
public class SymbolTable {
    // Why use a TreeSet? Why not just an ArrayList or a LinkedList?
    private static final Set<String> keywords =
            new TreeSet<>(Arrays.asList("abstract", "assert", "boolean", "break", "byte",
                                        "case", "catch", "char", "class", "const", "continue",
                                        "default", "do", "double", "else", "extends", "false",
                                        "final", "finally", "float", "for", "goto", "if",
                                        "implements", "import", "instanceof", "int", "interface",
                                        "long", "native", "new", "null", "package", "private",
                                        "protected", "public", "return", "short", "static",
                                        "strictfp", "super", "switch", "synchronized", "this",
                                        "throw", "throws", "transient", "true", "try", "void",
                                        "volatile", "while"));

    /**
     * A class representing
     */
    class Symbol {
        String name;
        Integer value;
        Symbol left;
        Symbol right;

        Symbol(String k, Integer v){
            this.name = k;
            this.value = v;
        }

        public String toString(){
            return String.format("[%s, %d]", name, value);
        }
    }

    private Symbol root;
    private int size;

    public SymbolTable(){
        root = null;
        size = 0;
    }

    public int getSize(){
        return size;
    }

    /**
     * Identifies whether or not the variable is a legal Java identifier.
     * <p>
     * Read section 3.8 from the following resource to learn how to identify legal Java identifiers:
     * <a href=https://docs.oracle.com/javase/specs/jls/se9/html/jls-3.html>Lexical Structure</a>
     * <p>
     * This includes checking to make sure the identifier is not a keyword, boolean literal, or null
     * literal.
     * @param k the variable name
     * @return true if variable is a legal Java identifier.
     * @see Character#isJavaIdentifierStart(char)
     * @see Character#isJavaIdentifierPart(char) 
     */
    static boolean isValidJavaIdentifier(String k){
        //YOUR CODE HERE
		if(keywords.equals(k) == true) {
			return false;
		}
    	if(Character.isJavaIdentifierStart(k.charAt(0)) == false) {
    		return false;
    	}
    	for(int i = 0; i < k.length(); i++) {
    		if(Character.isJavaIdentifierPart(i) == false) {
    			return false;
    		}
    	}
        return true;
    }

    /**
     * If the variable is a legal Java identifier,
     * add the symbol and it's corresponding value into the SymbolTree.
     * <p>
     * Here is the algorithm to add the symbol to the SymbolTree:
     * <ol>
     *     <li> If the root is null, create a new Symbol and assign it to the root.
     *     <li> If the root is not null, create a temporary variable, current, and assign it to the root value.
     *     <li> If k is larger than the current node, check the right child, otherwise check the left child
     *     <li> While the child is not null:
     *     <ul>
     *         <li> If k is larger then current, assign current to its right child.
     *         <li> else assign current to its left child.
     *     </ul>
     *     <li> create a new Symbol and assign it the correct child.
     * </ol>
     * @param k the symbol name
     * @param v the value to be associated with the symbol
     * @throws RuntimeException if k is not a valid Java identifier
     *                          use the following message: {@code String.format("\"%s\" is not a valid Java identifier", k)}
     */
    public void put(String k, Integer v){
        // YOUR CODE HERE
    	if(isValidJavaIdentifier(k) == false) {
    		//System.out.printf("\"%s\" is not a valid Java identifier", k);
    		throw new RuntimeException("\"" + k + "\"" + " is not a valid Java identifier");
    	}
    	if(root == null) {
    		root = new Symbol(k, v);
    	}
    	else {
    		Symbol current = root;
    		Symbol parent = null;
    		while(current != null) {
    			if(k.compareTo(current.name) < 0) {
    				parent = current;
    				current = current.left;
    			}
    			else if(k.compareTo(current.name) > 0) {
    				parent = current;
    				current = current.right;
    			}
    			else {
    				current.value = v;
    				return;
    			}
    		}
			if(k.compareTo(parent.name) < 0) {
				parent.left = new Symbol(k, v);
				size++;
			}
			else {
				parent.right = new Symbol(k, v);
				size++;
			}
    	}
    }



    /**
     * Return the Integer associated with the variable name, k. <br>
     * If the key is not a legal Java identifier, throw a RuntimeException with the message below. <br>
     * If the key is not in the tree throw a RumTimeException with the message below.
     * @param k the variable name
     * @return the value associated with the variable
     * @throws RuntimeException if k is not a legal Java identifier, use the following message:
     *                          {@code String.format("\"%s\" is not a valid Java identifier", k)}
     * @throws RuntimeException if the variable does not exist, use the following message
     *                          {@code String.format("\"%s\" does not exist", k)}
     */
    public Integer get(String k){
        // YOUR CODE HERE
    	if(isValidJavaIdentifier(k) == false) {
    		//System.out.printf("\"%s\" is not a valid Java identifier\n", k);
    		throw new RuntimeException("\"" + k + "\"" + " is not a valid Java identifier");
    	}
    	Symbol current = root;
    	while(current != null) {
			if(k.compareTo(current.name) < 0) {
    			current = current.left;
    		}
			else if(k.compareTo(current.name) > 0) {
				current = current.right;
			}
			else {
				return current.value;
			}
    	}
		//System.out.printf("\"%s\" does not exist\n", k);
		throw new RuntimeException("\"" + k + "\"" + " does not exist");
       // return -1;
    }

    public List<Symbol> inorder() {
        return inorderRecursive(root, new ArrayList<Symbol>());
    }


    /**
     * Similar to the infixRecursive method you implemented in the previous assignment.
     * For expressions this concept is identified as infix notation. The same concept for trees
     * is identified as an inorder traversal.
     * <p>
     * Instead of creating a String, add the Symbol to the ArrayList.
     * <ol>
     *     <li> Add the Symbol from the left subtree
     *     <li> Add the root Symbol
     *     <li> Add the Symbol from the right subtree
     * </ol>
     * <p>
     * @param current the current Symbol
     * @param infix the ArrayList
     * @return an ArrayList with Symbols in inorder traversal
     */
    public static List<Symbol> inorderRecursive(Symbol current, List<Symbol> infix) {
    	if(current == null) {
    		return infix;
    	}
    	inorderRecursive(current.left, infix);
    	infix.add(current);
    	inorderRecursive(current.right, infix);
        return infix;
    }



    public static void main(String[] args) {
        SymbolTable st = new SymbolTable();
        st.put("e", 18);
        st.put("a", 43);
        st.put("d", 3);
        st.put("b", 3);
        st.put("z", 17);
        st.put("y", 4);
        System.out.println(st.inorder());
        st.put("x", 5);
        st.put("k", 2);
        st.put("y", 21);
        st.put("e", 20);
        st.put("^", 4);
        System.out.println(st.inorder());
        System.out.println("a: " + st.get("a"));
        System.out.println("e: " + st.get("e"));
        System.out.println("y: " + st.get("y"));
        System.out.println("z: " + st.get("z"));
        System.out.println("d: " + st.get("d"));

    }

}
