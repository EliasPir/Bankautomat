#ifndef BALANCE_H
#define BALANCE_H

#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QString>
#include "accountview.h"

namespace Ui {
class balance;
}

class balance : public QWidget
{
    Q_OBJECT

public:
    explicit balance(QWidget *parent = nullptr);
    ~balance();
    void closeEvent(QCloseEvent *event);
    QString currentAccount;
    void getInfo(QString currentAccount);
    void getBalance(QString currentAccount);
    void getActions(QString currentAccount);
    accountview *av;

private slots:
    void getInfoSlot (QNetworkReply *reply);
    void getBalanceSlot (QNetworkReply *reply2);
    void getActionsSlot (QNetworkReply *reply3);
    void on_btnClose_clicked();
    void doTimerSlot();

private:
    Ui::balance *ui;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *manager2;
    QNetworkAccessManager *manager3;
    QNetworkReply *reply;
    QNetworkReply *reply2;
    QNetworkReply *reply3;
    QByteArray response_data;
    QTimer *timer;
    int timerSeconds;
};

#endif // BALANCE_H
