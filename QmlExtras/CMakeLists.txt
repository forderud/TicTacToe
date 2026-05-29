qt_add_library(QmlExtras STATIC)

qt_add_qml_module(QmlExtras
    URI QmlExtras
    VERSION 1.0
    QML_FILES
        "Display.qml"
)

target_link_libraries(QmlExtras PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)
