#ifndef ACCOUNTACTIONS_H
#define ACCOUNTACTIONS_H

#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QString>
#include "accountview.h"

namespace Ui {
class accountactions;
}

class accountactions : public QWidget
{
    Q_OBJECT

public:
    explicit accountactions(QWidget *parent = nullptr);
    ~accountactions();
    void closeEvent(QCloseEvent *event);
    void getActions(QString currentAccount);
    void getInfo(QString currentAccount);
    void getBalance(QString currentAccount);
    accountview *av;
    QString currentAccount;

private slots:
    void getInfoSlot (QNetworkReply *reply3);
    void getBalanceSlot (QNetworkReply *reply2);
    void getActionsSlot (QNetworkReply *reply);
    void doTimerSlot();
    void on_btnClose_clicked();

private:
    Ui::accountactions *ui;

    QNetworkAccessManager *manager;
    QNetworkAccessManager *manager2;
    QNetworkAccessManager *manager3;
    QNetworkReply *reply;
    QNetworkReply *reply2;
    QNetworkReply *reply3;
    QTimer *timer;
    int timerSeconds;
};

#endif // ACCOUNTACTIONS_H
