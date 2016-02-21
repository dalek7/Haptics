#include "StdAfx.h"
#include "ddGL.h"

vwLight::vwLight(void)
{
}

vwLight::~vwLight(void)
{
}





void vwLight::InitTextureParams()
{
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);		
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glEnable(GL_ALPHA_TEST);
		//glAlphaFunc(GL_GREATER ,0.01);//0.01,

	//glCullFace(GL_FRONT);								// Set Culling Face To Back Face : GL_BACK
	glEnable(GL_CULL_FACE);								// Enable Culling


}


void vwLight::SetDefaultMaterial()
{
	glEnable(GL_BLEND); 
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//

	glFrontFace( GL_CW );

	GLfloat	ambientProperties[]  = {0.1f, 0.1f, 0.1f, 1.0f};//{1.0f, 1.0f, 1.0f, 1.0f};//
	GLfloat	diffuseProperties[]  = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat	specularProperties[] = {0.1f, 0.1f, 0.1f, 1.0f};
	
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);
//	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuseProperties);
	glEnable( GL_COLOR_MATERIAL );

}

