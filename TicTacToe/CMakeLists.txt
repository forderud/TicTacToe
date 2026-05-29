qt_add_executable(TicTacToe WIN32 MACOSX_BUNDLE
    main.cpp
    ResultMgr.hpp
    ResultMgr.cpp
)

target_link_libraries(TicTacToe PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    ResultChecker
)
if (APPLE)
    set_target_properties(TicTacToe PROPERTIES
        # Embed framework(s) into .app bundle
        XCODE_EMBED_FRAMEWORKS ResultChecker
        XCODE_EMBED_FRAMEWORKS_CODE_SIGN_ON_COPY YES
    )

    if(IOS)
        set_target_properties(TicTacToe PROPERTIES
            # Look for dylibs inside .app bundle Frameworks folder
            INSTALL_RPATH "@executable_path/Frameworks"
        )
    endif()
endif()

qt_add_qml_module(TicTacToe
    URI demos.TicTacToe
    QML_FILES
        "Main.qml"
        "content/ApplicationState.qml"
        "content/Display.qml"
        "content/NumberPad.qml"
        "content/CalculatorButton.qml"
)

if(ANDROID)
    set_target_properties(TicTacToe PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android"
        QT_ANDROID_PACKAGE_NAME "io.qt.TicTacToe"
        QT_ANDROID_TARGET_SDK_VERSION 34
        QT_ANDROID_VERSION_CODE 10
        QT_ANDROID_VERSION_NAME "1.0"
    )
    if(CMAKE_BUILD_TYPE STREQUAL Release)
        qt_import_plugins(TicTacToe
            INCLUDE_BY_TYPE imageformats Qt::QSvgPlugin
            EXCLUDE_BY_TYPE qmltooling
            EXCLUDE_BY_TYPE iconengines
            EXCLUDE_BY_TYPE networkinformation
            EXCLUDE_BY_TYPE tls
            EXCLUDE_BY_TYPE platforminputcontexts
        )
    endif()
endif()

if(APPLE)
    set_target_properties(TicTacToe PROPERTIES
        OUTPUT_NAME "TicTacTå" # display name
        MACOSX_BUNDLE_BUNDLE_NAME "TicTacToe"
        MACOSX_BUNDLE_GUI_IDENTIFIER "io.qt.TicTacToe"
    )
    if(IOS)
        set(asset_catalog_path "ios/Assets.xcassets")
        target_sources(TicTacToe PRIVATE "${asset_catalog_path}")
        set_source_files_properties(${asset_catalog_path} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        set_target_properties(TicTacToe
            PROPERTIES XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME AppIcon)
    endif()
endif()

install(TARGETS TicTacToe
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_qml_app_script(
    TARGET TicTacToe
    OUTPUT_SCRIPT deploy_script
    MACOS_BUNDLE_POST_BUILD
    NO_UNSUPPORTED_PLATFORM_ERROR
    DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
)
install(SCRIPT ${deploy_script})
