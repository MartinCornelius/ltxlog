#include <string.h>

#define FILESTACK_SIZE 64

char file_stack[FILESTACK_SIZE][256];
int file_stack_top = -1;

void push_file(const char *filename)
{
  if (file_stack_top < FILESTACK_SIZE - 1) {
    file_stack_top++;
    strncpy(file_stack[file_stack_top], filename, 255);
    file_stack[file_stack_top][255] = '\0';
  }
}

void pop_file()
{
  if (file_stack_top >= 0) {
    file_stack_top--;
  }
}

const char* current_file()
{
  if (file_stack_top >= 0) {
    return file_stack[file_stack_top];
  }
  return "master.tex"; /* Fallback */
}
