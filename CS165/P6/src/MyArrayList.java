import java.util.Arrays;

/**
 * MyArrayList.java - student implementation of ArrayList
 * Author: ?????
 * Date:   ?????
 * Class:  CS165
 * Email:
 *
 * @param <E> the type of elements in this list
 */
public class MyArrayList<E> implements IArrayList<E> {

    /**
     * Declare underlying array
     */
    private E[] underlyingArray;

    /**
     * Current size
     */
    private int listSize;

    public final static double CAPACITY_INCREASE = 0.5;

    /**
     * Constructs an empty list with the specified initial capacity.
     * @param initialCapacity the initial capacity of the list
     */
    @SuppressWarnings("unchecked")
	public MyArrayList(int initialCapacity) {
        // YOUR CODE HERE
    	underlyingArray = (E[]) new Object[initialCapacity];
    }

    /**
     * Constructs an empty list with an initial capacity of ten.
     * Because we are using generics you will have to create a new
     * array of type Object and cast it to type E.
     * <p>
     * Think about constructor chaining.
     */
    public MyArrayList() {
        // YOUR CODE HERE
    	this(10);
    }


    /**
     * Special debug method
     */
    public void printDebug() {
        Debug.printf("ArrayList.size() = %d\n", listSize);
        Debug.printf("ArrayList.capacity() = %d\n", underlyingArray.length);
        for (int index = 0; index < listSize; index++) {
            E e = (E)underlyingArray[index];
            String sElement = e.getClass().getName() + "@" + Integer.toHexString(e.hashCode());
            System.err.printf("ArrayList[%d]:  %s: %s\n", index, sElement, e.toString());
        }
    }


    // If the array is full, expand its capacity by an additional 50% (defined through
    // CAPACITY_INCREASE), using integer math. For example, if the current capacity is 15
    // the new capacity will be 22, and if the current capacity is 22 the new capacity
    // will be 33.
    @Override
    public boolean add(E e) {
        // YOUR CODE HERE
    	if(listSize == underlyingArray.length) {
    		int size = underlyingArray.length + (int) (underlyingArray.length * CAPACITY_INCREASE);
    		reallocateArray(size);
    		}
    	for(int i = 0; i < underlyingArray.length; i++) {
    		if(i > listSize) {
    			throw new IndexOutOfBoundsException();	
    		}
    		if(underlyingArray[i] == null) {
    			underlyingArray[i] = e;
    			listSize++;
    			return true;
    		}
    	}
        return false;
    }


    // If the array is full, expand its capacity by an additional 50% (defined through
    // CAPACITY_INCREASE), using integer math. For example, if the current capacity is 15
    // the new capacity will be 22, and if the current capacity is 22 the new capacity
    // will be 33.
    @Override
    public void add(int index, E e) {
        // YOUR CODE HERE
    	if(listSize == underlyingArray.length) {
    		int size = underlyingArray.length + (int) (underlyingArray.length * CAPACITY_INCREASE);
    		reallocateArray(size);
    		}
    	E temp = underlyingArray[index];
    	underlyingArray[index] = e;
    	for(int i = underlyingArray.length - 1; i > index+1; i--) {
    		underlyingArray[i] = underlyingArray[i-1];
    	}
    	underlyingArray[index+1] = temp;
    	listSize++;
    }

    @Override
    public boolean remove(Object o) {
        // YOUR CODE HERE
    	boolean result = false;
    	int index = 0;
    	for(int i = 0; i < underlyingArray.length; i++) {
    		if(o==null ? get(i)==null : o.equals(get(i))) {
    			index = i;
    			//underlyingArray[i] = null;
    			//listSize--;
    			result = true;
    			}
    		}
    	for(int i = index; i < listSize; i++) {
    		underlyingArray[i] = underlyingArray[i+1];
    	}
		listSize--;
        return result;
    }


    @Override
    public E remove(int index) {
        // YOUR CODE HERE
    	E result = null;
    	for(int i = index; i < underlyingArray.length - 1; i++) {
    		if(i == index) {
    			result = underlyingArray[i];
    			underlyingArray[i] = null;
    			listSize--;
    		}
    		underlyingArray[i] = underlyingArray[i+1];
    	}
    	
    	return result;
    }

    @Override
    public void removeRange(int fromIndex, int toIndex) {
        // YOUR CODE HERE
    	int count = toIndex - fromIndex;
//    	for(int i = fromIndex; i < toIndex; i++) {
//    			underlyingArray[i] = null;
//    			listSize--;
//    			count++;
//    		}
    	for(int i = fromIndex; i < listSize; i++) {
    		underlyingArray[i] = underlyingArray[i+count];
    	}
    	listSize = listSize - count;
    }
    

    @Override
    public E get(int index) {
        // YOUR CODE HERE
        return underlyingArray[index];
    }

    @Override
    public E set(int index, E e) {
        // YOUR CODE HERE
    	E result = underlyingArray[index];
    	underlyingArray[index] = e;
        return result;
    }


    @Override
    public boolean contains(Object o) {
        // YOUR CODE HERE
    	for(int i = 0; i < underlyingArray.length; i++) {
    		if(o.equals(get(i))) {
    			return true;
    		}
    	}
        return false;
    }

    @Override
    public int indexOf(Object o) {
        // YOUR CODE HERE
    	for(int i = 0; i < underlyingArray.length; i++) {
    		if(underlyingArray[i].equals(o)) {
    			return i;
    		}
    	}
        return -1;
    }

    @Override
    public int lastIndexOf(Object o) {
        // YOUR CODE HERE
    	for(int i = underlyingArray.length-1; i > 0; i--) {
    		if(o.equals(get(i))) {
    			return i;
    		}
    	}
        return -1;
    }

    @Override
    public void clear() {
        // YOUR CODE HERE
    	for(int i =0; i < underlyingArray.length; i++) {
    		underlyingArray[i] = null;
    	}
    	listSize = 0;
    }


    @Override
    public int size() {
        // YOUR CODE HERE

        return listSize;
    }

    @Override
    public boolean isEmpty() {
        // YOUR CODE HERE
    	if(listSize == 0) {
    		return true;
    	}
        return false;
    }

    // use the reallocateArray method
    public void trimToSize() {
        // YOUR CODE HERE
    	reallocateArray(listSize);
    }


    private void reallocateArray(int capacity) {
        // YOUR CODE HERE

    	underlyingArray = Arrays.copyOf(underlyingArray, capacity);
    	
    }

}
