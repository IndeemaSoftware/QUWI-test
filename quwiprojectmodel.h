#ifndef QUWIPROJECTMODEL_H
#define QUWIPROJECTMODEL_H

#include <QObject>

class QuwiProjectModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString nLogoUrl READ logo_url WRITE setLogoUrl NOTIFY logoUrlChanged)
public:
    explicit QuwiProjectModel(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QString logo_url() const;
    void setLogoUrl(const QString &logo_url);

signals:
    void logoUrlChanged();

private:
    QString mName;
    QString mLogoUrl;
};

#endif // QUWIPROJECTMODEL_H
