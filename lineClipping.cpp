#include <vector>
using namespace std;
#include "lineClipping.h"
/***********************************************
*���p����<0�����㡢����umax����֤umax�����uֵ
*���p����>0�����㡢����umin����֤umin����Сuֵ
*���umax>umin������0�����򷵻�1
***********************************************/
int Clip_Top(float p,float q,float &umax,float &umin){	
	float r=0.0;
    if(p<0.0)	//�߶δӲü������ⲿ���쵽�ڲ���ȡ���ֵr������umax
	{  
		r=q/p;
		if (r>umin) return 0;	//umax>umin���������֮
		else if (r>umax)  umax=r; 
	}
	else if(p>0.0)      //�߶δӲü������ڲ����쵽�ⲿ,ȡ��Сֵr������umin
		{  
			r=q/p;
			if (r<umax) return 0;	//umax>umin���������֮
			else if(r<umin)  umin=r; 
		}
	   else 		//p=0ʱ���߶�ƽ���ڲü�����
	      if(q<0.0) return 0;
	 return 1;
}
/*************************************************************
*��֪winRect�����ζ��󣬴�ű�׼�ü�����4������Ϣ
*    points����Ķ�̬���飬���ֱ��2���˵���Ϣ
*���ݲü����ڵ����ұ߽磬��umax��
*���ݲü����ڵ��¡��ϱ߽磬��umin
*���umax>umin���ü����ں�ֱ���޽��㣬������ü���ֱ���¶˵�
***************************************************************/
void Line_Clipping(vector<point> &points,rect & winRect){
	//�Ƚ����ұ߽磬�������umax
	point &p1=points[0],&p2=points[1];
	float dx=p2.x-p1.x,dy=p2.y-p1.y,umax=0.0,umin=1.0;		  
	point p=p1;
	if (Clip_Top(-dx,p1.x- winRect.w_xmin,umax,umin))  //��߽�
		if (Clip_Top(dx,winRect.w_xmax-p1.x, umax,umin)) //�ұ߽�
			//�Ƚ��¡��ϱ߽磬�����С��umin
			if (Clip_Top(-dy,p1.y- winRect.w_ymin, umax,umin)) //�±߽�
				if (Clip_Top(dy,winRect.w_yman-p1.y, umax,umin)) //�ϱ߽�
				{//��ü���ֱ���¶˵�	
					p1.x=(int)(p.x+umax*dx);
					p1.y=(int)(p.y+umax*dy);
					p2.x=(int)(p.x+umin*dx);
					p2.y=(int)(p.y+umin*dy);
				}
} 