#ifndef WITHDRAW_H
#define WITHDRAW_H

#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QString>
#include "accountview.h"

namespace Ui {
class withdraw;
}

class withdraw : public QWidget
{
    Q_OBJECT

public:
    explicit withdraw(QWidget *parent = nullptr);
    ~withdraw();
    void closeEvent(QCloseEvent *event);
    void getInfo(QString currentAccount);
    void getBalance(QString currentAccount);
    QString currentAccount;
    accountview *av;

private slots:
    void getInfoSlot (QNetworkReply *reply);
    void getBalanceSlot (QNetworkReply *reply2);
    void doWithdrawSlot(QNetworkReply *reply);
    void on_btnWithdraw20_clicked();
    void on_btnWithdraw40_clicked();
    void on_btnWithdraw60_clicked();
    void on_btnWithdraw100_clicked();
    void on_btnWithdraw200_clicked();
    void on_btnWithdraw500_clicked();
    void on_btnWithdrawCustom_clicked();
    void doTimerSlot();
    void doInfoTimerSlot();
    void on_btnClose_clicked();
    void on_lineWithdrawCustom_textEdited();

private:
    Ui::withdraw *ui;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *manager2;
    QNetworkReply *reply;
    QNetworkReply *reply2;
    QNetworkAccessManager *postManager;
    QByteArray response_data;
    void doWithdraw(QString amount);
    int timerSeconds;
    QTimer *timer;
    QTimer *infotimer;


};

#endif // WITHDRAW_H
