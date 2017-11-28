#ifndef SAUVEGARDESETTINGS_H
#define SAUVEGARDESETTINGS_H

#include <QObject>
#include <QWidget>
#include <QSettings>

class SauvegardeSettings : public QSettings
{
    Q_OBJECT
public:
    explicit SauvegardeSettings(QWidget *parent = 0);

signals:

public slots:
};

#endif // SAUVEGARDESETTINGS_H
