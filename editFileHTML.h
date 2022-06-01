#ifndef EDITFILEHTML_H
#define EDITFILEHTML_H


#include <QtWidgets>

namespace functions
{

QString fNamePublic(QString strfile)
{
    QStringList lstNamePublic=strfile.split("<title>");
    QString str=lstNamePublic[1];
    lstNamePublic=str.split("</title>");
    str=lstNamePublic[0];
    str.replace("\n","");
    return str;
}

QString fCountUser(QString strfile)
{
    QString str;
    QStringList lstNamePublic=strfile.split("edge_owner_to_timeline_media");
    str=lstNamePublic[1];
    lstNamePublic=str.split(",");
    str=lstNamePublic[0];
    lstNamePublic=str.split("{");
    str=lstNamePublic[1];
    lstNamePublic=str.split(":");
    str=lstNamePublic[1];
    return str;
}

QString fLinkPublic(QString strfile)
{
    QString str;
    QStringList lstNamePublic=strfile.split("x-default");
    str=lstNamePublic[0];
    lstNamePublic=str.split("link rel=\"alternate\" href=");
    str=lstNamePublic[2];
    lstNamePublic=str.split("hreflang");
    str=lstNamePublic[0];
    lstNamePublic=str.split("\"");
    str=lstNamePublic[1];
    return str;
}

QString fCountLike(QString strfile)
{
    QString str;
    QStringList lstNamePublic=strfile.split("edge_media_preview_like");
    str=lstNamePublic[1];
    lstNamePublic=str.split(",");
    str=lstNamePublic[0];
    lstNamePublic=str.split("count");
    str=lstNamePublic[1];
    lstNamePublic=str.split(":");
    str=lstNamePublic[1];
    str.replace("}","");
    return str;
}

QString fCountComment(QString strfile)
{
    QString str;
    QStringList lstNamePublic=strfile.split("edge_media_preview_comment");
    str=lstNamePublic[0];
    lstNamePublic=str.split(",");
    str=lstNamePublic[0];
    lstNamePublic=str.split("count");
    str=lstNamePublic[1];
    lstNamePublic=str.split(":");
    str=lstNamePublic[1];
    str.replace("}","");
    return str;
}

QString fFileRead(QString strNameFile,QWidget *parent)
{
    QString str;
    QFile file(strNameFile);

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(parent, QString::fromUtf8("Ошибка"), QString::fromUtf8("Ошибка открытия файла"));
        return str="Ошибка";
    }

    file.close();

    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        // qDebug()<<"stream.readAll()"<<stream.readAll();
        str=stream.readAll();
        file.close();
        if (stream.status()!=QTextStream::Ok){
            QMessageBox::critical(parent, QString::fromUtf8("Ошибка"), QString::fromUtf8("Ошибка записи с файла"));
            return str="Ошибка";
        }
    }
    return str;
}

void fFileWrite(QString strNameFile,QString strData,QString strIsWriteOnly){

    QFile file(strNameFile);
    if(strIsWriteOnly=="WriteOnly")
    {
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);
        stream<<strData;
        file.close();
        if (stream.status()!=QTextStream::Ok){
            qDebug()<<"Ошибка записи файла";
        }
    }
    }
    else
        {
        if(file.open(QIODevice::Append)){
            QTextStream stream(&file);
            stream<<strData;
            file.close();
            if (stream.status()!=QTextStream::Ok){
                qDebug()<<"Ошибка записи файла";
            }
        }
    }
}

QString fTextDecoder(QString strTextCode){

    QByteArray baOutputText;
    QTextCodec *codecUTF = QTextCodec::codecForName("UTF-8");
    baOutputText=codecUTF->fromUnicode(strTextCode);
    QString strTextDecoder;
    strTextDecoder=baOutputText;
    return strTextDecoder;
}

QString fEditTextDecoder(QString strTextCode){

    QRegExp reg("[0-9] {3,5}");

    QStringList lst=strTextCode.split("\\");
    strTextCode="";
    foreach (QString str, lst) {
        if(str.contains(reg)){
            strTextCode+="\\"+str;
        }
    }

    return strTextCode;
}

