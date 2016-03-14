package monitor;

import java.util.*;


/*
 * Consumer class
 */
public class Consumer extends Thread{
	int ID;
	private Producer producer;
	
	
	public Consumer(int ID, Producer producer) {
		this.ID = ID;
		this.producer = producer;
	}
	
	@Override
	public void run() {
		try {

			while (true) {
				int ID = this.ID;
				// get the request
				Request request = producer.getRequest(ID);
				int length = request.length;
				int r_ID = request.ID;
				//Process the request
				while(length>0){
					sleep(1000);
					length--;
				}
				//print outputs
				Date date2 = new Date();
				System.out.println("Consumer "+ID+": " + "Compeleted request "+ r_ID+ " at time "+ date2.toString());
				System.out.println("====================================================\n");
				
			}
			
		} catch (Exception e) {
			// TODO: handle exception
		}
	}	
	
}
