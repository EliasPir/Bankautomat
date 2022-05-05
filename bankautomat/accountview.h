#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#include <QWidget>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QString>

namespace Ui {
class accountview;
}

class accountview : public QWidget
{
    Q_OBJECT

public:
    explicit accountview(QWidget *parent = nullptr);
    ~accountview();
    QString currentAccount;
    void getInfo(QString cardnumber);
    void startTimer();

private slots:
    void on_btnGetBalance_clicked();
    void on_btnLogout_clicked();
    void getInfoSlot (QNetworkReply *reply);
    void on_btnWithdraw_clicked();
    void doTimerSlot();

    void on_btnGetActions_clicked();

private:
    Ui::accountview *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QNetworkAccessManager *postManager;
    QTimer *timer;
    int timerSeconds;
};

#endif // ACCOUNTVIEW_H
