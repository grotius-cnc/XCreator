#include "XMainWindow.h"

int main(int argc, char** argv)
{
    std::string str;
    if(argc > 1){
           str = argv[1];
    }

    // Create new application.
    XMainWindow *MainWindow=new XMainWindow(str);
    // Show application.
    MainWindow->run();
}
