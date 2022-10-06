# XCreator

A Work in progress of Skynet Cyberdyne 2022.

This project is precompiled on linux-pro amd64, 

	https://sourceforge.net/projects/linux-11-pro/

This project is programmed for using with OpenGL 3.0 or higher.
If you want to use a lower OpenGL version, you have to downgrade the openGL shader language inside the xcreator code yourself. 

To clone this repository :
	git clone https://github.com/grotius-cnc/XCreator.git


![XDesignerDialog](https://user-images.githubusercontent.com/44880102/194404378-7965d88d-a66b-4fd6-8747-61146b25c7c8.jpg)

![XFileOpenDialog](https://user-images.githubusercontent.com/44880102/194404395-12e6be5d-ba60-4a6e-bd87-ab3418a3d4db.jpg)

![XTextEditor](https://user-images.githubusercontent.com/44880102/194404400-12750fca-4301-4aa4-a9c4-6ff7d00b8811.jpg)

To rebuild the dependencies in the "/vendor" directory, you can remove all content in "build" dir, then in terminal : cmake .. && make

The same is for the "XDesignerDialog" directory. Remove content in "build", in terminal : cmake .. && make

For the "/vendor/freetype-2.12.1" library I advise to do a "make install" afterwards. On my pc the compile flags for this lib only work
when pointing to the local system dir. You can check the CMakeList.txt for this.

You can edit this project in Qt designer if you like to do so. Just open one of the CMakeList.txt files in Qt.
Qt will create a CMakeList.txt.user file... 




