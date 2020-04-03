#include "quwiapi.h"
#include "quwiapiparser.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#define CMD_LOGIN "/auth/login"

QuwiAPI::QuwiAPI(QString url, QuwiCore *parent) : QuwiCore(url, parent)
{

}

void QuwiAPI::login(QString user, QString passwd)
{
    QUrl lServiceURL(formUrl(CMD_LOGIN, APIVersion()));

    QNetworkRequest lRequest(request(lServiceURL));

    QByteArray lBody = QuwiAPIParser::loginCredentialsToJson(user, passwd);
    qDebug() << QString::fromStdString(lBody.toStdString());
    mgr()->post(lRequest, lBody);
}

void QuwiAPI::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    qDebug() << __FUNCTION__;
    qDebug() << reply;
}

void QuwiAPI::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug() << __FUNCTION__;
    qDebug() <<errors;
}

void QuwiAPI::handleResponse(QNetworkReply *reply)
{
    qDebug() << __FUNCTION__;
    QByteArray lResponse = reply->readAll();
    qDebug() << lResponse;
}
