//
//  structures.h
//  temp
//
//  Created by tea jakic on 11.12.2020..
//

#ifndef structures_h
#define structures_h

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

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>


#include <string>

using namespace std;

GLuint window;
GLuint sub_width = 512, sub_height = 512;


void changeSize(int w, int h);
class Vertex {
public:
    float x, y, z;
    Vertex(float x1, float y1, float z1) {
        x = x1; y = y1; z = z1;
    }
};

class Source {
public:
    Vertex position;
    int q;
    Vertex colour;
    double size;
    Source():position(0,0,0), q(0), colour(0,0,0), size(0){}
};


class Particle {
public:
    float x, y, z;
    float r, g, b;
    float v;
    int t;
    float sX, sY, sZ;
    float osX, osY, osZ;
    double kut; double size;
};


void myDisplay            ();
void myIdle                ();
void myReshape            (int width, int height);
void myKeyboard            (unsigned char theKey, int mouseX, int mouseY);

void drawEmitter        ();
void drawParticles        ();
void drawParticle        (Particle p);
GLuint LoadTextureRAW( const char * filename, int wrap );
std::vector<Particle> particles;
Source emitter;
Source emitter2;
double maxH = 42.0;
double pi = 3.14159;
//int tempQ = -1;
GLuint tex;
Vertex eye(3, 5, 0);
Vertex cam(-1, 0, 0);



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


#endif /* structures_h */
