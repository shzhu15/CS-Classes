
public class ProducerConsumer{

	public static void main(String[] args) {
		CircularBuffer buffer = new CircularBuffer();			//buffer
		
        Thread producer = new Thread(new Producer(buffer));		//creating thread for producer
        Thread consumer = new Thread(new Consumer(buffer));		//creating thread for consumer
        
        producer.start();			//starting producer thread
        consumer.start();			//starting consumer thread
        
        try {
            consumer.join();		//waiting for consumer thread
        	producer.join();		//waiting for producer thread

        } 
        catch (InterruptedException e) {
			e.printStackTrace();
        }
        
		System.out.println("Exiting!");
		return;
	}

}
