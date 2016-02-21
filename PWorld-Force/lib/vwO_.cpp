#include "stdafx.h"
#include "vwO.h"

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
}

vwO::~vwO()
{
	Close();
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

void vwO::MakeBox(float a,float b,float c)
{
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
	pFace[0].Tri(pVer,1,3,0);
	pFace[1].Tri(pVer,1,2,3);
	pFace[2].Tri(pVer,0,4,5);
	pFace[3].Tri(pVer,0,5,1);
	pFace[4].Tri(pVer,1,5,6);
	pFace[5].Tri(pVer,1,6,2);
	pFace[6].Tri(pVer,2,6,3);
	pFace[7].Tri(pVer,3,6,7);
	pFace[8].Tri(pVer,3,7,0);
	pFace[9].Tri(pVer,0,7,4);
	pFace[10].Tri(pVer,4,7,5);
	pFace[11].Tri(pVer,5,7,6);

	FindGourad();
}

void vwO::MakePlane(float a,float b,int m,int n)
{
	Init( (m+1)*(n+1),2*m*n);

	float dx,dy;
	dx	= a/((float)m);
	dy	= b/((float)n);

	int i,j;
	for (j=0;j<=n;j++)
	for (i=0;i<=m;i++)
		pVer[(m+1)*j+i]	= dhVector(dx*i,dy*j,0);

	int np = 0;
	for (j=0;j<n;j++)
	for (i=0;i<m;i++)
	{
		int idx	= (m+1)*j+i;
		pFace[np++].Tri(pVer,idx,idx+1,idx+m+1);
		pFace[np++].Tri(pVer,idx+m+1,idx+1,idx+m+2);
	}

	FindGourad();
}


void vwO::Draw(BOOL bDispAxis)
{
	glPushMatrix();
	//glMultMatrixf(H1.v);

	DrawObject(bDispAxis);
//	for (int i=0;i<m_child.GetSize();i++)
//		m_child[i]->Draw(bDispAxis);


	glPopMatrix();

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

void vwO::DrawObject(BOOL bDispAxis)
{
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

	if(bDispAxis)
		DisplayOrigin();
}

void vwO::FindGourad()
{
	if ( pNormal)	delete []pNormal;
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
