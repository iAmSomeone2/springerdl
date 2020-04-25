find_package(CURL REQUIRED COMPONENTS HTTP HTTPS)
find_package(Threads REQUIRED)


add_library(bookdl STATIC bookdl.c bookdl.h)
target_include_directories(bookdl PUBLIC SYSTEM ${CURL_INCLUDE_DIRS})
target_link_libraries(bookdl CURL::libcurl Threads::Threads)

add_executable(springerdl springerdl.c springerdl.h)
target_link_libraries(springerdl bookdl)

# Install directive
install(TARGETS springerdl
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})