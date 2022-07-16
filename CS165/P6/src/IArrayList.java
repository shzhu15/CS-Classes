
/**
 * IArrayList.java - ArrayList interface for data structure assignment
 * Author: Chris Wilcox
 * Date:   2/17/2017
 * Class:  CS165
 * Email:  wilcox@cs.colostate.edu
 * javadoc created or copied from oracle by garethhalladay, Fall17.
 * @param <E> the type of elements in this list
 */
public interface IArrayList<E> extends IList<E> {

    /**
     * Trims the capacity to the size of the existing array
     */
    public abstract void trimToSize();
}

