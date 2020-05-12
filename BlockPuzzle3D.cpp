#include <iostream>
#include <glut.h>
#include <sstream>
#include <Windows.h>
#include <fstream>

using namespace std;


const int N = 5, Ny = N + 3;
bool cube[N][Ny][N];


double rotate_y;
double rotate_x;

int  speedRotate;

double a, b;

static int Kx, Ky, Kz;
double K;

bool down, gameOver;
int maxX, maxZ;
int score, BestScore;

int F;

class Cube
{
    bool cube[N][Ny][N];
public:
    Cube()
    {
        for (int x = 0; x < N; x++)
            for (int y = 0; y < Ny; y++)
                for (int z = 0; z < N; z++)
                    cube[x][y][z] = 0;
    }

    void Set(int x, int y, int z, bool F)
    {
        cube[x][y][z] = F;
    }

    bool get(int x, int y, int z) {
        return cube[x][y][z];
    }

    void clearArr() {
        for (int x = 0; x < N; x++)
            for (int y = 0; y < Ny; y++)
                for (int z = 0; z < N; z++)
                    cube[x][y][z] = 0;
    }

    void draw(double x, double y, double z, double kx, double ky, double kz)
    {
        glLoadIdentity();
        // Rotate when user changes rotate_x and rotate_y
        glRotatef(rotate_x, 1.0, 0.0, 0.0);
        glRotatef(rotate_y, 0.0, 1.0, 0.0);

        glBegin(GL_LINE_STRIP);//(GL_POLYGON);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, y + ky, -z + kz);
        glVertex3f(x + kx, y + ky, z + kz);
        glVertex3f(x + kx, -y + ky, z + kz);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, y + ky, z + kz);
        glVertex3f(-x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, -y + ky, -z + kz);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glVertex3f(x + kx, y + ky, z + kz);
        glVertex3f(x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, y + ky, -z + kz);
        glVertex3f(-x + kx, y + ky, z + kz);
        glVertex3f(x + kx, y + ky, z + kz);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, -y + ky, z + kz);
        glVertex3f(-x + kx, -y + ky, -z + kz);
        glVertex3f(x + kx, -y + ky, -z + kz);
        glEnd();

    }
};
Cube arena[N][Ny][N];
void drawString(void* font, const char* text, float x, float y)
{
    if (!text) 
    {
        return;
    }
    glRasterPos2f(x, y);
    while (*text)
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
}

void text(bool f, double x, double y, string line, int num = -1) {
    if (f)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLoadIdentity();
    if (num != -1) {
        string line1 = to_string(num);
        line += line1;
    }
    char* c = &*line.begin();
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, c, x, y);
}
Cube cub, Figure;
void setup() {

    rotate_y = 170;
    rotate_x = 15;

    speedRotate = 5;

    a = 0.5, b = a / N;

    K = 2 * b;

    F = 1;

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            for (int z = 0; z < N; z++) {
                cube[x][y][z] = 0;
            }
        }
    }
    ifstream outf("BestScore.txt");

    if (!outf)
    {
        BestScore = 0;
    }
    else {
        outf >> BestScore;
    }

}

void BigCub() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    // Rotate when user changes rotate_x and rotate_y
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);


    glBegin(GL_LINE_STRIP);
    glVertex3f(a, -a, -a);      // P1 is red
    glVertex3f(a, a, -a);      // P2 is green
    glVertex3f(-a, a, -a);      // P3 is blue
    glVertex3f(-a, -a, -a);      // P4 is purple
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex3f(a, -a, a);
    glVertex3f(a, a, a);
    glVertex3f(-a, a, a);
    glVertex3f(-a, -a, a);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex3f(a, -a, -a);
    glVertex3f(a, a, -a);
    glVertex3f(a, a, a);
    glVertex3f(a, -a, a);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex3f(-a, -a, a);
    glVertex3f(-a, a, a);
    glVertex3f(-a, a, -a);
    glVertex3f(-a, -a, -a);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex3f(a, a, a);
    glVertex3f(a, a, -a);
    glVertex3f(-a, a, -a);
    glVertex3f(-a, a, a);
    glEnd();

    glBegin(GL_LINE_STRIP);
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
        if (i < 6) 
        if (cub.get(xIndex, i + 1, zIndex))//////////////////////////
            yIndex = -i;
    }
    if (yIndex >= -2) gameOver = 1;
    return yIndex;
}

