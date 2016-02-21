#ifndef __VWO__
#define __VWO__

#include "gl/gl.h"
#include "gl/glu.h"
#include "3d/dhVector.h"
#include "3d/dhMat.h"

class vwPolygon
{
public:
		vwPolygon();
public:
		dhVector *v[3];
		void	Tri(dhVector*,int,int,int);
};

class vwO
{
public:
		vwO();
		~vwO();
public:
		// startup
		void	Init(int,int);
		void	Close();
		
		void	MakeBox(float,float,float);
		void	MakePlane(float,float,int m=10,int n=10);
		void	MakeCylinder(float r,float R,float h,int n=36);
		void	DrawNormal();
		void	Draw(BOOL bDispAxis=FALSE);
		void	DrawObject(BOOL bDispAxis=FALSE);

		void	FindFlat();
		void	FindGourad();


		void	DisplayOrigin();

public:
		dhVector	*pVer;
		int			nVer;
		dhVector	*pNormal;

		vwPolygon	*pFace;
		int			nFace;

};

#endif