#include "quwicore.h"

#include <QNetworkReply>

QuwiCore::QuwiCore(QString url, QObject *parent) : QObject(parent),
    mAPIVersion{DEFAULT_API_VERSION}
{
    setUrl(url);

    mToken = "";

    mMgr = new QNetworkAccessManager();
    connect(mMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleResponse(QNetworkReply*)));
    connect(mMgr, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)), this, SLOT(sslErrors(QNetworkReply *, const QList<QSslError> &)));
    connect(mMgr, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)), this, SLOT(authenticationRequired(QNetworkReply*, QAuthenticator*)));
}

QuwiCore::~QuwiCore()
{
    delete mMgr;
}

QString QuwiCore::url() const
{
    return mUrl;
}

void QuwiCore::setUrl(const QString &url)
{
    mUrl = url;
}

QNetworkAccessManager *QuwiCore::mgr() const
{
    return mMgr;
}

QString QuwiCore::getVersion(QNetworkReply *reply)
{
    QString rVersion(UNDEFINED);

    if (!reply->request().url().path().isEmpty()) {
        rVersion = reply->request().url().path();
    }

    if (UNDEFINED != rVersion) {
        rVersion = rVersion.mid(0, rVersion.indexOf("/", 1));
        rVersion.remove(0, 1);
    }

    return rVersion;
}

QString QuwiCore::getCommand(QNetworkReply *reply)
{
    QString rCommand(UNDEFINED);
    QString lVersion = getVersion(reply);

    if (!reply->request().url().path().isEmpty()) {
        rCommand = reply->request().url().path();
    }

    if (UNDEFINED != rCommand) {
        QString lTmp("/");
        lTmp.append(lVersion);
        lTmp.append("/");

        rCommand.remove(lTmp);// removing version from path
        rCommand.remove(rCommand.size()-1, 1);//removing last / from path
    }

    return rCommand;
}

QNetworkRequest QuwiCore::request(QUrl url)
{
    QNetworkRequest lRequest(url);
    lRequest.setRawHeader("content-type", "application/json");
    if (!mToken.isEmpty()) {
        QString lValue = "Bearer " + mToken;
        lRequest.setRawHeader("Authorization", lValue.toUtf8());
    }

    return lRequest;
}

QNetworkRequest QuwiCore::requestFormData(QUrl url, QByteArray data, int size)
{
    QNetworkRequest lRequest(url);
    lRequest.setRawHeader("content-type", "multipart/form-data; boundary="+data );

    if (!mToken.isEmpty()) {
        QString lValue = "Bearer " + mToken;
        lRequest.setRawHeader("Authorization", lValue.toUtf8());
    }
    lRequest.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(size));

    return lRequest;
}


QByteArray QuwiCore::serverUrl(QByteArray version)
{
    QByteArray rServerUrl = url().toUtf8();
    rServerUrl.append(version);

    return rServerUrl;
}

QString QuwiCore::getToken() const
{
    return mToken;
}

void QuwiCore::setToken(const QString &token)
{
    mToken = token;
}

QString QuwiCore::APIVersion() const
{
    return mAPIVersion;
}

void QuwiCore::setAPIVersion(const QString &aPIVersion)
{
    mAPIVersion = aPIVersion;
}

QString QuwiCore::formUrl(QString url)
{
    return QString(mUrl.toUtf8().append(url));

}

QString QuwiCore::formUrl(QString url, QString version)
{
    return QString(mUrl.toUtf8().append("/").append(version).append(url));

}
