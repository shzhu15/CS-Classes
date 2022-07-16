import java.nio.charset.MalformedInputException;
import java.util.*;

/**
 *
 */
public class ExpressionTree extends ATree {

    public Queue<String> parse(String expression) {
        Queue<String> infix = new LinkedList<>();
        // YOUR CODE HERE
        StringTokenizer temp = new StringTokenizer(expression, "-+*()/%", true);
        while(temp.hasMoreTokens()) {
        	String trimed = temp.nextToken().trim();
        	if(!trimed.isEmpty()) {
        		//System.out.println(trimed);
        		infix.add(trimed);
        	}

        }
        //System.out.println(infix.toString());
        return infix;
    }

    public List<String> convert(Queue<String> infix) {
        List<String> postfix = new ArrayList<>();
        Deque<String> operators = new ArrayDeque<>(); // used as a stack
        // YOUR CODE HERE
        while(!infix.isEmpty()) {
        	if(ATree.isInteger(infix.peek()) == true) {
        		postfix.add(infix.poll());
        	}
        	else if(ATree.isOperator(infix.peek()) == true) {
        		while(!operators.isEmpty() && ATree.precedence(operators.peek()) <= ATree.precedence(infix.peek())) {
        			if(operators.peek().equals("(")) {
        				break;	
        			}
        			postfix.add(operators.pop());
        		}
        		operators.push(infix.poll());
        	}
        	else if(infix.peek().equals("(")) {
        		operators.push(infix.poll());
        	}
        	else if(infix.peek().equals(")")) {
        		infix.poll();
        		while(!operators.isEmpty() && !operators.peek().equals("(")) {
        			postfix.add(operators.pop());
        		}
        		operators.pop();
        	}
        }
        if(infix.isEmpty()) {
        	while(!operators.isEmpty()) {
        		postfix.add(operators.pop());
        	}
        }  
        //return new ArrayList<String>(Arrays.asList("10", "8", "2", "+", "*", "13", "32", "/", "5", "%", "-"));
        return postfix;
    }

    @Override
    public void build(List<String> postfix) {
        Collections.reverse(postfix);
        for (String token : postfix)
            buildRecursive(root, token);
    }

    /**
     * Builds an expression tree from the postfix representation returned from the convert method.
     * To build the correct tree, pull tokens from {@code List<String> postfix}, and places
     * them at the next available node in the tree.
     * Here is the exact algorithm:
     * <ol>
     *     <li> If the tree root is null, create a new node containing the token,
     *          assign it to the root, and return {@code true}.
     *     <li> If the right child of the current node is null, create a new node
     *          with the token, place it in the right child, and return {@code true}.
     *     <li> If the right child of the current node is an operator, make a recursive
     *          call passing the right child and token, and return true if successful,
     *          otherwise continue.
     *     <li> If the left child of the current node is null, create a new node with
     *          the token, place it in the left child, and return {@code true}.
     *     <li> If the left child of the current node is an operator, make a recursive
     *          call passing the left child and token, and return {@code true} if successful,
     *          otherwise continue.
     *     <li> If none of the above code returns {@code true}, then the code has failed to add
     *          the token to the tree, so return {@code false}.
     * </ol>
     *
     * Our implementation of the recursive method is ~19 lines of code
     * @param current the current Node being checked
     * @param token the token to add
     * @return {@code true}, if successful
     */
    public boolean buildRecursive(Node current, String token) {
        // YOUR CODE HERE
    	if(root == null) {
    		current = new Node(token);
    		root = current;
    		return true;
    	}
    	if(current.right == null) {
    		current.right = new Node(token);
    		return true;
    	}
    	if(current.right.token.equals("+") || current.right.token.equals("-") ||current.right.token.equals("*") || current.right.token.equals("/") || current.right.token.equals("%") ||
    			current.right.token.equals("(") || current.right.token.equals(")")) {
    		if(buildRecursive(current.right, token) == true) {
    			return true;
    		}
    		
    	}
    	if(current.left == null) {
    		current.left = new Node(token);
    		return true;
    	}
    	if(current.left.token.equals("+") || current.left.token.equals("-") || current.left.token.equals("*") || current.left.token.equals("/") || current.left.token.equals("%") ||
    			current.left.token.equals("(") || current.left.token.equals(")")) {
    		if(buildRecursive(current.left, token) == true) {
    			return true;
    		}
    	}
    	return false;
    }

