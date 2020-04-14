#ifndef QUWIDATAMODEL_H
#define QUWIDATAMODEL_H

#include <QObject>

#include "quwiprojectmodel.h"

class QuwiDataModel : public QObject
{
    Q_OBJECT
public:
    explicit QuwiDataModel(QObject *parent = nullptr);

    QuwiProjectModel *data() const;
    void setData(QuwiProjectModel *data);

private:
    QuwiProjectModel *mData;
};

#endif // QUWIDATAMODEL_H
