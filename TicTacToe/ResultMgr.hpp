#pragma once
#include <QObject>
#include <QQmlEngine>
#include <ResultChecker/ResultChecker.hpp> // only for signature
#ifdef _WIN32
#include <Windows.h>
#endif


class ResultMgr : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    enum Status {
        Ongoing,
        X_won,
        O_won,
        Tie,
    };
    Q_ENUM(Status)

    ResultMgr();
    ~ResultMgr();

    // returns a (Status, win-mask) tuple
    Q_INVOKABLE QVariantList check(const QByteArray& cells);

private:
#ifdef _WIN32
    HMODULE m_lib = nullptr;
#else
    void*   m_lib = nullptr;
#endif
    decltype(&CheckForWin) m_func_ptr = nullptr;
};
