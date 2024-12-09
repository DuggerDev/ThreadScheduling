/* myThread.h */

#include <unistd.h>
#include <ucontext.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>
#include "mysem.h"

void cleanup(void);
void task1(int);
void task2(int);
void signalHandler(int signal);
