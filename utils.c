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
