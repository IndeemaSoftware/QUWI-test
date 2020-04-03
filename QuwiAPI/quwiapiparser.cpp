#include "quwiapiparser.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

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

QList<QuwiProject> *QuwiAPIParser::parseProjects(QByteArray data)
{
    QList<QuwiProject> *lList = new QList<QuwiProject>();

    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject lObj = document.object();
    QJsonArray lProjects = lObj.value("projects").toArray();

    if (lProjects.size() > 0) {
        foreach (const QJsonValue & val, lProjects) {
            QuwiProject lProject;
            lProject.setId(val.toObject().value("id").toInt());
            lProject.setUid(val.toObject().value("uid").toString());
            lProject.setName(val.toObject().value("name").toString());
            lProject.setLogoUrl(QUrl(val.toObject().value("logo_url").toString()));
            lProject.setPosition(val.toObject().value("position").toInt());
            lProject.setIsActive(val.toObject().value("is_active").toBool());
            lProject.setHasStarred(val.toObject().value("has_starred").toBool());

            lList->append(lProject);
        }
    }

    return lList;
}
