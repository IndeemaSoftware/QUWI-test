#include "quwiprojectmodel.h"

QuwiProjectModel::QuwiProjectModel(QObject *parent) : QObject(parent)
{

}

QString QuwiProjectModel::name() const
{
    return mName;
}

void QuwiProjectModel::setName(const QString &name)
{
    mName = name;
}

QString QuwiProjectModel::logo_url() const
{
    return mLogoUrl;
}

void QuwiProjectModel::setLogoUrl(const QString &logoUrl)
{
    mLogoUrl = logoUrl;
}
