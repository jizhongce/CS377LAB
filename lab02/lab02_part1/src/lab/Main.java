package lab;

public class Main {
	public static void main(String[] args){
		Round_Robin rr = new Round_Robin();
		First_Come_First_Serve fcfs = new First_Come_First_Serve();
		
		fcfs.FCFS("Traces/100-100-6.txt","100-100-6");
		fcfs.FCFS("Traces/100-100-8.txt","100-100-8");
		fcfs.FCFS("Traces/100-100-11.txt","100-100-11");
		fcfs.FCFS("Traces/100-200-6.txt","100-200-6");
		fcfs.FCFS("Traces/100-200-8.txt","100-200-8");
		fcfs.FCFS("Traces/100-200-11.txt","100-200-11");
		fcfs.FCFS("Traces/100-600-6.txt","100-600-6");
		fcfs.FCFS("Traces/100-600-8.txt","100-600-8");
		fcfs.FCFS("Traces/100-600-11.txt","100-600-11");

		
		rr.RR("Traces/100-100-6.txt","100-100-6");
		rr.RR("Traces/100-100-8.txt","100-100-8");
		rr.RR("Traces/100-100-11.txt","100-100-11");
		rr.RR("Traces/100-200-6.txt","100-200-6");
		rr.RR("Traces/100-200-8.txt","100-200-8");
		rr.RR("Traces/100-200-11.txt","100-200-11");
		rr.RR("Traces/100-600-6.txt","100-600-6");
		rr.RR("Traces/100-600-8.txt","100-600-8");
		rr.RR("Traces/100-600-11.txt","100-600-11");
	}
}
