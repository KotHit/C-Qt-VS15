#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settings.h"
#include "json.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QVariantList>
#include <QPixmap>
#include <QTimer>
#include <QEvent>
#include <QMainWindow>
#include <QDataStream>
#include <QUrlQuery>
#include <QDebug>
#include <QFile>
#include <QMap>
#include <QUrl>
#include <QNetworkRequest>
#include <QScopedPointer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QFile file;

private:
    Ui::MainWindow *ui;
    QByteArray GET(QUrl);
    QByteArray POST(QUrl,QUrlQuery);
    QByteArray access_token;
    QList<QString> getFollowsList();
    QList<QString> getImageUrl();

private slots:
    void check_url(QUrl);
public slots:
    void userInfo();
    void about();
    bool isTokenValid();
    void unfollow();
  //  void saveImage();

signals:
    void auth_success();
};

#endif // MAINWINDOW_H
