#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFile>
#include <QDataStream>


class settings
{
public:
    settings();

    static QString code;
    static QByteArray access;
    static void Load(QString file_name="1.txt");
    static void Save(QString file_name="1.txt");
};

#endif // SETTINGS_H
