#ifndef __VWO__
#define __VWO__

#include "ddGL.h"


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
		void	DrawNormal();
		void	Draw(BOOL bDispAxis=FALSE);
		void	DrawObject(BOOL bDispAxis=FALSE);

		void	FindFlat();
		void	FindGourad();

		dhVector len;

public:
		dhVector	*pVer;
		int			nVer;
		dhVector	*pNormal;

		vwPolygon	*pFace;
		int			nFace;



public:
	// coordinate
		void	Trans(dhVector);
		void	Trans(float,float,float);
		void	Rot(float a,float b,float r);	// general coord.
		void	RotX(float);
		void	RotY(float);
		void	RotZ(float);

		
		void	Scale(float);
		void	Scale(dhVector);

		dhMat		H1;
public:
		BOOL	bShow;


public:
		void	DisplayOrigin();

		dhVector GetANormalAbs(int faceID);
		dhVector GetSurfaceNormalMV(int nFaceID, dhVector vw_o, dhVector vw_r);
		dhVector	DrawASurfaceNormal(int faceID, float scale,float *pArea, BOOL stickToMouse = FALSE);
		void	DrawLineWithArrow3D(dhVector stPt, dhVector endPt, BOOL arrowAtTheEnd = TRUE, float z_offset= 0, float scale_arrow= 1.0);
		void	GetTriangleVertices(int faceID, dhVector* pV, BOOL bApplyModelView = FALSE);
		void	DrawTriangle(int faceID, float offset_scaling);
		void	DrawTriangleLine(int faceID);
};

#endif