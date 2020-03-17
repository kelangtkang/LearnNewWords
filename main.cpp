#include <QApplication>
#include <string>
#include "cuasochinh.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CuaSoChinh cuaSo;
    cuaSo.setWindowTitle("Русский Язык");
    cuaSo.setMinimumSize(400, 170);
    cuaSo.show();

    return app.exec();
}
