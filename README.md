# PHILOSOPHERS

Dining philosophers problem is a problem created by Edsger Wybe Dijkstra in 1965 to explain the deadlock state of an operating system, which is traditionally commonly introduced in lectures on operating systems

## Note

The `philo` folder contains the project so that each philosopher checks his own death and also if there is one that has died, this causes there to be more mutex in the program which can cause them to die more easily, however with tests like ./philo 3 310 103 103 works correctly.

The `philo2` folder contains the same code but modified so that the main thread of the program is the one who checks for the death of the philosophers, greatly reducing the amount of mutex.
