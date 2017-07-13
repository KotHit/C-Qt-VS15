#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
using namespace QtJson;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   

    if(isTokenValid()){
        ui->webView->hide();

        emit userInfo();
    }
    else{
        qDebug()<<"Авторизация";
        ui->webView->load(QUrl("https://api.instagram.com/oauth/authorize/?client_id=b899f7e65d254b2999c487bfdc9454f3&scope=basic+public_content+follower_list+relationships&redirect_uri=http://localhost/&response_type=token"));
    }

    connect(ui->webView,SIGNAL(urlChanged(QUrl)),this,SLOT(check_url(QUrl)));
    connect(ui->bt_user,SIGNAL(clicked(bool)),this,SLOT(userInfo()));
    connect(ui->bt_follows,SIGNAL(clicked(bool)),this,SLOT(unfollow()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QByteArray MainWindow::GET(QUrl r)
{    

    QNetworkAccessManager *manager=new QNetworkAccessManager(this);
    QNetworkReply *reply=manager->get(QNetworkRequest (r));

    QEventLoop wait;
    connect(manager,SIGNAL(finished(QNetworkReply*)),&wait,SLOT(quit()));

    QTimer::singleShot(10000,&wait,SLOT(quit()));
    wait.exec();
    qDebug()<<"Maybe error "+reply->error();
    QByteArray answer=reply->readAll();

    reply->deleteLater();
    return answer;
}

QByteArray MainWindow::POST(QUrl r,QUrlQuery query)
{
    QNetworkAccessManager *manager=new QNetworkAccessManager(this);

    QByteArray data;
    data.append(query.toString());

    QNetworkReply *reply=manager->post(QNetworkRequest(r),data);

    QEventLoop wait;
    connect(manager,SIGNAL(finished(QNetworkReply*)),&wait,SLOT(quit()));

    QTimer::singleShot(10000,&wait,SLOT(quit()));
    wait.exec();
    qDebug()<<"Request... "+reply->error();
    QByteArray answer=reply->readAll();

    reply->deleteLater();
    return answer;
}

void MainWindow::userInfo()
{
    qDebug()<<"userInfo run";
    QString s="https://api.instagram.com/v1/users/self/";

    QUrl url(s);

    QUrlQuery query;

    query.addQueryItem("access_token",settings::access);
    url.setQuery(query);

    QByteArray answer=GET(url);
    QVariantMap map=parse(answer).toMap().value("data").toMap();

    QString username=map.value("username").toString();
   // QString profile_picture=map.value("profile_picture").toString();
ui->plainTextEdit->insertPlainText(answer);

    QVariantMap map2=map.value("counts").toMap();

    QString follows=map2.value("follows").toString();
    QString followed_by=map2.value("followed_by").toString();

//    QPixmap *pix=new QPixmap;
//    QUrl img(profile_picture);
//    QByteArray b_img=GET(img);
//    pix->loadFromData(b_img);

    if(answer.contains("data")){
        ui->lb_user->setText(username);
     //   ui->lb_picture->setPixmap(*pix);
        ui->lb_follows->setText(follows);
        ui->lb_followed_by->setText(followed_by);
      qDebug()<<"Contains data";
    }

}
void MainWindow::check_url(QUrl url)
{

    url=url.toString().replace("#","?");
    settings::access=QUrlQuery(url).queryItemValue("access_token").toUtf8();

    if(settings::access.isEmpty()){
       qDebug()<<"no token there";
        return;
    }

  //  ui->le_token->setText(settings::access);
    settings::Save();
}


void MainWindow::about()
{
    qDebug()<<"followed_by run";

    QUrl url("https://api.instagram.com/v1/media/shortcode/BF_0b7fx8wJ");

    QUrlQuery query;
    query.addQueryItem("access_token",settings::code);
    url.setQuery(query);

    QByteArray answer=GET(url);

    QVariantList list=parse(answer).toMap().value("data").toMap().value("users_in_photo").toList();

    foreach(QVariant pl,list){
        QString str=pl.toMap()["user"].toMap()["username"].toString();
        ui->textEdit->append(str);
    }

    ui->plainTextEdit->insertPlainText(answer);//map["data"].toString()

}



bool MainWindow::isTokenValid()
{
    QString s="https://api.instagram.com/v1/users/self/";
    QUrl url(s);

    QUrlQuery query;
    query.addQueryItem("access_token",settings::access);
    url.setQuery(query);
    QByteArray answer=GET(url);

    if(answer.contains("data")){
      qDebug()<<"Contains data";
      return true;
    }
    return false;
}

void MainWindow::unfollow()
{
    QList<QString> followers=getFollowsList();
    QListIterator<QString> it(followers);
    while(it.hasNext()){
        QString s="https://api.instagram.com/v1/users/"+it.next()+"/relationship";
        QUrl url(s);

        QUrlQuery query;
        query.addQueryItem("access_token",settings::access);
        query.addQueryItem("action","unfollow");
        url.setQuery(query);

        QByteArray answer=POST(url,query);
        QVariantMap map=parse(answer).toMap().value("data").toMap();
        QString st=map.value("outgoing_status").toString();
      //  ui->textEdit->append(answer);
    }
    QMessageBox::information(this,"Unfollow","Unfollow user success!");
}

QList<QString> MainWindow::getFollowsList()
{
    QString s="https://api.instagram.com/v1/users/self/follows";
    QUrl url(s);

    QUrlQuery query;
    query.addQueryItem("access_token",settings::access);
    url.setQuery(query);

    QByteArray answer=GET(url);
    QVariantList list=parse(answer).toMap().value("data").toList();
  //  ui->textEdit->append(answer);
    QList<QString> array;
    int i=0;

    foreach(QVariant pl,list){
        i++;
     //   if(i<190){
        QString str=pl.toMap()["id"].toString();
        array<<str;
    //     ui->textEdit->append(str);
     //   }

    }
    return array;

}

QList<QString> MainWindow::getImageUrl()
{
//    QPixmap *img;

//    QString s="https://api.instagram.com/v1/users/self/follows";
//    QUrl url(s);

//    QUrlQuery query;
//    query.addQueryItem("access_token",settings::code);
//    url.setQuery(query);

}


