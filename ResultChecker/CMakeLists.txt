include(CMakePackageConfigHelpers)

add_library(ResultChecker SHARED
  ResultChecker.cpp
  ResultChecker.hpp
)

if (APPLE)
  # package shared lib as a framework
  set_target_properties(ResultChecker PROPERTIES
    FRAMEWORK TRUE
    FRAMEWORK_VERSION A
    MACOSX_FRAMEWORK_IDENTIFIER "ResultChecker"
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "ResultChecker" # avoid Xcode warning
    VERSION 1.0.0   # "current version" in semantic format in Mach-O binary file
    SOVERSION 1.0.0 # "compatibility version" in semantic format in Mach-O binary file
    MACOSX_FRAMEWORK_BUNDLE_VERSION "${VERSION}" # to avoid app store validation error
    MACOSX_FRAMEWORK_SHORT_VERSION_STRING "${VERSION}" # to avoid app store validation error
    PUBLIC_HEADER   ${CMAKE_CURRENT_LIST_DIR}/ResultChecker.hpp
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
    XCODE_ATTRIBUTE_SKIP_INSTALL YES # to avoid "archive" packaging problems
  )
else()
    # enable "#include <ResultChecker/ResultChecker.hpp>" in client projects
    target_include_directories(ResultChecker INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
    )
endif()

if(ANDROID)
    target_link_libraries(ResultChecker PRIVATE log)
endif()

# install rules
install(
    TARGETS ResultChecker
    EXPORT ResultCheckerTargets
    DESTINATION .
    FRAMEWORK DESTINATION .
)
install(
    EXPORT ResultCheckerTargets
    DESTINATION cmake
    NAMESPACE ResultChecker::
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ResultCheckerConfigVersion.cmake
    VERSION 1.0.0
    COMPATIBILITY SameMinorVersion
)
install(
    FILES
        ResultCheckerConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/ResultCheckerConfigVersion.cmake
    DESTINATION cmake
)
