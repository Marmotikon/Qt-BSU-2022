#include <QApplication>

#include "controller/controller.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  Controller controller;

  return QApplication::exec();
}
