package monitor;

import java.util.*;

/*
 * Producer class
 */
public class Producer extends Thread{

	// the max number of requests in the queue
	private final int MAX_REQUEST;
	// the time for producer to sleep after creating a request
	private final int sleep_time;
	//the count for requests in total
	private int total_count = 0;
	//count for requests in the queue
	private int count = 0;
	//the max number of requests in total
	private int max;
	//request queue
	private Queue<Request> queRequests = new LinkedList<Request>();

	
	//constructor
	public Producer(int input, int sleep_time, int max){
		MAX_REQUEST = input;
		this.sleep_time = sleep_time;
		this.max = max;
	}
	
	
	@Override
	public void run() {
	
			//while loop only runs when number of requests less than the max
			while(total_count < max){
				//put the request to queue
				putRequest();
				total_count++ ;
				count++;
			}
		
	}
	
	//synchronized method for putting requests into queue
	private synchronized void putRequest(){
		try {
			//if the queue is full, wait
			while(count == MAX_REQUEST)
				wait();
			//else create request
			Request request = new Request(total_count);
			//add to the queue
			queRequests.add(request);
			//instance to get the current time
			Date date = new Date();
			//outputs
			System.out.println("Producer: Producing Request " + request.ID + " length "
			+request.length+" at " + date.toString());
			System.out.println("Producer: sleeping for next "+ sleep_time/1000 + "s");
			System.out.println("----------------------------------------------\n");
			sleep(sleep_time);
			//notify waiting threads
			notifyAll();
			
			
		} catch (Exception e) {
			// TODO: handle exception
		}
	}
	
	//create consumers
	public Consumer[] consumer(int input,Producer producer) {
		Consumer[] consumers = new Consumer[input];
		for (int i = 0; i < input; i++) {
			Consumer consumer = new Consumer(i,producer);
			consumers[i] = consumer;
			consumer.start();
		}
		
		return consumers;
	}
	
	//synchronized method for getting the requests from queue
	public synchronized Request getRequest(int ID){
		Request request = null;
		
		try {
			notifyAll();
			//if the queue is empty, wait
			while(count == 0){
				wait();
			}
			//else get the request
			Request tmp = queRequests.remove();
			request = tmp;
			count--;
			int length = request.length;
			Date date = new Date();
			System.out.println("Consumer "+ID+": Assigned request "+request.ID
					+ " for next " + length + " seconds. Current time is " + date.toString());
			System.out.println("====================================================\n");
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		return request;
	}

}
