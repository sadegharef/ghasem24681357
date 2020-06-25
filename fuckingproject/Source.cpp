#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;

//Point class for taking the points
class Point
{
public:
    GLfloat x, y, z;
    void setxyz(GLfloat x2, GLfloat y2, GLfloat z2)
    {
        x = x2;
        y = y2;
        z = z2;
    }
    void setxy(GLfloat x2, GLfloat y2)
    {
        x = x2;
        y = y2;
    }
};

//define global variable
Point keyFrame[4];
Point G[52];
int keyframe = 4;
//define cube point and cube angle

//factorial
int factorial(int n)
{
    if (n <= 1)
        return(1);
    else
        n = n * factorial(n - 1);
    return n;
}
//tartib k az n
float binomial_coff(int n, float k)
{
    float ans;
    ans = (float)(factorial(n) / (factorial((int)k) * 1.0 * factorial(n - (int)k)));
    return ans;
}
//Calculate the bezier point [generalized]
Point drawBezierGeneralized(Point PT[], float t) {
    Point P;
    P.x = 0;
    P.y = 0;
    P.z = 0;
    for (int i = 0; i < keyframe; i++)
    {
        P.x = P.x + binomial_coff((keyframe - 1), (float)i) * pow(t, (float)i) * pow((1 - t), (keyframe - 1 - i)) * PT[i].x;
        P.y = P.y + binomial_coff((keyframe - 1), (float)i) * pow(t, (float)i) * pow((1 - t), (keyframe - 1 - i)) * PT[i].y;
        P.z = P.z + binomial_coff((keyframe - 1), (float)i) * pow(t, (float)i) * pow((1 - t), (keyframe - 1 - i)) * PT[i].z;
    }
    return P;
}
//define the init
void myInit() {
    glClearColor(.0, .0, .0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    keyFrame[0].setxyz(0.0, 0.0, 3.0);
    keyFrame[1].setxyz(2.0, -2.5, 2.0);
    keyFrame[2].setxyz(0.0, 3.0, -3.0);
    keyFrame[3].setxyz(3.0, 0.0, 0.0);
   
    int i = 1;
    G[0] = keyFrame[0];
    for (float t = 0.0f; t <= 1.0f; t += 0.02f)
    {
        Point p2 = drawBezierGeneralized(keyFrame, t);
        cout << p2.x << ",  " << p2.y << ", " << p2.z << endl;
        cout << endl;
        G[i] = p2;
        i++;
    }
}
//drawing function
int points = 0;
void draw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //first cube
    glPushMatrix();
    glTranslatef(G[points].x, G[points].y, G[points].z);
    glColor3f(1, 1, 1);
    glScalef(0.8f, 1.6f, 0.4f);
    glutSolidCube(.4);
    glPopMatrix();
    //flush
    glFlush();
}
//define constance speed
void timer(int v) {
    // Updata movement parameters
    if (points == 51)
        return;
    points++;

    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}
//on mouse click function
void myMouse(int button, int state, int x, int y) {
    // If left button was clicked
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glutTimerFunc(100, timer, 0);
    }
}
//define the variable speed
void keyboard(unsigned char key, int x, int y)
{

    switch (key) {
    case '1':
        points++;
        glutPostRedisplay();
        break;

    case '2':
        points--;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}
//reshaping
void reshape(int w, int h) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(atan(tan(50.0 * 3.14159 / 360.0) / 1.0) * 360.0 / 3.141593, 1.0, 3.0, 7.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(5.0, 2.0, 5.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
}

//main
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 500);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Bezier Curve");

    myInit();
    glutKeyboardFunc(keyboard);
    glutMouseFunc(myMouse);
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    
    glutMainLoop();

    return 0;
}