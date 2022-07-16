import java.util.Random;

public class Producer implements Runnable{
	
	CircularBuffer buffer;						//buffer
	int generated = 0;							//count for items generated
	double value = 0;							//value of generated items
	
    public Producer(CircularBuffer buffer){		//setting the buffer
        this.buffer = buffer;
    }
	@Override
	public void run() {
		// TODO Auto-generated method stub
		while(generated < 1000000) {				//keep thread running for 1 million items
//			if(generated % 100000 == 0 && generated != 0) {									//for every 100000 items, print out
//				System.out.printf("Producer: Generated %,d items, Cumulative value of generated items=%.3f\n", generated, value);
//			}
			synchronized(buffer) {				//synchronizing buffer
				if(buffer.isFull() == true) {		//if buffer is full
					try {			
						buffer.wait();				//then wait
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				Random random = new Random();
				Double bufferElement = random.nextDouble() * 100.0;				//getting random number for item
				
				buffer.add(bufferElement);										//inserting item into buffer
				generated++;													//increase count of generated
				value += bufferElement;											//add the item to value
//				if(generated % 100000 == 0) {									//for every 100000 items, print out
//					System.out.printf("Producer: Generated %,d items, Cumulative value of generated items=%.3f\n", generated, value);
//				}
				buffer.notify();				//notify other thread
			}
			if(generated % 100000 == 0 && generated != 0) {									//for every 100000 items, print out
				System.out.printf("Producer: Generated %,d items, Cumulative value of generated items=%.3f\n", generated, value);
			}
		}
		System.out.printf("Producer: Finished generating %,d items\n", generated);
		
	}
}
