#include "mysem.h"

#define DEBUG 0

extern int currentThread;


void atomic_swap(volatile long long int * lock)
{
	/* This function can be used to atomically 
 	 * swap a value in %r14 to variable lock.
 	 */

	   __asm__ __volatile__(
			"LOCK: xorq %r14, %r14;"
			"xchg %r14,(%rdi);"
			"andq %r14,%r14;"
			"jz LOCK;");

}

int mysem_init(mysem_t * mysem, int val) {
	/* This function initializes the semaphore.  mysem_t is defined in
	 * mysem.h. It returns 1 if the provided semaphore, mysem is valid.
	 * 0 if the semaphore value is NULL.  It has a fixed size queue
	 * (Q[THREADS]) to hold the thread id of each blocked thread.  Each
	 * element of Q is initialized to 1. Variable lock is used to
	 * create atomicity for all semaphore operations (mysem_post,
	 * mysem_wait).
	 */
	int i;
	if (mysem != NULL){
		mysem->val = val;
		mysem->lock = 1;
		mysem->blkThreads = 0;
		for (i = 0; i < THREADS; i++)
			mysem->Q[i] = -1;
		return 1;
	}
	else
		return 0;
}


void mysem_wait(mysem_t * mysem)
{
	/* Need to first atomically move the value from mysem struct to a
	 * register. Then check if the value is equal to 1. If it is, simply
	 * decrement and store 0 back. If it is equal to zero, we
	 * need to suspend the thread and keep the value at 0. It then need
	 * to call the signal handler to start a new thread. When it is
	 * awaken later by mysem_post, it should try to reenter the
	 * critical section. Otherwise, we can have race. 
	 * I'm also providing an example on how to use conditional compiler
	 * to add debug information. Note that DEBUG is defined at the top
	 * of this file with the value of 0. If you change DEBUG to 1, the
	 * debug statements will print.
	 * */

#if DEBUG == 1
		printf("Blocking Thread %d (val = %d)\n", currentThread, mysem->val);
#endif
		// your implementation must satisfy the assertion below.
		assert(mysem->val >= 0);
}

void mysem_post(mysem_t * mysem)
{
	/* Need to first atomically move the value from mysem struct to a
	 * register. Then check if the value is 0 and there is at least one
	 * blocked thread. If there is, increment the
	 * value to 1 and wake up a thread. If the value is not 0 or no
	 * blocked threads, just increment the value by 1. The
	 * implementation should support both counting and binary
	 * semaphores.*/ 
#if DEBUG == 1
		printf("Wake up thread %d.\n", tid);
#endif
		// your implementation must satisfy the assertion below.
		// For this example, the mysem->val should not exceed 1
		// since the semaphore is simply providing mutual exclusion.
		// In general, mysem->val can be greater than 1 when it is use
		// as a counting sempahor.
		assert(mysem->val <= 1);
}

int mysem_value(mysem_t * mysem)
{
	/* This function simply returns the semaphore value. */
	return mysem->val;
}
