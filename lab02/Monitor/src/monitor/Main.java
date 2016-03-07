package monitor;


/***
 * 
 * @author shengbo lou zhongce ji yucheng lu 
 *
 *	Main class
 */
public class Main {
	
	public static void main(String[] args){
		// 10 max requests in the queue, 1 second waiting time, 20 max requests in total
		Producer producer = new Producer(10,1000,20);
		producer.start();
		// 5 consumers
		producer.consumer(5, producer);
	}
	
}
