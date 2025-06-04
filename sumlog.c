#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "sumlog.h"

int nr_errors = 0;
int nr_warnings = 0;

void sum_log_file(char *path)
{
  FILE *f = fopen(path, "r");
  if(!f) {
    perror("fopen");
  }

  char line[4096];
  char prev_line[4096];
  int found_error = 0;
  while (fgets(line, sizeof(line), f)) {
    /*
     * This should not check for '?' but rather
     * check for empty string. I think that will
     * be the best option.
     * Alternatively, it would need different
     * things to look for based on the error message.
     */
    if (found_error && strstr(line, "?")) {
      found_error = 0;
      printf("%s\n", line);
    }
    else if (found_error && isblank(line[0])) {
      continue;
    }
    else if (found_error) {
      printf("%s\n", line);
    }

    if (strstr(line, "!")) {
      printf("[ERROR] %s", line);
      nr_errors += 1;
      found_error = 1;

      if (found_error && strstr(prev_line, ".tex")) {
        printf("file: %s\n", prev_line);
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
