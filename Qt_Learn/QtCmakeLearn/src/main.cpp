#include "mainwindow.h"
#include <QVBoxLayout>
#include <QApplication>
#include "fixedaspectratiolabel.h"
//#include "testUseOpencv.h"
int main(int argc, char *argv[])
{

    //testOpencvMain();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    printf("111111111\n");
    // QWidget w1;
    // QVBoxLayout *layout = new QVBoxLayout(&w1);

    // FixedAspectRatioLabel *label = new FixedAspectRatioLabel(&w1);
    // label->setAspectRatio(2.0); // 设置宽高比为2:1
    // label->setAlignment(Qt::AlignCenter);
    // label->setText("Fixed Aspect Ratio Label");
    // label->setStyleSheet("background-color: blue;");
    // layout->addWidget(label);
    // w1.setLayout(layout);
    // w1.show();
    return a.exec();
}
