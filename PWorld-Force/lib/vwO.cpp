#include "stdafx.h"
#include "ddGL.h"

vwPolygon::vwPolygon()
{
	for (int i=0;i<3;i++)
		v[i]	= NULL;
}

void vwPolygon::Tri(dhVector *p,int a,int b,int c)
{
	v[0] = &p[a];
    v[1] = &p[b];
    v[2] = &p[c];
}

vwO::vwO()
{
	pVer	= NULL;
	pFace	= NULL;
	nVer	= NULL;
	nFace	= NULL;
	pNormal	= NULL;

	bShow	= TRUE;
}

vwO::~vwO()
{
	Close();
	Dbg("vwObj::~vwObj()");

}

void vwO::Init(int nv,int nf)
{
	Close();

	pVer	= new dhVector[nv];
	pFace	= new vwPolygon[nf];
	nVer	= nv;
	nFace	= nf;
}

void vwO::Close()
{
	if (pVer)	delete []pVer;
	pVer	= NULL;
	if (pFace)	delete []pFace;
	pFace	= NULL;
	if (pNormal)delete []pNormal;
	pNormal	= NULL;

	nVer	= 0;
	nFace	= 0;
}

void vwO::RotY(float y)
{
	H1	= H1.RotY(RAD(y))*H1;
}


void vwO::RotX(float x)
{
	H1	= H1.RotX(RAD(x))*H1;
}

void vwO::RotZ(float x)
{
	H1= H1.RotZ(RAD(x))*H1;
}


void vwO::Rot(float a,float b,float r)
{
	dhVector v = H1.O();
	H1.I();
	H1	= H1.RotZ(RAD(r))*H1.RotY(RAD(b))*H1.RotX(RAD(a));
	H1	= H1	+ v;
}

void vwO::Trans(float x,float y,float z)
{
	H1.v[12]	= x;
	H1.v[13]	= y;
	H1.v[14]	= z;
}

void vwO::Trans(dhVector v)
{
	vwO::Trans(v.x,v.y,v.z);
}


void vwO::Scale(float s)
{
	int i;
	for(i=0; i<nVer; i++)
	{
		
		pVer[i] = pVer[i].Scaling(s);


	}
}


void vwO::Scale(dhVector s)
{
	int i;
	for(i=0; i<nVer; i++)
	{
		
		pVer[i] = pVer[i].Scaling(s);

	}
}

void vwO::MakeBox(float a,float b,float c)
{
	len.Vector(a, b, c);

	Init(8,12);

	pVer[0].Vector( 0,0,0 );
    pVer[1].Vector( a,0,0 );
    pVer[2].Vector( a,b,0 );
    pVer[3].Vector( 0,b,0 );
    pVer[4].Vector( 0,0,c );
    pVer[5].Vector( a,0,c );
    pVer[6].Vector( a,b,c );
    pVer[7].Vector( 0,b,c );

	// cw
	pFace[0].Tri(pVer,0,1,3);
	pFace[1].Tri(pVer,3,1,2);
	pFace[2].Tri(pVer,5,0,4);
	pFace[3].Tri(pVer,1,0,5);
	pFace[4].Tri(pVer,5,6,1);
	pFace[5].Tri(pVer,6,2,1);
	pFace[6].Tri(pVer,6,3,2);
	pFace[7].Tri(pVer,6,7,3);
	pFace[8].Tri(pVer,7,0,3);
	pFace[9].Tri(pVer,7,4,0);
	pFace[10].Tri(pVer,7,5,4);
	pFace[11].Tri(pVer,7,6,5);

	FindGourad();
}

