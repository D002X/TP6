#include "client.h"
#include <QtNetwork/QHostAddress>

Client::Client(QObject *parent) : QObject(parent)
{
    qDebug() << QString::fromUtf8("Instancie un objet QTcpSocket");
    tcpSocket = new QTcpSocket(this); // 1.
    qDebug() << QString::fromUtf8("Creation de la socket et visualisation de l etat de la socket :") << tcpSocket->state();

    QObject::connect(tcpSocket, &QTcpSocket::connected, this, &Client::estConnectee); // Remplissage du connect
    QObject::connect(tcpSocket, &QTcpSocket::disconnected, this, &Client::estDeconnectee); // Remplissage du connect
    QObject::connect(tcpSocket, &QTcpSocket::errorOccurred, this, &Client::gestionErreur); // Remplissage du connect
    QObject::connect(tcpSocket, &QTcpSocket::readyRead, this, &Client::recevoir); // Remplissage du connect
}

Client::~Client()
{
    qDebug() << QString::fromUtf8("Ferme la socket");
    tcpSocket->close();
}

void Client::demarrer()
{
    qDebug() << QString::fromUtf8("Connexion au serveur");
    tcpSocket->connectToHost(QHostAddress::LocalHost, PORT_SERVEUR); // 2. (ici le serveur sera localhost)
    qDebug() << QString::fromUtf8("État de la connexion de la socket :") << tcpSocket->state();
}

void Client::estConnectee()
{
    qDebug() << QString::fromUtf8("Le client est bien connecte au serveur ayant pour adresse :") << this->tcpSocket->peerAddress().toString() << "\n";
    qDebug() << QString::fromUtf8("et pour port :") << this->tcpSocket->peerPort() << "\n";
    qDebug() << "Connecté au serveur !";
    this->envoyer("Bonjour a vous ! ");
}

void Client::estDeconnectee()
{
    qDebug() << QString::fromUtf8("Le client est bien deconnecte");
    tcpSocket->deleteLater();
}

void Client::gestionErreur(QAbstractSocket::SocketError erreur)
{
    qDebug() << QString::fromUtf8("Une erreur s est produite sur la socket : ") << tcpSocket->errorString();
    qDebug() << QString::fromUtf8("Message d'erreur :") << erreur;
}

void Client::recevoir()
{
    QByteArray data = tcpSocket->readAll(); // Lire toutes les données reçues
    qDebug() << "Des donnes ont ete reçues : " << data << "\n"; // afficher les données reçues dans un qdebug ici....
}

void Client::envoyer(QByteArray message)
{
    qint64 ecrits = tcpSocket->write(message);
    if (ecrits == -1) {
        qDebug() << QString::fromUtf8("Erreur lors de l’envoi !");
    } else {
        qDebug() << QString::fromUtf8("Message envoyé : ") << message;
        qDebug() << QString::fromUtf8("Octets envoyés : ") << ecrits;
        qDebug() << QString::fromUtf8("Message envoyé avec succès !");
    }
}
