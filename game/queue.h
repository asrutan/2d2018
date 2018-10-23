// queue.h
// Alex Rutan
// 10/18/18

#ifndef QUEUE_EXIST
#define QUEUE_EXIST

#define QUEUE_LENGTH 255

class Queue{

private:
	struct Method {
		int id;
		float startTime;
		unsigned int delay;
		unsigned int timeCalled;
		bool repeat;
		int timesToRepeat;
		int repeatCount = 1;
	};

	int queueLength = QUEUE_LENGTH;
	Method* queue[QUEUE_LENGTH];
	int methodAmount = 0;
	unsigned int *time;

public:
	Queue();
	//Queue(unsigned int *);
	~Queue();
	void SetTimePtr(unsigned int *);
	void Push(int method, unsigned int delay, bool repeat, int times);
	int Execute();

}; //end Queue

#endif //QUEUE_EXISTS