QVector<QPair<QString,QString> > fLinkPosts(QString strTextCode)
{
    QStringList lst_edge=strTextCode.split("edge_liked_by",QString::SkipEmptyParts);
    QVector<QPair<QString,QString> > vec;
    QString str,str_shortcode;
    QPair<QString,QString> par;

    QList<QString>::iterator it=lst_edge.end();
    for(;it!=lst_edge.begin();)
    {
        --it;
        str= *it;

        QStringList lst_shortcode=str.split("shortcode",QString::SkipEmptyParts);
        QStringList lst_timestamp=str.split("taken_at_timestamp",QString::SkipEmptyParts);

        if(lst_shortcode.count()==2 && lst_timestamp.count()==2)
        {
            lst_shortcode=lst_shortcode[1].split(",",QString::SkipEmptyParts);
            lst_timestamp=lst_timestamp[1].split(",",QString::SkipEmptyParts);

            if(lst_shortcode[0].isEmpty()==false && lst_timestamp[0].isEmpty()==false)
            {
                str_shortcode=lst_shortcode[0].replace("\":","");
                str_shortcode=str_shortcode.replace("\"","");
                par.first=lst_timestamp[0].replace("\":","");
                par.second="https://www.instagram.com/p/"+str_shortcode+"/";

                vec<<par;
            }
        }
    }
    qSort(vec);
    return vec;
}

QString fCaptionPost(QString strTextCode)
{
    QString str;
    QStringList lstCaptionPost=strTextCode.split("edge_media_to_caption");
    str=lstCaptionPost[1];
    lstCaptionPost=str.split("text\":\"");
    str=lstCaptionPost[1];
    lstCaptionPost=str.split("}");
    str=lstCaptionPost[0];

    return str;
}

QVector<QPair<QString,QString> > fCommentPost(QString strTextCode)
{
    QString str,str_username,str_text;
    QVector<QPair<QString,QString> > vec;
    QPair<QString,QString> par;
    QStringList lstCommentPost=strTextCode.split("media_to_parent_comment");
    str=lstCommentPost[1];

    lstCommentPost=str.split("\"username\":");

    QList<QString>::iterator it=lstCommentPost.begin();
    for(;it!=lstCommentPost.end();++it)
    {
        qDebug()<<"--------------------------------";
        qDebug()<<"--------------------------------";
        qDebug()<<*it;
        qDebug()<<"--------------------------------";
        qDebug()<<"--------------------------------";
        if(it!=lstCommentPost.begin()){
       //   str_username= *it;
       // lstCommentPost=str_username.split("}");
       // str_username=lstCommentPost[0];
       // par.first=str_username;

//        str_text=*it;
//        lstCommentPost=str_text.split("text\":");
//        str_text=lstCommentPost[1];
//        lstCommentPost=str_username.split("\"created_at\"");
//        str_text=lstCommentPost[0];
//        par.second=str_text;
//        vec<<par;
    }
    }

    return vec;
}

bool fEditPost(QString strPost,QString Keyword)
{
    QStringList lstPost;
    lstPost=strPost.split(" ");

    bool isKeyWord=false;

    QList<QString>::iterator it =
            qFind(lstPost.begin(),lstPost.end(),Keyword);
    if(it!=lstPost.end())
        isKeyWord=true;

    if(isKeyWord==false)
    {
        QList<QString>::iterator it =
            qFind(lstPost.begin(),lstPost.end(),Keyword+".");
    if(it!=lstPost.end())
        isKeyWord=true;
    }

    if(isKeyWord==false)
    {
    QList<QString>::iterator it =
            qFind(lstPost.begin(),lstPost.end(),Keyword+",");
    if(it!=lstPost.end())
        isKeyWord=true;
    }

    if(isKeyWord==false)
{
    QList<QString>::iterator it =
            qFind(lstPost.begin(),lstPost.end(),Keyword+"?");
    if(it!=lstPost.end())
        isKeyWord=true;
    }

    if(isKeyWord==false)
    {
    QList<QString>::iterator it =
            qFind(lstPost.begin(),lstPost.end(),Keyword+"!");
    if(it!=lstPost.end())
        isKeyWord=true;
    }

    return isKeyWord;

}

}



#endif // EDITFILEHTML_H
