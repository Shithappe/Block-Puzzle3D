// Controls:    Left Arrow  - Rotate Left
//              Right Arrow - Rotate Right


#include <iostream>
#include <glut.h>
//#include <Windows.h>
//#include <stdio.h>
//#include <stdarg.h>
//#include <math.h>

const int N = 5;

double rotate_y = 15;
double rotate_x = 15;

bool arena[N][N][N]; 
int  speedRotate = 5;

double a = 0.5,
       b = a/N;
       
double Kx = 0, Ky = 0, Kz = 0,
       K = 2 * b;


void cub(double x, double y, double z, double kx, double ky, double kz) {

    // Reset transformations
    glLoadIdentity();


    // Rotate when user changes rotate_x and rotate_y
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    // glColor3f(1.0, 0.0, 1.0);
    glVertex3f(x+kx, -y+ky, -z+kz);
    glVertex3f(x+kx, y + ky, -z + kz);
    glVertex3f(x+kx, y + ky, z + kz);
    glVertex3f(x+kx, -y + ky, z + kz);
    glEnd();

    // Green side - LEFT
    glBegin(GL_LINE_STRIP);
    //glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-x+kx, -y + ky, z + kz);
    glVertex3f(-x+kx, y + ky, z+kz);
    glVertex3f(-x+kx, y + ky, -z + kz);
    glVertex3f(-x+kx, -y + ky, -z + kz);
    glVertex3f(-x+kx, -y + ky, z + kz);
    glEnd();

    // Blue side - TOP
    glBegin(GL_LINE_STRIP);
    // glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x+kx, y + ky, z + kz);
    glVertex3f(x+kx, y + ky, -z + kz);
    glVertex3f(-x+kx, y + ky, -z + kz);
    glVertex3f(-x+kx, y + ky, z + kz);
    glVertex3f(x+kx, y + ky, z + kz);
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_LINE_STRIP);
    // glColor3f(1.0, 0.0, 0.0);
    glVertex3f(x+kx, -y + ky, -z + kz);
    glVertex3f(x+kx, -y + ky, z + kz);
    glVertex3f(-x+kx, -y + ky, z + kz);
    glVertex3f(-x+kx, -y + ky, -z + kz);
    glVertex3f(x+kx, -y + ky, -z + kz);
    glEnd();
}

void BigCub() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    // Rotate when user changes rotate_x and rotate_y
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);


    //Multi-colored side - FRONT
    glBegin(GL_LINE_STRIP);
    glVertex3f(a, -a, -a);      // P1 is red
    glVertex3f(a, a, -a);      // P2 is green
    glVertex3f(-a, a, -a);      // P3 is blue
    glVertex3f(-a, -a, -a);      // P4 is purple

    //glColor3f(1.0, 0.0, 0.0);    // 
   //glColor3f(0.0, 1.0, 0.0);     //
    //glColor3f(0.0, 0.0, 1.0);     //
   // glColor3f(1.0, 0.0, 1.0);     //

    glEnd();

    // White side - BACK
    glBegin(GL_LINE_STRIP);
    // glColor3f(1.0, 1.0, 1.0);
    glVertex3f(a, -a, a);
    glVertex3f(a, a, a);
    glVertex3f(-a, a, a);
    glVertex3f(-a, -a, a);
    glEnd();

    // Purple side - RIGHT
    glBegin(GL_LINE_STRIP);
    // glColor3f(1.0, 0.0, 1.0);
    glVertex3f(a, -a, -a);
    glVertex3f(a, a, -a);
    glVertex3f(a, a, a);
    glVertex3f(a, -a, a);
    glEnd();

    // Green side - LEFT
    glBegin(GL_LINE_STRIP);
    //glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-a, -a, a);
    glVertex3f(-a, a, a);
    glVertex3f(-a, a, -a);
    glVertex3f(-a, -a, -a);
    glEnd();

    // Blue side - TOP
    glBegin(GL_LINE_STRIP);
    // glColor3f(0.0, 0.0, 1.0);
    glVertex3f(a, a, a);
    glVertex3f(a, a, -a);
    glVertex3f(-a, a, -a);
    glVertex3f(-a, a, a);
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_LINE_STRIP);
    // glColor3f(1.0, 0.0, 0.0);
    glVertex3f(a, -a, -a);
    glVertex3f(a, -a, a);
    glVertex3f(-a, -a, a);
    glVertex3f(-a, -a, -a);
    glVertex3f(a, -a, -a);
    glEnd();

}


void display() {
    BigCub();
    cub(b, b ,b, Kx, Ky, Kz);
    //cub(b, b, b, 0, 0, 0);

    cub(b, b, b, -K, 0, 0);
    cub(b, b, b, 0, 0, 0);
    cub(b, b, b, K, 0, 0);

    glFlush();
    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {

    if (key == GLUT_KEY_HOME) {
        rotate_x += speedRotate;
    }

    //  Left arrow - decrease rotation by 5 degree


    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT) {
        rotate_y += speedRotate;
    }

    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT) {
        rotate_y -= speedRotate;
    }

    else if (key == GLUT_KEY_UP) {
        //rotate_x += 5;
        if (a < 0.61) {
            a = a + 0.01;
            b = b + 0.01 / N;
            K = 2 * b;
        }
    }

    else if (key == GLUT_KEY_DOWN) {
        // rotate_x -= 5;
        if (a > 0.05) {
            a = a - 0.01;
            b = b - 0.01 / N;
            K = 2 * b;
        }
    }

    else if (key == GLUT_KEY_F2) 
        Ky += K;
    else if (key == GLUT_KEY_F1)
        Ky -= K;


    //  Request display update
    glutPostRedisplay();
}

void NormalKeyHandler(unsigned char key, int x, int y)
{
    
    if (key == 'd')
        Kx += 2 * b;
    else if (key == 'a')
        Kx -= K;
    else if (key == 's')
        Kz += K;
    else if (key == 'w')
        Kz -= K;
    else if (key == 27)
        exit(0);
        

    std::cout << key << std::endl;
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {

    //  Initialize GLUT and process user parameters
    glutInit(&argc, argv);

    //  Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create window
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("---");

    //  Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);

    // Callback functions
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(NormalKeyHandler);

    glutDisplayFunc(display);


    //  Pass control to GLUT for events
    glutMainLoop();

    return 0;

}