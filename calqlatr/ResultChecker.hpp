#ifndef RESULTCHECKER_HPP
#define RESULTCHECKER_HPP

#include <QObject>
#include <QQmlEngine>

class ResultChecker : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    ResultChecker();
    ~ResultChecker();

    Q_INVOKABLE bool CheckForWin(QStringList cells);
};

#endif // RESULTCHECKER_HPP
