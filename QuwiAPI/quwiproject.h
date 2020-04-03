#ifndef QUWIPROJECT_H
#define QUWIPROJECT_H

#include <QObject>
#include <QUrl>

class QuwiProject
{
public:
    bool hasStarred() const;
    void setHasStarred(bool hasStarred);

    bool isActive() const;
    void setIsActive(bool isActive);

    int position() const;
    void setPosition(int position);

    QUrl logoUrl() const;
    void setLogoUrl(const QUrl &logoUrl);

    QString uid() const;
    void setUid(QString uid);

    QString name() const;
    void setName(const QString &name);

    int id() const;
    void setId(int id);

private:
    int mId;
    QString mName;
    QString mUid;
    QUrl mLogoUrl;
    int mPosition;
    bool mIsActive;
    bool mHasStarred;
};

#endif // QUWIPROJECT_H
