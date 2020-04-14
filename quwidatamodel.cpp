#include "quwidatamodel.h"

QuwiDataModel::QuwiDataModel(QObject *parent) : QObject(parent)
{

}

QuwiProjectModel *QuwiDataModel::data() const
{
    return mData;
}

void QuwiDataModel::setData(QuwiProjectModel *data)
{
    mData = data;
}
