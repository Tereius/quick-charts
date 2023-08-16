#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char** argv)
{

  qunsetenv("QT_STYLE_OVERRIDE");
  qunsetenv("QT_QUICK_CONTROLS_STYLE");

  QApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.addImportPath("/home/bjoern/dev/source/quick-charts/cmake-build-debug/src");
  engine.addImportPath("/home/bjoern/dev/source/quick-charts/cmake-build-debug/controls");
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}
