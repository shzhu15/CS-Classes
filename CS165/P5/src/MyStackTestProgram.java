// TestProgram.java - Test program for stack lab
// Author: Chris Wilcox
// Date:   2/11/2017
// Class:  CS165
// Email:  wilcox@cs.colostate,edu

import java.util.EmptyStackException;
import java.util.Random;
import java.util.Stack;

public class MyStackTestProgram {

    private static Random random = new Random();

    public static void main(String[] args) {
    	
        // Make a Java stack
        Stack<String> javaStack = new Stack<>();
        // Make a student stack
        MyStack<String> myStack = new MyStack<>();


        // test each method, leave code in so that TA can verify the class
        testPush(javaStack, myStack);
        testPop(javaStack, myStack);
        testPeek(javaStack, myStack);
        testSize(javaStack, myStack);
        testClear(javaStack, myStack);
        testIsEmpty(javaStack, myStack);
        testFirstIndex(javaStack, myStack);
        testLastIndex(javaStack, myStack);
        testContains(javaStack, myStack);
        testSearch(javaStack, myStack);
    }

    public static void testPush(Stack<String> javaStack, MyStack<String> myStack){
        System.err.println("testPush: verifying push() method");
        pushRandom(javaStack, 10);
        pushRandom(myStack, 10);
        System.err.println("Java Stack: " + javaStack);
        System.err.println("My Stack: " + myStack);
    }

    public static void testPop(Stack<String> javaStack, MyStack<String> myStack){
        System.err.println("testPop: verifying pop() method");
        pushRandom(javaStack, 10);
        pushRandom(myStack, 10);
        // Legal pops
        for (int i = 0; i < 10; i++) {
            System.err.printf("javaStack.pop(): %4s, myStack.pop(): %4s\n", javaStack.pop(), myStack.pop());
        }

        // Stack empty
        try {
            javaStack.pop();
        } catch (EmptyStackException e) {
            System.err.println("Java Stack: caught EmptyStackException");
        }
        try {
            myStack.pop();
        } catch (EmptyStackException e) {
            System.err.println("My Stack: caught EmptyStackException");
        }
    }

    public static void testPeek(Stack<String> javaStack, MyStack<String> myStack){
        System.err.println("testPeek: verifying peek() method");
        pushRandom(javaStack, 10);
        pushRandom(myStack, 10);
        for (int i = 0; i < 10; i++) {
            System.err.printf("javaStack.peek(): %4s, myStack.peek(): %4s\n", javaStack.peek(), myStack.peek());
            javaStack.pop();
            myStack.pop();
        }
    }

    public static void testSize(Stack<String> javaStack, MyStack<String> myStack){
        System.err.println("testSize: verifying size() method");
        pushRandom(javaStack, 23456);
        pushRandom(myStack, 23456);
        for (int i = 0; i < 12123; i++) {
            javaStack.pop();
            myStack.pop();
        }
        System.err.printf("javaStack.size(): %4s, myStack.size(): %4s\n", javaStack.size(), myStack.size());
    }

    public static void testClear(Stack<String> javaStack, MyStack<String> myStack){
        System.err.println("testClear: verifying clear() method");
        pushRandom(javaStack, 23456);
        pushRandom(myStack, 23456);
        javaStack.clear();
        myStack.clear();
        System.err.printf("javaStack.size(): %s, myStack.size(): %s\n", javaStack.size(), myStack.size());
    }

    public static void testIsEmpty(Stack<String> javaStack, MyStack<String> myStack){
        System.err.printf("javaStack.isEmpty(): %4s, myStack.isEmpty(): %4s\n", javaStack.isEmpty(), myStack.isEmpty());
        javaStack.push("1111");
        myStack.push("2222");
        System.err.printf("javaStack.isEmpty(): %4s, myStack.isEmpty(): %4s\n", javaStack.isEmpty(), myStack.isEmpty());
        javaStack.pop();
        myStack.pop();
        System.err.printf("javaStack.isEmpty(): %4s, myStack.isEmpty(): %4s\n", javaStack.isEmpty(), myStack.isEmpty());
    }

    public static void testFirstIndex(Stack<String> javaStack, MyStack<String> myStack){
        pushRandom(javaStack, 1234);
        pushRandom(myStack, 1234);
        pushRandom(javaStack, 1234); // guarantees duplicates, same random seed
        pushRandom(myStack, 1234); // guarantees duplicates, same random seed
        System.err.println("javaStack.indexOf(\"7449\"): " + javaStack.indexOf("7449"));
        System.err.println("myStack.indexOf(\"7449\"): " + myStack.indexOf("7449"));
    }

    public static void testLastIndex(Stack<String> javaStack, MyStack<String> myStack){
        pushRandom(javaStack, 1234);
        pushRandom(myStack, 1234);
        pushRandom(javaStack, 1234); // guarantees duplicates, same random seed
        pushRandom(myStack, 1234); // guarantees duplicates, same random seed
        System.err.println("javaStack.lastIndexOf(\"7449\"): " + javaStack.lastIndexOf("7449"));
        System.err.println("myStack.lastIndexOf(\"7449\"): " + myStack.lastIndexOf("7449"));
    }

    public static void testContains(Stack<String> javaStack, MyStack<String> myStack){
        pushRandom(javaStack, 1234);
        pushRandom(myStack, 1234);
        System.err.println("javaStack.contains(\"7449\"): " + javaStack.contains("7449"));
        System.err.println("coolStack.contains(\"7449\"): " + myStack.contains("7449"));
        System.err.println("javaStack.contains(\"4444\"): " + javaStack.contains("4444"));
        System.err.println("coolStack.contains(\"4444\"): " + myStack.contains("4444"));
    }

    public static void testSearch(Stack<String> javaStack, MyStack<String> myStack){
        pushRandom(javaStack, 1234);
        pushRandom(myStack, 1234);
        System.err.println("javaStack.search(\"7449\"): " + javaStack.search("7449"));
        System.err.println("coolStack.search(\"7449\"): " + myStack.search("7449"));
        System.err.println("javaStack.search(\"4444\"): " + javaStack.search("4444"));
        System.err.println("coolStack.search(\"4444\"): " + myStack.search("4444"));
    }



    // Initialize stack by pushing random data
    private static void pushRandom(Stack<String> stack, int number) {
        random.setSeed(1234);
        for (int i = 0; i < number; i++) {
            stack.push(Integer.toString(random.nextInt(10000)));
        }
    }
    private static void pushRandom(MyStack<String> stack, int number) {
        random.setSeed(1234);
        for (int i = 0; i < number; i++) {
            stack.push(Integer.toString(random.nextInt(10000)));
        }
    }
}

