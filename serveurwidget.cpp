#include "serveurwidget.h"
#include "ui_serveurwidget.h"

serveurWidget::serveurWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::serveurWidget)
    ,socketEcouteServeur(new QTcpServer)
    ,socketDialogueClient(nullptr)
{
    ui->setupUi(this);
    if( !socketEcouteServeur->listen(QHostAddress::Any,ui->spinBox_numport->value())){
        ui->listWidget->addItem("serveur sourd");
    }else{
        ui->listWidget->addItem("serveur en écoute");
        connect(socketEcouteServeur,&QTcpServer::newConnection,this,&serveurWidget::onQtcpServer_newConnection);

    }

}

serveurWidget::~serveurWidget()
{
    delete ui;
    delete socketEcouteServeur;
    delete socketDialogueClient;
}


void serveurWidget::on_pushButton_serveur_clicked()
{

}

void serveurWidget::onQtcpServer_newConnection()
{
    if(socketDialogueClient==nullptr){
        socketDialogueClient = socketEcouteServeur->nextPendingConnection();
        ui->listWidget->addItem("nouvelle connexion");
        connect(socketDialogueClient,&QTcpSocket::readyRead,this,&serveurWidget::onQTcpSocket_readyRead);
        connect(socketDialogueClient,&QTcpSocket::disconnected,this,&serveurWidget::onQtcpSocket_disconneted);
    }
}

void serveurWidget::onQTcpSocket_readyRead()
{
    ui->listWidget->addItem("reception");
    QChar commande;
    if(socketDialogueClient->bytesAvailable())
    {
        QByteArray tmp=socketDialogueClient->readAll();
        commande = tmp.at(0);

        QString messageCommande = "commande recue :"+ tmp +"";
        ui->listWidget->addItem(messageCommande);

        QString messageReponce = "Réponce envoyée : ";
        QString reponse;


        switch (commande.toLatin1()) {
        case 'u':
            reponse=getenv("USER");
            socketDialogueClient->write(reponse.toUtf8());
            ui->listWidget->addItem(messageReponce += reponse);

            break;
        case 'c':
            reponse=QSysInfo::machineHostName();
            socketDialogueClient->write(reponse.toUtf8());
            ui->listWidget->addItem(messageReponce += reponse);
            break;
        case 'o':
            reponse=QSysInfo::kernelType();
            socketDialogueClient->write(reponse.toUtf8());
            ui->listWidget->addItem(messageReponce += reponse);
            break;
        case 'a':
            reponse=QSysInfo::currentCpuArchitecture();
            socketDialogueClient->write(reponse.toUtf8());
            ui->listWidget->addItem(messageReponce += reponse);
            break;
        default:
            break;
        }

    }
}

void serveurWidget::onQtcpSocket_disconneted()
{
    ui->listWidget->addItem("déconnexion client");
    socketDialogueClient=nullptr;
}
