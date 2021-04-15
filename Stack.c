< 스택 (LIFO) >

1. 전역변수로 스택 구현
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

// 전역 변수로 배열, top(index) 구현
typedef int element;							// element : int
element stack[MAX_STACK_SIZE];
int top = -1;									// top : 0번째부터 시작


:: Check if stack in empty 
int is_empty() {								// Q1) why not elemet? wht int?
	return (top == -1);
}


:: Check if stack is full
int is_full() {
	return (top == (MAX_STACK_SIZE - 1));
}


:: Insert data in stack
void push(element item) {
	if (is_full()) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else stack[++top] = item;                     // After increase top(index value) -> item insert
}


:: Delete data in stack
element pop() {
	if (is_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return stack[top--];                     // After delete data in stack -> top(index value) decrease
}


:: See datas in stack(!= pop(), delete data X)
element peak() {
	if (is_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
	}
  else return stack[top];
}

int main(void) {
	push(1);
	push(2);
	push(3);
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	return 0;
}




2. 구조체로 스택 정의(매개변수 X)
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_STRING 100

// element 구조체 선언
typedef struct {
	int student_no;						// variables
	char name[MAX_STRING];
	char address[MAX_STRING];
}element;

element stack[MAX_STACK_SIZE];
int top = -1;							// Index(top++, if adding data in stack), top : stack's top index(start from 0)


// Check if stack is empty
int is_empty() {
	return (top == -1);
}

// Check if stack is full
int is_full() {
	return (top == (MAX_STACK_SIZE - 1));		// 
}

// Adding data in stack
void push(element item) {
	if (is_full()) {							// If stack is full, data can't add in stack(overflow)
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else stack[++top] = item;					// else : add data in stack & top++
}

// return top data in stack & delete
element pop() {
	if (is_empty()) {							// if stack is empty, pop().me can't delete data in stack
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);								// error
	}
	else
		return stack[top--];
}

// peek().me
// return top data in stack(diff with pop().me)
element peek() {								
	if (is_empty()) {							// Check if stack is empty
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);								// error
	}
	else return stack[top];						// return top data of stack without delete
}


// main method
int main(void) {
	element ie = { 20010926, "Kwon", "Seoul" };			// Declare stack variable
	element oe;											//			''

	push(ie);		// Add dada(ie) in stack
	oe = pop();		// return top data of stack & delete data in stack

	printf("학번: %d\n", oe.student_no);
	printf("이름: %s\n", oe.name);
	printf("주소: %s\n", oe.address);

	return 0;
}





3. 구조체로 스택 정의(매개변수 O)
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == MAX_STACK_SIZE - 1);
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
		//exit(1);
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

int main(void) {
	StackType s;

	init_stack(&s);
	push(&s, 1); push(&s, 2); push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
}




4. 동적 배열 프로그램
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element;				// element : int
typedef struct {					// Declare StackType structure
	element* data;					// variables
	int capacity;					// Define stack's size
	int top;
}StackType;

// -> : 구조체 포인터 이름 -> 멤버 이름(== (*구조체 포인터 이름).멤버이름)
// Create stack method(init().me)
void init_stack(StackType* s){
	s->top = -1;
	s->capacity = 1;            // stack's 1st size
	s->data = (element*)malloc(s->capacity * sizeof(element));					// 동적 메모리 할당(s->capacity * sizeof * sizeof(element) :: 반환되는 주소 type : element
}

// is_empty method
int is_empty(StackType * s) {
	return (s->top == -1);
}

// is_full method
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

// push method
void push(StackType* s, element item) {
	// if stack is full with data -> make more space (* 2)
	if (is_full(s)) {
		s->capacity *= 2;
		s->data = (element*)realloc(s->data, s->capacity * sizeof(element));			// realloc : make more space
	}
	s->data[++(s->top)] = item;					// Add new data :: top++ & push item(new data)
	printf("%d\n", s->data[s->top]);
}

// pop method
element pop(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else {
		int return_value = s->data[s->top];		// Delete data(that index is top)
		s->top--;
		return return_value;
	}
}


// main method
int main(void)
{
	StackType s;			// Declare structure(StackType) variable : s
	init_stack(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	free(&s);				// make free from Dynamic Allocation
}



5. 괄호 검사 코드
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}
int is_empty(StackType* s) {
	return (s->top == -1);
}
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

// check bracket is match
int check_matching(const char* in) {
	StackType s;
	char ch, open_ch;
	int i, n = strlen(in);
	init_stack(&s);

	for (i = 0; i < n; i++) {
		ch = in[i];
		// use switch to find bracket
		switch (ch) {
		case '(': case '[': case '{':
			push(&s, ch);
			break;
		case ')': case']': case '}':
			if (is_empty(&s)) 
				return 0;
			else {
				open_ch = pop(&s);
				if((open_ch == '(' && ch != ')') ||
					(open_ch == '[' && ch != ']') ||
					(open_ch == '{' && ch != '}')) {
					return 0;
				}
				break;
			}
		}
	}
	if (!is_empty(&s)) return 0;
	return 1;
}

int main(void) {
	char* p = "{ A[(i+1)]=0}";
	if (check_matching(p) == 1)
		printf("%s 괄호검사성공\n", p);
	else
		printf("%s 괄호검사실패\n", p);
	return 0;
}






6. 후위표기식 계산
// 후위표기식 계산
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == MAX_STACK_SIZE - 1);
}

void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		return s->data[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
	}
	else
		return s->data[s->top];
}

int eval(char exp[]) {
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;        // create stack s

	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';
			push(&s, value);
		}
		else {
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) {
			case '+':	push(&s, op1 + op2);	break;
			case '-':	push(&s, op1 - op2);	break;
			case '*':	push(&s, op1 * op2);	break;
			case '/':	push(&s, op1 / op2);	break;
			}
		}
	}
	return pop(&s);
}

int main(void) {
	int result;
	printf("후위표기식은 82/3-32*+\n");
	result = eval("82/3-32*+");
	printf("결과값은 %d\n", result);

	return 0;
}

