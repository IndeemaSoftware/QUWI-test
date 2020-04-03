/***************************************************************************
 *                                                                         *
 *   This Quwi services API was created by by Indeema Software Inc.      *
 *   Quwi SDK is under MIT license so you are free to use it.           *
 *   https://indeema.com                                                   *
 *                                                                         *
 *   In case if you have any issues or comments, please conntact us:       *
 *   support@indeema.com                                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QQUWICORE_H
#define QUWICORE_H

#include <QObject>
#include <QNetworkRequest>
#include <QSslError>
#include <QAuthenticator>

/** @file */

/**Undefined value for strings*/
#define UNDEFINED "-1"

/**By default we are using "v1" version of API*/
#define DEFAULT_API_VERSION "v1"

class QNetworkReply;
class QNetworkAccessManager;

/*! \class QuwiCore
    \brief Basic class for any QUWI API class that keeps basic configuration to communicate with QUWI APIs
    \details To start using QuwiCore can save you time as it contains methods for request formation QNetworkRequest request(QUrl url);
    request manager and url parsers to know request name.
*/

class QuwiCore : public QObject
{
    Q_OBJECT
public:
    //! This constructor saves basic QUWI API url and initializes QNetworkAccessManager object
    /*!
        \param url basic url to QUWI API
        \param parent parent object
    */
    explicit QuwiCore(QString url, QObject *parent = 0);
    ~QuwiCore();

    //! Basic Quwi API url
    QString url() const;
    //! Sets basic Quwi API url
    void setUrl(const QString &url);

    //! Version of API. By default the value os "v1"
    /*!
        \return API version
    */
    QString APIVersion() const;
    //! Sets vertion of API to use
    /*!
    */
    void setAPIVersion(const QString &aPIVersion);

protected:
    QString getToken() const;

    void setToken(const QString &token);
    //! Forms url from base url (set in class constructor) + method url
    /*!
        \return is used to simplify process of url creation
    */
    QString formUrl(QString url);
    //! Forms url from base url (set in class constructor) + API version + method url
    /*!
        \return is used to simplify process of url creation
    */
    QString formUrl(QString url, QString version);

protected slots:
    //! Pure virtual slot that should be implemented in child class. This slot is connected to signal of QNetworkAccessManager object
    /*!
    */
    virtual void authenticationRequired(QNetworkReply *, QAuthenticator *) = 0;
    //! Pure virtual slot that should be implemented in child class this slot is connected to signal of QNetworkAccessManager object
    /*!
    */
    virtual void sslErrors(QNetworkReply *, const QList<QSslError> &) = 0;
    //! Pure virtual slot that should be implemented in child class this slot is connected to signal of QNetworkAccessManager object
    /*!
    */
    virtual void handleResponse(QNetworkReply *) = 0;

protected:
    //! QNetworkAccessManager object
    /*!
        \return QNetworkAccessManager object to REST API requests
    */
    QNetworkAccessManager *mgr() const;
    //! Returns version of API. By default it's "v1"
    /*!
        \return QString of API version. By default "v1"
    */
    QString getVersion(QNetworkReply*);
    //! Takes method name to clasify request
    /*!
        \return QString of request method
    */
    QString getCommand(QNetworkReply*);
    //! Forms request with standart headers
    /*!
        \return QNetworkRequest with prefilled headers
    */
    QNetworkRequest request(QUrl url);
    //! Server url for provided API version
    /*!
        \return Server url for provided API version
    */
    QByteArray serverUrl(QByteArray version);


private:
    QNetworkAccessManager* mMgr;
    QString mUrl;
    QString mAPIVersion;
    QString mToken;
};

#endif // QUWICORE_H
