#include <iostream>
#include <glut.h>
#include <sstream>
#include<string>
#include <ctime>
#include <Windows.h>
using namespace std;


const int N = 5, Ny = N + 3;
bool fugure[N][Ny][N];
bool cub[N][Ny][N];
bool cube[N][Ny][N];


double rotate_y = 170;
double rotate_x = 15;

int  speedRotate = 5;

double a = 0.5,
b = a / N;

double Kx = 0, Ky = 0, Kz = 0,
K = 2 * b;

int countKx = Kx, countKz = Kz;


bool down = 0;


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

void figure(int kx, int ky, int kz) {
    srand(time(0));

    int f = rand() % 7;
    f = 6;
    int maxX = 2, maxZ = 2;
    int TempX = 2, TempZ = 2;

    //std::cout << f;
    //switch (f)
    //{
    //case 0:
    //case 1:
    //case 2:
    //case 3:
    //case 4:
    //case 6: {


    fugure[2][5][2] = 1;
    fugure[3][5][2] = 1;
    fugure[2][5][3] = 1;


    if (down) {
        for (int x = 0; x < N; x++)
            for (int y = 0; y < Ny; y++)
                for (int z = 0; z < N; z++)
                    if (fugure[x][y][z] == 1) {

                        if (cube[x][y - 1][z] == 0 && y > 0) {
                            cout << endl << x << ' ' << y << ' ' << z << endl;
                            fugure[x][y][z] = 0;
                            fugure[x][y - 1][z] = 1;
                        }
                        else {
                            cube[x][y][z] = 1;
                        }
                    }
        down = 0;
    }




    for (int x = N; x > 0; x--)
        for (int y = Ny; y > 0; y--)
            for (int z = N; z > 0; z--)
                if (fugure[x][y][z] == 1)
                    arena[x][y][z].draw(b, b, b, (-x + N / 2) * K, (y * K) - N / 2 * K, (-z + N / 2) * K);
    ////cub1(b, b, b, (-x + N / 2 +kx) * K, (y + Ny / 2) * K, (-z + N / 2 + kz) * K);
    ////Sleep(300);


//}
//default:
//    break;
//}
}





void display() {
    cout << Kx << " " << Ky << ' ' << Kz;
    BigCub();

    // text(0.75, 0, "ad");

    figure(Kx, Ky, Kz);


    for (int x = 0; x < N; x++)
        for (int y = 0; y < Ny; y++)
            for (int z = 0; z < N; z++)
                if (cube[x][y][z] == 1)
                    arena[x][y][z].draw(b, b, b, (-x + N / 2) * K, (y * K) - N / 2 * K, (-z + N / 2) * K);//cub1(b, b, b, (-x + N / 2)*K, (y * K)-2*K, (-z + N / 2) * K);


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


    //  Request display update
    glutPostRedisplay();
}

void NormalKeyHandler(unsigned char key, int x, int y)
{
    if (key == 'd' && Kx < 2)
        Kx += 1;
    else if (key == 'a' && Kx > -2)
        Kx -= 1;
    else if (key == 's' && Kz < 2)
        Kz += 1;
    else if (key == 'w' && Kz > -2)
        Kz -= 1;
    else if (key == 32) {
        down = 1;
    }

    else if (key == 27)
        exit(0);


    cout << key << std::endl;
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {

    setup();
    //cube[0][0][0] = 1;
    //arena[0][1][0] = 1;
    //arena[0][2][0] = 1;
    //arena[0][3][0] = 1;
    //arena[0][4][0] = 1;
    //arena[0][5][0] = 1;


     //1  
    //fugure[0][3][0] = 1;

    //2
    //fugure[0][3][0] = 1;
    //fugure[0][4][0] = 1;
    //fugure[0][3][1] = 1;

    //3
    //fugure[-1][3][0] = 1;
    //fugure[0][3][0] = 1;
    //fugure[1][3][0] = 1;

    //4
    //fugure[0][3][0] = 1;
    //fugure[1][3][0] = 1;
    //fugure[1][4][0] = 1;
    //fugure[0][4][0] = 1;

    //5
    //fugure[0][3][0] = 1;
    //fugure[0][3][1] = 1;
    //fugure[0][4][1] = 1;
    //fugure[0][4][0] = 1;

    //fugure[0][3][1] = 1;
    //fugure[0][3][1] = 1;
    //fugure[0][4][1] = 1;
    //fugure[0][4][1] = 1;

    //6
    //fugure[0][3][0] = 1;
    //fugure[1][3][0] = 1;
    //fugure[1][3][1] = 1;
    //fugure[0][3][1] = 1;

    //7
    //fugure[0][3][0] = 1;
    //fugure[1][3][1] = 1;
    //fugure[0][3][1] = 1;


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