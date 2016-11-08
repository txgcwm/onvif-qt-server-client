#include <QNetworkConfigurationManager>
#include <QNetworkInterface>
#include <QNetworkSession>
#include <QInputDialog>
#include <QApplication>
#include <QHostInfo>
#include <QDebug>

#include "onvifserverthread.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString ipStr;
    QStringList ipStrs;
    int tcpPort = 8004;

    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol
                && address != QHostAddress(QHostAddress::LocalHost)){

            qDebug() << address.toString();
            ipStrs << address.toString();
        }
    }

    bool ok;

    ipStr = QInputDialog::getItem(NULL, "Select Server IP",
                                    "IPs:", ipStrs, 0, false, &ok);
    if (!ok || ipStr.isEmpty()) {
        qDebug() << "Server ip not selected";
        return 0;
    }

    qDebug() << "Selected ip" << ipStr;

    OnvifServerThread onvifServerThread(ipStr, tcpPort);

    onvifServerThread.start();

    return a.exec();
}


