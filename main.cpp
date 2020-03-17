#include <QApplication>
#include <string>
#include "cuasochinh.h"
#include "napdulieu.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CuaSoChinh cuaSo;
    cuaSo.setWindowTitle("Русский Язык");
//    cuaSo.setWindowFlags(Qt::WindowStaysOnTopHint);
    cuaSo.resize(500, 180);
    cuaSo.show();

    return app.exec();
}
