#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define MAX_STACK_SIZE 1024

typedef struct Stack {
  int* ptr;
  size_t capacity;
  size_t TOP;  
} Stack;

Stack* initialiseStack (size_t len) {
  Stack* st = (Stack*) malloc(sizeof(Stack) );
  st->capacity = len;
  st->TOP = -1;
  st->ptr = (int*) calloc(len, sizeof(int) );

  return st;
}

void StackCleanup(Stack* st) {
  free(st->ptr);
  free(st);
}

void push(Stack* st, int val) {
  // Check if the Stack is Full
  if (st->TOP == st->capacity) {
    // Check if Max Capacity Already Reached
    if (st->capacity == MAX_STACK_SIZE) {
      printf("\n Cannot expand Stack any further... \n");
      return;
    }
    
    // Allocating a bigger Container to the Stack
    size_t newCapacity = min(2*st->capacity, MAX_STACK_SIZE);
    st->ptr = realloc(st->ptr, newCapacity);
    // Update Stack Capacity
    st->capacity = newCapacity;
  }
  // Increment TOP
  ++st->TOP;
  st->ptr[st->TOP] = val;  
}

int pop(Stack* st) {
  // Check if Stack Empty
  if (st->TOP == -1) {
    printf("\nCannot POP from empty Stack!! \n");
    return 0;
  }
  // Updating TOP
  st->TOP--;
  return st->ptr[st->TOP+1];
}

int peek(Stack* st) {
  // Check if Stack Empty
  if (st->TOP == -1) {
    printf("\n Stack is Empty!");
    return 0;
  }
  return st->ptr[st->TOP];
}

void printStack(Stack* st) {
  printf("\n\n Capacity : %d    TOP : %d", st->capacity, st->TOP);
  printf("\nStack Values : \n");
  for (int i = 0;i<=st->TOP;++i) {
    printf("%d ", st->ptr[i]);
  }
  printf("\n");
}

int main (int argc, char* argv[]) {
  Stack* st = initialiseStack(2);
  int choice = 1;
  int val = 0;

  while (choice != 0) {
    printf("\n\nStack Program....");
    printf("\n Press...");
    printf("\n 1 : PUSH()    2 : POP()    3 : PEEK()    4 : printStack()    0 : exit");
    printf("\nYour Choice : ");
    scanf("%d", &choice);

    switch (choice) {
      case 0 : 
      printf("\nExiting the Program!!");
      break;

      case 1 : 
      printf("\nEnter value to Push : ");
      scanf("%d", &val);
      push(st, val);
      break;

      case 2 : 
      val = pop(st);
      printf("\nValue Popped : %d", val);
      break;

      case 3 : 
      printf("\nTOP Value : %d", peek(st) );
      break;

      case 4 : 
      printStack(st);
      break;

      default : 
      printf("\nWrong Option...");
    }
  }

  // Cleanup
  StackCleanup(st);
  return 0;
}
