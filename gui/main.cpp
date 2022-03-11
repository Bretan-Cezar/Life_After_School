#include <QApplication>
#include "StartGUI.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    StartGUI start_gui{};

    start_gui.show();

    return QApplication::exec();
}
