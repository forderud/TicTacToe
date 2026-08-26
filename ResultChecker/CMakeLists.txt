# Example to showcase run-time loading of shared libraries on mobile platforms

add_library(ResultChecker SHARED
  ResultChecker.cpp
  ResultChecker.hpp
)

target_link_libraries(ResultChecker PRIVATE
    Qt6::Core
)

if (APPLE)
  # package shared lib
  set_target_properties(ResultChecker PROPERTIES
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "ResultChecker" # avoid Xcode warning
    VERSION 1.0.0   # "current version" in semantic format in Mach-O binary file
    SOVERSION 1.0.0 # "compatibility version" in semantic format in Mach-O binary file
    PUBLIC_HEADER   ${CMAKE_CURRENT_LIST_DIR}/ResultChecker.hpp
    XCODE_ATTRIBUTE_SKIP_INSTALL YES # to avoid "archive" packaging problems
  )
endif()

# enable "#include <ResultChecker/ResultChecker.hpp>" in client projects
target_include_directories(ResultChecker INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

if(ANDROID)
    target_link_libraries(ResultChecker PRIVATE log)
endif()
