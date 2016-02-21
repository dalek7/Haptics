#pragma once



typedef struct __view
{
	float	n,f;
	float	angle;
	float	fAR;	// aspect ratio.
	float	w,h;
	
	dhVector	o;	// camera position == eye
	dhVector	r;	// rotation



} VIEW;

class vwCamera
{
public:
	vwCamera(void);
	~vwCamera(void);

	void InitCam();

public:
	void ApplyProjectionTransform();
	void ApplyOrtho();
	void SetCamera(int, int);

	void CopyMatrices();
	void CopyMatricesd(double *mm_,double *pm_, int* vp_ );


	GLdouble*	GetMM();
	GLdouble*	GetPM();
	int*	GetVP();


	//Projection
	
	dhVector Projection2(dhVector v);
	void UnProjection(dhVector, dhVector* output);

	BOOL MouseMove(int nFlags,CPoint pt);

public:
	VIEW	vw;

protected:
	GLdouble	mm[16];
	GLdouble	pm[16];
	int			vp[4];
	dhMat		mat_mm, mat_pm;

protected:
	CPoint	ptMouseOld;





};