    @Override
    public String prefix() {
        return prefixRecursive(root);
    }

    /**
     * Concatenates the tokens in the expression tree returned from the
     * {@link #build(List)} method in <b>prefix</b> order.
     * <p>
     * Accumulate the operator first, then the string from the left
     * and right subtrees. Add an extra space after each token.
     * <p>
     * Our implementation of this method is ~2 lines of code.
     * @param current the root node
     * @return the tokens in prefix order
     */
    public String prefixRecursive(Node current) {
        // YOUR CODE HERE
    	String result = "";
    	if(ATree.isInteger(current.token)) {
        	result = current.token + " ";
    		return current.token;
    	}
    	//result = current.token + " ";
    	result += current.token + " " + prefixRecursive(current.left) + " " + prefixRecursive(current.right);
        return result;
    }

    @Override
    public String infix() {
        return infixRecursive(root);
    }

    /**
     * Concatenates the tokens in the expression tree returned from the
     * {@link #build(List)} method in <b>infix</b> order.
     * <ol>
     *     <li> Accumulate the string from the left subtree
     *     <li> Add the operator
     *     <li> Accumulate the string from the right subtree
     * </ol>
     * This method should add parentheses to maintain the correct evaluation order,
     * add a left parentheses before traversing the left subtree, and a right
     * parentheses after traversing the right subtree.
     * Do not add any space to the expression string.
     * <p>
     * Our implementation of this method is ~2 lines of code.
     * @param current
     * @return the tokens in infix order
     */
    public String infixRecursive(Node current) {
        // YOUR CODE HERE
    	String result = "(";
    	if(ATree.isInteger(current.token)) {
    		return current.token;
    	}
		result = "(" + infixRecursive(current.left) + current.token + infixRecursive(current.right) + ")";

        return result;
    }

    @Override
    public String postfix() {
        return postfixRecursive(root);
    }

    /**
     * Concatenates the tokens in the expression tree returned from the
     * {@link #build(List)} method in <b>postfix</b> order.
     * First accumulate the string from the left and right subtrees, then add the
     * operator. Add an extra space after each token.
     * <p>
     * Our implementation of this method is ~2 lines of code.
     * @param current
     * @return
     */
    public String postfixRecursive(Node current) {
        // YOUR CODE HERE
    	String result = "";
    	if(ATree.isInteger(current.token)) {
    		return current.token;
    	}
    	result = postfixRecursive(current.left) + " " + postfixRecursive(current.right) + " " + current.token;
    	return result;
    }

    public int evaluate() {
        return evaluateRecursive(root);
    }

    /**
     * Traverses the expression tree and produces the correct answer, which should be an integer.
     * To evaluate, call the recursive version of the method to get the result from the left
     * subtree, do the same for the right subtree, then combine these two results using the
     * operator. A case statement based on the operator is needed to perform the arithmetic.
     * <p>
     * Our implementation uses one helper method (~7 lines of code) and is, itself, ~2 lines of code.
     * @param current
     * @return
     */
    public int evaluateRecursive(Node current) {
        // YOUR CODE HERE
    	String op = "";
    	int left = 0;
    	int right = 0;
    	int result = 0;

    	if(ATree.isInteger(current.token)) {
    		return ATree.valueOf(current.token);
    	}
    	if(ATree.isOperator(current.token)) {
        	op = current.token;
        	left = evaluateRecursive(current.left);
        	right = evaluateRecursive(current.right);
            result += evaluate(op, left, right);
    	}

    
    	return result;
    }
    
    public int evaluate(String op, int left, int right) {
    	int result = 0;
    	switch(op) {
		case"+": 
			result = left + right;
			break;
		case"-": 
			result = left - right;
			break;
		case"*": 
			result = left * right;
			break;
		case"/": 
			result = left / right;
			break;
		case"%": 
			result = left % right;
			break;    			
    	}
    	return result;
	}

    
    

}
