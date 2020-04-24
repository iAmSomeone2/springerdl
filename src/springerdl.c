#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "springerdl.h"

int main(int argc, char* argv[]) {
    char* input_file_loc = NULL;
    char* out_dir_loc = NULL;
    __uint32_t limit = 0;
    __uint32_t thread_limit = 1;

    int opt_result;

    opterr = 0;

    /*
        TODO: fix segfault issue when no text is provided to options.
    */
    while((opt_result = getopt(argc, argv, OPTS)) != -1) {
        switch(opt_result) {
            case 'i':
                input_file_loc = optarg;
                break;
            case 'o':
                out_dir_loc = optarg;
                break;
            case 'l':
                limit = strtoul(optarg, NULL, 10);
                break;
            case 't':
                thread_limit = strtoul(optarg, NULL, 10);
                break;
            default:
                abort();
        }
    }

    if (input_file_loc == NULL) {
        fprintf(stderr, "No input file given.\n");
        return 2;
    }

    FILE* in_file = fopen(input_file_loc, "r");
    if (in_file == NULL) {
        fprintf(stderr, "Failed to open input file: '%s'\n", input_file_loc);
        return 1;
    }

    __uint32_t num_urls = get_num_urls(in_file);

    printf("Number of links in file: %u\n", num_urls);

    bookdl_t* book_dls = (bookdl_t*)(malloc(sizeof(bookdl_t) * num_urls));
    init_bookdl_array(num_urls, book_dls);

    get_orig_urls(in_file, num_urls, book_dls);
    fclose(in_file);

    set_redirect_url(&book_dls[1]);

    free_bookdl_array(num_urls, book_dls);
    free(book_dls);
    return 0;
}

__uint32_t get_num_urls(FILE* in_file) {
    fpos_t loc;
    fgetpos(in_file, &loc);

    fseek(in_file, 0, SEEK_SET);

    __uint32_t line_count = 0;

    char buff;

    while ((buff = getc(in_file)) != EOF) {
        if (buff == '\n') {
            line_count++;
        }
    }

    fsetpos(in_file, &loc);
    return line_count;
}

void get_orig_urls(FILE* in_file, __uint32_t link_count, bookdl_t* bookdl_array) {
    fpos_t loc;
    fgetpos(in_file, &loc);

    fseek(in_file, 0, SEEK_SET);

    char c;
    char buff[256];

    __uint32_t links_read = 0;
    __uint16_t line_len = 0;

    while ((c = getc(in_file)) != EOF && links_read < link_count) {
        if (c == '\r') {
            // We don't want carriage returns in our data.
            continue;
        } else if (c != '\n') {
            buff[line_len] = c;
            line_len++;
        } else {
            bookdl_array[links_read].originalURL = (char*)(malloc(sizeof(char) * (line_len + 1)));
            strncpy(bookdl_array[links_read].originalURL, buff, line_len);
            links_read++;
            line_len = 0;
        }
    }

    fsetpos(in_file, &loc);
}