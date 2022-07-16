import java.util.Arrays;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.NoSuchElementException;

/**
 * CoolLinkedList.java - student implementation of LinkedList
 * Author: ?????
 * Date:   ?????
 * Class:  CS165
 * Email:
 *
 * @param <E> the type of elements in this list
 */
public class MyLinkedList<E> implements ILinkedList<E> {

    // Node data structure
    public class Node {
        // YOUR CODE HERE
    	public Node next;
    	E data;
    	
    	public Node(E data) {
    	    this(data, null);
    	}

    	public Node(E data, Node next) {
    	    this.next = next;
    	    this.data = data;
    	}
    	
    	public Node getNext() {
    		return next;
    	}
    	public void setNext(Node nextNode) {
    	    next = nextNode;
    	}
    	public E getData() {
    		return data;
    	}
    }

    // Head (first) pointer
    private Node listHead;

    // Tail (last) pointer
    private Node listTail;

    // Current size
    private int listSize;

    // Default constructor
    public MyLinkedList() {
        // YOUR CODE HERE
    	listHead = null;
    	listSize = 0;
    }

    /**
     * Special debug method. Uncomment this method after completing the Node class.
     */
    public void printDebug() {
         /*
        Debug.printf("LinkedList.size() = %d\n", listSize);
        int index = 0;
        for (Node c = listHead; c != null; c = c.next) {
            String sNode = c.getClass().getSimpleName() + "@" + Integer.toHexString(c.hashCode());
            String sNext;
            if (c.next == null)
                sNext = "null";
            else
                sNext = c.next.getClass().getSimpleName() + "@" + Integer.toHexString(c.hashCode());
            Debug.printf("LinkedList[%d]: element %s, next %s\n", index++, sNode, sNext);
        }
         */
    }

    // Possible helper method? Delete if you don't want to use it.
    private Node getNode(int index){
        Node current = listHead;
    	while(index != 0) {
    		current = current.getNext();
    		index--;
    	}
    	return current;
    }

    public boolean add(E e) {
        // YOUR CODE HERE
    	Node temp = new Node(e);
    	Node current = listHead;
    	if(current == null) {
    		listHead = temp;
    		listSize++;
    		System.out.println(listHead.getData());
    		return true;
    	}
    	while(current.getNext() != null) {
    		current = current.getNext();
    	}
    	current.setNext(temp);
    	listSize++;
        return true;
    }

    public void add(int index, E e) {
        // YOUR CODE HERE
        Node temp = new Node(e);
        Node current = listHead;

        if (index == 0){
            temp.setNext(listHead);
            listHead = temp;
            listSize++;
        } 
        else {
        	while(index-1 != 0) {
        		System.out.println("index:" + index);
        		current = current.getNext();
        		index--;
            }
        	getNode(index-1).setNext(temp);
            temp.setNext(current.getNext());
            current.setNext(temp);
        }
        listSize++;
    }

    public boolean remove(Object o) {
        // YOUR CODE HERE
    	Node current = listHead;
    	for(int i = 0; i < listSize; i++) {
    		if(o.equals(current.getData())) {
            	getNode(i-1).setNext(getNode(i-1).getNext().getNext());
            	listSize--;
            	return true;
    		}
    		current = current.getNext();
    	}
        return false;
    }

    public E remove(int index) {
        // YOUR CODE HERE
    	E result = null;
        if (index == 0) {
        	result = listHead.getData();
            listHead = listHead.getNext();
        } 
        else {
        	result = getNode(index).getData();
        	getNode(index).setNext(getNode(index).getNext().getNext());

        }
        listSize--;
        return result;
    }


    @Override
    public void removeRange(int fromIndex, int toIndex) {
        // YOUR CODE HERE
    	int count = toIndex - fromIndex;
    	getNode(fromIndex).setNext(getNode(fromIndex));
    	listSize = listSize - count;
    }

    public E get(int index) {
        // YOUR CODE HERE
        Node current = listHead;
        for (int i = 0; i < index; i++){
            current = current.getNext();
        }

        return current.getData();
    }


    public E set(int index, E e) {
        // YOUR CODE HERE
        Node current = listHead;
        Node temp = new Node(e);
        for (int i = 0; i < index; i++){
            current = current.getNext();
        }
    	E result = current.getData();
    	current = temp;
        return result;
    }

    public boolean contains(Object o) {
        // YOUR CODE HERE
    	Node current = listHead;
    	for(int i = 0; i < listSize; i++) {
    		if(o.equals(current.getData())) {
            	return true;
    		}
    		current = current.getNext();
    	}
        return false;
    }

    public int indexOf(Object o) {
        // YOUR CODE HERE
    	Node current = listHead;
    	for(int i = 0; i < listSize; i++) {
    		if(o.equals(current.getData())) {
            	return i;
    		}
    		current = current.getNext();
    	}
        return -1;
    }

    public int lastIndexOf(Object o) {
        // YOUR CODE HERE
    	int count = 0;
    	Node current = listHead;
    	for(int i = 0; i < listSize; i++) {
    		if(o.equals(current.getData())) {
            	count = i;
    		}
    		current = current.getNext();
    	}
    	if(count > -1) {
    		return count;
    	}
        return -1;
    }

    public void clear() {
        // YOUR CODE HERE
    	listHead = null;
    	listTail = null;
    	listHead.setNext(listTail);
    }

    public int size() {
        // YOUR CODE HERE

        return listSize;
    }

    public boolean isEmpty() {
        // YOUR CODE HERE
    	if(listSize == 0) {
    		return true;
    	}
        return false;
    }

    public void addFirst(E e) {
        // YOUR CODE HERE
        Node temp = new Node(e);
    	Node current = listHead;
    	listHead = temp;
    	temp.setNext(current);

    }

    public void addLast(E e) {
        // YOUR CODE HERE
        Node temp = new Node(e);
    	Node current = getNode(listSize);
    	current.setNext(temp);
    	listTail = temp;
    }

    public E removeFirst() {
        // YOUR CODE HERE
    	E result = listHead.getData();
    	listHead = null;
        return result;
    }

    public E removeLast() {
        // YOUR CODE HERE
    	E result = listTail.getData();
    	listTail = null;
        return result;
    }

    public void push(E e) {
        // YOUR CODE HERE
        Node temp = new Node(e);
    	Node current = listHead;
    	listHead = temp;
    	temp.setNext(current);
    }

    public E pop() {
        // YOUR CODE HERE
    	E result = listHead.getData();
    	listHead = null;
        return result;
    }

    public E peek() {
        // YOUR CODE HERE
        return listHead.getData();
    }



    // Extra credit
    public class MyLinkedListIterator implements ListIterator<E> {
        // declare and initialize member variables

        @Override
        public boolean hasNext() {
            // YOUR CODE HERE

            return false;
        }

        @Override
        public E next() {
            // YOUR CODE HERE

            return null;
        }

        @Override
        public boolean hasPrevious() {
            // YOUR CODE HERE

            return false;
        }

        @Override
        public E previous() {
            // YOUR CODE HERE

            return null;
        }

        @Override
        public int nextIndex() {
            // YOUR CODE HERE

            return 0;
        }

        @Override
        public int previousIndex() {
            // YOUR CODE HERE

            return 0;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }

        @Override
        public void set(E e) {
            throw new UnsupportedOperationException();
        }

        @Override
        public void add(E e) {
            throw new UnsupportedOperationException();
        }
    }

    public MyLinkedListIterator listIterator() {
        // YOUR CODE HERE

        return null;
    }

}

