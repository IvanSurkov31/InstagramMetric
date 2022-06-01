#include <QtWidgets>
#include <QtNetwork>

#include "httpwindow.h"

HttpWindow::HttpWindow(QWidget *parent)
    : QDialog(parent)
{
#ifndef QT_NO_SSL
    urlLineEdit = new QLineEdit("");
#else
    urlLineEdit = new QLineEdit("http://qt-project.org/");
#endif

    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName("");
    proxy.setPort(123);
    proxy.setUser("");
    proxy. setPassword ( "") ;
    QNetworkProxy::setApplicationProxy(proxy);

#ifndef QT_NO_SSL
    connect(&qnam, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            this, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
#endif

    setWindowTitle(tr("HTTP"));
    urlLineEdit->setFocus();
}

void HttpWindow::startRequest(QUrl url)
{
    reply = qnam.get(QNetworkRequest(url));

    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
}

void HttpWindow::downloadFile()
{

    url = urlLineEdit->text();
    startRequest(url);
}

void HttpWindow::httpFinished()
{
   this->CodeHtmltext+=reply->readAll();

}

#ifndef QT_NO_SSL
void HttpWindow::sslErrors(QNetworkReply*,const QList<QSslError> &errors)
{
    QString errorString;
    foreach (const QSslError &error, errors) {
        if (!errorString.isEmpty())
            errorString += ", ";
        errorString += error.errorString();
    }

    if (QMessageBox::warning(this, tr("HTTP"),
                             tr("One or more SSL errors has occurred: %1").arg(errorString),
                             QMessageBox::Ignore | QMessageBox::Abort) == QMessageBox::Ignore) {
        reply->ignoreSslErrors();
    }
}
#endif
