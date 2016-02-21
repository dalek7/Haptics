// GLWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PWorld.h"
#include "GLWnd.h"
#include "PWorldDoc.h"
#include "PWorldView.h"

extern CPWorldView *pv;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CGLWnd


CGLWnd::CGLWnd()
{
	tcnt0 = 0;


	pGL			= &m_gl;
	pHL			= &m_haptics;

	objID		= 0;
	tangle		= 0;


}

CGLWnd::~CGLWnd()
{
}


BEGIN_MESSAGE_MAP(CGLWnd, CWnd)
	//{{AFX_MSG_MAP(CGLWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGLWnd message handlers

void CGLWnd::OnDestroy() 
{

	KillTimer(1);


/*
	if (ghHD != HD_INVALID_HANDLE)
    {
        hdDisableDevice(ghHD);
    }
*/
	CWnd::OnDestroy();
	
}
float t0=0;
int prev_objID = -1;
void CGLWnd::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==1)
	{	

		//watchdog
		objID = pv->m_model_id.GetValued();
		if(prev_objID != objID)
		{
			Dbg("%d --> %d", prev_objID, objID);


		}


		prev_objID = objID;

		tangle = pv->m_edit_angle.GetValuef();

		//VIEW *pvw = &pGL->pCamera->vw;
		//pv->dbg(0,"%.2f, %.2f, %.2f", pvw->o.x, pvw->o.y, pvw->o.z);


		if(tcnt0<2) t0 = m_haptics.m_tm.End();
		float tnow = m_haptics.m_tm.End() - t0;

		
		if(pHL->bInit)
		{

			pv->dbg(0,"%d, %.2f, %d", tcnt0, tnow, m_haptics.bTakingRest);

			pv->dbg(1,"%d, %d samples", m_haptics.bTakingRest, m_haptics.traj_dev.GetSize());


			//pv->dbg(2,"%.2f, %.2f, %.2f", m_haptics.gPos[0], m_haptics.gPos[1], m_haptics.gPos[2]);
			pv->dbg(2,"%.2f, %.2f, %.2f", m_haptics.gForce[0], m_haptics.gForce[1], m_haptics.gForce[2]);

		}
		
		
		//

		Invalidate();

		
	}
	CWnd::OnTimer(nIDEvent);
}

int CGLWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_hDC	= ::GetDC( m_hWnd );

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// Size of this structure
		1,								// Version of this structure	
		PFD_DRAW_TO_WINDOW |			// Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |			// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,				// Double buffered mode
		PFD_TYPE_RGBA,					// RGBA Color mode
		32,								// Want 32bit color 
		8,16,8,8,8,0,					// Not used to select mode
		0,0,							// Not used to select mode
		64,16,16,16,0,						// Not used to select mode
		32,								// Size of depth buffer
		8,								// Not used to select mode
		0,								// Not used to select mode
		PFD_MAIN_PLANE,					// Draw in main plane
		0,								// Not used to select mode
		0,0,0 };						// Not used to select mode

	int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	VERIFY(SetPixelFormat(m_hDC, nPixelFormat, &pfd));
	m_hRC = wglCreateContext(m_hDC);

	wglMakeCurrent(m_hDC,m_hRC);
	{
		initScene();
	}
	wglMakeCurrent(NULL,NULL);

	// init.


	// Initialize object
	
	float l = 1.5;

	m_obj.MakeBox(l,l,l);
	m_obj.Trans(-l/2.0,0,-l/2.0);



	
	//m_obj.MakePlane(3,5,10,10);


	SetTimer(1,30,NULL);
	
	return 0;
}

void CGLWnd::initScene()
{
    pGL->initGL();
    //pHL->initHL();
}


void CGLWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	wglMakeCurrent( m_hDC,m_hRC);
	Draw();				
	SwapBuffers( m_hDC);
	wglMakeCurrent( m_hDC,NULL);

}

void CGLWnd::Draw()
{
	if(pv->m_chk_fill.GetCheck())
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();   

		VIEW *pvw = &pGL->pCamera->vw;
		glTranslatef(pvw->o.x, pvw->o.y, pvw->o.z);
		glRotatef(pvw->r.x,1,0,0);
		glRotatef(pvw->r.y,0,1,0);

	}

	if(pHL->bInit)
	{
		updateWorkspace();

		
		drawSceneHaptics();
	}
	
	drawSceneGraphics();
	
	if(pHL->bInit)
	{
		pHL->GetPosDevice();
		tcnt0++;
	}
	

}


		

void CGLWnd::drawSceneGraphics()
{
	glClearColor(0,0,0,255);	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	
	       

    // Draw 3D cursor at haptic device position.
	if(pHL->bInit)
		drawCursor();
	DrawGrid(3,0.3);
	glPushMatrix();
	
		//glTranslatef(0,0,-1);
		//m_obj.Draw(TRUE);
		glRotatef(tangle, 0, 1, 0);
		pGL->pCamera->CopyMatrices();
		//DrawSphere(1);
			if(objID ==2)
		{
			DrawTorus(0.3, 0.8);
		}
		else if(objID==1)
		{
			DrawSphere(1);
		}
		else if(objID==3)
		{
			//DrawTorusC(32, 32);
		}
		else
		{
			//GLfloat TubeRadius, GLfloat Radius, GLint Sides, GLint Rings
			DrawTorusPartial(0.25, 1, 32, 32, 0.9);
			//m_obj.Draw(TRUE);
		}


	glPopMatrix();


}


