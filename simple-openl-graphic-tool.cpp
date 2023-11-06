#include <GL/glut.h>
#include <cmath>
#include<string>
# define M_PI 3.14159

#include"onMidPointEllispe.cpp"

void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

struct Ellipse {
    int x, y, a, b;
};

std::vector<struct Ellipse> ellipses;

struct Color {
    int r = 255;
    int g=0, b=0;
};

struct Color globalColor;

std::string mode = "Right click to select a graph type";

int startX, startY, endX, endY;
bool drawing = false;
int menuStatus = 0;

void drawEllipse(int x, int y, int a, int b) {
    glColor3f(globalColor.r, globalColor.g, globalColor.b);
    glTranslated(x, y, 0);
    onMidPointEllispe(a, b);
    glTranslated(-x , -y , 0);
}

void drawRectangle(int x1, int y1, int x2, int y2) {
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    if (drawing && (menuStatus == 1)) {
        int width = abs(endX - startX);
        int height = abs(endY - startY);
        drawRectangle(startX, startY, endX, endY);
        drawEllipse((startX + endX) / 2, (startY + endY) / 2, width / 2, height / 2);
    }

    if (!drawing && (menuStatus == 1)) {
        int width = abs(endX - startX);
        int height = abs(endY - startY);
        drawEllipse((startX + endX) / 2, (startY + endY) / 2, width / 2, height / 2);
    }

    for (const auto& ellipse : ellipses) {
        drawEllipse(ellipse.x, ellipse.y, ellipse.a, ellipse.b);
    }

    renderBitmapString(10, glutGet(GLUT_WINDOW_HEIGHT) - 20, GLUT_BITMAP_HELVETICA_18, mode.c_str());

    glutSwapBuffers();
}

void menuFunc(int value) {
    if (value == 1) {
        menuStatus = 1;
        mode = "Ellipses";
    }
    if (value == 2) {
        ellipses.clear();
        mode = "Right click to select a graph type";
        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Create a menu
        int menu = glutCreateMenu(menuFunc);
        glutAddMenuEntry("Ellipse", 1);
        glutAddMenuEntry("Clear", 2);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && menuStatus == 1) {
        startX = endX = x;
        startY = endY = y;
        //printf("%d,%d",x,y);
        drawing = true;
        mode = "hold SHIFT and draw the graph for a circle";
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && menuStatus == 1) {
        drawing = false;
        int width = abs(endX - startX);
        int height = abs(endY - startY);
        ellipses.push_back({ (startX + endX) / 2, (startY + endY) / 2, width / 2, height / 2 });
        startX = 0; startY = 0; endX = 0; endY = 0;
        mode = "ellipses";
        glutPostRedisplay();
    }
}

void motion(int x, int y) {
    if (drawing) {
        endX = x;
        endY = y;
        glutPostRedisplay();
        // If Shift is pressed, make it a circle
        if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
            endY = startY + abs(endX-startX);
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

    glutMainLoop();

    return 0;
}

