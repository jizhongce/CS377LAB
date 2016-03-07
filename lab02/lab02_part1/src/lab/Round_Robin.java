package lab;

import java.io.*;
import java.util.*;



public class Round_Robin {
	
	
	public void RR(String path, String fileName){
		int compeleted_jobs = 0;
		
		
		try {
			Scanner scanner = new Scanner(new File(path));
			int Job_Number = scanner.nextInt();
			int Simulation_Time = scanner.nextInt();
			int Max_length = scanner.nextInt();
			
			Job[] jobs = new Job[Job_Number];
			int count = 0;
			while (scanner.hasNext()) {
				int a = scanner.nextInt();
				int b = scanner.nextInt();
				Job newJob = new Job(b, a);
				jobs[count] = newJob;
				count++;
			}
			
			
			Queue<Job> readyQueue = new LinkedList<Job>();
			
			int first_arrival = jobs[0].getArrvialTime();
			
			if(first_arrival == 0){
				//add jobs with initial arrival time
				for (int i = 0; i < jobs.length; i++) {
					if(jobs[i].getArrvialTime() == first_arrival){
						readyQueue.add(jobs[i]);
					}
				}				
			}

			
			
			
			//actual processing
			int running_time = 0;
			
			while(running_time <= Simulation_Time){
				
				if(!readyQueue.isEmpty()){
					Job tmp = readyQueue.remove();
					running_time++;
					tmp.processing();
					
					
					for (int i = 0; i < jobs.length; i++) {
						if(jobs[i].getArrvialTime() == running_time){
							readyQueue.add(jobs[i]);
						}
					}
					//System.out.println(tmp.getTotal());
					//check if job is completed
					if(tmp.getLeft() == 0){
						tmp.CompletionTime(running_time);
						compeleted_jobs++;
						continue;
					}
					
					
					readyQueue.add(tmp);	
				}
				else{
					running_time++;
					//add arrival jobs to readyQueue
					for (int i = 0; i < jobs.length; i++) {
						if(jobs[i].getArrvialTime() == running_time){
							readyQueue.add(jobs[i]);
						}				
					}
				}
			}//while END
			
			
			int total_wating_time = 0;
			for (int i = 0; i < Job_Number; i++) {
				if(jobs[i].getCompletionTime() == 0){
					continue;
				}
				total_wating_time += (jobs[i].getCompletionTime() - jobs[i].getArrvialTime() - jobs[i].getTotal());
			}
			int average_waiting_time = (int)total_wating_time/compeleted_jobs;
			
			System.out.println("RR " + fileName + ": " + average_waiting_time);
			
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