void vwO::DrawNormal()
{
	for (int i=0;i<nFace;i++)
	{
		vwPolygon *p	= &pFace[i];
		glBegin(GL_TRIANGLES);
		
		dhVector n = (*p->v[2]-*p->v[1])*(*p->v[0]-*p->v[1]);
		n	= n.Unit();
		n	= n*-1;
		glNormal3f(n.x,n.y,n.z);
		{
			glVertex3d(p->v[0]->x,p->v[0]->y,p->v[0]->z);
			glVertex3d(p->v[1]->x,p->v[1]->y,p->v[1]->z);
			glVertex3d(p->v[2]->x,p->v[2]->y,p->v[2]->z);	
		}
		glEnd();
	}
}
void vwO::Draw(BOOL bDispAxis)
{
	glPushMatrix();
	glMultMatrixf(H1.v);

	DrawObject(bDispAxis);
//	for (int i=0;i<m_child.GetSize();i++)
//		m_child[i]->Draw(bDispAxis);


	glPopMatrix();

}

void vwO::DrawObject(BOOL bDispAxis)
{
	glEnable(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D,m_tx.nTexID);
	//Dbg("%d", m_tx.nTexID);
	

	for (int i=0;i<nFace;i++)
	{
		vwPolygon *p	= &pFace[i];

		int a,b,c;
		a	= p->v[0]-pVer;
		b	= p->v[1]-pVer;
		c	= p->v[2]-pVer;

		glBegin(GL_TRIANGLES);
		{
			if (pNormal)
			{
				glNormal3f(pNormal[c].x,pNormal[c].y,pNormal[c].z);
				glVertex3d(p->v[2]->x,p->v[2]->y,p->v[2]->z);

				
				glNormal3f(pNormal[b].x,pNormal[b].y,pNormal[b].z);
				glVertex3d(p->v[1]->x,p->v[1]->y,p->v[1]->z);

				glNormal3f(pNormal[a].x,pNormal[a].y,pNormal[a].z);
				glVertex3d(p->v[0]->x,p->v[0]->y,p->v[0]->z);

				/*
				glNormal3f(pNormal[c].x,pNormal[c].y,pNormal[c].z);
				glVertex3d(p->v[2]->x,p->v[2]->y,p->v[2]->z);

				
				glNormal3f(pNormal[b].x,pNormal[b].y,pNormal[b].z);
				glVertex3d(p->v[1]->x,p->v[1]->y,p->v[1]->z);

				glNormal3f(pNormal[a].x,pNormal[a].y,pNormal[a].z);
				glVertex3d(p->v[0]->x,p->v[0]->y,p->v[0]->z);

  */
				/*
				glNormal3f(pNormal[a].x,pNormal[a].y,pNormal[a].z);

				//glTexCoord2f( pUV[2*a],pUV[2*a+1]);
				glVertex3d(pVer[a].x,pVer[a].y,pVer[a].z);
				//glVertex3d(p->v[0]->x,p->v[0]->y,p->v[0]->z);

				glNormal3f(pNormal[b].x,pNormal[b].y,pNormal[b].z);
				//glTexCoord2f( pUV[2*b],pUV[2*b+1]);
				glVertex3d(pVer[b].x,pVer[b].y,pVer[b].z);
				//glVertex3d(p->v[1]->x,p->v[1]->y,p->v[1]->z);
				
				glNormal3f(pNormal[c].x,pNormal[c].y,pNormal[c].z);
				//glTexCoord2f( pUV[2*c],pUV[2*c+1]);
				glVertex3d(pVer[c].x,pVer[c].y,pVer[c].z);
				//glVertex3d(p->v[2]->x,p->v[2]->y,p->v[2]->z);
				*/
			}
			else
			{
				glVertex3d(p->v[0]->x,p->v[0]->y,p->v[0]->z);
				glVertex3d(p->v[1]->x,p->v[1]->y,p->v[1]->z);
				glVertex3d(p->v[2]->x,p->v[2]->y,p->v[2]->z);	
			}
		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);


	if(bDispAxis)
		DisplayOrigin();

}
void vwO::FindGourad()
{
	int *pIndex	= new int[nVer];
	memset(pIndex,0,sizeof(int)*nVer);
	pNormal	= new dhVector[nVer];
	memset(pNormal,0,sizeof(dhVector)*nVer);

	int i;
	for (i=0;i<nFace;i++)
	{
		vwPolygon *p = &pFace[i];

		dhVector n = (*p->v[2]-*p->v[1])*(*p->v[0]-*p->v[1]);
		n	= n.Unit();
		n	= n*-1;

		int a,b,c;
		a	= p->v[0]-pVer;
		b	= p->v[1]-pVer;
		c	= p->v[2]-pVer;

		pNormal[a]	= pNormal[a] + n;
		pIndex[a]	= pIndex[a]+1;
		pNormal[b]	= pNormal[b] + n;
		pIndex[b]	= pIndex[b]+1;
		pNormal[c]	= pNormal[c] + n;
		pIndex[c]	= pIndex[c]+1;
	}

	for (i=0;i<nVer;i++)
	{
		if ( pIndex[i]==0)	continue;
		float f	= 1./pIndex[i];
		pNormal[i]	= pNormal[i]*f;
		pNormal[i]	= pNormal[i].Unit();
	}

	delete pIndex;
}


void vwO::DisplayOrigin()
{

	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR,currentColor);

	glPushMatrix();
	//glMultMatrixf(H1.v);

	glDisable(GL_LIGHTING);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(1.0f, 0.0f, 0.0f); // ending point of the line
	glEnd();

	glColor3f(0,1,0);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 1.0f, 0.0f); // ending point of the line
	glEnd( );

	glColor3f(0,0,1);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
	glVertex3f(0.0f, 0.0f, 1.0f); // ending point of the line
	glEnd( );
	glColor3f(1,1,1);

	glEnable(GL_LIGHTING);


	glPopMatrix();
	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
}



