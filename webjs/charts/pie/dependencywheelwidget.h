#ifndef DEPENDENCYWHEELWIDGET_H
#define DEPENDENCYWHEELWIDGET_H

#include <QMap>
#include <QSet>

#include "webjs/base/d3viewer.h"

namespace d3widgets {

class DependencyWheelWidget : public d3widgets::D3Viewer
{
    Q_OBJECT

public:
    explicit DependencyWheelWidget(QWidget *parent = 0);
    Q_PROPERTY(float padding READ padding WRITE setPadding)
    Q_PROPERTY(int margin READ margin WRITE setMargin)
    QString strDecoderjs;
    QString strCoderjs;

public slots:
    QVariant data();
    int margin();
    float padding();
    void setPadding(const float padding);
    void setMargin(const int margin);
    void appendDependency(const QString &from, const QString &to);
    void clearDependencies();
    void itemClicked();

    void setDecoderjs(const QString &str);
    QString getDecoderjs();

private:
    QMap<QString, QSet<QString> > dependencies;
    float mPadding;
    int mMargin;


signals:
    void update();
    void CoderUpdate();
};
}

#endif // DEPENDENCYWHEELWIDGET_H
