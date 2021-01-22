//
//  sprite.cpp
//  temp
//
//  Created by tea jakic on 11.12.2020..
//
/*
#include <stdio.h>
//g++ -O3  -Iinclude -Llib -o test.exe test.cpp  -lfreeglut -lopengl32 -lglu32
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include "structures.h"

#include <string>

// #include <math.h>
// #include <iostream>
using namespace std;

void initIL()
{
    ilInit();
    ilutInit();
    ilEnable(IL_CONV_PAL);
}

class sprites
{

public:
    GLuint tex;
    float x, y, z;
    float scale = 1;
    sprites() {}
    sprites(string in)
    {

        tex = iluLoadImage((ILstring)in.c_str());
    }
    sprites(string in, int init)
    {
        if (init == 1)
            initIL();
        tex = iluLoadImage((ILstring)in.c_str());
    }
    void onOff(int i)
    {
        if (i == 0)
        {
            glDepthMask(true);
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHTING);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glDisable(GL_BLEND);
        }

        else
        {
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHTING);
            glDisable(GL_CULL_FACE);
            glDepthMask(false);
            glEnable(GL_BLEND);
        }
    }

    void draw(float cx, float cy, float cz)
    {
        float angleHorizontal = 0;

        float vx = cx - (x - 0.5 * scale), vz = cz - z;

        angleHorizontal = acos(vz / sqrt(vx * vx + vz * vz)) * 180.0 / 3.14159;
        // cout << vz / sqrt(vx * vx + vz * vz) << " " << vx << " " << vz << endl;
        glBindTexture(GL_TEXTURE_2D, tex);
        if (vx < 0)
            angleHorizontal *= -1;
        glTranslatef(x, y, z);
        glRotatef(angleHorizontal, 0, 1, 0);

        glBegin(GL_QUADS);

        glTexCoord2f(0, 0);
        glVertex3f(-.5 * scale, -.5 * scale, 0);
        glTexCoord2f(0, 1);
        glVertex3f(-.5 * scale, .5 * scale, 0);
        glTexCoord2f(1, 1);
        glVertex3f(.5 * scale, .5 * scale, 0);
        glTexCoord2f(1, 0);
        glVertex3f(.5 * scale, -.5 * scale, 0);
        glEnd();

        glRotatef(-angleHorizontal, 0, 1, 0);
        glTranslatef(-x, -y, -z);
    }
    void setPos(float px, float py, float pz)
    {
        x = px;
        y = py;
        z = pz;
    }
    void setScale(float x)
    {
        scale = x;
    }
    void setPosAndScale(float px, float py, float pz, float scale)
    {
        setPos(px, py, pz);
        setScale(scale);
    }
    void move(float px, float py, float pz)
    {
        x += px;
        y += py;
        z += pz;
    }
    void moveAndScale(float px, float py, float pz, float scale)
    {
        move(px, py, pz);
        setScale(scale);
    }

    void drawAt(float px, float py, float pz, float scaley, float camx, float camy, float camz)
    {
        moveAndScale(px, py, pz, scaley);
        draw(camx, camy, camz);
        moveAndScale(-px, -py, -pz, scale);
    }
};
*/
