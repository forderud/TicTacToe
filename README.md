Qt mobile Android/iOS app to showcase dynamically loaded plugins

## Qt links
* Qt documentation: [Qt for iOS - Building from Source](https://doc.qt.io/qt-6/ios-building-from-source.html) - also need to pass `-shared` to build Qt as shared/dynamic libraries.
* Qt issue: [iOS, tvOS, watchOS: Add support for dynamic linking](https://qt-project.atlassian.net/browse/QTBUG-42937) ("in progress" as of May 2026)

### Associated Qt patches
* qtbase: [iOS: Embed shared library dependencies into app bundles automatically](https://codereview.qt-project.org/c/qt/qtbase/+/735955)
* qtbase: [iOS: Enable building platform plugin as shared library](https://codereview.qt-project.org/c/qt/qtbase/+/734076)
* qtspeech: [iOS: Explicitly link to Foundation](https://codereview.qt-project.org/c/qt/qtspeech/+/738600)
* qtconnectivity: [iOS: Explicitly link to Foundation](https://codereview.qt-project.org/c/qt/qtconnectivity/+/738599)
