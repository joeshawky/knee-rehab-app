#ifndef PARSER_H
#define PARSER_H

#include <QObject>

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = nullptr);

    Q_INVOKABLE QString redColor();




signals:
};

#endif // PARSER_H
