#ifndef XCHUNKER_H
#define XCHUNKER_H

/*
        Copyright (c) 2022 Skynet Cyberdyne

        This software is provided 'as-is', without any express or implied
        warranty. In no event will the authors be held liable for any damages
        arising from the use of this software.

        Permission is granted to anyone to use this software for any purpose,
        excluding commercial applications, and to alter it and redistribute it
        freely, subject to the following restrictions:

        1. The origin of this software must not be misrepresented; you must not
           claim that you wrote the original software. If you use this software
           in a product, an acknowledgment in the product documentation would
           be appreciated but is not required.

        2. Altered source versions must be plainly marked as such, and must not
           be misrepresented as being the original software.

        3. This notice may not be removed or altered from any source
           distribution.
*/

#include <GL/gl.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <lodepng.h>

//! Consider using a typedef.
typedef std::vector<std::vector<GLubyte>> XChunks;
typedef std::vector<GLubyte> XChunk;
//! The data of a png texture. *pixels, buffersize.
typedef std::pair<GLubyte*,size_t> XPngPixmap;
//! Chunker to create a serie of packages from a file to send over socket. The data is a openGl texture, cq pixmap.
class XChunker {
public:
    //! Empty constructor.
    XChunker(){}
    //! Destructor.
    ~XChunker(){}
    //! Load a picture from file into a png texture.
    XPngPixmap loadPngTextureFromFile(std::string theFileName){
        GLubyte *thePixels;
        size_t theSize;
        lodepng_load_file(&thePixels,&theSize,theFileName.c_str());
        return {thePixels,theSize};
    }
    //! Load a .png picture into chunks, given a package size.
    XChunks loadPictureIntoChunks(std::string theFileName, size_t thePackageSize){
        GLubyte *thePixels;
        size_t theSize;
        lodepng_load_file(&thePixels,&theSize,theFileName.c_str());
        return pngPixmapToChunks(thePixels,theSize,thePackageSize);
    }
    void savePictureFromChunks(std::string theFileName, XChunks theChunks){
        std::pair<GLubyte*,size_t> thePng=chunksToPngPixmap(theChunks);
        lodepng_save_file(thePng.first,thePng.second,theFileName.c_str());
    }
    
    //! Function to glue back packages together into original .png picture.
    //!
    //!     - theChunks             THe vector of packages.
    //!     - Return                a pair, contaning *pixels and size of the pixel buffer. *pixels is a array of pixels[i]
    //!
    std::pair<GLubyte*,size_t> chunksToPngPixmap(std::vector<std::vector<GLubyte>> theChunks){
        return glueChunks(theChunks);
    }
    //! Function to pack a openGl texture, cq pixmap into packages of given size. The last package will fit to the buffersize.
    //!
    //!     - thePixels             The OpenGl *data or Texture *data.
    //!     - thePixelBufferSize    The image width*height*channels, or the size of thePixels.
    //!     - thePackageSize        The desired package size or chunk size in Kib*1000 or GluBytes.
    //!     - Return                A vector of packages.
    //!
    std::vector<std::vector<GLubyte>> pngPixmapToChunks(GLubyte *thePixels, size_t thePixelBufferSize, size_t thePackageSize){
        return createChunks(thePixels,thePixelBufferSize,thePackageSize);
    }
    //! Or the same function where a XPngPixmap is used. Pixmap(*pixels,size), thePackageSize = desired chunk size.
    std::vector<std::vector<GLubyte>> pngPixmapToChunks(XPngPixmap thePixmap, size_t thePackageSize){
        return createChunks(thePixmap.first,thePixmap.second,thePackageSize);
    }

    //! Extended universal tool to pack differnt kind of data types in fixed chunks of data.
    template< typename T>
    XChunks anyTypeToChunks(T *thePixels, size_t thePixelBufferSize, size_t thePackageSize){
        return AnyTypeToChunksTemplate<T>(thePixels,thePixelBufferSize,thePackageSize);
    }
    //! Process chunk data back into original file.
    template< typename T>
    std::pair<T*,size_t> chunksToAnyType(std::vector<std::vector<T>> thePackages){
        return glueChunksTemplate(thePackages);
    }
private:
    //! Derived from DemoC example.
    //! Create packages from a texture, cq pixmap of a given size, The last package size is set to fit the data size.
    std::vector<std::vector<GLubyte>> createChunks(GLubyte *thePixels, size_t thePixelBufferSize, size_t thePackageSize){
        std::vector<GLubyte> vec;
        std::vector<std::vector<GLubyte>> vecvec;
        uint k=0;
        for(uint i=0; i<thePixelBufferSize; i++){
            vec.push_back(thePixels[i]);
            if(k==thePackageSize){
                vecvec.push_back(vec);
                vec.clear();
                k=0;
            }
            if(i==thePixelBufferSize-1){
                vecvec.push_back(vec);
            }
            k++;
        }
        return vecvec;
    }
    //! This will round any value to above.
    //! std::cout<<XChunker().round(2.01)<<std::endl; Output=3
    //! std::cout<<XChunker().round(2.991)<<std::endl; Output=3
    int roundUp(float d) {
        return std::floor(d + 1.0);
    }

