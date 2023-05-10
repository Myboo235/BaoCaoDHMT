#include <GL/gl.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

// Setup window size 500x500
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
// Setup cube controls' rotation speed

#define TITLE "Bao Cao DHMT"
#define MSG "W,S,A,D: Rotate    SPACE: Pause/Resume    R: Frame    Q: Quit    U:Print Matrix   X,Y:Scale" //
#define PI 3.141592653589793238462643383279502884L                                                        /* pi */

// Struct point dung de luu xyz(co the dung class)
typedef struct
{
    float x;
    float y;
    float z;
} Point3D;

typedef struct
{
    float R;
    float G;
    float B;
} ColorRGB;

Point3D vertices[6][4] = {
    {{0.5, 0.5, 0.5}, {0.5, -0.5, 0.5}, {-0.5, -0.5, 0.5}, {-0.5, 0.5, 0.5}},
    {{-0.5, 0.5, 0.5}, {-0.5, -0.5, 0.5}, {-0.5, -0.5, -0.5}, {-0.5, 0.5, -0.5}},
    {{-0.5, 0.5, -0.5}, {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}, {0.5, 0.5, -0.5}},
    {{0.5, 0.5, -0.5}, {0.5, -0.5, -0.5}, {0.5, -0.5, 0.5}, {0.5, 0.5, 0.5}},
    {{-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5}, {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5}},
    {{-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}, {0.5, -0.5, 0.5}, {-0.5, -0.5, 0.5}}};
ColorRGB colors[6] = {
    {0.376, 0.007, 0.933},
    {0.839, 0.007, 0.933},
    {0.933, 0.376, 0.007},
    {0.564, 0.933, 0.007},
    {0.376, 0.490, 0.545},
    {0.898, 0.223, 0.207}};

float aX = 0.1, aY = 0.1, aZ = 0, tY = 0;
int frame = 0, stop = 0;
int size_cube = 0;

void display_matrix()
{
    std::cout << "Matrix :\n";
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
            std::cout << (vertices[i])[j].x << "   " << (vertices[i])[j].y << "   " << (vertices[i])[j].z << "\n";
        std::cout << "\n";
    }
}

Point3D myScale(Point3D ca, double a)
{

    ca = {ca.x * a, ca.y * a, ca.z * a};

    return ca;
}

Point3D myRotate(Point3D ca, double a, std::string r)
{
    float sina = sin(a * PI / 180);
    float cosa = cos(a * PI / 180);
    // cout << sina << cosa;
    if (r == "x")
        ca = {ca.x, ca.y * cosa - ca.z * sina, ca.y * sina + ca.z * cosa};
    else if (r == "y")
        ca = {ca.x * cosa + ca.z * sina, ca.y, -ca.x * sina + ca.z * cosa};
    else if (r == "z")
        ca = {ca.x * cosa - ca.y * sina, ca.x * sina + ca.y * cosa, ca.z};

    return ca;
}

void rotate(double a, std::string r)
{
    if (r == "x")
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 4; j++)
                vertices[i][j] = myRotate(vertices[i][j], a, "x");
        }
    }
    else if (r == "y")
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 4; j++)
                vertices[i][j] = myRotate(vertices[i][j], a, "y");
        }
    }
    else if (r == "z")
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 4; j++)
                vertices[i][j] = myRotate(vertices[i][j], a, "z");
        }
    }
}

void scale(double a)
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 4; j++)
            vertices[i][j] = myScale(vertices[i][j], a);
}

void drawString(float x, float y, float z, char *string, int big_font)
{
    char *c;
    glRasterPos3f(x, y, z);

    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(big_font ? GLUT_BITMAP_HELVETICA_18 : GLUT_BITMAP_HELVETICA_12, *c);
    }
}
// Ham ve mat cua khoi lap phuong
void drawQuad(GLint size, Point3D points[4], ColorRGB color)
{
    int i;
    glPolygonMode(GL_FRONT_AND_BACK, frame ? GL_LINE : GL_FILL);
    glColor4f(color.R, color.G, color.B, 1);
    glBegin(GL_QUADS);
    for (i = 0; i < 4; i++)
        glVertex3i(size * points[i].x, size * points[i].y, size * points[i].z);
    glEnd();
}
// Ham ve khoi lap phuong
void drawCube(int size)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        drawQuad(size, vertices[i], colors[i]);
    }
}
// Ham display
void display()
{
    while (size_cube == 0)
    {
        std::cout << "Input size : ";
        std::cin >> size_cube;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    //    glRotatef(aX, 1, 0, 0);
    //    glRotatef(aZ, 0, 0, 1);
    //    glRotatef(tY, 0, 1, 0);

    drawCube(size_cube);
    glPopMatrix();

    glColor4f(0, 0.650, 1, 1);
    drawString(-16.0, 45.0, 0.0, TITLE, 1);

    glColor4f(0.470, 0.564, 0.611, 1);
    drawString(-47.0, -47.0, 0.0, MSG, 0);

    glFlush();
    glutSwapBuffers();

    if (!stop)
    {
        rotate(1, "y");
    }
}
void display_init()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -50, 50);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0, 0, 0, 0);
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // ROTATE X 20DEG
    case 'w':
    case 'W':
        rotate(20, "x");
        break;
    // ROTATE X -20DEG
    case 's':
    case 'S':
        rotate(-20, "x");
        break;
    // ROTATE Z 20DEG
    case 'a':
    case 'A':
        rotate(20, "z");
        break;
    // ROTATE Z -20DEG
    case 'd':
    case 'D':
        rotate(-20, "z");
        break;
    // FRAME
    case 'r':
    case 'R':
        frame ^= 1;
        break;
    // 'SPACE' to  stop
    case 0x20:
        stop ^= 1;
        break;
    // map 'Q' to exit
    case 0x1B:
    case 'q':
    case 'Q':
        exit(0);
        break;

    // DISPLAY MATRIX
    case 'U':
    case 'u':
        display_matrix();
        break;

    case 'x':
    case 'X':
        scale(2);
        break;
    case 'y':
    case 'Y':
        scale(0.5);
        break;
    }
}

int main(int argc, char **argv)
{
    rotate(10, "x");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Cube");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    // Run initial setup
    display_init();
    glutMainLoop();
    return 0;
}
