#include "quwiapiparser.h"
#include <QJsonObject>
#include <QJsonDocument>

QuwiAPIParser::QuwiAPIParser(QObject *parent) : QObject(parent)
{

}

QByteArray QuwiAPIParser::loginCredentialsToJson(QString email, QString passwd)
{
    QJsonObject object;
    object["email"] = email;
    object["password"] = passwd;

    QJsonDocument doc(object);
    return doc.toJson();
}