void CGLWnd::drawSceneHaptics()
{    
    // Start haptic frame.  (Must do this before rendering any haptic shapes.)
   hlBeginFrame();

    // Set material properties for the shapes to be drawn.
    hlMaterialf(HL_FRONT_AND_BACK, HL_STIFFNESS, 0.7f);
    hlMaterialf(HL_FRONT_AND_BACK, HL_DAMPING, 0.1f);
    hlMaterialf(HL_FRONT_AND_BACK, HL_STATIC_FRICTION, 0.2f);
    hlMaterialf(HL_FRONT_AND_BACK, HL_DYNAMIC_FRICTION, 0.3f);

    // Start a new haptic shape.  Use the feedback buffer to capture OpenGL
    // geometry for haptic rendering.
    hlBeginShape(HL_SHAPE_FEEDBACK_BUFFER, pHL->gSphereShapeId);

    // Use OpenGL commands to create geometry.
	
   	glPushMatrix();
		
	//glTranslatef(0,0,-1);

	glRotatef(tangle, 0, 1, 0);
	pGL->pCamera->CopyMatrices();

	if(objID ==2)
	{
		DrawTorus(0.3, 0.8);
	}
	else if(objID==1)
	{
		DrawSphere(1);
	}
	else if(objID==3)
	{
		//DrawTorusC(32, 32);
	}
	else
	{
		DrawTorusPartial(0.25, 1, 32, 32, 0.9);
		//m_obj.Draw();
	}

	

	glPopMatrix();


    // End the shape.
    hlEndShape();

    // End the haptic frame.
    hlEndFrame();
}

void CGLWnd::drawCursor()
{
    static const double kCursorRadius = 0.5;
    static const double kCursorHeight = 1.5;
    static const int kCursorTess = 15;
    HLdouble proxyxform[16];

    GLUquadricObj *qobj = 0;

    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);
    glPushMatrix();

    if (!pHL->gCursorDisplayList)
    {
        pHL->gCursorDisplayList = glGenLists(1);
        glNewList(pHL->gCursorDisplayList, GL_COMPILE);
        qobj = gluNewQuadric();
               
        gluCylinder(qobj, 0.0, kCursorRadius, kCursorHeight,
                    kCursorTess, kCursorTess);
        glTranslated(0.0, 0.0, kCursorHeight);
        gluCylinder(qobj, kCursorRadius, 0.0, kCursorHeight / 5.0,
                    kCursorTess, kCursorTess);
    
        gluDeleteQuadric(qobj);
        glEndList();
    }
    
    // Get the proxy transform in world coordinates.
    hlGetDoublev(HL_PROXY_TRANSFORM, proxyxform);

	//proxyxform[14] *= -1.0;


	pv->SetProxyForm(proxyxform);

    glMultMatrixd(proxyxform);

    // Apply the local cursor scale factor.
    glScaled(pHL->gCursorScale, pHL->gCursorScale, pHL->gCursorScale);

    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.0, 0.5, 1.0);

    glCallList(pHL->gCursorDisplayList);

    glPopMatrix(); 
    glPopAttrib();
}


void CGLWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	
	wglMakeCurrent(m_hDC,m_hRC);
	{
		pGL->SetCamera(cx,cy);///m_game.Init();
	}
	VERIFY(wglMakeCurrent(NULL,NULL));	



}

/*******************************************************************************
 Use the current OpenGL viewing transforms to initialize a transform for the
 haptic device workspace so that it's properly mapped to world coordinates.
*******************************************************************************/
void CGLWnd::updateWorkspace()
{
   
	pGL->pCamera->CopyMatrices();
	GLdouble* mm	= pGL->pCamera->GetMM();
	GLdouble* pm	= pGL->pCamera->GetPM();
	GLint* vp		= pGL->pCamera->GetVP();

	pv->DispMM(mm);
	pv->DispPM(pm);
	pv->DispVP(vp);
  
    // Compute cursor scale.
	if(tcnt0==0)
	{
		hlMatrixMode(HL_TOUCHWORKSPACE);
		hlLoadIdentity();
    
    // Fit haptic workspace to view volume.
		hluFitWorkspace(pm);

		//gCursorScale = hluScreenToModelScale(modelview, projection, viewport);
		pHL->gCursorScale = hluScreenToModelScale(mm, pm, vp);
		pHL->gCursorScale *= CURSOR_SIZE_PIXELS;	//0.08
	}
}


void CGLWnd::OnMouseMove(UINT nFlags, CPoint point) 
{

	if (pGL->MouseMove(nFlags,point))
	{
		Invalidate();
		

		//pWnd->InvalidateRect(CRect(0,0,1280,1024)+CPoint(1280,0));
	}

	CWnd::OnMouseMove(nFlags, point);
}


