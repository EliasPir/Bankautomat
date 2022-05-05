#include "withdraw.h"
#include "ui_withdraw.h"

withdraw::withdraw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::withdraw)
{
    ui->setupUi(this);

    timerSeconds = 0;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this,SLOT(doTimerSlot()));
    timer->start(1000);

    infotimer = new QTimer(this);
    connect(infotimer,SIGNAL(timeout()), this,SLOT(doInfoTimerSlot()));

}

withdraw::~withdraw()
{
    delete ui;
}

void withdraw::closeEvent(QCloseEvent *event)
{
    av->startTimer();
}

void withdraw::getInfo(QString currentAccount)
{
    qDebug()<<currentAccount;
    QString site_url="http://localhost:3000/asiakas/"+currentAccount;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(getInfoSlot(QNetworkReply*)));
    reply = manager->get(request);
}

void withdraw::getBalance(QString currentAccount)
{
    qDebug()<<currentAccount;
    QString site_url="http://localhost:3000/tili/"+currentAccount;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    manager2 = new QNetworkAccessManager(this);
    connect(manager2, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(getBalanceSlot(QNetworkReply*)));
    reply2 = manager2->get(request);
}

void withdraw::getInfoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    qDebug()<<response_data;
    foreach (const QJsonValue &value, json_array)
    {
        QJsonObject json_obj = value.toObject();
        ui->labelAccountInfo->setText(json_obj["etunimi"].toString()+"\n"+json_obj["sukunimi"].toString()+"\n"+json_obj["osoite"].toString()+"\n"+json_obj["puhnro"].toString());

    }
    reply->deleteLater();
    manager->deleteLater();
}

void withdraw::getBalanceSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    qDebug()<<response_data;
    foreach (const QJsonValue &value, json_array)
    {
        QJsonObject json_obj = value.toObject();
        ui->labelBalance->setText("Tilin saldo: "+QString::number(json_obj["saldo"].toDouble())+"€");
        qDebug()<<"Balance";

    }
    reply2->deleteLater();
    manager2->deleteLater();
}

void withdraw::doWithdrawSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    reply->deleteLater();
    qDebug()<<response_data;

    infotimer->stop();
    infotimer->start(8000);

    if(response_data != "true")
    {
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject jsonObject = json_doc.object();
        qDebug()<<(jsonObject["message"].toString());
        ui->labelInfoMessage->setText(jsonObject["message"].toString());
    }

    else
    {
        ui->labelInfoMessage->setText("Nosto suoritettu");
        qDebug()<<"Nostettu raha";
        getBalance(currentAccount);
    }
}

void withdraw::doWithdraw(QString amount)
{
    QJsonObject json;
    json.insert("tilinumero",currentAccount);
    json.insert("amount",amount);
    QString site_url="http://localhost:3000/withdraw/";
    QNetworkRequest request((site_url)); request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished (QNetworkReply*)), this, SLOT(doWithdrawSlot(QNetworkReply*)));
    reply = manager->post(request, QJsonDocument(json).toJson());
}

void withdraw::on_btnWithdraw20_clicked()
{
    doWithdraw("20");
    timerSeconds = 0;
}

void withdraw::on_btnWithdraw40_clicked()
{
    doWithdraw("40");
    timerSeconds = 0;
}

void withdraw::on_btnWithdraw60_clicked()
{
    doWithdraw("60");
    timerSeconds = 0;
}

void withdraw::on_btnWithdraw100_clicked()
{
    doWithdraw("100");
    timerSeconds = 0;
}

void withdraw::on_btnWithdraw200_clicked()
{
    doWithdraw("200");
    timerSeconds = 0;
}

void withdraw::on_btnWithdraw500_clicked()
{
    doWithdraw("500");
    timerSeconds = 0;
}

void withdraw::on_btnWithdrawCustom_clicked()
{
    doWithdraw(ui->lineWithdrawCustom->text());
    timerSeconds = 0;
    ui->lineWithdrawCustom->clear();
}

void withdraw::doTimerSlot()
{
    timerSeconds++;
    qDebug()<<"Sekunteja: "+QString::number(timerSeconds);

    if(timerSeconds >= 10)
    {
        timer->stop();
        close();
    }
}

void withdraw::doInfoTimerSlot()
{
        ui->labelInfoMessage->clear();
        infotimer->stop();
}


void withdraw::on_btnClose_clicked()
{
    timer->stop();
    close();
}


void withdraw::on_lineWithdrawCustom_textEdited()
{
    timerSeconds = 0;
}

