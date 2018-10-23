//queue.cpp
//Alex Rutan / PA
//11/22/15

#include <iostream>
#include "queue.h"

using namespace std;

Queue::Queue() {
	for (int i = 0; i < queueLength; i++) {
		queue[i] = NULL;
	}
}//end constructor

Queue::~Queue() {
}
//end deconstructor

void Queue::SetTimePtr(unsigned int * Time) {
	time = Time;
}

int Queue::Execute() {
	bool keepGoing = true;
	int i = 0;
	while (keepGoing) {
		if (queue[i] != NULL) {
			if (*time - queue[i]->timeCalled >= queue[i]->delay) {

				int id = queue[i]->id;

				queue[i]->repeatCount++;

				//Change time called to now in case repeat and delays.
				queue[i]->timeCalled = *time;

				if (!queue[i]->repeat) {
					queue[i] = NULL;
					methodAmount--;
				}
				else if (queue[i]->timesToRepeat <= queue[i]->repeatCount) {
					queue[i]->repeat = false;
				}
				return(id);
			}
		}

		else if (i > methodAmount) {
			keepGoing = false;
		}

		i++;
	}
	return 0;
}

void Queue::Push(int method, unsigned int delay, bool repeat, int times) {
	bool keepGoing = true;
	int i = 0;
	while (keepGoing) {
		if (queue[i] == NULL) {
			queue[i] = new Method();
			queue[i]->id = method;
			queue[i]->delay = delay;
			queue[i]->timeCalled = *time;
			queue[i]->repeat = repeat;
			queue[i]->timesToRepeat = times;
			methodAmount++;
			keepGoing = false;
		}
		i++;
	}
}