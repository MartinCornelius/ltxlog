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

#define MAX_PATH 1024

/*
 * The root directory for the latex project.
 * Where the .tex files are.
 */
char workdir[MAX_PATH] = ".";

/*
 * If using a out or build folder in latex project.
 * This is the folder containing the .log file.
 */
char outdir[MAX_PATH] = ".";

/*
 * Name of log file to examine
 * Defaults to master
 */
char log_filename[256] = "master";

void usage(int status) 
{
  printf("Usage: %s [options]\n", PROGRAM_NAME);
  printf("Options:\n");
  printf("\t--help           Show this help message\n");
  printf("\t--version        Show version info\n");
  printf("\t--workdir DIR    Set working directory for .tex files\n");
  printf("\t--outdir DIR     Set directory containing .log file\n");
  printf("\t--log-name NAME  Set name of log file to examine (no extension)\n");
  exit(status);
}

int main(int argc, char*argv[]) 
{
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0) {
      // Help
      usage(EXIT_SUCCESS);
    }
    else if (strcmp(argv[i], "--workdir") == 0) {
      // Workdir
      if (i + 1 < argc) {
        strncpy(workdir, argv[++i], MAX_PATH - 1);
      }
      else {
        fprintf(stderr, "Missing value for --workdir\n");
        usage(EXIT_FAILURE);
      }
    }
    else if (strcmp(argv[i], "--outdir") == 0) {
      // Outdir
      if (i + 1 < argc) {
        strncpy(outdir, argv[++i], MAX_PATH - 1);
      }
      else {
        fprintf(stderr, "Missing value for --outdir\n");
        usage(EXIT_FAILURE);
      }
    }
    else if (strcmp(argv[i], "--log-name") == 0) {
      // Log name
      if (i + 1 < argc) {
        strncpy(log_filename, argv[++i], sizeof(log_filename) - 1);
      }
      else {
        fprintf(stderr, "Missing value for --log-name\n");
        usage(EXIT_FAILURE);
      }
    }
    else {
      fprintf(stderr, "Unknown option: %s\n", argv[i]);
      usage(EXIT_FAILURE);
    }
  }
  
  /* Full path to log file */
  char full_log_path[MAX_PATH * 2];
  snprintf(full_log_path, sizeof(full_log_path), "%s/%s/%s.log", workdir, outdir, log_filename);
  sum_log_file(full_log_path);
  return 0;
}

