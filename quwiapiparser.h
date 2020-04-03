#ifndef QUWIAPIPARSER_H
#define QUWIAPIPARSER_H

#include <QObject>

class QuwiAPIParser : public QObject
{
    Q_OBJECT
public:
    explicit QuwiAPIParser(QObject *parent = nullptr);

    static QByteArray loginCredentialsToJson(QString parent, QString child);
};

#endif // QUWIAPIPARSER_H
