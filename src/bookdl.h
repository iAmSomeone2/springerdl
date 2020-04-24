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

static const char HEADER_FILE[] = "./headers.txt";

typedef struct bookdl {
    char* originalURL;
    char* redirectURL;
    char* downloadURL;
} bookdl_t;

/**
 * Sets all char pointers to NULL
 */
void init_bookdl_array(__uint32_t array_len, bookdl_t* bookdl_array);

/**
 * Clears all used memory in each bookdl of the supplied array.
 */
void free_bookdl_array(__uint32_t array_len, bookdl_t* bookdl_array);

/**
 * Finds and sets the redirect URL for the bookdl passed to the function
 * 
 * @param bookdl_item pointer to a single bookdl to modify.
 */
void set_redirect_url(bookdl_t* bookdl_item);

#endif // SPRINGERDL_BOOKDL_H