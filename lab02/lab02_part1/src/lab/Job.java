package lab;

public class Job {

	private int total,left,CompletionTime,arrvialTime;

	//This is the Job class, which takes two parameters,
	//total, the legnth of the job
	//arrivalTime, the arrive time of the job
	//attribute left is the time left till completion
	//attribute CompletionTime is time that job finishes
	public Job(int total,int arrvialTime){
		this.total=total;
		left = total;
		this.arrvialTime = arrvialTime;
		CompletionTime = 0;
	}

	//This method simulates the processing of a job by simply minus 
	//the time left by one
	public void processing(){
		left--;
	}

	//return the total of a job
	public int getTotal(){
		return total;
	}

	//return the left of a job
	public int getLeft(){
		return left;
	}
	
	//set the completionTime of a job
	public void CompletionTime(int time){
		this.CompletionTime = time;
	}

	//return the completionTIme of a job
	public int getCompletionTime(){
		return this.CompletionTime;
	}

	//return the arrivalTime of a job
	public int getArrvialTime(){
		return arrvialTime;
	}
	
	
}
