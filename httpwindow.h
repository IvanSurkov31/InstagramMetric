#ifndef HTTPWINDOW_H
#define HTTPWINDOW_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QUrl>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFile;
class QLabel;
class QLineEdit;
class QProgressDialog;
class QPushButton;
class QSslError;
class QAuthenticator;
class QNetworkReply;

QT_END_NAMESPACE

class HttpWindow : public QDialog
{
    Q_OBJECT

public:
    HttpWindow(QWidget *parent = 0);

    void startRequest(QUrl url);

    QLineEdit *urlLineEdit;
    QNetworkReply *reply;
    QString CodeHtmltext;
    bool httpRequestAborted;


public slots:
     void downloadFile();

private slots:

    void httpFinished();

#ifndef QT_NO_SSL
    void sslErrors(QNetworkReply*,const QList<QSslError> &errors);
#endif

private:

    QUrl url;
    QNetworkAccessManager qnam;

};

#endif
