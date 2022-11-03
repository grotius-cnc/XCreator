#ifndef XGRIDLAYOUT_H
#define XGRIDLAYOUT_H

#include <XOpenGLLine.h>

class XGridLayout : public XWidget {
public:
    XGridLayout(XWindow *theWindow){
        this->setWindow(theWindow);
          setScissorWindow(theWindow);
        myLine=new XOpenGLLine();
    }

    void setSize(XSize theSize){
        mySize->setSize(theSize);
    }
    //! Set the rows and colums.
    void setRowsAndColums(uint theRows, uint theColums){
        if(theRows==0){
            theRows=1;
            std::cerr<<"theRows set to minimal:1"<<std::endl;
        }
        if(myColums==0){
            myColums=1;
            std::cerr<<"theColums set to minimal:1"<<std::endl;
        }
        myRows=theRows;
        myColums=theColums;
    }
    void addWidgetToGridLayout(XWidget *theWidget, uint theRow, uint theColum){
        this->addWidget(theWidget);
        myCells.push_back({theWidget,theRow,theColum});
    }


    //! Draw the layout and the widgets.
    void draw(){
        //! Save the current scissor size to be restored at end of this function.
        saveScissorState();

        //! This can be confusing.
        if(hasParent()){
            this->setScissorUnion(ParentScissorSize(),mySize->Size());
        }

        drawBoundaryRectangular(myBoundaryOffset,myLineWidth);
        drawRows(myRows,myBoundaryOffset,myLineWidth);
        drawColums(myColums,myBoundaryOffset,myLineWidth);

        //! Set widget sizes.
        for(uint i=0; i<myCells.size(); i++){
            uint row= myCells.at(i).theRow;
            uint colum=myCells.at(i).theColum;

            uint cellwidth=(mySize->Width()-myBoundaryOffset-myBoundaryOffset)/myColums;
            uint x=0;
            x+=myBoundaryOffset;
            x+=cellwidth*colum;

            uint cellheight=(mySize->Height()-myBoundaryOffset-myBoundaryOffset)/myRows;
            uint y=0;
            y+=myBoundaryOffset;
            y+=cellheight*row;
            myCells.at(i).theWidget->setSize({{float(x),float(y),0},float(cellwidth),float(cellheight)});

            //myCells.at(i).theWidget->draw();
        }

        drawWidgetVec();
        restoreScissorState();
    }

private:
    struct XCell {
        XWidget *theWidget;
        uint theRow=0;
        uint theColum=0;
    };
    std::vector<XCell> myCells;

    XSize *mySize=new XSize();
    XOpenGLLine *myLine;
    uint myRows=1, myColums=1;
    uint myLineWidth=1;
    uint myBoundaryOffset=5;

    void drawRows(uint theRows, uint theBoundaryOffset, uint theLineWidth){
        uint theHeight=mySize->Height()-theBoundaryOffset-theBoundaryOffset;
        uint theHeightIncrement=theHeight/theRows;

        for(uint i=0; i<theHeight; i+=theHeightIncrement){

            uint s=theBoundaryOffset;
            XPoint a={mySize->Origin().X()+s,
                      mySize->Origin().Y()+s+i,
                      mySize->Origin().Z()};
            XPoint b={mySize->Origin().X()+mySize->Width()-s,
                      mySize->Origin().Y()+s+i,
                      mySize->Origin().Z()};

            myLine->drawLine(a,b,theLineWidth,{0.5,0.5,0.5,1.0},Window());
        }
    }

    void drawColums(uint theColums, uint theBoundaryOffset, uint theLineWidth){
        uint theWidth=mySize->Width()-theBoundaryOffset-theBoundaryOffset;
        uint theWidthIncrement=theWidth/theColums;

        for(uint i=0; i<theWidth; i+=theWidthIncrement){

            uint s=theBoundaryOffset;
            XPoint a={mySize->Origin().X()+s+i,
                      mySize->Origin().Y()+s,
                      mySize->Origin().Z()};
            XPoint b={mySize->Origin().X()+s+i,
                      mySize->Origin().Y()+mySize->Height()-s,
                      mySize->Origin().Z()};

            myLine->drawLine(a,b,theLineWidth,{0.5,0.5,0.5,1.0},Window());
        }
    }

    void drawBoundaryRectangular(uint theBoundaryOffset, uint theLineWidth){
        uint s=theBoundaryOffset;
        XPoint a={mySize->Origin().X()+s,
                  mySize->Origin().Y()+s,
                  mySize->Origin().Z()};
        XPoint b={mySize->Origin().X()+mySize->Width()-s,
                  mySize->Origin().Y()+s,
                  mySize->Origin().Z()};
        XPoint c={mySize->Origin().X()+mySize->Width()-s,
                  mySize->Origin().Y()+mySize->Height()-s,
                  mySize->Origin().Z()};
        XPoint d={mySize->Origin().X()+s,
                  mySize->Origin().Y()+mySize->Height()-s,
                  mySize->Origin().Z()};

        myLine->drawLine(a,b,theLineWidth,{0.5,0.5,0.5,1.0},Window());
        myLine->drawLine(b,c,theLineWidth,{0.5,0.5,0.5,1.0},Window());
        myLine->drawLine(c,d,theLineWidth,{0.5,0.5,0.5,1.0},Window());
        myLine->drawLine(d,a,theLineWidth,{0.5,0.5,0.5,1.0},Window());
    }
};

#endif
