# XCreator

A Work in progress, by Skynet Cyberdyne 2022.

Specification:

	Written in C++.
	Widget style program.
	Qt replacer.
	Header only.
	Uses modern OpenGL.
	No template functions used, no by reference "&" used.

To clone this repository including installing the submodules and automated install script :
	
	git clone --recurse-submodules https://github.com/grotius-cnc/XCreator.git XCreator
	cd XCreator
	./setup

To start a new project :

	./newXProject  # This will ask you for a XProjectName.

Examples:

Opencascade implementation, notice the button widget on top of the opencascade widget :

![XDesignerDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XOpenCascadeTexture/XOpenCascadeTexture.jpg)

Linuxcnc capture gremlin screen, send it to a remote pc trough sockets, internet :

![XDesignerDialog](https://github.com/grotius-cnc/XCreator/blob/main/XLcncClientServer/XSocketServer.jpg)

OpenGl primitives :

![XDesignerDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XDrawOpenGLPrimitives/XDrawOpenGLPrimitives.jpg)

TextEditor :

![XTextEditor](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XTextEditorDialog/XTextEditorDialog.jpg)

Ready to go ImageButtons that will pop up different dialogs like [FileOpen, FileSave, Message, Input, CheckList, ArrayInput, ColorChooser]

![XTextEditor](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XTinyDialogs/XTinyDialogs.jpg)

Terminal :

![XFileOpenDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XTerminal/XTerminal.jpg)

Splitter layout : 

![XFileOpenDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XHorizontalSplitterDialog/XHorizontalSplitterLayout.jpg)

Socket server client, in this example we tranfer data from client to server : 

![XFileOpenDialog](https://raw.githubusercontent.com/grotius-cnc/XCreator/main/XSocket/XSocket.jpg)

This project is tested on:

	https://sourceforge.net/projects/linux-11-pro/

Project editor hints:

	You can edit this project in Qt designer if you like to do so. 
	Just open one of the CMakeList.txt files as project in Qt.
	Qt will create a CMakeList.txt.user file... 


	
	
	


