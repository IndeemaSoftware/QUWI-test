#ifndef QUWIAPI_H
#define QUWIAPI_H

#include "quwicore.h"

class QuwiAPI : public QuwiCore
{
public:
    QuwiAPI(QString url, QuwiCore *parent = 0);

    void login(QString user, QString passwd);

protected slots:
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void handleResponse(QNetworkReply *reply);
};

#endif // QUWIAPI_H