dhVector vwO::GetSurfaceNormalMV(int nFaceID, dhVector vw_o, dhVector vw_r)
{

	if(nFaceID<0 || nFaceID >=nFace) return dhVector(0,0,0);
	vwPolygon *pF = &pFace[nFaceID];

	int a,b,c;
	a	= pF->v[0]- pVer;
	b	= pF->v[1]- pVer;
	c	= pF->v[2]- pVer;


	dhVector v[3];

	dhMat T;
	T	= vw_o*-1;
	dhMat R,tmp;
	R	= tmp.RotX(RAD(vw_r.x))*tmp.RotY(RAD(vw_r.y));

	v[0]	= T*R*H1 *pVer[a];
	v[1]	= T*R*H1 *pVer[b];
	v[2]	= T*R*H1 *pVer[c];
				
	dhVector n_transformed = (v[2]-v[1])*(v[0]-v[1]);
	return n_transformed.Unit();
}



dhVector vwO::GetANormalAbs(int faceID)
{
	if(faceID<0 || faceID >=nFace) return dhVector(0,0,0);


	vwPolygon *p	= &pFace[faceID];

	int a,b,c;
	a	= p->v[0]-pVer;
	b	= p->v[1]-pVer;
	c	= p->v[2]-pVer;
	
	dhVector n = (*p->v[2]-*p->v[1])*(*p->v[0]-*p->v[1]);

	//n	= H*n;
	n	= n.Unit();
	

	return n;

}


void vwO::GetTriangleVertices(int faceID, dhVector* pV, BOOL bApplyModelView )
{

	if(faceID<0 || faceID >=nFace) return;


	vwPolygon *p	= &pFace[faceID];

	//pV =  *p->v;
	dhVector p_rtn[3];

	p_rtn[0] = *p->v[0];
	p_rtn[1] = *p->v[1];
	p_rtn[2] = *p->v[2];

	if(bApplyModelView)
	{

		dhVector vw_o = pGL->pCamera->vw.o;
		dhVector vw_r = pGL->pCamera->vw.r;

		dhMat T;
		T	= vw_o*-1;
		dhMat R,tmp;
		R	= tmp.RotX(RAD(vw_r.x))*tmp.RotY(RAD(vw_r.y));

		p_rtn[0]	= T*R*p_rtn[0];
		p_rtn[1]	= T*R*p_rtn[1];
		p_rtn[2]	= T*R*p_rtn[2];

	}

	pV[0] = p_rtn[0];
	pV[1] = p_rtn[1];
	pV[2] = p_rtn[2];

}



