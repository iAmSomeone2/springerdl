/*
    springerdl -- a simple pdf downloader utility for free Springer-published books.
    Copyright (C) 2020  Brenden Davidson

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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