#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "sumlog.h"
#include "utils.h"

int nr_errors = 0;
int nr_warnings = 0;

void sum_log_file(char *path)
{
  FILE *f = fopen(path, "r");
  if(!f) {
    perror("fopen");
  }

  char line[1024];
  char prev_line[1024];
  int found_error = 0;
  while (fgets(line, sizeof(line), f)) {
    if (found_error && is_blank_line(line)) {
      found_error = 0;
      printf("\n");
    }
    else if (found_error && is_irrelevant(line)) {
      continue;
    }
    else if (found_error) {
      printf("%s", line);
    }

    /* Error types */
    if (strstr(line, "!")) {
      printf("[ERROR] %s", line);
      nr_errors += 1;
      found_error = 1;

      if (found_error && strstr(prev_line, ".tex")) {
        printf("file: %s", prev_line);
      }
    }
    /*
    else if (strstr(line, "Warning")) {
      printf("[WARN] %s", line);
      nr_warnings += 1;
      found_error = 1;
    }
    */

    strncpy(prev_line, line, sizeof(prev_line) - 1);
  }
  fclose(f);
  print_sumlog();
}

void print_sumlog(void)
{
  printf("\n=============================\n");
  printf("Errors:   %d\n", nr_errors);
  // printf("Warnings: %d\n", nr_warnings);
}
