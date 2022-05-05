#include "accountview.h"
#include "ui_accountview.h"
#include "mainwindow.h"
#include "withdraw.h"
#include "balance.h"
#include "accountactions.h"

accountview::accountview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::accountview)
{
    ui->setupUi(this);

    timerSeconds = 0;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this,SLOT(doTimerSlot()));
    timer->start(1000);
}

accountview::~accountview()
{
    delete ui;
}

void accountview::on_btnGetBalance_clicked()
{
    timerSeconds = 0;
    timer->stop();

    balance *bc = new balance;
    bc->currentAccount=currentAccount;
    bc->getInfo(currentAccount);
    bc->getBalance(currentAccount);
    bc->getActions(currentAccount);
    bc->av=this;
    bc->show();
}

void accountview::on_btnLogout_clicked()
{
    timerSeconds = 0;
    timer->stop();
    close();
    qDebug()<<"Ulos kirjautuminen onnistui";
}

void accountview::getInfoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    qDebug()<<response_data;
    foreach (const QJsonValue &value, json_array)
    {
        QJsonObject json_obj = value.toObject();
        ui->labelWelcome->setText("Tervetuloa "+json_obj["etunimi"].toString()+" "+json_obj["sukunimi"].toString());

    }
    reply->deleteLater();
    manager->deleteLater();
}

void accountview::getInfo(QString cardnumber)
{
    qDebug()<<currentAccount;
    QString site_url="http://localhost:3000/asiakas/getByCardNumber/"+cardnumber;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished (QNetworkReply*)),
    this, SLOT(getInfoSlot(QNetworkReply*)));
    reply = manager->get(request);
}

void accountview::startTimer()
{
    timer->stop();
    timer->start(1000);
}


void accountview::on_btnWithdraw_clicked()
{
    timerSeconds = 0;
    timer->stop();

    withdraw *wd = new withdraw;
    wd->currentAccount=currentAccount;
    wd->getInfo(currentAccount);
    wd->getBalance(currentAccount);
    wd->av=this;
    wd->show();
    qDebug()<<"Rahan nostoon siirrytty";
}


void accountview::doTimerSlot()
{
    timerSeconds++;
    qDebug()<<"Sekunteja: "+QString::number(timerSeconds);

    if(timerSeconds >= 30)
    {
        timer->stop();
        close();
    }
}

void accountview::on_btnGetActions_clicked()
{
    timerSeconds = 0;
    timer->stop();

    accountactions *ac = new accountactions;
    ac->currentAccount=currentAccount;
    ac->getActions(currentAccount);
    ac->getInfo(currentAccount);
    ac->getBalance(currentAccount);
    ac->av=this;
    ac->show();
    qDebug()<<"Tilitapahtumiin siirrytty";
}

