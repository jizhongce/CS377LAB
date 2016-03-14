compile: javac lab/*.java

run: java lab/Main

Team Member:
shengbo lou: 28530995
zhongce ji: 28551884
yucheng lu: 28411887

    We use the java language to complete the first part of the lab2.
    We are requested to implement Round_Robin and First_Come_First_Serve scheduling
    to schedule the input the jobs.

  Job.java: This file have a class which is called Job this class have constructor
    which will take 2 arguments, one is total which is total execution time of the job
    the other one is the arrvialTime which is the arrive time of the job.

    There are 4 variables:
      total: int, this is the total execution time of the job, it will be initialized in
            constructor
      left: int, this represents how many time the job still needed to be executed
            it will be initialized as total time in constructor
      CompletionTime: int, this represents the time the job is completed,it will be
            initialized as 0 in constructor
      arrvialTime: int, this represents the time the job is arrived, it will be
            initialized in constructor

    Also there are some method inside this class:
      processing(): This method means process the job and the left time will decrement
                    by one.
      getTotal(): This method will return the total time of the Job.
      getLeft(): This method will return left which means how many time the job left to be executed.
      CompletionTime(): This method will set the job's CompletionTime as the time that
            the job is completed.
      getCompletionTime(): This method will return the CompletionTime which represents the time
            the job is completed.
      getArrvialTime(): This method will return the arrive time of the job.


  Round_Robin.java: This file will implement the Round_Robin Scheduler. For the Round_Robin
      we assume the process time is 1. So every job will work 1 time and it will be put into
      a readyQueue. Then we continue to do this until the Simulation_Time. We have some
      variables:
      compeleted_jobs: int, this will record how many jobs have been completed.
      readyQueue: Queue<Job>, this will store jobs that need to be waited.
      first_arrival: int, this will record the first jobs' arrive time.
      running_time: int, this will record the running time.

      First we use scanner to get the data from the file. And then get first three ints, Then
      use loop to get each jobs arrive time and execution time then create the jobs and put them
      into a job array. Then we take the first job's arrive time, then we check if the first job's
      arrive time is 0 then we will add jobs whose arrive time is 0 into the readyQueue. After that
      we have a while loop, it will continue run until the running time reach the Simulation_Time. In
      the while loop, if the readyQueue is not empty, we first remove a first jobs in the queue and
      process it, add the running time. Then we have to check at this time, if we have jobs whose arrive
      time is same as the running time, which means at this time those jobs need to be arrived so we add
      them into the readyQueue. Then we check that if the job's left time is 0 which means that the job is
      completed so we have to set the job's complication time as the current running_time, and we do not
      need to put the job back to the readyQueue. If the job is not complicated then we need to put the job
      back into the end of the readyQueue. Then if the readyQueue is empty, we need to add the jobs whose
      arrive time is current running time into the readyQueue. Then after we jump out of the while loop,
      we just use the for loop to print out all jobs waiting time and use the equation:
      total waiting = complication time - arrive time - execution time.

  First_Come_First_Serve.java: This file will implement the First_Come_First_Serve Scheduler. For the
      First_Come_First_Serve, it will be simple then the Round_Robin, because First_Come_First_Serve Scheduler,
      it will execute the job who comes first. First we have some variables:
      curr_time: int , this will record the current running time.
      readyQueue: Queue<Job>, this will store the jobs that need to be executed.

      It will be the same for the Round_Robin. Then there will be some different in the while loop. In the
      while loop, first we check if the readyQueue is not empty, we will remove the first job and use another
      while loop to execute it until it is completed. So in the second while loop, we will add up the running time,
      So we have to check if at the current time do we have other jobs arrive, if we have we have to add them into
      the readyQueue. Then we set the job's complication time as current time and do not put it back into the readyQueue,
      If the readyQueue is empty, we have to add up the current time and add the jobs into the ready queue if the
      jobs' arrive time is current time.

  Main.java: In this file we will print out the whole result of the lab2 In the main class,
  we create Round_Robin object and print out the result of the input with Round_Robin Schedule.
  Also we create First_Come_First_Serve object and print out the result of the input with
  First_Come_First_Serve Schedule.
