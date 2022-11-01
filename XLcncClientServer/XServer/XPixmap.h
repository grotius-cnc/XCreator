#ifndef XPixmap_H
#define XPixmap_H

#include <vector>
#include <iostream>

//! Structure to hold raw image data.
struct XPixmap {
    std::vector<unsigned char> pixels;
    uint width=0;
    uint height=0;
};

#endif
