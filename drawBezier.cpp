#include <vector>
using namespace std;
#include <GL/glut.h>
//#include "graphicType.h"
//��������
void drawPolygonalLine(vector<point> &points,color &c ){//���ݵ�������������points����������	 
	glColor3f(c.r, c.g, c.b); 
	glBegin (GL_LINE_STRIP);
		for(int i=0;i<points.size();i++){
			glVertex2i(points[i].x, points[i].y);
		}		
	glEnd();
}
//��������
void drawPolygonalLine(vector<point> &points ,point &p,color &c){//���ݵ�������������points����������	
	glColor3f(c.r, c.g, c.b); 
	glBegin (GL_LINE_STRIP);
		for(int i=0;i<points.size();i++){
			glVertex2i(points[i].x, points[i].y);
		}		
		glVertex2i(p.x, p.y);
	glEnd();
}
//������Ƶ���n<4������һ��n-1��Bezier���߶Σ��������һ������Bezier����
void drawBezierCurve(vector<Point> &points,color &c){
	GLfloat ControlP[4][3];
	int iPointNum=points.size();
	int i;
	if(iPointNum<4){//���Ƶ���<4������һ��n-1��Bezier���߶�
		for(i=0;i<iPointNum;i++){
			ControlP[i][0]=points[i].x;
			ControlP[i][1]=points[i].y;
			ControlP[i][2]=0.0;	
		}				
	}
	else{
		for(i=0;i<4;i++){//���Ƶ���>=4������һ������Bezier���߶�
			ControlP[i][0]=points[i].x;
			ControlP[i][1]=points[i].y;
			ControlP[i][2]=0.0;					
		}	
	}		
	glColor3f(c.r, c.g, c.b); 
	glPointSize(2);
	if(iPointNum>4)
		glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,*ControlP);//����һάȡֵ��
	else
		glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,iPointNum,*ControlP);//����һάȡֵ��
	glEnable(GL_MAP1_VERTEX_3);
	glMapGrid1f(100,0.0,1.0);//���ɾ��ȷֲ���һά�������ֵ
	glEvalMesh1(GL_LINE, 0, 100);//����Bezier����
}
//ͨ����m��3+1�����Ƶ㣬����m��n-1��ezier���߶� 
//void drawBezierCurve(vector<Point> &points,int n,color &c){	
//
//}
//ͨ����m��3+1�����Ƶ㣬����m��n-1��Bezier���߶� 
void drawBezierCurve(vector<Point>& points, int n, color& c) {
	int m = points.size() / 2; // �����ж��ٶ�����
	vector<Point> curvePoints;
	curvePoints.push_back(points[0]);
	curvePoints.push_back(points[1]);
	curvePoints.push_back({ (points[1].x + points[2].x) / 2,
			(points[1].y + points[2].y) / 2 });
	drawBezierCurve(curvePoints, c);
	curvePoints.clear();
	int i = 1;
	for ( i = 1; i < m; i++) {
		if (i * 2 + 2 >= points.size()) {
			break;
		}
		vector<Point> curvePoints; // ��ȡÿ�����ߵĿ��Ƶ�
		curvePoints.push_back({ (points[i * 2].x + points[i * 2 -1].x) / 2,
			(points[i * 2].y + points[i * 2 -1].y) / 2 });
		curvePoints.push_back(points[i * 2]);
		curvePoints.push_back(points[i * 2 + 1]);
		curvePoints.push_back({(points[i * 2 + 1].x + points[i * 2 + 2].x) / 2,
			(points[i * 2 + 1].y + points[i * 2 + 2].y) / 2 });
		drawBezierCurve(curvePoints, c); // ʹ�����еĺ�������ÿ������
	}
	i--;
	curvePoints.push_back({ (points[i * 2 + 1].x + points[i * 2 + 2].x) / 2,
			(points[i * 2 + 1].y + points[i * 2 + 2].y) / 2 });
	for (int j = i * 2 + 2; j < points.size(); j++) {
		curvePoints.push_back(points[j]);
	}
	drawBezierCurve(curvePoints, c);
}


void drawBSplineCurve(const vector<point>& points, int ControlN, color& c)
{
	glColor3f(c.r, c.g, c.b);
	int caiyang = 10; 
	vector<point> curvePoints;
	int n = points.size() - 1;
	float dt = 1.0 / caiyang;
	for (int i = 2; i < n; i++)
	{
		for (float t = 0; t <= 1; t += dt)
		{
			float t2 = t * t;
			float t3 = t2 * t;

			float b0 = (1 - t) * (1 - t) * (1 - t) / 6.0;
			float b1 = (3 * t3 - 6 * t2 + 4) / 6.0;
			float b2 = (-3 * t3 + 3 * t2 + 3 * t + 1) / 6.0;
			float b3 = t3 / 6.0;

			float x = b0 * points[i - 2].x + b1 * points[i - 1].x + b2 * points[i].x + b3 * points[i + 1].x;
			float y = b0 * points[i - 2].y + b1 * points[i - 1].y + b2 * points[i].y + b3 * points[i + 1].y;

			curvePoints.push_back(point(x, y));
		}
	}

	glBegin(GL_LINE_STRIP);
	for (const auto& p : curvePoints)
	{
		glVertex2f(p.x, p.y);
	}
	glEnd();

	//glFlush(); 
}