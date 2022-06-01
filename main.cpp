#include "instmetric.h"
#include <QApplication>
#include "webjs/charts/pie/dependencywheelwidget.h"
#include <QDebug>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BasicMetric bm;
    bm.show();

    //for (int i = 0; i < 1 ; i++) //для тестирования затрат памяти
   // {
   // d3widgets::DependencyWheelWidget *dependencyWheelWidget = new d3widgets::DependencyWheelWidget();

    //setDependencies(dependencyWheelWidget);
   // dependencyWheelWidget->setMargin(200);
    //dependencyWheelWidget->show();
   // }

    return a.exec();
}
