package lab;

import java.io.*;
import java.util.*;

//This class is a simulation of the Round_Robin scheluder
public class Round_Robin {
	
	//This is themain function of RR scheduler, which takes
	//@param path, is the input file path
	//@fileName is the fileName of the input file
	public void RR(String path, String fileName){
		
		//compeleted_jobs is the count of compeleted jobs
		int compeleted_jobs = 0;
		
		try {

			//initialize a scanner to scan the input file
			Scanner scanner = new Scanner(new File(path));

			//the first line of input file is number of lines
			int Job_Number = scanner.nextInt();

			//the second line of input file is total running time of simulaiton
			int Simulation_Time = scanner.nextInt();

			//the max length of a single job
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
			Queue<Job> readyQueue = new LinkedList<Job>();

			//if the first job does not arrive at 0, then the scheduler will wait
			//for the first job
			int first_arrival = jobs[0].getArrvialTime();
			
			if(first_arrival == 0){
				//add jobs with initial arrival time
				for (int i = 0; i < jobs.length; i++) {
					if(jobs[i].getArrvialTime() == first_arrival){
						readyQueue.add(jobs[i]);
					}
				}				
			}

			//The simulation of the processing start here
			int running_time = 0;
			
			//This while loop represents the actual simulation of the scheduler
			//Jobs will be executing till the total simulation time
			while(running_time <= Simulation_Time){
				
				//if the queue is not empty, a job will be reomved from the queue
				if(!readyQueue.isEmpty()){
					Job tmp = readyQueue.remove();
					running_time++;
					tmp.processing();
					
					//add arrival jobs to the readyqueue
					for (int i = 0; i < jobs.length; i++) {
						if(jobs[i].getArrvialTime() == running_time){
							readyQueue.add(jobs[i]);
						}
					}
					
					//check if job is completed
					if(tmp.getLeft() == 0){
						tmp.CompletionTime(running_time);
						compeleted_jobs++;
						continue;
					}
					
					//if the job is not completed, add it back the ready queue
					readyQueue.add(tmp);	
				}

				//if the readyqueue is empty, and total simulation time is
				//not readched, waiting for jobs come
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
			
			//initializs the total waiting time for all jobs
			int total_wating_time = 0;

			//calculate the waiting time of all the jobs
			for (int i = 0; i < Job_Number; i++) {
				if(jobs[i].getCompletionTime() == 0){
					continue;
				}
				//get the total waiting time
				total_wating_time += (jobs[i].getCompletionTime() - jobs[i].getArrvialTime() - jobs[i].getTotal());
			}

			//calculating the average waiting time
			int average_waiting_time = (int)total_wating_time/compeleted_jobs;
			
			//print the output
			System.out.println("RR " + fileName + ": " + average_waiting_time);
			
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
