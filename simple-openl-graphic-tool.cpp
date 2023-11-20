#include <GL/glut.h>
#include <cmath>
#include<string>
# define M_PI 3.14159
#include"graphicType.h"

#include"onMidPointEllispe.cpp"
#include"lineClipping.cpp"


#include"drawBezier.h"
#include"drawBezier.cpp"


struct Ellipse {
    Point center;
    int a, b;
};

std::vector<struct Ellipse> ellipses;

struct Line {
    Point start,end;
};

std::vector<struct Line> lines;

struct LineColor {
    int r = 255;
    int g=0, b=0;
};

struct LineColor globalColor;

std::string mode = "Right click to select a graph type";

point startPoint, endPoint;

bool drawing = false;
int menuStatus = 0;

int iKeyPointNum = 0;
int xKey = 0, yKey = 0;

void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}


void drawEllipse(int x, int y, int a, int b) {
    glColor3f(globalColor.r, globalColor.g, globalColor.b);
    glTranslated(x, y, 0);
    onMidPointEllispe(a, b);
    glTranslated(-x , -y , 0);
}

void drawBaseRectangle(int x1, int y1, int x2, int y2) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2i(x2, y1);
    glVertex2i(x1, y2);
    glEnd();
}

void drawRect(int x1, int y1, int x2, int y2) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2) {
    glColor3f(globalColor.r, globalColor.g, globalColor.b);
    glBegin(GL_LINE_STRIP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    if (menuStatus == 1) {
        if (drawing) {
            int width = abs(endPoint.x - startPoint.x);
            int height = abs(endPoint.y - startPoint.y);
            drawBaseRectangle(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
            drawEllipse((startPoint.x + endPoint.x) / 2, (startPoint.y + endPoint.y) / 2, width / 2, height / 2);
        }

        if (!drawing) {
            int width = abs(endPoint.x - startPoint.x);
            int height = abs(endPoint.y - startPoint.y);
            drawEllipse((startPoint.x + endPoint.x) / 2, (startPoint.y + endPoint.y) / 2, width / 2, height / 2);
    }
    }

    for (const auto& ellipse : ellipses) {
        drawEllipse(ellipse.center.x, ellipse.center.y, ellipse.a, ellipse.b);
    }

    for (const auto& line : lines) {
        drawLine(line.start.x, line.start.y, line.end.x, line.end.y);
    }

    if (menuStatus == 2) {
        if (iKeyPointNum == 1) {
            if (drawing) {
                drawLine(startPoint.x, startPoint.y, xKey, yKey);
            }
        }
        if (iKeyPointNum == 2) {
            drawRect(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
    }
    
    renderBitmapString(10, glutGet(GLUT_WINDOW_HEIGHT) - 20, GLUT_BITMAP_HELVETICA_18, mode.c_str());

    glutSwapBuffers();
}

void menuFunc(int value) {
    startPoint.x = endPoint.x = startPoint.y = endPoint.y = 0;
    xKey = yKey = 0;
    if (value == 1) {
        menuStatus = 1;
        mode = "Ellipses";
    }
    if (value == 2) {
        iKeyPointNum = 0;
        menuStatus = 2;
        mode = "Line press \"P\" to start (should input in ENGLISH rather than CHINESE)";
        glutPostRedisplay();
    }
    if (value == 99) {
        ellipses.clear();
        lines.clear();
        menuStatus = 0;
        mode = "Right click to select a graph type";
        glutPostRedisplay();
    }
}

void keyboardFunc(unsigned char key, int x, int y) {
    if (menuStatus == 2) {
        if (key == 'p' || key == 'P') {
            if (iKeyPointNum == 0) {
                iKeyPointNum = 1;
                mode = "Left click and Draw to add a point; press \"E\" to finish";
            }
        }
        if (key == 'e' || key == 'E') {
            if (iKeyPointNum == 1) {
                iKeyPointNum = 2;
                endPoint.x = 0; endPoint.y = 0; startPoint.x = 0; startPoint.y = 0;
                mode = "Left click and Draw to use Liang-Barsky clipping";
            }
        }
        if (key == 'c' || key == 'C') {
            if (iKeyPointNum == 2) {
                rect r{ (float)startPoint.x ,(float)startPoint.y,(float)endPoint.x , (float)endPoint.y };
                for (auto& line : lines) {
                    std::vector<point> v;
                    v.push_back(line.start);
                    v.push_back(line.end);
                    Line_Clipping(v, r);
                    line.start = v[0];
                    line.end = v[1];
                }
                mode = "left click and draw to use Liang-Barsky clipping";
            }
        }
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Create a menu
        int menu = glutCreateMenu(menuFunc);
        glutAddMenuEntry("Ellipse", 1);
        glutAddMenuEntry("Line", 2);
        glutAddMenuEntry("Clear", 99);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
    if (menuStatus == 1) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            startPoint.x = endPoint.x = x;
            startPoint.y = endPoint.y = y;
            drawing = true;
            mode = "hold SHIFT and draw the graph for a circle";
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
            drawing = false;
            int width = abs(endPoint.x - startPoint.x);
            int height = abs(endPoint.y - startPoint.y);
            point center = point((startPoint.x + endPoint.x) / 2, (startPoint.y + endPoint.y) / 2);
            ellipses.push_back({ center, width / 2, height / 2 });
            endPoint.x = 0; endPoint.y = 0; startPoint.x = 0; startPoint.y = 0;
            mode = "ellipses";
            glutPostRedisplay();
        }
    }
    
    if (menuStatus == 2 ) {
        if (iKeyPointNum == 1) {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
                drawing = true;
                endPoint.x = x;
                endPoint.y = y;
                xKey = x; yKey = y;
                if (lines.size() == 0) {
                    startPoint.x = x; startPoint.y = y;
                    lines.push_back({ x,y });
                }
            }
            else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && drawing) {
                drawing = false;
                point end = point(xKey, yKey);
                point start = point(startPoint.x, startPoint.y);
                lines.push_back({start,end});
                startPoint.x = xKey; startPoint.y = yKey;
                endPoint.x = 0; endPoint.y = 0;
                xKey = 0; yKey = 0;
                glutPostRedisplay();
            }
        }
        if (iKeyPointNum == 2) {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
                drawing = true;
                startPoint.x = endPoint.x = x;
                startPoint.y = endPoint.y = y;
            }
            else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && drawing) {
                drawing = false;
                mode = "press \"C\" to cut";
                glutPostRedisplay();
            }
        }
    }
}

void motion(int x, int y) {
    if (drawing) {
        endPoint.x = x;
        endPoint.y = y;
        xKey = x; yKey = y;
        glutPostRedisplay();
        // If Shift is pressed, make it a circle
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
            endPoint.y = startPoint.y + abs(endPoint.x - startPoint.x);
            /*printf("shift");*/
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Ellipse Drawing");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 800.0, 600.0, 0.0);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutKeyboardFunc(keyboardFunc);

    glutMainLoop();

    return 0;
}

