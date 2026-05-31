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
    enum State {
        Ongoing = GameState::Ongoing,
        X_won = GameState::X_won,
        O_won = GameState::O_won,
        Tie = GameState::Tie,
    };
    Q_ENUM(State)

    ResultMgr();
    ~ResultMgr();

    // returns a (Status, win-mask) tuple
    Q_INVOKABLE QVariantMap check(const QByteArray& cells);

private:
#ifdef _WIN32
    HMODULE m_lib = nullptr;
#else
    void*   m_lib = nullptr;
#endif
    decltype(&CheckForWin) m_func_ptr = nullptr;
};
