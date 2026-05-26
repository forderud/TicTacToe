#pragma once
#include <QObject>
#include <QQmlEngine>

class ResultChecker : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    ResultChecker();
    ~ResultChecker();

    /** Positive retval means "x" won and negative that "o" have won */
    Q_INVOKABLE int check(QString cells);
};