    //! A exotic class derived from above. Input datatypes without writing a new function.
    template< typename T>
    std::vector<std::vector<T>> AnyTypeToChunksTemplate(T *thePixels, size_t thePixelBufferSize, size_t thePackageSize){
        std::vector<T> vec;
        std::vector<std::vector<T>> vecvec;
        uint k=0;
        for(uint i=0; i<thePixelBufferSize; i++){
            vec.push_back(thePixels[i]);
            if(k==thePackageSize){
                vecvec.push_back(vec);
                vec.clear();
                k=0;
            }
            if(i==thePixelBufferSize-1){
                vecvec.push_back(vec);
            }
            k++;
        }
        return vecvec;
    }
    //! Glue the packages back together.
    GLubyte* glueChunks(std::vector<std::vector<GLubyte>> thePackages, size_t theSize){
        GLubyte *thePixels = (GLubyte *)malloc(theSize);
        int k=0;
        for(uint i=0; i<thePackages.size(); i++){
            for(uint j=0; j<thePackages.at(i).size(); j++){
                thePixels[k]=thePackages.at(i).at(j);
                k++;
            }
        }
        return thePixels;
    }
    //! Derived from above function. Here the byte size of the packages is calculated from the vector sizes.
    std::pair<GLubyte*,size_t> glueChunks(std::vector<std::vector<GLubyte>> thePackages){
        size_t theSize=getChunksByteSize(thePackages);
        GLubyte *thePixels = (GLubyte *)malloc(theSize);
        int k=0;
        for(uint i=0; i<thePackages.size(); i++){
            for(uint j=0; j<thePackages.at(i).size(); j++){
                thePixels[k]=thePackages.at(i).at(j);
                k++;
            }
        }
        return {thePixels,theSize};
    }

    //! Derived from above function. But for any type.
    template<typename T>
    std::pair<T*,size_t> glueChunksTemplate(std::vector<std::vector<T>> thePackages){
        size_t theSize=getByteSize(thePackages);
        T *thePixels = (T *)malloc(theSize);
        int k=0;
        for(uint i=0; i<thePackages.size(); i++){
            for(uint j=0; j<thePackages.at(i).size(); j++){
                thePixels[k]=thePackages.at(i).at(j);
                k++;
            }
        }
        return {thePixels,theSize};
    }
public:
    //! Some example code i tested to ensure the code is working.
    //! Save texture in array and restore.
    void demoA(){
        //! Load a sample texture.
        GLubyte *x;
        size_t size;
        lodepng_load_file(&x,&size,"icons/test.png");
        lodepng_save_file(x,size,"out_original.png");

        //! Save to array.
        GLubyte vec[size];
        for(uint i=0; i<size; i++){
            vec[i]=x[i];
        }

        //! Back to texture.
        GLubyte *b = (GLubyte *)malloc(size);
        for(uint i=0; i<size; i++){
            b[i]=vec[i];
        }
        lodepng_save_file(b,size,"array.png");
    }
    //! Save texture as vector and restore.
    void demoB(){
        //! Load a sample texture.
        GLubyte *x;
        size_t size;
        lodepng_load_file(&x,&size,"icons/test.png");
        lodepng_save_file(x,size,"out_original.png");

        //! Save to array.
        std::vector<GLubyte> vec;
        for(uint i=0; i<size; i++){
            vec.push_back(x[i]);
        }

        //! Back to texture.
        GLubyte *b = (GLubyte *)malloc(size);
        for(uint i=0; i<vec.size(); i++){
            b[i]=vec.at(i);
        }
        lodepng_save_file(b,size,"vector.png");
    }
    //! Save texture as vector packages and restore.
    void demoC(){
        //! Load a sample .png picture into a texture.
        GLubyte *x;
        size_t size;
        lodepng_load_file(&x,&size,"icons/test.png");
        lodepng_save_file(x,size,"out_original.png");

        //! Save to fixed packages. The last package size is set to fit the data size.
        size_t packagesize=2000;
        std::vector<GLubyte> vec;
        std::vector<std::vector<GLubyte>> vecvec;
        uint k=0;
        for(uint i=0; i<size; i++){
            vec.push_back(x[i]);
            if(k==packagesize){
                vecvec.push_back(vec);
                vec.clear();
                k=0;
            }
            if(i==size-1){
                vecvec.push_back(vec);
            }
            k++;
        }
        //! Restore back to texture.
        GLubyte *b = (GLubyte *)malloc(size);
        int s=0;
        for(uint i=0; i<vecvec.size(); i++){
            for(uint j=0; j<vecvec.at(i).size(); j++){
                b[s]=vecvec.at(i).at(j);
                s++;
            }
        }
        //! Save the pixels into a .png image.
        lodepng_save_file(b,s,"vectorvector.png");

        std::cout<<"We loaded a .png image, chucked the data up in chunks, repacked the data and saved back as picture."<<std::endl;
        std::cout<<"packages:"<<vecvec.size()<<" bytes:"<<s<<" KiB:"<<s/1000<<std::endl;
    }
    size_t getChunkByteSize(XChunk theChunk){
        size_t size=0;
        for(uint i=0; i<theChunk.size(); i++){
            size++;
        }
        return size;
    }
    size_t getChunksByteSize(XChunks theChunks){
        size_t size=0;
        for(uint i=0; i<theChunks.size(); i++){
            for(uint j=0; j<theChunks.at(i).size(); j++){
                size++;
            }
        }
        return size;
    }
};
#endif


































