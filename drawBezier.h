#include <vector>

using namespace std;
//���ݵ�������������points���������� 
void drawPolygonalLine(vector<point> &points,color &c );
//���ݵ�������������points����������
void drawPolygonalLine(vector<point> &points ,point &p,color &c);
//������Ƶ���n<4������һ��n-1��Bezier���߶Σ��������һ������Bezier���߶�
void drawBezierCurve(vector<Point> &points,color &c); 
//ͨ����m��3+1�����Ƶ㣬����m��n-1��ezier���߶� 
void drawBezierCurve(vector<Point> &points,int n,color &c);
	
 