// For normal normal display (MODE 1, 2), Mode 3 Also 
dhVector vwO::DrawASurfaceNormal(int faceID, float scale, float *pArea, BOOL stickToMouse)
{
	
	if(faceID<0 || faceID >=nFace) return dhVector(-1,-1,-1);
	glDisable(GL_LIGHTING);

	dhVector n = GetANormalAbs(faceID);

	n	= n*scale;

	dhVector tr[3];
	GetTriangleVertices(faceID, tr); //____

	if(stickToMouse)
	{
		// Barycentric coordnate !!!
		//float *pArea = //((CGL*) pWorld)->g_area;
		
		dhVector p_weighted;
		p_weighted = tr[0].Scaling(pArea[0]) + tr[1].Scaling(pArea[1]) + tr[2].Scaling(pArea[2]);
		n = p_weighted + n;

		DrawLineWithArrow3D(p_weighted, n, TRUE, 0,0.3);

	}

	else
	{
		dhVector triangle_o	= tr[0]+tr[1]+tr[2];
		triangle_o = triangle_o/3.0;

		n = triangle_o + n;

		DrawLineWithArrow3D(triangle_o, n, TRUE, 0,0.3);

	}

	glEnable(GL_LIGHTING);

	return n;
}


void vwO::DrawLineWithArrow3D(dhVector stPt_gl, dhVector endPt_gl, BOOL arrowAtTheEnd, float z_offset,  float scale_arrow)
{

	z_offset = 0;
	//glPushMatrix();
	//glMultMatrixf(H.v);

	dhVector vw_o = pGL->pCamera->vw.o;
	dhVector vw_r = pGL->pCamera->vw.r;

	dhMat T;
	T	= vw_o*-1;
	dhMat R,tmp;
	R	= tmp.RotX(RAD(vw_r.x))*tmp.RotY(RAD(vw_r.y));

	stPt_gl		= H1*stPt_gl;
	endPt_gl	= H1*endPt_gl;

	glBegin(GL_LINES);
		glVertex3f(stPt_gl.x, stPt_gl.y, stPt_gl.z + z_offset);	//p
		glVertex3f(endPt_gl.x, endPt_gl.y, endPt_gl.z + z_offset);								//q
	glEnd();



	//glPopMatrix();

	dhVector stPt_gdi, endPt_gdi;

	
	// Considering the vertex rotation
	stPt_gl		= stPt_gl;
	endPt_gl	= endPt_gl;

	
	stPt_gdi	= pGL->pCamera->Projection2(stPt_gl);
	endPt_gdi	= pGL->pCamera->Projection2(endPt_gl);

	
	double angle; 
	angle		= atan2( (double) stPt_gdi.y - endPt_gdi.y, (double) stPt_gdi.x - endPt_gdi.x );

	double hypotenuse; 
	hypotenuse = sqrt( square(stPt_gdi.y - endPt_gdi.y) + square(stPt_gdi.x - endPt_gdi.x) );


	dhVector pt_arrow_gdi[2], pt_arrow_gl[2];
	
	
	if(arrowAtTheEnd)
	{
		pt_arrow_gdi[0].x = (endPt_gdi.x + scale_arrow *hypotenuse* cos(angle + PI / 4.0));
		pt_arrow_gdi[0].y = (endPt_gdi.y + scale_arrow *hypotenuse* sin(angle + PI / 4.0));

		pt_arrow_gdi[1].x = (endPt_gdi.x + scale_arrow *hypotenuse* cos(angle - PI / 4.0));
		pt_arrow_gdi[1].y = (endPt_gdi.y + scale_arrow *hypotenuse* sin(angle - PI / 4.0));

	}
	else
	{
		pt_arrow_gdi[0].x = (endPt_gdi.x - scale_arrow *hypotenuse* cos(angle + PI / 4.0));
		pt_arrow_gdi[0].y = (endPt_gdi.y - scale_arrow *hypotenuse* sin(angle + PI / 4.0));

		pt_arrow_gdi[1].x = (endPt_gdi.x - scale_arrow *hypotenuse* cos(angle - PI / 4.0));
		pt_arrow_gdi[1].y = (endPt_gdi.y - scale_arrow *hypotenuse* sin(angle - PI / 4.0));

	}


	pGL->pCamera->UnProjection(pt_arrow_gdi[0], &pt_arrow_gl[0]);
	pGL->pCamera->UnProjection(pt_arrow_gdi[1], &pt_arrow_gl[1]);


	//pt_arrow_gl[0].z = endPt_gl.z;
	//pt_arrow_gl[1].z = endPt_gl.z;


	glBegin(GL_LINES);
		glVertex3f(endPt_gl.x, endPt_gl.y, endPt_gl.z + z_offset);	//p
		glVertex3f(pt_arrow_gl[0].x, pt_arrow_gl[0].y, pt_arrow_gl[0].z + z_offset);								//q
	glEnd();

	
	glBegin(GL_LINES);
		glVertex3f(endPt_gl.x, endPt_gl.y, endPt_gl.z +z_offset);	//p
		glVertex3f(pt_arrow_gl[1].x, pt_arrow_gl[1].y, pt_arrow_gl[1].z +z_offset);								//q
	glEnd();

	//glPopMatrix();


}


