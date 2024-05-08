#include <QWidget>
#include <QWindow>
#include <QTimer>
#include <QLabel>
#include <QQmlContext>
#include <QQuickWidget>
#include <QQmlComponent>
#include <QApplication>
#include <QQmlApplicationEngine>


int main(int argc, char *argv[]) {

    //将样式设置为Basic，不然会导致组件显示异常
    qputenv("QT_QUICK_CONTROLS_STYLE","Basic");
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

//    QQuickWidget *qmlWidget = new QQuickWidget(QUrl("qrc:/qml/main.qml"));
//    qmlWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
//    qmlWidget->resize(800, 600);
//    qmlWidget->show();

    // 绑定到QT 同时设置窗口大小
//    QWidget *m_widget = QWidget::createWindowContainer(m_window);
//    m_widget->setMinimumSize(width, height);
//    m_widget->show();
    return app.exec();
}