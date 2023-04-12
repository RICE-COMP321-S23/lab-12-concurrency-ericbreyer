# Exercises

## Concurrency

This exercise builds on the information in Section 3 of the lab page. You may
want to refer back to that section as you work on this exercise.

### Thread Concurrency Exercise #1

Modify `tiny.c` to use *thread concurrency* using Pthreads. Compile it using
"`make`".

To test your work, run `./tiny` and connect to it with a web browser as
discussed on the lab page.

**IMPORTANT:** As also discussed on the lab page, when you are done testing your
`tiny` server, be sure to **stop the execution** of your `tiny` server.

## Condition Variables

This exercise builds on the information in Section 5 of the lab page. You may
want to refer back to that section as you work on this exercise.

### Condition Variables Exercise #1

The provided source code for this exercise is located in the subdirectory
`echo-key+sor` in your repository for this lab. In particular, for this
exercise, you will use the program `echo-key`, for which the source code is
`echo-key.c`, located there. For this exercise, you should "`cd`" into this
`echo-key+sor` subdirectory.

This program reads user input characters and echoes them each back to the
screen. But it performs this simple task in a slightly complicated manner using
the *producer-consumer* paradigm. The producer thread reads each user input
character and adds it to a shared buffer. Two consumer threads each read
characters from the buffer and echo them back. Specifically, each character is
read from the buffer and echoed by exactly one of these two consumer threads. A
shared variable `cnt` keeps track of the number of characters currently in the
shared buffer.

Compile this program on CLEAR using the command: `make echo-key`

Execute the program using the command: `./echo-key` Type in some characters and
see them echoed back on the screen.

Run the command `top` from *another shell window* on the **same** CLEAR server
machine. This command shows all processes currently running on the computer,
sorted by those consuming the most CPU time. Why is your `echo-key` program
inefficient? **NOTE:** The `echo-key` program must be run as a *foreground*
process, since if it is instead run in the background, the operating system will
suspend it when it tries to read from the terminal.

Terminate the `echo-key` program now by typing a control-C.

Now modify the `echo-key` program to use a condition variable to *efficiently*
provide the needed synchronization between these threads.

Again, compile and execute the program. Do you observe the same characters being
echoed multiple times? If so, it could be due to the issue noted below in using
condition variables.

**CAVEAT:** When a thread returns from `pthread_cond_wait`, there is no
guarantee that the associated condition is still true, especially when more than
one thread is unblocked such as when using `pthread_cond_broadcast`. Thus, the
associated condition should be checked again before performing any operation
based on it, as shown in the corrected, modified code below:

#### Thread 1

```
LOCK MUTEX
/* use "while" below instead of "if" */
while (shared_val == 0)
        COND WAIT
perform task
...
...
UNLOCK MUTEX
```

#### Thread 2

```
LOCK MUTEX
...
...
shared_val = 1
COND SIGNAL
UNLOCK MUTEX
```

Fix your solution based on this caveat. Compile and execute the program. Also,
is the program more efficient now? Why?

Did your solution unconditionally (i.e., always) `pthread_cond_signal` the
condition variable? Can you optimize your solution to avoid the overhead of
unnecessary signal operations?

## Barriers

This exercise builds on the information in Section 6 of the lab page. You may
want to refer back to that section as you work on this exercise.

### Barriers Exercise #1

In the directory `echo-key+sor`, the program for Exercise #3 is `sor-pthreads`,
with provided source code in the file `sor-pthreads.c`. For this exercise, you
should "`cd`" into this `echo-key+sor` subdirectory.

This program implements an algorithm known as *Red-Black Successive
Over-Relaxation (SOR)*, which is a method for solving partial differential
equations. The algorithm iterates over all non-boundary (i.e., non-edge) squares
in a square N×N grid and, for each, updates its value to the average of the
value at each of its four direct neighbors. For example, consider the 9×9 grid
shown below:

![Red-Black Successive Over-Relaxation](https://www.clear.rice.edu/comp321/html/laboratories/lab12/Figures/rb-sor.png)

Here, the value of each square like **A** is updated as follows: value(**A**) =
(value(**B**) + value(**C**) + value(**D**) + value(**E**)) / 4. The algorithm
typically is run and is repeated until the change in the value at every square,
between the current iteration and the previous iteration, is less than some
specified threshold.

This algorithm can be parallelized by dividing responsibility for the grid into
roughly equal-sized bands of rows, and assigning each band of rows to be updated
by a different parallel thread, as indicated in the example above (for three
threads).

Specifically, the grid is treated as a checkerboard, with alternating red and
black squares. Each iteration is divided into two phases. In the first phase,
only the red squares are updated based on the values of their neighboring black
squares. Similarly, in the second phase, only the black squares are updated
based on the values of their neighboring red squares. Note that each phase can
proceed without any synchronization between the individual threads, but at the
end of each phase, all threads must synchronize.

In the provided `sor-pthreads.c` program, the algorithm is repeated only for a
fixed number of iterations. Then the program prints the final sum of all squares
in the grid.

Compile the program using the command

```
make sor-pthreads
```

Then execute the program using the command

```
./sor-pthreads -t num_threads -n num_rows_cols
```

where *num_threads* is the number of threads to use, and *num_rows_cols* is the
number of rows and columns to use (the default value for *num_threads* is 4, and
the default value for *num_rows_cols* is 2000). Is the result from running
`sor-pthreads` consistent across multiple runs? Why not?

Now add barrier synchronization to the program at appropriate places in the code
to make the threads synchronize and thus ensure that the algorithm works as it
should. Compile and execute the modified program. Is the result now consistent
across multiple runs?
