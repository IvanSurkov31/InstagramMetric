#ifndef BASICMETRIC_H
#define BASICMETRIC_H

#include <QWidget>
#include "httpwindow.h"
#include <QtWidgets>
#include "webjs/charts/pie/dependencywheelwidget.h"

class QLabel;
class QLineEdit;
class QTextEdit;
class QPushButton;

class BasicMetric : public QWidget
{
    Q_OBJECT
public:
    explicit BasicMetric(QWidget *parent = 0);

    ~BasicMetric();

private:
    QLabel* lblPublic;
    QLabel* lblDateTime;
    QLabel* lblUpdate;
    QLineEdit* leditPublic;
    QTextEdit* teditInfoMetric;
    QPushButton* pbDownload;
    QPushButton* pbStop;
    QComboBox*  cbPublic;
    QSpinBox*  sbUpdate;

    QString namePublic;
    QVector<QPair<QString,QString> > vecLinkPosts;

    int countUrlPosts;

    HttpWindow* httpwind;

    d3widgets::DependencyWheelWidget *dependencyWheelWidget ;

public slots:

    void slotClicked();
    void slotclq();
    void slotSetPost();
    void slotGetPost();

};

class postInsta
{
private:

    QString link;
    QString namePublic;
    int countLike;
    int countComment;
    int countRepost;
    int countHashtag;

public:
    postInsta(QString strlink, QString strNamePublic,int cLike,int cComment,int cRepost,int cHashtag):link(strlink),
        namePublic(strNamePublic),countLike(cLike),countComment(cComment),countRepost(cRepost),countHashtag(cHashtag){}

    ~postInsta(){}

    void setCountLike(int cLike ){countLike=cLike;}
    void setcountComment(int cComment ){countComment=cComment;}
    void setcountRepost(int cRepost ){countRepost=cRepost;}
    void setcountHashtag(int cHashtag ){countHashtag=cHashtag;}

    int getcountComment(){return countComment;}
    int getCountLike(){return countLike;}
    int getcountRepost(){return countRepost;}
    int getcountHashtag(){return countHashtag;}

};

#endif // BASICMETRIC_H
