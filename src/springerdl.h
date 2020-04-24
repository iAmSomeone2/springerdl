#ifndef SPRINGERDL_SPRINGERDL_H
#define SPRINGERDL_SPRINGERDL_H

#include <stdint.h>
#include <stdio.h>

#include "bookdl.h"

// Program execution options
static const char OPTS[] = "i:o:l:t:";

/**
 * Determines the number of links in the file.
 * 
 * @param in_file input file
 * 
 * @returns number of links (a.k.a. lines) in the file.
 */
__uint32_t get_num_urls(FILE* in_file);

/**
 * Reads the URLs from the input file into the bookdl structs up to the number specified by 'link_count'.
 * 
 * @param in_file input file
 * @param link_count number of links to read in
 * @param bookdl_array pointer to array of bookdl structs to update
 */
void get_orig_urls(FILE* in_file, __uint32_t link_count, bookdl_t* bookdl_array);

#endif // SPRINGERDL_SPRINGERDL_H