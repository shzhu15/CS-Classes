import java.util.Iterator;
import java.util.ListIterator;

/**
 * ILinkedList.java - LinkedList interface for data structure assignment
 * Author: Chris Wilcox
 * Date:   2/17/2017
 * Class:  CS165
 * Email:  wilcox@cs.colostate.edu
 * javadoc created or copied from oracle by garethhalladay, Fall17.
 * @param <E> the type of elements in this list
 */
public interface ILinkedList<E> extends IList<E> {

    /**
     * Adds element to head (first) of list
     * @param e the new element
     */
    public abstract void addFirst(E e);

    /**
     * Adds element to tail (last) of list
     * @param e the new element
     */
    public abstract void addLast(E e);

    /**
     * Removes element from head (first) of list
     * @return the element that was just removed
     */
    public abstract E removeFirst();

    /**
     * Removes element from tail (last) of list
     * @return the element that was just removed
     */
    public abstract E removeLast();

    /**
     * Pushes element onto head (first) of list
     * @param e the new element
     */
    public abstract void push(E e);

    /**
     * Pops element from head (first) of list
     * @return the element that was just removed
     */
    public abstract E pop();

    /**
     * Peeks at element at head (first) of list
     * @return the element at the head (first) of the list
     */
    public abstract E peek();

    /**
     * Return a {@code ListIterator} for the list
     * @return a {@code ListIterator} for the list
     */
    public abstract ListIterator<E> listIterator();
}
