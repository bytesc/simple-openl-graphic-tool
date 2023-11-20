#include <vector>

using namespace std;
//根据点序列向量数组points，绘制折线 
void drawPolygonalLine(vector<point> &points,color &c );
//根据点序列向量数组points，绘制折线
void drawPolygonalLine(vector<point> &points ,point &p,color &c);
//如果控制点数n<4，绘制一段n-1次Bezier曲线段，否则绘制一段三次Bezier曲线段
void drawBezierCurve(vector<Point> &points,color &c); 
//通过（m×3+1）控制点，绘制m段n-1次ezier曲线段 
void drawBezierCurve(vector<Point> &points,int n,color &c);
	
 