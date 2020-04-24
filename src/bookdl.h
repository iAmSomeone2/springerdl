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