#include "serveur.h"
#include <QTcpSocket>

Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
}

void Server::demarrer()
{
    if (!tcpServer->listen(QHostAddress::Any, 1234)) {
        qCritical() << "Unable to start the server:" << tcpServer->errorString();
        return;
    }
    qDebug() << "Connecté au serveur !" << tcpServer->serverPort();
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::NewConnection);
}

void Server::NewConnection()
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QTcpSocket::disconnected, clientConnection, &QTcpSocket::deleteLater);
    qDebug() << "Nouveau client" << clientConnection->peerAddress().toString();
}
