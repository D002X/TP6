#include "serveur.h"
#include <QTcpServer>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server serveur;
    serveur.demarrer();
    return a.exec();
}