void figure() {
    srand(0);
    if (F == 6) F = 1;
    if (F == 1) {
        Figure.Set(0, 1, 0, 1);
        Figure.Set(1, 1, 0, 1);
        Figure.Set(2, 1, 0, 1);
        maxX = 2;
        maxZ = 0;
    }
    else if (F == 2) {
        Figure.Set(0, 1, 0, 1);
        Figure.Set(0, 1, 1, 1);
        Figure.Set(1, 1, 0, 1);

        maxX = 1;
        maxZ = 1;
    }
    else if (F == 3) {
        Figure.Set(0, 1, 0, 1);
        Figure.Set(0, 1, 1, 1);
        maxX = 0;
        maxZ = 1;
    }
    else if (F == 4) {
        Figure.Set(0, 1, 0, 1);
        maxX = 0;
        maxZ = 0;
    }
    else if (F == 5) {
        Figure.Set(0, 1, 0, 1);
        Figure.Set(0, 1, 1, 1);
        Figure.Set(0, 1, 2, 1);
        maxX = 0;
        maxZ = 2;
    }


    while (down)
    {
        Ky--;
        if (Ky == getMaxDepth()) {
            int xIndex = -Kx;
            int yIndex = -getMaxDepth();
            int zIndex = -Kz; // y = -x + N /2 // x = N /2 - y


            if (F == 1) {
                cub.Set(xIndex + 0, yIndex, zIndex + 0, 1);
                cub.Set(xIndex + 1, yIndex, zIndex + 0, 1);
                cub.Set(xIndex + 2, yIndex, zIndex + 0, 1);

                score += 3;
            }
            else if (F == 2) {
                cub.Set(xIndex + 0, yIndex, zIndex + 0, 1);
                cub.Set(xIndex + 0, yIndex, zIndex + 1, 1);
                cub.Set(xIndex + 1, yIndex, zIndex + 0, 1);

                score += 3;
            }
            else if (F == 3) {
                cub.Set(xIndex + 0, yIndex, zIndex + 0, 1);
                cub.Set(xIndex + 0, yIndex, zIndex + 1, 1);

                score += 2;
            }
            else if (F == 4) {
                cub.Set(xIndex + 0, yIndex, zIndex + 0, 1);
                score += 1;
            }
            else if (F == 5) {
                cub.Set(xIndex + 0, yIndex, zIndex + 0, 1);
                cub.Set(xIndex + 0, yIndex, zIndex + 1, 1);
                cub.Set(xIndex + 0, yIndex, zIndex + 2, 1);
                score += 3;
            }

            Kx = 0;
            Ky = 0;
            Kz = 0;
            down = 0;
            F++;
        }
    }

    for (int x = 0; x < N; x++)
        for (int y = 0; y < Ny; y++)
            for (int z = 0; z < N; z++)
                if (Figure.get(x, y, z))
                    Figure.draw(b, b, b, (-x + Kx + N / 2) * K, (-y + Ky + Ny / 2) * K, (-z + Kz + N / 2) * K);

    Figure.clearArr();

}

int clear(int i) {
    for (int x = 0; x < N; x++)
        for (int z = 0; z < N; z++) {
            if (!cube[x][6 - i][z]) return -1;
            if (!cub.get(x, 6 - i, z)) return -1;  //
        }
    for (int x = 0; x < N; x++)
        for (int z = 0; z < N; z++) {
            cube[x][6 - i][z] = 0;
            cub.Set(x, 6 - i, z, 0);
        }
    score += 25;
    return i;
}

void allClear() {
    for (int i = 0; i < Ny - 1; i++)
    {
        int n = clear(i);
        if (n > -1) {
            for (int x = n; x < N; x++)
                for (int z = n; z < N; z++) {
                    cube[x][n][z] = 0;
                    cub.Set(x, n, z, 0);
                }
            for (int x = 0; x < N; x++)
                for (int y = 0; y < Ny; y++)
                    for (int z = 0; z < N; z++) {
                        if (cube[x][y - n - 1][z]) {
                            cube[x][y - n - 1][z] = 0;
                            cube[x][6 - n][z] = 1;
                        }
                        if (cub.get(x, y - n - 1, z)) {
                            cub.Set(x, y - n - 1, z, 0);
                            cub.Set(x, 6 - n, z, 1);
                        }
                    }
        }
    }
}

void display() {

    cout << Kx << " " << Ky << ' ' << Kz;
    BigCub();

    figure();
    allClear();


    for (int x = 0; x < N; x++)
        for (int y = 0; y < Ny; y++)
            for (int z = 0; z < N; z++)
                if (cub.get(x, y, z))
                    cub.draw(b, b, b, (-x + N / 2) * K, (-y + Ny / 2) * K, (-z + N / 2) * K);


    text(0, -0.9, -0.9, "score ", score);
    text(0, 0.4, -0.9, "best score ", BestScore);
    if (gameOver == 1) {
        text(1, 0, 0, "G A M E  O V E R");
        if (score > BestScore) {
            ofstream outf("BestScore.txt");
            if (!outf)
            {
                cerr << "Uh oh, SomeText.txt could not be opened for writing!" << endl;
            }
            outf << score;
        }
        //Sleep(500);
        //exit(0);
    }

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

    else if (key == GLUT_KEY_LEFT) {
        rotate_y -= speedRotate;
    }

    else if (key == GLUT_KEY_UP) {
        if (a < 0.61) {
            a = a + 0.01;
            b = b + 0.01 / N;
            K = 2 * b;
        }
    }

    else if (key == GLUT_KEY_DOWN) {
        if (a > 0.05) {
            a = a - 0.01;
            b = b - 0.01 / N;
            K = 2 * b;
        }
    }


    glutPostRedisplay();
}

void NormalKeyHandler(unsigned char key, int x, int y)
{
    if (key == 'd' && Kx < 0)
        Kx += 1;
    else if (key == 'a' && Kx > -4 + maxX)
        Kx -= 1;
    else if (key == 's' && Kz < 0)
        Kz += 1;
    else if (key == 'w' && Kz > -4 + maxZ)
        Kz -= 1;
    else if (key == 32 && Ky >= -6) {
        down = 1;
        Ky--;
    }

    else if (key == 27) {
        if (score > BestScore) {
            ofstream outf("BestScore.txt");
            if (!outf)
            {
                cerr << "Uh oh, SomeText.txt could not be opened for writing!" << endl;
            }
            outf << score;
        }
        exit(0);
    }


    cout << key << std::endl;
    glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) 
        {
            rotate_x = 195;
            display();
        }
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_UP) 
        {
            rotate_x = 15;
            display();
        }
    }
}


int main(int argc, char* argv[]) {
    setup();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("BlockPuzzle3D");
    glEnable(GL_DEPTH_TEST);
    if (!gameOver) {
        glutSpecialFunc(specialKeys);
        glutKeyboardFunc(NormalKeyHandler);
        glutMouseFunc(mouseButton);
    }
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}