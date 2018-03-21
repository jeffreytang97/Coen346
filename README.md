# Coen346

We may use semaphores for wait(), etc. 
One process at a time.
Use threads.

To do list / additional notes:

- [ ] Sorting algorithm for both active and expired queues (bubble sort) depending on priority (increasing order) -- Jeff
	-Sort the PIDVector so when we insert in the queues, we inserted from the back so it is sorted

- [x] Time quantum (Tq) function using the equations -- Hong 

- [x] Priority update function, when process having been granted 2 successive time quanta -- Hong

- [ ] Insert process from PIDVector in queues function -- Hong

- [ ] Function that checks which which queue is active -- Jeff
	- When queue flagged as active is empty, change flags of both queues and start execution for new active queue.
	- return type is a vector

- [ ] Convert input files reading to function -- Jeff

- [ ] execution of processes in the main

- [ ] scheduler and addToQueue function

- [ ] output file
	If-else:
	- Started, paused, arrived, resumed and terminated.
	- paused if process not completed when (burst time - time quanta) != 0.
	- when new process arrives, resume previous process for time quanta and change its priority and pause it
	- Terminated when (burst time - time quanta) == 0.
