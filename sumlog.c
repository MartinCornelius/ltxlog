#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "sumlog.h"
#include "file-utils.h"
#include "utils.h"

extern char workdir[];

int nr_errors = 0;
int nr_warnings = 0;
char current_file_name[256];

void sum_log_file(char *path)
{
  FILE *f = fopen(path, "r");
  if(!f) {
    printf("path to open: %s\n", path);
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

    /* Track current file */
    if (extract_tex_filename(line, current_file_name, sizeof(current_file_name))) {
      push_file(current_file_name);
    }
    
    /* Print source line from tex file */
    if (strncmp(line, "l.", 2) == 0 && isdigit(line[2])) {
      int lineno = atoi(line + 2);
      char full_path[1024];
      snprintf(full_path, sizeof(full_path), "%s/%s", workdir, current_file_name);
      print_tex_line(full_path, lineno);
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
