#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <curl/curl.h>

#include "bookdl.h"

void init_bookdl_array(__uint32_t array_len, bookdl_t* bookdl_array) {
    for (__uint32_t i = 0; i < array_len; i++) {
        bookdl_array[i].downloadURL = NULL;
        bookdl_array[i].originalURL = NULL;
        bookdl_array[i].redirectURL = NULL;
    }
}

void free_bookdl_array(__uint32_t array_len, bookdl_t* bookdl_array) {
    for (__uint32_t i = 0; i < array_len; i++) {
        if (bookdl_array[i].downloadURL != NULL) {
            free(bookdl_array[i].downloadURL);
        }
        if (bookdl_array[i].originalURL != NULL) {
            free(bookdl_array[i].originalURL);
        }
        if (bookdl_array[i].redirectURL != NULL) {
            free(bookdl_array[i].redirectURL);
        }
    }
}

void set_redirect_url(bookdl_t* bookdl_item) {
    CURL* curl = curl_easy_init();
    CURLcode res;
    long response_code;
    char* redir_url;

    FILE* header_file = fopen(HEADER_FILE, "w+");
    if (!header_file) {
        fprintf(stderr, "Failed to open file to store headers.\n");
        curl_easy_cleanup(curl);
        return;
    }

    // Set the URL to be used in the call to CURL.
    curl_easy_setopt(curl, CURLOPT_URL, bookdl_item->originalURL);

    curl_easy_setopt(curl, CURLOPT_HEADERDATA, header_file);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perfom() failed: %s\n", curl_easy_strerror(res));
    } else {
        res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        if ((res == CURLE_OK) && ((response_code / 100) != 3)) {
            // Only 300's are redirects
            fprintf(stderr, "Not a redirect.\n");
        } else {
            res = curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &redir_url);

            if ((res == CURLE_OK) && redir_url) {
                size_t url_len = strlen(redir_url);
                bookdl_item->redirectURL = (char*)(malloc(sizeof(char) * (url_len + 1)));
                strncpy(bookdl_item->redirectURL, redir_url, url_len);
            }
        }
    }

    fclose(header_file);
    curl_easy_cleanup(curl);
}