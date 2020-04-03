#include "quwiproject.h"

bool QuwiProject::hasStarred() const
{
    return mHasStarred;
}

void QuwiProject::setHasStarred(bool hasStarred)
{
    mHasStarred = hasStarred;
}

bool QuwiProject::isActive() const
{
    return mIsActive;
}

void QuwiProject::setIsActive(bool isActive)
{
    mIsActive = isActive;
}

int QuwiProject::position() const
{
    return mPosition;
}

void QuwiProject::setPosition(int position)
{
    mPosition = position;
}

QUrl QuwiProject::logoUrl() const
{
    return mLogoUrl;
}

void QuwiProject::setLogoUrl(const QUrl &logoUrl)
{
    mLogoUrl = logoUrl;
}

QString QuwiProject::uid() const
{
    return mUid;
}

void QuwiProject::setUid(QString uid)
{
    mUid = uid;
}

QString QuwiProject::name() const
{
    return mName;
}

void QuwiProject::setName(const QString &name)
{
    mName = name;
}

int QuwiProject::id() const
{
    return mId;
}

void QuwiProject::setId(int id)
{
    mId = id;
}

QList<int> QuwiProject::users() const
{
    return mUsers;
}

void QuwiProject::setUsers(const QList<int> &users)
{
    mUsers = users;
}
