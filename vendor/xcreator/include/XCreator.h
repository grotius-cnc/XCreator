#ifndef XCREATOR_H
#define XCREATOR_H

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include <XFace.h>
#include <XArc.h>
#include <XPolygon.h>
#include <XLine.h>
#include <XOpenGlCad.h>
#include <XSize.h>
#include <XRotate.h>
#include <XTexture.h>
#include <XTexturePlane.h>

//XArc *aArc;
//  XPolygon *aArcPolygon, *aSquareHole;
XLine *l;
XFace *mask, *face, *test;
XOpenGLCad *cad;
XSize *XSize;
XTexture *tex;
XTexturePlane *texp;

void setup(){

    XSize=new struct XSize();
    XSize->setX(1000);
    XSize->setY(1000);

    XPolygon aFace;
    aFace.setPointVec({{100,100,0},{500,100,0},{500,500,0},{100,500,0}});

    XPolygon aSquareHole;
    aSquareHole.setPointVec({{110,110,0},{120,110,0},{120,120,0},{110,120,0}});

    XArc aArc;
    aArc.setPoints({300,300,0},{300,300,0},{330,300,0},1);
    XPolygon aArcPolygon(aArc.PointVec());




    std::vector<XPolygon> aHoleVec;
    aHoleVec.push_back(aSquareHole);
    aHoleVec.push_back(aArcPolygon);


    test=new XFace(aFace,aHoleVec);

    face=new XFace(aFace,aHoleVec);

    tex=new XTexture("/home/user/XCreator/Icons/face-cool.png",300,600,0);

    texp=new XTexturePlane("/home/user/XCreator/Icons/face-cool.png",50,50,0,100,100);

    l=new XLine({500,500,0},{1000,1000,0});

}

void events(){



    // face->rotateAroundGravity(0.1);

    // face->draw();

    //    test->rotateAroundGravity(-0.1);
    //    test->draw();

    //aArcPolygon->draw();

    //    if(test->isPressed()){
    //        test->setFaceColor({XColorGreen});
    //    } else if (test->isMouseOnShape()){
    //        test->setFaceColor({XColorBlue});
    //    } else {
    //         test->setFaceColor({XColorBackGround});
    //    }


   // l->draw();

    tex->draw();
    texp->draw();



}
#endif // XCREATOR_H




//    cad=new XOpenGLCad(*new XFace(*new XPolygon ({{10,10,0},{310,10,0},{310,610,0},{10,610,0}})));

//    // If the cad drawing extends the widget boundary's we use a mask to paint over stuff we don't want to see.
//    XPolygon aHole=cad->Polygon();
//    XPolygon aWindow;
//    aWindow.setPointVec({{0,0,0},{0,1000,0},{1000,1000,0},{1000,0,0}});

//    mask=new XFace(aWindow,aHole);
//    mask->setFaceColor({XColorBlack});














