#include "quwiapi.h"
#include "quwiapiparser.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

//please always start with / and finish with /
#define CMD_LOGIN "/auth/login/"

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

void QuwiAPI::logout()
{
    setToken("");
    emit logoutSucced();
}

//private functions
void QuwiAPI::handleLoginResponce(QByteArray data)
{
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject json = document.object();

    qDebug() << data;
    qDebug() << json.value("first_errors");

    if (json.value("first_errors") == QJsonValue::Undefined) {
        QString lToken = json["token"].toString();
        if (!lToken.isEmpty()) {
            setToken(lToken);
            emit loginSucced();
        }
    } else {
        emit loginFailed("Please check if entered credentials where correct");
    }
}

//protected functions
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
    qDebug() << getCommand(reply);

    if (reply->error() == QNetworkReply::NoError) {
        if (QString(CMD_LOGIN).contains(getCommand(reply))) {
            handleLoginResponce(lResponse);
        }
    } else {
        if (QString(CMD_LOGIN).contains(getCommand(reply))) {
            handleLoginResponce(lResponse);
        }
    }
}
