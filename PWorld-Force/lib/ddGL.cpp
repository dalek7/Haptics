#include "stdafx.h"
#include "ddGL.h"

ddGL	*pGL	= NULL;

ddGL::ddGL()
{

	pCamera	= &m_camera;


	pLight	= &m_light;
}


BOOL ddGL::Init()
{
	Dbg("ddGL::Init()");

	SetCamera(W,H);

	return TRUE;
}


BOOL ddGL::MouseMove(int nFlags,CPoint pt)
{

	return pCamera->MouseMove(nFlags,pt);

	//return FALSE;
}

void ddGL::SetCamera(int w,int h)
{
	pCamera->SetCamera(w, h);

	//pLight->InitTextureParams();
	//pLight->SetDefaultMaterial();

}


void ddGL::initGL()
{
    // Enable depth buffering for hidden surface removal.
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    
    // Cull back faces.
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    // Setup other misc features.
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
	static const GLfloat light_model_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    static const GLfloat light0_diffuse[] = {0.9f, 0.9f, 0.9f, 0.9f};   
    static const GLfloat light0_direction[] = {0.0f, -0.4f, 1.0f, 0.0f};    

    // Setup lighting model.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
    glEnable(GL_LIGHT0);   
}
