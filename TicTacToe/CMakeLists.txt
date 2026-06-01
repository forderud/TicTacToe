qt_add_executable(TicTacToe WIN32 MACOSX_BUNDLE
    main.cpp
    ResultMgr.hpp
    ResultMgr.cpp
)

qt_add_qml_module(TicTacToe
    URI TicTacToe
    QML_FILES
        "Main.qml"
        "content/ApplicationState.qml"
        "content/NumberPad.qml"
        "content/CalculatorButton.qml"
)

target_link_libraries(TicTacToe PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    QmlExtras
    ResultChecker
)
if(NOT QML_EXTRAS_SHARED)
    target_link_libraries(TicTacToe PRIVATE
        QmlExtrasplugin # needed if QmlExtras is built as static lib
    )
endif()

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

if(ANDROID)
    set_target_properties(TicTacToe PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android"
        QT_ANDROID_PACKAGE_NAME "forderud.TicTacToe"
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
        OUTPUT_NAME "TicTacToe" # display name
        MACOSX_BUNDLE_BUNDLE_NAME "TicTacToe"
        MACOSX_BUNDLE_GUI_IDENTIFIER "forderud.TicTacToe"
    )
    if(IOS)
        set(asset_catalog_path "ios/Assets.xcassets")
        target_sources(TicTacToe PRIVATE "${asset_catalog_path}")
        set_source_files_properties(${asset_catalog_path} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
        set_target_properties(TicTacToe
            PROPERTIES XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME AppIcon)
    endif()
endif()
