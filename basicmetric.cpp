#include "basicmetric.h"
#include <QtWidgets>
#include "editFileHTML.h"
#include "webjs/charts/pie/dependencywheelwidget.h"

BasicMetric::BasicMetric(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *HBLtopLayout = new QHBoxLayout;
    QVBoxLayout *VBLmainLayout = new QVBoxLayout;
    QHBoxLayout *HBLdownloadLayout = new QHBoxLayout;
    QHBoxLayout *HBLupdateLayout = new QHBoxLayout;
    QHBoxLayout *HBLstopLayout = new QHBoxLayout;

    lblPublic=new QLabel("Паблик");
    leditPublic=new QLineEdit("https://www.instagram.com/go_voronezh/");
    teditInfoMetric=new QTextEdit;

    lblDateTime=new QLabel;
    pbDownload=new QPushButton("Начать мониторинг");
    pbStop=new QPushButton("Остановить");

    lblUpdate=new QLabel("Время обновления (каждый/час)");
    sbUpdate=new QSpinBox;
    sbUpdate->setMinimum(1);
    sbUpdate->setMaximum(24);

    cbPublic=new QComboBox;
    QStringList lst;
    lst=functions::fFileRead("Publics.txt",this).split(";");
    cbPublic->addItems(lst);

    httpwind=new HttpWindow;
    httpwind->urlLineEdit->setText(leditPublic->text());

    HBLupdateLayout->addWidget(lblUpdate);
    HBLupdateLayout->addWidget(sbUpdate);
    HBLupdateLayout->addStretch();

    HBLtopLayout->addWidget(lblPublic);
    HBLtopLayout->addWidget(cbPublic);

    HBLstopLayout->addWidget(pbStop);
    HBLstopLayout->addStretch();

    HBLdownloadLayout->addWidget( pbDownload);
    HBLdownloadLayout->addWidget(lblDateTime);
    HBLdownloadLayout->addStretch(1);
    HBLdownloadLayout->addStretch();
    VBLmainLayout->addLayout(HBLtopLayout);
    VBLmainLayout->addLayout(HBLdownloadLayout);
    VBLmainLayout->addLayout(HBLstopLayout);
    VBLmainLayout->addLayout( HBLupdateLayout);
    VBLmainLayout->addWidget(teditInfoMetric);

    this->setLayout(VBLmainLayout);

    connect(pbDownload, SIGNAL(clicked()),
            this, SLOT(slotClicked()));

}

void BasicMetric::slotClicked()
{
    this->pbDownload->setEnabled(false);

    QDateTime dtCurrent;
    QString strDateTime = dtCurrent.date().currentDate().toString("dd/MM/yy") + dtCurrent.time().currentTime().toString("h:m");
    this->lblDateTime->setText(strDateTime);

    QString strLinkPublic=cbPublic->currentText();
    strLinkPublic="https://www.instagram.com/"+strLinkPublic+"/";
    qDebug()<<strLinkPublic;
    httpwind->urlLineEdit->setText(strLinkPublic);
    httpwind->downloadFile();

    QTimer::singleShot(2000,this,SLOT(slotclq()));

}

void BasicMetric::slotclq(){

    QString strCodeHtml=httpwind->CodeHtmltext;

    httpwind->CodeHtmltext="";
    vecLinkPosts=functions::fLinkPosts(strCodeHtml);

    countUrlPosts=vecLinkPosts.count()-1;
  
    httpwind->urlLineEdit->setText(vecLinkPosts.at(vecLinkPosts.count()-1).second);
    httpwind->downloadFile();

    QTimer::singleShot(1000,this,SLOT(slotSetPost()));
}

void BasicMetric::slotSetPost(){

    QString strCaptionPost=httpwind->CodeHtmltext;


    httpwind->CodeHtmltext="";

    QString strCode=functions::fCaptionPost(strCaptionPost);
    QString strFile1="<!DOCTYPE html><html ><head><meta charset=utf-8\"> \n" \
            "<title></title></head><body><p id=\"demo\"> \n" \
            "</p><script>var str=\"";
    QString strFile2="\"; \n  function fdecoder(){document.getElementById(\"demo\").innerHTML = str; \n"\
            "api.setDecoderjs(str);}fdecoder(); \n"\
            "api.update.connect(fdecoder);</script></body></html>";
    strCode.replace("\"","");
    strCode=strFile1+strCode+strFile2;

    functions::fFileWrite("index.html",strCode,"WtiteOnly");

    dependencyWheelWidget = new d3widgets::DependencyWheelWidget();

    QTimer::singleShot(6000,this,SLOT(slotGetPost()));

    if(countUrlPosts!=1)
    {qDebug()<<"qqq"<<vecLinkPosts.at(countUrlPosts).second;
        qDebug()<<countUrlPosts;
        httpwind->urlLineEdit->setText(vecLinkPosts.at(countUrlPosts).second);
        httpwind->downloadFile();

        QTimer::singleShot(4000,this,SLOT(slotSetPost()));
    }
    else
    {
        this->pbDownload->setEnabled(false);
        this->sbUpdate->setEnabled(false);
        this->cbPublic->setEnabled(false);
    }
    countUrlPosts--;
}

void BasicMetric::slotGetPost()
{
    bool isKeyWorld;
    QStringList lstWordCaptionPost;
    QString strDecoderCaptionPost=dependencyWheelWidget->getDecoderjs();
    QString strUrlPosttoKeyWorld;
    QStringList lstKeywords;

    lstKeywords=functions::fFileRead("Keywords.txt",this).split(";",QString::SkipEmptyParts);


    strDecoderCaptionPost=strDecoderCaptionPost.toLower();
  //  qDebug()<<"--------------------";
  //  qDebug()<<strDecoderCaptionPost;
  //  qDebug()<<"--------------------";

    this->pbDownload->setEnabled(true);
    foreach (QString strKeyWorld, lstKeywords) {
        isKeyWorld=functions::fEditPost(strDecoderCaptionPost,strKeyWorld);
        if(isKeyWorld==true)
        {//qDebug()<<"ДА";
            strUrlPosttoKeyWorld="\r\n"+strKeyWorld+";"+vecLinkPosts.at(countUrlPosts).second+"\r\n";
            functions::fFileWrite(cbPublic->currentText()+".txt",strUrlPosttoKeyWorld,"WtiteOnly");
            return;
        }

    }

    this->pbDownload->setEnabled(true);
    this->sbUpdate->setEnabled(true);
    this->cbPublic->setEnabled(true);

}

BasicMetric::~BasicMetric()
{

}
