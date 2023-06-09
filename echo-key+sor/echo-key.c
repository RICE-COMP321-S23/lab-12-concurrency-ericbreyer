/*
 * Echo key - using producer-consumer paradigm.
 */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "csapp.h"

#define NITEMS 10 /* Number of items in shared buffer. */

/* Shared variables. */
char shared_buffer[NITEMS]; /* Echo buffer. */
int shared_cnt;             /* Item count. */

pthread_mutex_t mutex;     /* pthread mutex. */
pthread_cond_t cond_empty; /* pthread cond variable to wait on empty buffer. */
pthread_cond_t cond_full;  /* pthread cond variable to wait on full buffer. */
unsigned int prod_index = 0; /* Producer index into shared buffer. */
unsigned int cons_index = 0; /* Consumer index into shard buffer. */

void *producer(void *arg);
void *consumer(void *arg);

int
main(void)
{
        pthread_t prod_tid, cons_tid1, cons_tid2;

        /* Initialize pthread variables. */
        Pthread_mutex_init(&mutex, NULL);

        /* INITIALIZE THE CONDITION VARIABLES HERE. */
        pthread_cond_init(&cond_empty, NULL);
        pthread_cond_init(&cond_full, NULL);
        /* FILL ME IN. */

        /* Start producer thread. */
        Pthread_create(&prod_tid, NULL, producer, NULL);

        /* Start consumer threads. */
        Pthread_create(&cons_tid1, NULL, consumer, NULL);
        Pthread_create(&cons_tid2, NULL, consumer, NULL);

        /* Wait for threads to finish. */
        Pthread_join(prod_tid, NULL);
        Pthread_join(cons_tid1, NULL);
        Pthread_join(cons_tid2, NULL);

        /* Clean up. */
        Pthread_mutex_destroy(&mutex);

        /* DESTROY THE CONDITION VARIABLES HERE. */
        pthread_cond_destroy(&cond_empty);
        pthread_cond_destroy(&cond_full);
        /* FILL ME IN. */

        return (0);
}

/* Producer thread executes this function. */
void *
producer(void *arg)
{
        char key;

        /* Cast to eliminate warnings. */
        (void)arg;

        while (true) {

                /* Read input key. */
                scanf("%c", &key);

                /* MODIFY THE CODE BELOW TO WAIT ON APPROPRIATE CONDITION
                 * VARIABLE. */
                /* FILL ME IN. */

                /* Acquire mutex lock. */
                Pthread_mutex_lock(&mutex);

                /* If buffer is full, release mutex lock and check again. */
                while (shared_cnt == NITEMS)
                        pthread_cond_wait(&cond_full, &mutex);

                /* Store key in shared buffer. */
                shared_buffer[prod_index] = key;

                /* SIGNAL THE APPROPRIATE CONDITION VARIABLE HERE. */
				if(shared_cnt == 0) {
				pthread_cond_broadcast(&cond_empty);
				}
                /* FILL ME IN. */

                /* Update shared count variable. */
                shared_cnt++;

                /* Update producer index. */
                if (prod_index == NITEMS - 1)
                        prod_index = 0;
                else
                        prod_index++;

                /* Release mutex lock. */
                Pthread_mutex_unlock(&mutex);
        }
        return (NULL);
}

/* Consumer thread executes this function. */
void *
consumer(void *arg)
{
        char key;
        int id = (int)Pthread_self();

        /* Cast to eliminate warnings. */
        (void)arg;

        while (true) {

                /* MODIFY THE CODE BELOW TO WAIT ON APPROPRIATE CONDITION
                 * VARIABLE. */
                /* FILL ME IN. */

                /* Acquire mutex lock. */
                Pthread_mutex_lock(&mutex);

                /* If buffer is empty, release mutex lock and check again. */
                while (shared_cnt == 0)
                        pthread_cond_wait(&cond_empty, &mutex);

                /* Read key from shared buffer. */
                key = shared_buffer[cons_index];

                /* Echo key. */
                printf("consumer %d %c\n", id, key);

                /* SIGNAL THE APPROPRIATE CONDITION VARIABLE HERE. */
				if(shared_cnt == NITEMS) {
					pthread_cond_broadcast(&cond_full);
				}
                /* FILL ME IN. */

                /* Update shared count variable. */
                shared_cnt--;

                /* Update consumer index. */
                if (cons_index == NITEMS - 1)
                        cons_index = 0;
                else
                        cons_index++;

                /* Release mutex lock. */
                Pthread_mutex_unlock(&mutex);
        }
        return (NULL);
}
