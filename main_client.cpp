#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client monClient;
    monClient.demarrer();

    return a.exec();
}
