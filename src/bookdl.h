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

#ifndef SPRINGERDL_BOOKDL_H
#define SPRINGERDL_BOOKDL_H

#include <stdint.h>
#include <sys/stat.h>

// Standard Linux directory permissions 
static const int DIR_PERM = (S_IRWXU | S_IRWXG | S_IXOTH);

static const char   BASE_DL_URL[] = "https://link.springer.com/content/pdf/10.1007%2F";
static const size_t BASE_URL_LEN = 49;
static const size_t ISBN_LEN = 19;

typedef struct bookdl {
    char*   original_url;
    char    isbn[ISBN_LEN];
    char*   dl_url;
    char*   out_dir;
} bookdl_t;

/**
 * Sets all char pointers to NULL
 */
void init_bookdl_array(__uint32_t array_len, bookdl_t* bookdl_array, char* out_dir);

/**
 * Clears all used memory in each bookdl of the supplied array.
 */
void free_bookdl_array(__uint32_t array_len, bookdl_t* bookdl_array);

/**
 * Finds and sets the isbn number for the bookdl passed to the function
 * 
 * @param bookdl_item pointer to a single bookdl to modify.
 */
void set_isbn_number(bookdl_t* bookdl_item);

/**
 * Finds and sets the isbn numbers for all books in the array.
 * 
 * @param array_len number of items in bookdl_array
 * @param bookdl_array pointer to array of bookdl structs
 */
void set_all_isbn_numbers(__uint32_t array_len, bookdl_t* bookdl_array);

/**
 * Uses the ISBN to generate the download URL.
 * 
 * @param bookdl_item pointer to a single bookdl to modify.
 */
void generate_dl_url(bookdl_t* bookdl_item);

/**
 * Generates download URLs for all items in the array.
 * 
 * @param array_len number of items in bookdl_array
 * @param bookdl_array pointer to array of bookdl structs
 */
void generate_all_dl_urls(__uint32_t array_len, bookdl_t* bookdl_array);

/**
 * pthread-compatible book download function.
 * 
 * @param raw_bookdl_item bookdl_t pointer expected here.
 */
void *download_book(void *raw_bookdl_item);

/**
 * Runs simultaneous downloads of the PDFs using pthread.
 * 
 * @param array_len number of items in bookdl_array
 * @param bookdl_array pointer to array of bookdl structs
 * @param thread_limit max number of simultaneous downloads
 */
void download_all_books(__uint32_t array_len, bookdl_t* bookdl_array, __uint32_t thread_limit);

#endif // SPRINGERDL_BOOKDL_H