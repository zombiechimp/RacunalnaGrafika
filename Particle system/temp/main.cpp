
#include "structures.h"
#define FOV 90.0
#define FR 2000
#define NIR 0.1


using namespace std;

sprites text;
int main(int argc, char ** argv)
{
    
    emitter.position.x = 0.0; emitter.position.y = 0; emitter.position.z = 0.0;
    emitter.q = 10;
    emitter.colour.x = 1.0; emitter.colour.y = 0.0; emitter.colour.z = 1.0;
    emitter.size = 0.4;
    
    emitter2.position.x = 2.0; emitter2.position.y = 0; emitter2.position.z = 0.0;
    emitter2.q = 10;
    emitter2.colour.x = 0; emitter2.colour.y = 1.0; emitter2.colour.z = 0.0;
    emitter2.size = 0.2;
    
    text = sprites((string) "/Users/teajakic/Desktop/Bee.jpg");

    srand (time(NULL));
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(sub_width,sub_height);
    glutInitWindowPosition(100,100);
    glutInit(&argc, argv);
    
    window = glutCreateWindow("2nd lab");
    
    glutReshapeFunc(changeSize);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutIdleFunc(myIdle);
    
    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);                    // Set The Blending Function For Translucency
    glEnable(GL_BLEND);
    
    
    glutMainLoop();
    return 0;
}


void changeSize(int w, int h)
{

    
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;

    
    glMatrixMode(GL_PROJECTION);

    
    glLoadIdentity();

    
    glViewport(0, 0, w, h);

    
    gluPerspective(FOV, ratio, NIR, FR);

    
    glMatrixMode(GL_MODELVIEW);
}

int t = 0;

void myDisplay()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(eye.x, eye.y, eye.z, eye.x + cam.x, eye.y + cam.y, eye.z + cam.z, 0.0f, 1.0f, 0.0f);
    
    
    drawParticles();
    
    glutSwapBuffers();
}

int currentTime = 0; int previousTime = 0;

void myIdle() {
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    int timeInterval = currentTime - previousTime;
    if(timeInterval > 100) {
    
        if(emitter.q > 0) {
            int n = rand() % emitter.q + 1;
            
            for (int j = 0; j < n; j++) {
                double x, y, z, norm;
                x = (rand()%2000-1000) / (double)1000;
                y = (rand()%2000-1000) / (double)1000;
                z = (rand()%2000-1000) / (double)1000;
                norm = pow(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0), 0.5);
                x /= norm; y /= norm; z /= norm;
                Particle c;
                if(n%2 == 0) {
                    c.x = emitter.position.x; c.z = emitter.position.z; c.y = emitter.position.y;
                    c.r = emitter.colour.x; c.g = emitter.colour.y; c.b = emitter.colour.z; c.v = 0.8;
                    c.sX = x; c.sY = y; c.sZ = z;
                    c.t = 80 + (rand()%23 - 10);
                    c.size = emitter.size;
                    particles.push_back(c);
                }
                else {
                    c.x = emitter2.position.x; c.z = emitter2.position.z; c.y = emitter2.position.y;
                    c.r = emitter2.colour.x; c.g = emitter2.colour.y; c.b = emitter2.colour.z; c.v = 0.8;
                    c.sX = x; c.sY = y; c.sZ = z;
                    c.t = 80 + (rand()%23 - 10);
                    c.size = emitter2.size;
                    particles.push_back(c);
                }
            }
        }
        
        std::cout<<"Num of particles" << particles.size() << std::endl;
        for (int j =  particles.size() - 1; j >= 0; j--) {
            
            
            Vertex s(0.0, 0.0, 1.0);
            Vertex os(0.0, 0.0, 0.0);
            Vertex e(0.0, 0.0, 0.0);
            
            e.x = particles.at(j).x - eye.x;
            e.y = particles.at(j).y - eye.y;
            e.z = particles.at(j).z - eye.z;
            
            os.x = s.y*e.z - e.y*s.z;
            os.y = e.x*s.z - s.x*e.z;
            os.z = s.x*e.y - s.y*e.x;
            
            double apsS = pow(pow((double)s.x, 2.0) + pow((double)s.y, 2.0) + pow((double)s.z, 2.0), 0.5);
            double apsE = pow(pow((double)e.x, 2.0) + pow((double)e.y, 2.0) + pow((double)e.z, 2.0), 0.5);
            double se = s.x*e.x + s.y*e.y + s.z*e.z;
            double angle = acos(se/(apsS*apsE));
            particles.at(j).kut = angle / (2*pi) * 360;
            particles.at(j).osX = os.x;
            particles.at(j).osY = os.y;
            particles.at(j).osZ = os.z;
            
            particles.at(j).y += particles.at(j).v * particles.at(j).sY;
            particles.at(j).z += particles.at(j).v * particles.at(j).sZ;
            particles.at(j).x += particles.at(j).v * particles.at(j).sX;
            
            particles.at(j).t--;
            
            if (particles.at(j).r > 0) particles.at(j).r -= 0.008;
            if (particles.at(j).b < 1.0) particles.at(j).b += 0.008;
            if (particles.at(j).t <= 0) {
                particles.erase(particles.begin()+j);
            }
        }
        
        myDisplay();
        previousTime = currentTime;
    }
}

void drawParticles() {
    for (int j = 0; j < particles.size(); j++) {
        drawParticle(particles.at(j));
    }
}

void drawParticle(Particle c) {

    
    glColor3f(c.r, c.g, c.b);
    glTranslatef(c.x, c.y, c.z);
    glRotatef(c.kut, c.osX, c.osY, c.osZ);//
    glBegin(GL_QUADS);
    
    glTexCoord2d(0.0,0.0); glVertex3f(-c.size, -c.size, 0.0);
    glTexCoord2d(1.0,0.0); glVertex3f(-c.size, +c.size, 0.0);
    glTexCoord2d(1.0,1.0); glVertex3f(+c.size, +c.size, 0.0);
    glTexCoord2d(0.0,1.0); glVertex3f(+c.size, -c.size, 0.0);
    
    glEnd();
    glRotatef(-c.kut, c.osX, c.osY, c.osZ);//
    glTranslatef(-c.x, -c.y, -c.z);
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY) {
    if(theKey == 'a') emitter.position.x -= 0.5;
    if(theKey == 'd') emitter.position.x += 0.5;
    if(theKey == 'w') emitter.position.z -= 0.5;
    if(theKey == 's') emitter.position.z += 0.5;
    if(theKey == 'o') emitter.position.y -= 0.5;
    if(theKey == 'p') emitter.position.y += 0.5;
    
}


