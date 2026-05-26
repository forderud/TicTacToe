#ifndef RESULTCHECKER_HPP
#define RESULTCHECKER_HPP

#include <QObject>
#include <QQmlEngine>

class ResultChecker : public QObject {
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
public:
    ResultChecker();
    ~ResultChecker();

    /** Positive retval means "x" won and negative that "o" have won */
    Q_INVOKABLE int Check(QString cells);
};

#endif // RESULTCHECKER_HPP
