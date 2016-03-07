package lab;

import java.io.*;
import java.util.*;



public class First_Come_First_Serve {
	@SuppressWarnings("resource")
	public void FCFS(String path, String fileName){
		int curr_time = 0;
		
		
		
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
			while(curr_time <=Simulation_Time){
				
				if(!readyQueue.isEmpty()){
					Job tmp = readyQueue.remove();
					while(tmp.getLeft()!=0){
						tmp.processing();
						curr_time++;
						
						//add arrival jobs to readyQueue
						for (int i = 0; i < jobs.length; i++) {
							if(jobs[i].getArrvialTime() == curr_time){
								readyQueue.add(jobs[i]);
							}				
						}
							
					}
		
					tmp.CompletionTime(curr_time);
					
				}
				//if waiting for jobs come
				else{
					curr_time++;
					//add arrival jobs to readyQueue
					for (int i = 0; i < jobs.length; i++) {
						if(jobs[i].getArrvialTime() == curr_time){
							readyQueue.add(jobs[i]);
						}				
					}
				}
					
			}
			

			
			int total_wating_time = 0;
			int tmp =Job_Number-1;
			for (int i = 0; i < Job_Number; i++) {
				
				if(jobs[i].getCompletionTime() == 0){
					tmp = i;
					break;
				}
				total_wating_time += (jobs[i].getCompletionTime() - jobs[i].getArrvialTime() - jobs[i].getTotal());
			}
			
			int average_waiting_time = total_wating_time/(tmp+1);
			
			System.out.println("FCFS " + fileName + ": " + average_waiting_time);
			
			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
