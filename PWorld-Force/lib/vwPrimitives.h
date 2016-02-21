#pragma once



inline void DrawGrid(float size, float step)
{
    // disable lighting
    glDisable(GL_LIGHTING);

	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR,currentColor);

    glBegin(GL_LINES);

	
    glColor3f(0.3f, 0.3f, 0.3f);
    for(float i=step; i <= size; i+= step)
    {
        glVertex3f(-size, 0,  i);   // lines parallel to X-axis
        glVertex3f( size, 0,  i);
        glVertex3f(-size, 0, -i);   // lines parallel to X-axis
        glVertex3f( size, 0, -i);

        glVertex3f( i, 0, -size);   // lines parallel to Z-axis
        glVertex3f( i, 0,  size);
        glVertex3f(-i, 0, -size);   // lines parallel to Z-axis
        glVertex3f(-i, 0,  size);
    }

    // x-axis
    glColor3f(0.5f, 0, 0);
    glVertex3f(-size, 0, 0);
    glVertex3f( size, 0, 0);

    // z-axis
    glColor3f(0,0,0.5f);
    glVertex3f(0, 0, -size);
    glVertex3f(0, 0,  size);

    glEnd();

	glColor4f(currentColor[0], currentColor[1], currentColor[2], currentColor[3]);
    // enable lighting back
    glEnable(GL_LIGHTING);
}


inline void DrawTorusPartial(GLfloat TubeRadius, GLfloat Radius, GLint Sides, GLint Rings, float fraction=1.0)
{
	GLfloat theta, phi, theta1;
	GLfloat cosTheta, sinTheta;
	GLfloat cosTheta1, sinTheta1;
	GLfloat ringDelta, sideDelta;
	GLfloat cosPhi, sinPhi, dist;

	sideDelta = 2.0f * PI / Sides;
	ringDelta = 2.0f * PI / Rings;
	theta1 = 0.0f;
	cosTheta = 1.0f;
	sinTheta = 0.0f;
	
	//TorusDL = glGenLists(1);
	//glNewList(TorusDL, GL_COMPILE);

	
	for ( int i = Rings; i >= Rings*(1-fraction); i-- ) {
		theta1 += ringDelta;
		cosTheta1 = cos(theta1);
		sinTheta1 = sin(theta1);
		glBegin(GL_QUAD_STRIP);
		phi = 0.0;
		for (int j = Sides; j >= 0; j-- ) {
			phi += sideDelta;
			cosPhi = cos(phi);
			sinPhi = sin(phi);
			dist = Radius + (TubeRadius * cosPhi);

			glNormal3f(cosTheta1 * cosPhi, -sinTheta1 * cosPhi, sinPhi);
			glVertex3f(cosTheta1 * dist, -sinTheta1 * dist, TubeRadius * sinPhi);

			glNormal3f(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi);
			glVertex3f(cosTheta * dist, -sinTheta * dist, TubeRadius * sinPhi);
		}
		glEnd();
		theta = theta1;
		cosTheta = cosTheta1;
		sinTheta = sinTheta1;
	}


	//glEndList();
}


inline void DrawTorus(float innerRadius, float outerRadius)
{

    GLint nsides; 
	GLint rings;

	//innerRadius = 0.3;
	//outerRadius = 0.8;
	nsides = 32;
	rings = 32;

	glutSolidTorus(innerRadius,outerRadius,nsides,rings);

}




inline void DrawSphere(float r)
{
	
	glutSolidSphere(r, 32, 32);
	//glutWireSphere(0.5, 32, 32);
}



/*
	glPushMatrix();
	glTranslatef(0,0,-3);
	glBegin(GL_POLYGON);
	glVertex3f(0.25,0.25,0);
	glVertex3f(0.75,0.25,0);
	glVertex3f(0.25,0.75,0);
	glVertex3f(0.25,0.75,0);
	glEnd();
	glPopMatrix();
*/
