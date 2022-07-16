
public class CircularBuffer {
    int size = 1000; // buffer length
    double[] buffer;	//buffer
    int out = 0;	//consuming counter
    int in = 0;		//producing counter
    int count = 0;		//how many items in buffer
  
    
    public CircularBuffer() {				//creating buffer
    	buffer = new double[size];
    }
    
    public int size() {					//getting count of items
    	return count;
    }
    
    public boolean isEmpty() {		//checking if buffer is empty
    	if(in == out) {
    		return true;
    	}
    	else {
    		return false;
    	}
    }
    public boolean isFull() {				//checking if buffer is full
    	if((in + 1) % size == out) {
    		return true;
    	}
    	else {
    		return false;
    	}
    }
    
    public void add(double item) {						//adding item into buffer
        buffer[in] = item;								//inserting item into buffer
        in = (in + 1) % size;							//getting position for next item
        count++;										//increasing count
      }
    
      public double remove() {							//removing item from buffer	
        double item = buffer[out];						//getting removed item
        out = (out + 1) % size;							//getting position for next item to consume
        count--;										//decrease count
        return item;									//return the item
      }
}
