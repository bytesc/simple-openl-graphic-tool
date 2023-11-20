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
void drawBezierCurve(vector<Point> &points,int n,color &c){	
}
 
 