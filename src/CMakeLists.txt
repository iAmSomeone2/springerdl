find_package(CURL REQUIRED COMPONENTS HTTP HTTPS)

add_library(bookdl STATIC bookdl.c bookdl.h)
target_include_directories(bookdl PUBLIC SYSTEM ${CURL_INCLUDE_DIRS})
target_link_libraries(bookdl CURL::libcurl)

add_executable(springerdl springerdl.c springerdl.h)
target_link_libraries(springerdl bookdl)