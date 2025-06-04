/****************************************************************************
 *
 *  Copyright (c) 2025 Martin Cornelius Nielsen.
 * 
 *  All Rights Reserved.
 * 
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sumlog.h"
#include "version.h"

void usage(int status) 
{
  printf("Usage: %s filename\n", PROGRAM_NAME);
  printf("   or: %s [options]\n\n", PROGRAM_NAME);

  exit(status);
}

int main(int argc, char*argv[]) 
{
  if (argc == 2) {
    if (strcmp(argv[1], "--help") == 0) {
      usage(EXIT_FAILURE);
    }
    if (strcmp(argv[1], "--version") == 0) {
      version();
      exit(EXIT_SUCCESS);
    }
  }

  sum_log_file(argv[1]);

  return 0;
}

