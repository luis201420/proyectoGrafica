#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

struct ver{
    float x;
    float y;
    float z;
};

int num_points;
float x, y, z;
std::vector<ver> cloud_points;
//std::string filename = "points.dat";
std::string filename = "prueba.txt";

void parsePoints(){
    std::ifstream ifile(filename);
    ifile >> num_points;
    cloud_points.resize(num_points);
    for(int i=0; i < num_points; i++){
        ifile >> x >> y >> z;
        ver p;
        p.x = x;
        p.y = y;
        p.z = z;
        std::cout << x << std::endl;
        std::cout << y << std::endl;
        cloud_points[i] = p;
    }
    std::cout << "n: " << cloud_points.size();
}

void point(float a, float b, float c){
  //glBegin(GL_POINTS);
  glVertex3d(a,b,c);
  //glEnd();
}

void cloudPoints(){
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    for(int i = 0; i < cloud_points.size(); i++)
    {
        glColor3f(0,0,0);
        if(cloud_points[i].x < 10 && cloud_points[i].y < 10)
            glColor3f(1,0,0);
        point(cloud_points[i].x*2,cloud_points[i].y,cloud_points[i].z);
    }
    glEnd();
}

double rotate_y = 0;
double rotate_x = 0;
double rotate_z = 0;

void specialKeys(int key, int x, int y){
    if(key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    else if(key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if(key == GLUT_KEY_UP)
        rotate_z += 5;
    else if(key == GLUT_KEY_DOWN)
        rotate_z -= 5;
    glutPostRedisplay();
}

void display(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(80, w/h, 0.01, 2500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(200,200,200,0,0,0,0,0,1);

    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    //colorcube();
    //glVertex3fv(ver[a]);
    cloudPoints();
    glutSwapBuffers();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(640, 640);
    glutCreateWindow("GLUT Cube");

    parsePoints();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
