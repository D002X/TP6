#ifndef SERVEUR_H
#define SERVEUR_H

#include <QTcpServer>
#include <QObject>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    void demarrer();

private:
    QTcpServer *tcpServer;

public slots:

    void NewConnection();
};
#endif // SERVEUR_H
