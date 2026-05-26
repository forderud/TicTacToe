#include <cassert>
#include <stdio.h>
#include "ResultChecker.hpp"

#ifndef _WIN32
  #define EMBED_SAMPLE_LIB_METADATA
  #include "../LibMetadata.hpp"
#endif


extern "C"
#ifndef _WIN32
  __attribute__ ((visibility ("default")))
#endif
std::string_view LibraryFunction () {
    static char buffer[1024] = {}; // static to allow string_view return
    size_t i = 0;
    i += snprintf(buffer+i, sizeof(buffer)-i, "Hello from ResultChecker!\n");
    assert(i <= sizeof(buffer));
    return std::string_view(buffer, i);
}
