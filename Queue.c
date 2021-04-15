// 선형 큐
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
	int front;							// Queue's first elemenet's index
	int rear;							// Queue's last element's index
	element data[MAX_QUEUE_SIZE];		// new data's storage
} QueueType;

// Error method
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// Reset method
void init_queue(QueueType* q) {
	q->rear = -1;
	q->front = -1;
}

// print queue method
void queue_print(QueueType* q) {
	for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
		if (i <= q->front || i > q->rear)
			printf("    |");
		else
			printf(" %d |", q->data[i]);
	}
	printf("\n");
}

// Check if Queue's data is full
int is_full(QueueType* q)
{
	if (q->rear == MAX_QUEUE_SIZE - 1)
		return 1;
	else
		return 0;
}

// Check if Queue's data is empty
int is_empty(QueueType* q) {
	if (q->front == q->rear)
		return 1;
	else
		return 0;
}

// Insert new data in Queue
void enqueue(QueueType* q, int item) {
	if (is_full(q)) {
		error("큐가 포화상태입니다.");
		return;
	}
	q->data[++(q->rear)] = item;
}

// Delete data in Queue
int dequeue(QueueType* q) {
	if (is_empty(q)) {
		error("큐가 공백상태입니다.");
		return -1;
	}
	int item = q->data[++(q->front)];
	return item;
}

 
// main method
int main(void) {
	int item = 0;		// Put data that Dequeue in item variable
	QueueType q;

	init_queue(&q);		// Reset Queue

	// Insert new data & print Queue
	enqueue(&q, 10); queue_print(&q);
	enqueue(&q, 20); queue_print(&q);
	enqueue(&q, 30); queue_print(&q);
	enqueue(&q, 40); queue_print(&q);


	// Delete data in Queue & put it in item.va & print Queue
	item = dequeue(&q); queue_print(&q);
	item = dequeue(&q); queue_print(&q);
	item = dequeue(&q); queue_print(&q);
	item = dequeue(&q); queue_print(&q);


	return 0;
}






// 원형 큐
#include <stdio.h> 
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;							// element = int
typedef struct {				
	element data[MAX_QUEUE_SIZE];				// Queue's storage
	int front, rear;							// front : queue's start part, rear : queue;s end part
} QueueType;

// error message method
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// Reser Queue's data
void init_queue(QueueType* q) {
	// 선형 큐와 다른 점
	q->front = 0;
	q->rear = 0;
}

// Check if queue is empty(front value == rear value -> queue is empty)
int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

// Check if queue is full(front value == (rear value) % MAX_QUEUE_SIZE + 1 -> queue is full)
int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);							// q->rear + 1 : empty, full을 구분하기 위해서 1자리 비워둔다. -> 선형 큐와 다른 점
}

// print queue's data
void queue_print(QueueType* q) {
	printf("QUEUE(front = %d rear = %d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);						// while문의 조건이 처음부터 성립하지않으므로 do-while 사용
	}
	printf("\n");
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[(q->front) % MAX_QUEUE_SIZE];
}

element peek(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}


int main(void) {
	QueueType queue;
	int element;

	init_queue(&queue);
	printf("--데이터 추가 단계--\n");
	while (!is_full(&queue)) {
		printf("정수를 입력하시오: ");
		scanf_s("%d", &element);
		enqueue(&queue, element);
		queue_print(&queue);
	}
	printf("큐는 포화상태입니다.\n\n");

	printf("--데이터 삭제 단계--\n");
	while (!is_empty(&queue)) {
		element = dequeue(&queue);
		printf("꺼내진 정수: %d \n", element);
		queue_print(&queue);
	}
	printf("큐는 공백상태입니다.\n");

	return 0;
}






// 버퍼(큐 응용(
#include <stdio.h> 
#include <stdlib.h>
//#include <time.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {				
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) {
	q->front = 0;
	q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void queue_print(QueueType* q) {
	printf("QUEUE(front = %d rear = %d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[(q->front) % MAX_QUEUE_SIZE];
}

element peek(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}


int main(void)
{
	QueueType queue;
	int element;

	init_queue(&queue);
	srand(time(NULL));

	for (int i = 0; i < 100; i++) {
		if (rand() % 5 == 0) {
			enqueue(&queue, rand() % 100);
		}
		queue_print(&queue);

		if (rand() % 10 == 0) {
			int data = dequeue(&queue);
		}
		queue_print(&queue);
	}
	return 0;
}
