# Coen346

We may use semaphores for wait(), etc. 
One process at a time.
Use threads.

To do list / additional notes:

- Sorting algorithm for both active and expired queues (bubble sort) depending on priority (increasing order)

- Time quantum (Tq) function using the equations 

- Priority update function, when process having been granted 2 successive time quanta

- When process arrives, insert from the PID vector to the expired queue vector

- Function that checks which which queue is active
	- When queue flagged as active is empty, change flags of both queues and start execution for new active queue.
	- return type is a vector

- execution of processes in the main

- output file
	If-else:
	- Started, paused, arrived, resumed and terminated.
	- paused if process not completed when (burst time - time quanta) != 0.
	- when new process arrives, resume previous process for time quanta and change its priority and pause it
	- Terminated when (burst time - time quanta) == 0.