import java.util.Collection;
/**
 * IList.java - List interface for data structure assignment
 * Author: Chris Wilcox
 * Date:   2/17/2017
 * Class:  CS165
 * Email:  wilcox@cs.colostate.edu
 * javadoc created or copied from oracle by garethhalladay, Fall17.
 * @param <E> the type of elements in this list
 */
public interface IList<E> {

    /**
     * Appends the specified element to the end of this list.
     * @param e element to be appended to this list
     * @return true (as specified by {@link Collection#add(Object)}
     */
    public abstract boolean add(E e);

    /**
     * Inserts the specified element at the specified position in this list.
     * Shifts the element currently at that position (if any) and any subsequent
     * elements to the right (adds one to their indices).
     * @param index index at which the specified element is to be inserted
     * @param e element to be inserted
     * @throws IndexOutOfBoundsException if the index is out of range {@code (index < 0 || index > size())}
     */
    public abstract void add(int index, E e);

    /**
     * Removes the first occurrence of the specified element from this list, if it is present.
     * If the list does not contain the element, it is unchanged. More formally, removes the
     * element with the lowest index i such that (o==null ? get(i)==null : o.equals(get(i)))
     * (if such an element exists). Returns true if this list contained the specified element
     * (or equivalently, if this list changed as a result of the call).
     * @param o element to be removed from this list, if present
     * @return true if this list contained the specified element
     */
    public abstract boolean remove(Object o);

    /**
     * Removes the element at the specified position in this list.
     * Shifts any subsequent elements to the left (subtracts one
     * from their indices).
     * @param index the index of the element to be removed
     * @return the element that was removed from the list
     * @throws IndexOutOfBoundsException if the index is out of range {@code (index < 0 || index > size())}
     */
    public abstract E remove(int index);

    /**
     * Removes from this list all of the elements whose index is between fromIndex,
     * inclusive, and toIndex, exclusive. Shifts any succeeding elements to the left
     * (reduces their index). This call shortens the list by {@code (toIndex - fromIndex)} elements.
     * (If {@code toIndex==fromIndex}, this operation has no effect.)
     * @param fromIndex index of first element to be removed
     * @param toIndex index after last element to be removed
     * @throws IndexOutOfBoundsException if fromIndex or toIndex is out of range:
     *                                  {@code  fromIndex < 0 || fromIndex >= size() ||
     *                                          toIndex > size() || toIndex < fromIndex }
     */
    public abstract void removeRange(int fromIndex, int toIndex);

    /**
     * Returns the element at the specified position in this list.
     * @param index index of the element to return
     * @return the element at the specified position in this list
     * @throws IndexOutOfBoundsException if the index is out of range {@code (index < 0 || index > size()) }
     */
    public abstract E get(int index);

    /**
     *
     * @param index index of the element to replace
     * @param e element to be stored at the specified position
     * @return the element previously at the specified position
     * @throws IndexOutOfBoundsException if the index is out of range {@code (index < 0 || index > size())}
     */
    public abstract E set(int index, E e);


    /**
     * Returns true if this list contains the specified element.
     * More formally, returns true if and only if this list contains at
     * least one element e such that {@code (o==null ? e==null : o.equals(e))}.
     * @param o element whose presence in this list is to be tested
     * @return true if this list contains the specified element
     */
    public abstract boolean contains(Object o);

    /**
     * Returns the index of the first occurrence of the specified element in
     * this list, or -1 if this list does not contain the element. More
     * formally, returns the lowest index i such that
     * {@code (o==null ? get(i)==null : o.equals(get(i)))}, or {@code -1} if there is no such index.
     * @param o element to search for
     * @return the index of the first occurrence of the specified element in this list,
     *         or -1 if this list does not contain the element
     */
    public abstract int indexOf(Object o);

    /**
     * Returns the index of the last occurrence of the specified element in this list, or -1 if
     * this list does not contain the element. More formally, returns the highest index i such
     * that {@code (o==null ? get(i)==null : o.equals(get(i)))}, or {@code -1} if there is no such index.
     * @param o element to search for
     * @return the index of the last occurrence of the specified element in this list, or -1
     *         if this list does not contain the element
     */
    public abstract int lastIndexOf(Object o);

    /**
     * Removes all of the elements from this list. The list will be empty after this call returns.
     */
    public abstract void clear();

    /**
     * @return Returns the number of elements in this list.
     */
    public abstract int size();

    // Returns whether list is empty

    /**
     * @return Returns true if this list contains no elements.
     */
    public abstract boolean isEmpty();
}

