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
    cuaSo.resize(400, 150);
    cuaSo.show();

    return app.exec();
}
