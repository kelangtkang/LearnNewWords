#include <string>
#include "cuasochinh.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CuaSoChinh cuaSo;
    cuaSo.setWindowTitle("Русский Язык");
    //cuaSo.setWindowIcon(QIcon(":/icon/Beat_2000x2000.svg"));
    cuaSo.setWindowIcon(QIcon(":/icon/Beat_64x64.png"));
    //cuaSo.setMinimumSize(400, 170);

    cuaSo.show();

    return app.exec();
}
