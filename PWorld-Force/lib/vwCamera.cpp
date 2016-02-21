#include "StdAfx.h"
//#include "vwCamera.h"
#include "ddGL.h"

vwCamera::vwCamera(void)
{

	InitCam();


	ptMouseOld	= CPoint(0,0);

}

vwCamera::~vwCamera(void)
{
}

void vwCamera::InitCam()
{
	double kFovY = 60;
	double kPI = 3.1415926535897932384626433832795;

	double nearDist, farDist;

	nearDist	= 2;//1.0 / tan((kFovY / 2.0) * kPI / 180.0);//2.74
	farDist		= nearDist+6;	//6.74

	vw.f	= farDist; 
	vw.n	= nearDist;
	vw.angle= kFovY;
	vw.o	= dhVector(0,-1,-4.5);//nearDist-10
	vw.r	= dhVector(0,0,0);
}

void vwCamera::SetCamera(int cx, int cy)
{

	vw.w	= cx;
	vw.h	= cy;
	vw.fAR= ((float)cx)/((float)cy);	
	
	
	glViewport( 0,0,cx,cy );

	//ApplyOrtho();
	ApplyProjectionTransform();

	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();  
	
	

}

void vwCamera::ApplyOrtho()
{
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

     /*     glortho
          [ 2/(r-l) 0 0 tx
            0 2/(t-b) 0 ty
            0 0 -2/(f-n) tz
            0 0 0 1] 
            tx =  -(r+l)/(r-l);
            ty = -(t+b)/(t-b);
            tz = -(f+n)/(f-n);
     */
   
	//glOrtho(	0, 800, 0, 600, 65535, 0.1);



	return;
    float l,r,t,b,f,n;
    l = 0;
    r = 800;
    t = 600;
    b = 0;
    f = vw.f;
    n = vw.n;
   
    float v[16]={0,};
    v[0]     = 2/(r-l);
    v[5]     = 2/(t-b);
    v[10]     = -2/(f-n);
    v[12]     = -(r+l)/(r-l);
    v[13]     = -(t+b)/(t-b);
    v[14]     = (f+n)/(f-n);     // change sign for (+)direction depth test.
    v[15]     = 1;


	glMultMatrixf(v);
    

}

void vwCamera::ApplyProjectionTransform()
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(vw.angle,vw.fAR,vw.n,vw.f );
//	glScalef(1, -1, 1);
}


void vwCamera::CopyMatrices()
{
	glGetDoublev(GL_MODELVIEW_MATRIX,	mm);
	glGetDoublev(GL_PROJECTION_MATRIX,	pm);
	glGetIntegerv(GL_VIEWPORT,			vp);


	for(int i=0; i<16; i++)
	{
		mat_mm.v[i]		= mm[i];
		mat_pm.v[i]		= pm[i];
	}
}


void vwCamera::CopyMatricesd(double *mm_,double *pm_, int* vp_ )
{

	glGetDoublev(GL_MODELVIEW_MATRIX,	mm_);
	glGetDoublev(GL_PROJECTION_MATRIX,	pm_);
	glGetIntegerv(GL_VIEWPORT,			vp_);
}



GLdouble* vwCamera::GetMM()
{
	return mm;
}
GLdouble* vwCamera::GetPM()
{
	return pm;
}

int* vwCamera::GetVP()
{
	return vp;
}



//Projection used by GL
dhVector vwCamera::Projection2(dhVector v)
{

	dhVector ret;
	
	double x, y, z;

	gluProject(v.x, v.y, v.z, mm, pm, vp, &x, &y, &z);

	ret.x = x;
	ret.y = vp[3] - y;
	ret.z = 0;


	return ret;
}
	



void vwCamera::UnProjection(dhVector pt_screen, dhVector* output)
{

	double out[3];

	gluUnProject(pt_screen.x, vw.h-pt_screen.y, 0, mm, pm, vp, &out[0],&out[1],&out[2] );
	
	output->x = out[0];
	output->y = out[1];
	output->z = out[2];

}




BOOL vwCamera::MouseMove(int nFlags,CPoint pt)
{
	CPoint dpt	= pt-ptMouseOld;
	ptMouseOld	= pt;

	int dx,dy;
	dx	= fabs((float)dpt.x);
	dy	= fabs((float)dpt.y);

	switch(nFlags)
	{
		case MK_LBUTTON|MK_RBUTTON:
		if (dx>dy)
		{
			if (dpt.x>2)		{	vw.r.y+=5;	return TRUE; }
			else if (dpt.x<-2)	{	vw.r.y-=5;	return TRUE; }
		}
		else
		{
			if (dpt.y>2)		{	vw.r.x+=5;	return TRUE; }
			else if (dpt.y<-2)	{	vw.r.x-=5;	return TRUE; }
		}
		break;
	

		case MK_RBUTTON:
		{
			vw.o.z -= (float)0.1f * dpt.y;
			
			break;
		}

		case MK_MBUTTON:
		{

			vw.o.x += (float)0.05f * dpt.x;
			vw.o.y -= (float)0.05f * dpt.y;
			
			break;
		}

	}
	/*
	CString buf;
	buf.Format("%d, %d", pt.x, pt.y);
	pv->dbg(buf,1);
	buf.Format("%d, %d", dpt.x, dpt.y);
	pv->dbg(buf);
*/

	return FALSE;
}

