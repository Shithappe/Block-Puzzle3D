#include <iostream>
#include <glut.h>
#include <sstream>
#include<string>
#include <ctime>
#include <Windows.h>
using namespace std;


const int N = 5, Ny = N + 3;
bool fugure[N][Ny][N];
//bool cub[N][Ny][N];
bool cube[N][Ny][N];


double rotate_y = 170;
double rotate_x = 15;

int  speedRotate = 5;

double a = 0.5,
b = a / N;

int Kx = 0, Ky = 0, Kz = 0;
double K = 2 * b;

int countKx = Kx, countKz = Kz;


bool down = 0;
int maxX, maxZ;


class Cube
{
public:
    Cube()
    {
        for (int x = 0; x < N; x++)
            for (int y = 0; y < Ny; y++)
                for (int z = 0; z < N; z++)
                    cube[x][y][z] = 0;
    }
    Cube(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        cube[x][y][z] = 1;
    }
    Cube(Cube& a)
    {
        x = a.x;
        y = a.y;
        z = a.z;
    }
    void Set(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        cube[x][y][z] = 1;
    }
    void draw(double x, double y, double z, double kx, double ky, double kz)
    {
        glLoadIdentity();
        // Rotate when user changes rotate_x and rotate_y
        glRotatef(rotate_x, 1.0, 0.0, 0.0);
        glRotatef(rotate_y, 0.0, 1.0, 0.0);

        // Purple side - RIGHT
        glBegin(GL_LINE_STRIP);//(GL_POLYGON);
        // glColor3f(1.0, 0.0, 1.0);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, y + ky, -z + kz);
        glVertex3f(x + kx, y + ky, z + kz);
        glVertex3f(x + kx, -y + ky, z + kz);
        glEnd();

        // Green side - LEFT
        glBegin(GL_LINE_STRIP);
        //glColor3f(0.0, 1.0, 0.0);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, y + ky, z + kz);
        glVertex3f(-x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, -y + ky, -z + kz);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glEnd();

        // Blue side - TOP
        glBegin(GL_LINE_STRIP);
        // glColor3f(0.0, 0.0, 1.0);
        glVertex3f(x + kx, y + ky, z + kz);
        glVertex3f(x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, y + ky, z + kz);
        glVertex3f(x + kx, y + ky, z + kz);
        glEnd();

        // Red side - BOTTOM
        glBegin(GL_LINE_STRIP);
        // glColor3f(1.0, 0.0, 0.0);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glEnd();
    }
private:
    int x, y, z;
};
Cube arena[N][Ny][N];
void drawString(void* font, const char* text, float x, float y)
{
    if (!text) // нульовий указівник
    {
        return;
    }
    // Встановлення позиції тексту:
    glRasterPos2f(x, y);
    while (*text)
    {
        // Рядок виводиться посимвольно:
        glutBitmapCharacter(font, *text);
        text++;
    }
}

void text(double x, double y, string line, int num = -1) {
    //line = to_string(line);
    if (num != -1) {
        string line1 = to_string(num);
        line += line1;
    }
    char* c = &*line.begin();
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, c, x, y);
}

void setup() {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            for (int z = 0; z < N; z++) {
                cube[x][y][z] = 0;
            }
        }
    }

}

void cub1(double x, double y, double z, double kx, double ky, double kz) {

    // Reset transformations
    glLoadIdentity();


    // Rotate when user changes rotate_x and rotate_y
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    // Purple side - RIGHT
    glBegin(GL_LINE_STRIP);//(GL_POLYGON);
    // glColor3f(1.0, 0.0, 1.0);
    glVertex3f(x + kx, -y + ky, -z + kz);
    glVertex3f(x + kx, y + ky, -z + kz);
    glVertex3f(x + kx, y + ky, z + kz);
    glVertex3f(x + kx, -y + ky, z + kz);
    glEnd();

    // Green side - LEFT
    glBegin(GL_LINE_STRIP);
    //glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-x + kx, -y + ky, z + kz);
    glVertex3f(-x + kx, y + ky, z + kz);
    glVertex3f(-x + kx, y + ky, -z + kz);
    glVertex3f(-x + kx, -y + ky, -z + kz);
    glVertex3f(-x + kx, -y + ky, z + kz);
    glEnd();

    // Blue side - TOP
    glBegin(GL_LINE_STRIP);
    // glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x + kx, y + ky, z + kz);
    glVertex3f(x + kx, y + ky, -z + kz);
    glVertex3f(-x + kx, y + ky, -z + kz);
    glVertex3f(-x + kx, y + ky, z + kz);
    glVertex3f(x + kx, y + ky, z + kz);
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_LINE_STRIP);
    // glColor3f(1.0, 0.0, 0.0);
    glVertex3f(x + kx, -y + ky, -z + kz);
    glVertex3f(x + kx, -y + ky, z + kz);
    glVertex3f(-x + kx, -y + ky, z + kz);
    glVertex3f(-x + kx, -y + ky, -z + kz);
    glVertex3f(x + kx, -y + ky, -z + kz);
    glEnd();
}

