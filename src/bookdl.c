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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>

#include <curl/curl.h>

#include "bookdl.h"

void init_bookdl_array(__uint32_t array_len, bookdl_t* bookdl_array, char* out_dir) {
    for (__uint32_t i = 0; i < array_len; i++) {
        bookdl_array[i].dl_url = NULL;
        bookdl_array[i].original_url = NULL;
        bookdl_array[i].isbn[0] = '\0';
        bookdl_array[i].out_dir = out_dir;
    }
}

void free_bookdl_array(__uint32_t array_len, bookdl_t* bookdl_array) {
    for (__uint32_t i = 0; i < array_len; i++) {
        if (bookdl_array[i].dl_url != NULL) {
            free(bookdl_array[i].dl_url);
        }
        if (bookdl_array[i].original_url != NULL) {
            free(bookdl_array[i].original_url);
        }
    }
}

void set_isbn_number(bookdl_t* bookdl_item) {
    strncpy(bookdl_item->isbn, bookdl_item->original_url + 50, ISBN_LEN);
}

void set_all_isbn_numbers(__uint32_t array_len, bookdl_t* bookdl_array) {
    for (__uint32_t i = 0; i < array_len; i++) {
        set_isbn_number(&bookdl_array[i]);
    }
}

void generate_dl_url(bookdl_t* bookdl_item) {
    size_t target_url_size = BASE_URL_LEN + ISBN_LEN + 5;

    bookdl_item->dl_url = (char*)(malloc(sizeof(char) * target_url_size));
    strncpy(bookdl_item->dl_url, BASE_DL_URL, BASE_URL_LEN);
    strncat(bookdl_item->dl_url, bookdl_item->isbn, ISBN_LEN);
    strncat(bookdl_item->dl_url, ".pdf", 5);
}

void generate_all_dl_urls(__uint32_t array_len, bookdl_t* bookdl_array) {
    for (__uint32_t i = 0; i < array_len; i++) {
        generate_dl_url(&bookdl_array[i]);
    }
}

void *download_book(void *raw_bookdl_item) {
    bookdl_t* bookdl_item = (bookdl_t*)(raw_bookdl_item);

    // Check if output directory exists.
    struct stat* buff = (struct stat*)(malloc(sizeof(struct stat)));
    if (stat(bookdl_item->out_dir, buff) != 0){
        int result = mkdir(bookdl_item->out_dir, DIR_PERM);
        if (result == -1) {
            fprintf(stderr, "Failed to create output directory.");
            free(buff);
            abort();
        }
    }
    free(buff);

    // Generate filename based on book isbn
    __uint32_t dir_str_len = strlen(bookdl_item->out_dir);
    char* out_file_name = (char*)(malloc(sizeof(char) * (dir_str_len + ISBN_LEN + 6)));
    out_file_name[0] = '\0';
    strncpy(out_file_name, bookdl_item->out_dir, dir_str_len);
    strncat(out_file_name, "/", 2);
    strncat(out_file_name, bookdl_item->isbn, ISBN_LEN);
    strncat(out_file_name, ".pdf", 5);

    // Open corresponding file.
    FILE* out_file = fopen(out_file_name, "w+b");
    free(out_file_name);

    // Set up for the HTTP request for the file dl
    CURL* curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, bookdl_item->dl_url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, out_file);

    curl_easy_perform(curl_handle);

    curl_easy_cleanup(curl_handle);
    fclose(out_file);
    return NULL;
}

void download_all_books(__uint32_t array_len, bookdl_t* bookdl_array, __uint32_t thread_limit) {
    pthread_t* thread_pool = (pthread_t*)(malloc(sizeof(pthread_t) * thread_limit));



    free(thread_pool);
}