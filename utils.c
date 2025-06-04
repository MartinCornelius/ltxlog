#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

/*
 * Checks if a given line consists only of whitespace characters.
 * Returns 1 if the line is blank, 0 otherwise
 */
int is_blank_line(const char *line)
{
  if (line == NULL) {
    return 0;
  }

  int white_space_counter = 0;

  for (int i = 0; line[i] != '\0'; i++) {
    if (!isspace((unsigned char)line[i])) {
      return 0;
    }
  }

  return 1;
}

/*
 * TODO: find better name :)
 * Checks if line is prefixed with a bunch of whitespace
 * and is not relevant for the error message.
 * Example: \tex_par:D or $
 */
int is_irrelevant(const char *line)
{
  if (line == NULL) {
    return 0;
  }

  for (int i = 0; line[i] != '\0'; i++) {
    if (i >= 5)
      return 1;

      if (!isspace((unsigned char)line[i])) {
        return 0;
    }
  }

  return 0;
}

/*
 * Extracts the filepath for a tex file
 * Returns 1 if a filename was found, 0 otherwise
 */
int extract_tex_filename(const char *line, char *out, size_t out_size)
{
  const char *p = line;

  // skip whitespace and opening '('
  while (*p && (*p == '(' || isspace(*p))) {
    p++;
  }

  const char *tex = strstr(p, ".tex");
  if (!tex) return 0;

  const char *start = tex;
  // TODO: PLEASE FIX ME
  while (start > p && (isalnum(*(start - 1)) || *(start - 1) == '/' || *(start - 1) == '.' || *(start - 1) == '_')) {
    start--;
  }

  size_t len = tex - start + 4; /* ".tex" = 4 chars */
  if (len >= out_size) len = out_size - 1;

  strncpy(out, start, len);
  out[len] = '\0';

  return 1;
}

void print_tex_line(const char *filename, int target_line)
{
  FILE *f = fopen(filename, "r");
  if (!f) {
    fprintf(stderr, "[WARN] Could not open file: %s\n", filename);
    return;
  }

  char buf[1024];
  char prev_buf[1024];
  int lineno = 1;
  while (fgets(buf, sizeof(buf), f)) {
    if (lineno == target_line) {
      /* This solution is very janky! */
      if (*buf == '\n') {
        printf("\t[adjusted]--> %s:%d: %s", filename, lineno - 1, prev_buf);
      }
      else {
        printf("\t--> %s:%d: %s", filename, lineno, buf);   
      }
      break;
    }
    lineno++;
    strncpy(prev_buf, buf, sizeof(prev_buf) - 1);
  }
  fclose(f);
}
