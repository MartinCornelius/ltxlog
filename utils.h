#ifndef UTILS_H
#define UTILS_H

int is_blank_line(const char *line);
int is_irrelevant(const char *line);
int extract_tex_filename(const char *line, char *out, size_t out_size);
void print_tex_line(const char *filename, int target_line);

#endif
