#pragma once
#include <QObject>
#include <QQmlEngine>
#include <ResultChecker/ResultChecker.hpp> // only for signature
#ifdef _WIN32
#include <Windows.h>
#endif


class ResultChecker : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    ResultChecker();
    ~ResultChecker();

    /** Positive retval means "x" won and negative that "o" have won */
    Q_INVOKABLE int check(QString cells);

private:
#ifdef _WIN32
    HMODULE m_lib = nullptr;
#endif
    decltype(&CheckForWin) m_func_ptr = nullptr;
};
