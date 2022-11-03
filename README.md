# XCreator, a c++ gui designer in development.

by Skynet Cyberdyne 2022.

To clone this repository including installing the submodules and automated install script :

    git clone --recurse-submodules https://github.com/grotius-cnc/XCreator.git XCreator
    
    To build the examples, visit the project build dir : ~/build/cmake .. && make

To start a new project :

	./newXProject  # This will ask you for a XProjectName.

Examples:

Opencascade implementation, notice the button widget on 
top of the opencascade widget :

![XDesignerDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XOpenCascadeTexture/XOpenCascadeTexture.jpg)

Linuxcnc capture gremlin screen, 
send it to a remote pc trough sockets, internet.
The code shows how to create python c++ bindings,
with a great performance. 

![XDesignerDialog](https://github.com/grotius-cnc/XCreator/blob/main/XLcncClientServer/XSocketServer.jpg)

OpenGl primitives :

![XDesignerDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XDrawOpenGLPrimitives/XDrawOpenGLPrimitives.jpg)

TextEditor, some work to do, but can be handy when code 
is updated at several points :

![XTextEditor](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XTextEdit/XTextEdit.jpg)

Ready to go ImageButtons that will pop up different dialogs like 
[FileOpen, FileSave, Message, Input, CheckList, ArrayInput, ColorChooser]

![XTextEditor](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XTinyDialogs/XTinyDialogs.jpg)

Terminal, a basic example how to interact with command-line interface :

![XFileOpenDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XTerminal/XTerminal.jpg)

Splitter layout, an sich a nice example  : 

![XFileOpenDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XHorizontalSplitterDialog/XHorizontalSplitterLayout.jpg)

Socket server client, in this example we tranfer data from client to server.
A more effiecent example is the XSocketServer example. Can also send text visa versa
and is more robust coded.

![XFileOpenDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XSocket/XSocket.jpg)

XGridLayout, a example how you can code a gridlayout.

![XFileOpenDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XGridLayout/XGridLayout.jpg)

XWindowNoBorder, a glfw window example without border.

![XFileOpenDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XWindowNoBorder/XWindowNoBorder.jpg)

XDeploy, create your .deb packages of your project to ship the final software. 
This includes creating desktop starters, menu entries, pre-and post scripts for installing etc. 
The whole circus in a nutshell.


This project is tested on:

    https://sourceforge.net/projects/linux-11-pro/

Project editor hints:

You can edit this project in Qt designer if you like to do so. 
Just open one of the CMakeList.txt files as project in Qt.
Qt will create a CMakeList.txt.user file... 







