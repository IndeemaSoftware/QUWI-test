#ifndef QUWIAPIPARSER_H
#define QUWIAPIPARSER_H

#include "quwiproject.h"

#include <QObject>

class QuwiAPIParser : public QObject
{
    Q_OBJECT
public:
    explicit QuwiAPIParser(QObject *parent = nullptr);

    //generate jsons
    static QByteArray loginCredentialsToJson(QString parent, QString child);

    //parse jsons
    static QList<QuwiProject> *parseProjects(QByteArray);
};

#endif // QUWIAPIPARSER_H
