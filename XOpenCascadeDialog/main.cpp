#include "XMainWindow.h"

int main(int argc, char** argv)
{
    // Create new application.
    XMainWindow *MainWindow=new XMainWindow("XFileDialog",800,500);
    // Show application.
    MainWindow->run();
}


