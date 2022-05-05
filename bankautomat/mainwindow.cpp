#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "accountview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::loginSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();

    if(response_data == "true")
    {
        QString site_url="http://localhost:3000/kortti/"+currentCardnumber;
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished (QNetworkReply*)),
        this, SLOT(cardInfo(QNetworkReply*)));
        manager->get(request);
    }
    else
    {
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject jsonObject = json_doc.object();
        qDebug()<<(jsonObject["message"].toString());
        ui->labelErrorMessage->setText(jsonObject["message"].toString());
    }
}

void MainWindow::cardInfo (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array)
    {
        QJsonObject json_obj = value.toObject();
        currentAccount = QString::number(json_obj["tilinumero"].toInt());
    }
    qDebug()<<currentAccount;
    reply->deleteLater();
    manager->deleteLater();

    if(currentAccount != "")
    {
        accountview *av = new accountview;
        av->currentAccount=currentAccount;
        av->show();
        av->getInfo(currentCardnumber);
        qDebug()<<"Kirjautuminen onnistui";
    }
}

void MainWindow::on_btnLogin_clicked()
{
    QJsonObject json;
    json.insert("korttinumero",ui->lineCard->text());
    json.insert("pin",ui->linePin->text());
    currentCardnumber = ui->lineCard->text();

    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    ui->lineCard->clear();
    ui->linePin->clear();
    ui->labelErrorMessage->clear();

    reply = postManager->post(request, QJsonDocument(json).toJson());
}
