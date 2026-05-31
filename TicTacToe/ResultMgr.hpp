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
        Ongoing = (int)GameState::Ongoing,
        X_won = (int)GameState::X_won,
        O_won = (int)GameState::O_won,
        Tie = (int)GameState::Tie,
    };
    Q_ENUM(State)

    ResultMgr();
    ~ResultMgr();

    // returns a (Status, win-mask) tuple
    Q_INVOKABLE State check(const QByteArray& cells);

    Q_INVOKABLE QByteArray mask();
private:
#ifdef _WIN32
    HMODULE m_lib = nullptr;
#else
    void*   m_lib = nullptr;
#endif
    decltype(&CheckForWin) m_func_ptr = nullptr;

    QByteArray m_mask;
};
