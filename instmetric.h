#ifndef INSTMETRIC_H
#define INSTMETRIC_H

#include <QMainWindow>
#include "basicmetric.h"

class InstMetric : public QMainWindow
{
    Q_OBJECT

public:
    InstMetric(QWidget *parent = 0);
    ~InstMetric();
};

#endif // INSTMETRIC_H
