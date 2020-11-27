#ifndef SERVEURWIDGET_H
#define SERVEURWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QHostInfo>
 #include <QSysInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class serveurWidget; }
QT_END_NAMESPACE

class serveurWidget : public QWidget
{
    Q_OBJECT

public:
    serveurWidget(QWidget *parent = nullptr);
    ~serveurWidget();
private slots:
    void on_pushButton_serveur_clicked();
    void onQtcpServer_newConnection();
    void onQTcpSocket_readyRead();
    void onQtcpSocket_disconneted();

private:
    Ui::serveurWidget *ui;
    QTcpServer *socketEcouteServeur;
    QTcpSocket *socketDialogueClient ;
};
#endif // SERVEURWIDGET_H