void cub2(double x, double y, double z, double kx, double ky, double kz) {

    // Reset transformations
    glLoadIdentity();


    // Rotate when user changes rotate_x and rotate_y
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    // Purple side - RIGHT
    glBegin(GL_LINE_STRIP);//(GL_POLYGON);
    // glColor3f(1.0, 0.0, 1.0);
    glVertex3f(x + kx, -y + ky, -z + kz);
    glVertex3f(x + kx, y + ky, -z + kz);
    glVertex3f(x + kx, y + ky, z + kz);
    glVertex3f(x + kx, -y + ky, z + kz);
    glEnd();

    // Green side - LEFT
    glBegin(GL_LINE_STRIP);
    //glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-x + kx, -y + ky, z + kz);
    glVertex3f(-x + kx, y + ky, z + kz);
    glVertex3f(-x + kx, y + ky, -z + kz);
    glVertex3f(-x + kx, -y + ky, -z + kz);
    glVertex3f(-x + kx, -y + ky, z + kz);
    glEnd();

    // Blue side - TOP
    glBegin(GL_POLYGON);
    // glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x + kx, y + ky, z + kz);
    glVertex3f(x + kx, y + ky, -z + kz);
    glVertex3f(-x + kx, y + ky, -z + kz);
    glVertex3f(-x + kx, y + ky, z + kz);
    glVertex3f(x + kx, y + ky, z + kz);
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_LINE_STRIP);
    // glColor3f(1.0, 0.0, 0.0);
    glVertex3f(x + kx, -y + ky, -z + kz);
    glVertex3f(x + kx, -y + ky, z + kz);
    glVertex3f(-x + kx, -y + ky, z + kz);
    glVertex3f(-x + kx, -y + ky, -z + kz);
    glVertex3f(x + kx, -y + ky, -z + kz);
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

int getMaxDepth() {
    int xIndex = -Kx;
    int zIndex = -Kz;
    int yIndex = -6;

    for (int i = Ny - 1; i >= 0; i--) {
        if (cube[xIndex][i + 1][zIndex])
            yIndex = -i;
    }

    return yIndex;
}

void figure() {
    fugure[0][1][0] = 1;
    fugure[1][1][0] = 1;
    fugure[2][1][0] = 1;
    fugure[3][1][0] = 1;
    fugure[4][1][0] = 1;
    

    if (Ky == getMaxDepth()) {
        int xIndex = -Kx;
        int yIndex = -getMaxDepth();
        int zIndex = -Kz; // y = -x + N /2 // x = N /2 - y
        cube[xIndex][yIndex][zIndex] = 1;
        cube[xIndex+1][yIndex][zIndex] = 1;
        cube[xIndex + 2][yIndex][zIndex] = 1;
        cube[xIndex + 3][yIndex][zIndex] = 1;
        cube[xIndex + 4][yIndex][zIndex] = 1;

        Ky = 0;
        Kz = 0;
        Kx = 0;
    }

    for (int x = 0; x < N; x++)
        for (int y = 0; y < Ny; y++)
            for (int z = 0; z < N; z++) {
                if (fugure[x][y][z])
                    arena[x][y][z].draw(b, b, b, (-x + Kx + N / 2) * K, (-y + Ky + Ny / 2) * K, (-z + Kz + N / 2) * K);
            }
}


//void done() {
//    int count = 0;
//    for (int x = 0; x < N; x++)
//        for (int z = 0; z < N; z++)
//            if (count < N * N) count++;
//    if (count == N * N)
//        for (int x = 0; x < N; x++)
//            for (int z = 0; z < N; z++)
//                cube[x][-6][z] = 0;
//
//}
//


void display() {
    cout << Kx << " " << Ky << ' ' << Kz;
    BigCub();

    figure();
   // done();

    for (int x = 0; x < N; x++)
        for (int y = 0; y < Ny; y++)
            for (int z = 0; z < N; z++)
                if (cube[x][y][z] == 1)
                    arena[x][y][z].draw(b, b, b, (-x + N / 2) * K, (-y + Ny / 2) * K, (-z + N / 2) * K);


    glFlush();
    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {

    if (key == GLUT_KEY_HOME) {
        rotate_x += speedRotate;
    }


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

    glutPostRedisplay();
}

void NormalKeyHandler(unsigned char key, int x, int y)
{
    if (key == 'd' && Kx < 0)
        Kx += 1;
    else if (key == 'a' && Kx > -4)
        Kx -= 1;
    else if (key == 's' && Kz < 0)
        Kz += 1;
    else if (key == 'w' && Kz > -4)
        Kz -= 1;
    else if (key == 32 && Ky >= -6) {
        down = 1;
        Ky--;
    }

    else if (key == 27)
        exit(0);


    cout << key << std::endl;
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {

    setup();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("---");
    glEnable(GL_DEPTH_TEST);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(NormalKeyHandler);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;

}