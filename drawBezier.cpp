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


 