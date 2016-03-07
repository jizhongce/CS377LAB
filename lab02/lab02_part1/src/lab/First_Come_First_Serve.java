package lab;

import java.io.*;
import java.util.*;

//This class is a simulation of the First_Come_First_Serve scheluder
public class First_Come_First_Serve {

	public void FCFS(String path, String fileName){

		//curr_time is the simulation of the local current time
		int curr_time = 0;

		try {

			//initialize a scanner to scan the input file
			Scanner scanner = new Scanner(new File(path));

			//the first line of input file is number of lines
			int Job_Number = scanner.nextInt();

			//the second line of input file is total running time of simulaiton
			int Simulation_Time = scanner.nextInt();

			int Max_length = scanner.nextInt();
			
			//initialize a list of jobs with their attributes
			Job[] jobs = new Job[Job_Number];
			int count = 0;
			while (scanner.hasNext()) {
				int a = scanner.nextInt();
				int b = scanner.nextInt();
				Job newJob = new Job(b, a);
				jobs[count] = newJob;
				count++;
			}
			
			
			//initialize a readyQueue for jobs that are ready to be executed
			Queue<Job> readyQueue = new LinkedList<>();
			
			//if the first job does not arrive at 0, then the scheduler will wait
			//for the first job
			int first_arrival = jobs[0].getArrvialTime();

			if(first_arrival == 0){
				//add jobs with initial arrival time
				for (Job job : jobs)
					if (job.getArrvialTime() == first_arrival)
						readyQueue.add(job);
			}

			//This while loop represents the actual simulation of the scheduler
			//Jobs will be executing till the total simulation time
			while(curr_time <=Simulation_Time){
				
				if(!readyQueue.isEmpty()){
					Job tmp = readyQueue.remove();
					while(tmp.getLeft()!=0){
						tmp.processing();
						curr_time++;
						
						//add arrival jobs to readyQueue
						for (Job job : jobs)
							if (job.getArrvialTime() == curr_time) {
								readyQueue.add(job);
							}
							
					}
					//When a job finishes, it will update its CompletionTime attribute
					//to current time
					tmp.CompletionTime(curr_time);
				}

				//if the readyqueue is empty, and total simulation time is
				//not readched, waiting for jobs come
				else{
					curr_time++;
					//add arrival jobs to readyQueue
					for (Job job : jobs) {
						if (job.getArrvialTime() == curr_time) {
							readyQueue.add(job);
						}
					}
				}
					
			}
			
			//initializs the total waiting time for all jobs
			int total_waiting_time = 0;
			int tmp =Job_Number-1;

			//If any job is completed, stop that job and calculate the waiting time of that job
			for (int i = 0; i < Job_Number; i++) {
				if(jobs[i].getCompletionTime() == 0){
					tmp = i;
					break;
				}
				// calculating the total waiting time for all jobs
				total_waiting_time += (jobs[i].getCompletionTime() - jobs[i].getArrvialTime() - jobs[i].getTotal());
			}
			
			//calculating the average waiting time
			int average_waiting_time = total_waiting_time/(tmp+1);

			//print the output
			System.out.println("FCFS " + fileName + ": " + average_waiting_time);
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}