//Highlight
void vwO::DrawTriangle(int faceID, float offset_scaling)
{
	if(faceID<0) return;

	vwPolygon *p	= &pFace[faceID];

	//dhVector sn = GetANormalAbs(faceID);

	dhVector sn_tr = GetSurfaceNormalMV(faceID,pGL->pCamera->vw.o, pGL->pCamera->vw.r);


	dhVector p0 =H1**p->v[0] + sn_tr.Scaling(offset_scaling);
	dhVector p1 =H1**p->v[1] + sn_tr.Scaling(offset_scaling);
	dhVector p2 =H1**p->v[2] + sn_tr.Scaling(offset_scaling);

	//glDisable(GL_LIGHTING);


	//glColor4f(1,0,1,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	

	glBegin(GL_TRIANGLES);
		glVertex3f(p0.x, p0.y, p0.z);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);

	glEnd();

	//glPolygonMode(GL_FRONT,GL_FILL);//((CGL*) pWorld)->view_mode
	//glEnable(GL_LIGHTING);

}


//Highlight
void vwO::DrawTriangleLine(int faceID)
{
	if(faceID<0) return;

	vwPolygon *p	= &pFace[faceID];

	//dhVector sn = GetANormalAbs(faceID);


	dhVector p0 =H1**p->v[0];
	dhVector p1 =H1**p->v[1];
	dhVector p2 =H1**p->v[2];

	//glDisable(GL_LIGHTING);


	//glColor4f(1,0,1,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	

	glDisable(GL_LIGHTING);
	glColor3f(1,0,0);
	
	glLineWidth(2);

	glBegin(GL_LINES);
		glVertex3f(p0.x, p0.y, p0.z);	//p
		glVertex3f(p1.x, p1.y, p1.z);								//q
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(p1.x, p1.y, p1.z);								//q
		glVertex3f(p2.x, p2.y, p2.z);

	glEnd();

	glBegin(GL_LINES);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p0.x, p0.y, p0.z);	//p
								//q
	glEnd();


	glEnable(GL_LIGHTING);
	glLineWidth(1);

	//glPolygonMode(GL_FRONT,GL_FILL);//((CGL*) pWorld)->view_mode
	//glEnable(GL_LIGHTING);

}
