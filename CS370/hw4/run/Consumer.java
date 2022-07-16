
public class Consumer implements Runnable{
	CircularBuffer buffer;							//buffer
	int consumed = 0;								//count for items consumed
	double value = 0;								//item value total
	
    public Consumer(CircularBuffer buffer){			//setting buffer
        this.buffer = buffer;
    }
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		while(consumed < 1000000) {						//keep thread running for 1  million items
			synchronized(buffer) {						//synchronizing buffer
				if(buffer.isEmpty() == true) {			//checking if buffer is empty
					try {
						buffer.wait();					//if so then wait
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				double remove = buffer.remove();		//getting removed item
				consumed++;								//increase count for items consumed
				value += remove;						//add the item to value, to get value
//				if(consumed % 100000 == 0) {			//every 100000 print out
//					System.out.printf("Consumer: Consumed %,d items, Cumulative value of consumed items=%.3f\n", consumed, value);
//				}
				buffer.notify();						//notify other thread
			}
			if(consumed % 100000 == 0 && consumed != 0) {			//every 100000 print out
				System.out.printf("Consumer: Consumed %,d items, Cumulative value of consumed items=%.3f\n", consumed, value);
			}
		}
		System.out.printf("Consumer: Finished consuming %,d items\n", consumed);
	}

}
