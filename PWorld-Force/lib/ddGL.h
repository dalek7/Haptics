#ifndef __DD_GL__
#define __DD_GL__



#include "gl/gl.h"
#include "gl/glu.h"
#include <GL/glut.h>

#pragma comment(lib, TEXT("glu32.lib"))
#pragma comment(lib, TEXT("opengl32.lib"))


#include "./3d/dhmat.h"
#include "./3d/dhVector.h"

#undef PI
#define PI	3.1415926535897932f
#define HPI	1.5707963267948966f
#define PI2	6.2831853071795864f

#undef DEG
#define DEG(a)          (180.*a/PI )
#undef RAD
#define RAD(a)          (PI*a/180.)


#define W	800
#define H	600 




#include "xRGB.h"
#include "ddMacros.h"
#include "ddMath.h"
/*
#include "../vString.h"

//#include "../3d/dhMat.h"

#include "../vArray.h"
#include "../PTRList.h"



*/

#include "vwPrimitives.h"
#include "vwCamera.h"
#include "vwLight.h"
#include "vwO.h"
/*
#include "ddLayer.h"
#include "ddScene.h"
*/


class ddGL
{
public:
		ddGL();

private:
		vwCamera	m_camera;
		vwLight		m_light;


public:
		vwCamera	*pCamera;
		vwLight		*pLight;

public:
		BOOL	Init();
		void	Run();
		void	Draw();
		void	Close();
		void	PreDraw();
		void	PostDraw();	
		void	SetScale(float);




public:
		void	SetCamera(int,int);
		
		void	initGL();

		BOOL	MouseMove(int,CPoint);
		CPoint	ptMouseOld;


public:
	
		GLdouble	modelMatrix[16];
		GLdouble	projMatrix[16];
		int			viewport[4];



};

extern ddGL	*pGL;

#endif