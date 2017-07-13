#include "settings.h"
#include <QDebug>
QString settings::code="no token";
QByteArray settings::access;

settings::settings()
{

}
void settings::Save(QString file_name){
    QFile f(file_name);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        qDebug()<<"Cannot save file";
        return;
    }
    qDebug()<<"runnig";
    f.write(settings::access);
    f.close();
    qDebug()<<"insert success";

}
void settings::Load(QString file_name){
    QFile f(file_name);
    if(!f.open(QIODevice::ReadOnly)){
        qDebug()<<"cannot load file";
        return;
    }
//    QDataStream stream;
//    QVariantMap l;
//    stream>>l;
//    f.close();
//    if(l.contains("access_token"))
//        code=l.value("access_token").toString();
    settings::access=f.readAll();
    f.close();
    qDebug()<<"read success";
}
