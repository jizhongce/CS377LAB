package lab;

public class Job {
	private int total,left,CompletionTime,arrvialTime;
	public Job(int total,int arrvialTime){
		this.total=total;
		left = total;
		this.arrvialTime = arrvialTime;
		CompletionTime = 0;
	}
	public void processing(){
		left--;
	}
	public int getTotal(){
		return total;
	}
	public int getLeft(){
		return left;
	}
	
	public void CompletionTime(int time){
		this.CompletionTime = time;
	}
	public int getCompletionTime(){
		return this.CompletionTime;
	}
	public int getArrvialTime(){
		return arrvialTime;
	}
	
	
}
