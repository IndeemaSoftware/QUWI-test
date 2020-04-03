#ifndef QUWIAPI_H
#define QUWIAPI_H

#include "quwicore.h"

class QuwiAPI : public QuwiCore
{
    Q_OBJECT
public:
    QuwiAPI(QString url, QuwiCore *parent = 0);

    void login(QString user, QString passwd);
    void logout();

private:
    void handleLoginResponce(QByteArray);

signals:
    void loginSucced();
    void loginFailed(QString);
    void logoutSucced();

protected slots:
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void handleResponse(QNetworkReply *reply);
};

#endif // QUWIAPI_H
