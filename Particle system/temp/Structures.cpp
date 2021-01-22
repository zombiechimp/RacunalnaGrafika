//
//  Structures.cpp
//  temp
//
//  Created by tea jakic on 11.12.2020..
//

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

class Izvor {
public:
    float x, y, z;
    int q;
    float cR, cG, cB;
    double size;
};

class Vrh {
public:
    float x, y, z;
    Vrh(float x1, float y1, float z1) {
        x = x1; y = y1; z = z1;
    }
};

class Cestica {
public:
    float x, y, z;
    float r, g, b;
    float v;
    int t;
    float sX, sY, sZ;
    float osX, osY, osZ;
    double kut; double size;
};

std::vector<Cestica> cestice;
Izvor i;

