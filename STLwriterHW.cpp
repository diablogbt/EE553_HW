/*
	Author: Yubao Geng
	No cite
	STL with Cube and Cylinder Generator
	Cylinder not complete
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<cstring>
using namespace std;
ofstream fout("gbt_hw.stl");

#define pi 3.141593
//#define TEST 1

class Shape{
	private:
		int type;
		vector<double> size;
	public:
		double ctx,cty,ctz;
		double the1,the2;
		int id;
		Shape(int tp,double x,double y,double z):type(tp){
			ctx=cty=ctz=0;
			the1=the2=0;
			size.push_back(x);
			size.push_back(y);
			size.push_back(z);
		}
		int getType()
		{
			return type;
		}
		vector<double>& getSize(){
			return size;
		}
};

class Cylinder: public Shape{
	private:
		
	public:
		Cylinder(double r,double h,int facets):Shape(2,r,h,facets){
		}		
};

class Cube: public Shape{
	private:
		
	public:
		Cube(double sx,double sy,double sz):Shape(1,sx,sy,sz){
		}
};

class CAD{
	public:
		vector<Shape*> shape;
		int num;
		
		CAD(){
			num=0;
		} 
		
		Shape& operator()(int i);
		void set_center(int,double,double,double);
		void add_cube(double x,double y,double z);
		void add_cylinder(double r,double h,double facets);
		friend void stl_gen(Shape&);
};

Shape& CAD::operator()(int i)
{
	return *shape[i];
}

void facet(vector<double>& nodes){
	fout<<"facet normal "<<nodes[0]<<' '<<nodes[1]<<' '<<nodes[2]<<endl;
	fout<<"couter loop"<<endl;
	for(int i=0;i<3;i++)
		fout<<"vertex "<<nodes[3*i+3]<<' '<<nodes[3*i+4]<<' '<<nodes[3*i+5]<<endl;
	fout<<"endloop"<<endl<<"endfacet"<<endl<<endl;
}

void CAD::add_cube(double x,double y,double z)
{
	num++;
	Shape* obj=new Cube(x,y,z);
	shape.push_back(obj);
}

void CAD::add_cylinder(double r,double h,double facets)
{
	num++;
	Shape* obj=new Cylinder(r,h,facets);
	shape.push_back(obj);
}


void CAD::set_center(int i,double x,double y,double z)
{
	shape[i-1]->ctx=x;
	shape[i-1]->cty=y;
	shape[i-1]->ctz=z;
}
void nd_val(vector<double>& nd,int i,double x,double y,double z)
{
	nd[i*3]=x;nd[i*3+1]=y;nd[i*3+2]=z;
}
void stl_gen(Shape& obj)
{
	
	
	int tp;
	tp=obj.getType();
	
	cout<<tp;
	vector<double> nd;
	for(int i=0;i<12;i++)
		nd.push_back(0);
	vector<double> siz=obj.getSize();
	
	
	
	cout<<'2';
	
	if(tp==1)
	{
		nd_val(nd,0,-1,0,0);
		nd_val(nd,1,obj.ctx-siz[0]/2,obj.cty-siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,2,obj.ctx-siz[0]/2,obj.cty+siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,3,obj.ctx-siz[0]/2,obj.cty+siz[1]/2,obj.ctz+siz[2]/2);
		facet(nd);
		
		nd_val(nd,0,-1,0,0);
		nd_val(nd,1,obj.ctx-siz[0]/2,obj.cty-siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,2,obj.ctx-siz[0]/2,obj.cty-siz[1]/2,obj.ctz+siz[2]/2);
		nd_val(nd,3,obj.ctx-siz[0]/2,obj.cty+siz[1]/2,obj.ctz+siz[2]/2);
		facet(nd);
		//-------------------1
		nd_val(nd,0,1,0,0);
		nd_val(nd,1,obj.ctx+siz[0]/2,obj.cty-siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,2,obj.ctx+siz[0]/2,obj.cty+siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,3,obj.ctx+siz[0]/2,obj.cty+siz[1]/2,obj.ctz+siz[2]/2);
		facet(nd);
		
		nd_val(nd,0,1,0,0);
		nd_val(nd,1,obj.ctx+siz[0]/2,obj.cty-siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,2,obj.ctx+siz[0]/2,obj.cty-siz[1]/2,obj.ctz+siz[2]/2);
		nd_val(nd,3,obj.ctx+siz[0]/2,obj.cty+siz[1]/2,obj.ctz+siz[2]/2);
		facet(nd);
		//-----------------2
		nd_val(nd,0,0,-1,0);
		nd_val(nd,1,obj.ctx-siz[0]/2,obj.cty-siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,2,obj.ctx+siz[0]/2,obj.cty-siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,3,obj.ctx+siz[0]/2,obj.cty-siz[1]/2,obj.ctz+siz[2]/2);
		facet(nd);
		
		nd_val(nd,0,0,-1,0);
		nd_val(nd,1,obj.ctx+siz[0]/2,obj.cty-siz[1]/2,obj.ctz+siz[2]/2);
		nd_val(nd,2,obj.ctx-siz[0]/2,obj.cty-siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,3,obj.ctx-siz[0]/2,obj.cty-siz[1]/2,obj.ctz+siz[2]/2);
		facet(nd);
		//-----------------3
		nd_val(nd,0,0,1,0);
		nd_val(nd,1,obj.ctx-siz[0]/2,obj.cty+siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,2,obj.ctx+siz[0]/2,obj.cty+siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,3,obj.ctx+siz[0]/2,obj.cty+siz[1]/2,obj.ctz+siz[2]/2);
		facet(nd);
		
		nd_val(nd,0,0,1,0);
		nd_val(nd,1,obj.ctx+siz[0]/2,obj.cty+siz[1]/2,obj.ctz+siz[2]/2);
		nd_val(nd,2,obj.ctx-siz[0]/2,obj.cty+siz[1]/2,obj.ctz-siz[2]/2);
		nd_val(nd,3,obj.ctx-siz[0]/2,obj.cty+siz[1]/2,obj.ctz+siz[2]/2);
		facet(nd);
	}
	
}

int main()
{
	CAD wd;
	wd.add_cube(2,3,4);
	
	fout<<"solid Unity Mesh"<<endl;
	stl_gen(wd(0));
}
