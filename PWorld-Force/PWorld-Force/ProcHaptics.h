#ifndef __DD_HAPTICS__
#define __DD_HAPTICS__

#define CURSOR_SIZE_PIXELS 20

#include <HL/hl.h>
#include <HDU/hduMatrix.h>
#include <HDU/hduError.h>

#include <HLU/hlu.h>

#pragma comment(lib, "hd.lib")
#pragma comment(lib, "hdud.lib")
#pragma comment(lib, "hl.lib")
#pragma comment(lib, "hlud.lib")

#include "../lib/vArray.h"
#include "../lib/Elapsed.h"
#include "../lib/ExpUtil.h"



#define MAX_INPUT_DOF   6   
#define MAX_OUTPUT_DOF  6

typedef struct
{
    HDlong encoder_values[MAX_INPUT_DOF];
    HDlong motor_dac_values[MAX_OUTPUT_DOF];   
    hduVector3Dd position;
	hduVector3Dd velocity;
	hduVector3Dd force;

} DeviceStateStruct;



typedef struct ___DevState
{
	float t;
	float position[3];			// QEIDirectionGet
	//float vel[3];			// QEIPositionGet
	//float motor_dac_values[3];
	float force[3];
	CPoint cursor;
	
} DevState;



enum {X=0, Y, Z};

class ProcHaptics
{
	public: 
		ProcHaptics();
		~ProcHaptics();

		BOOL		bInit;
		BOOL		bPlay;
		BOOL		bTakingRest;

		void	TakeRest(BOOL bRest = TRUE);
		void	ToggleTakingRest();


	public: 
		
		HDint nCurBtn;
		HDint nLastBtn;

		HHD			InitPhantom();
		void		ClosePhantom(HHD hHD);


		CElapsed	m_tm;


		void initHL();
	// Trajectory
	public:
		vArray <DevState,DevState> traj_dev;
		void GetPosDevice();
		int	SaveDevTraj();

		CString loc;
		double gPos[3];
		double gForce[3];



	void GetPosition(double* pos);
	void GetDevicePosition(double* pos); 
	void GetForce(double *force);



	/* Haptic device and rendering context handles. */
	 HHD ghHD;
	 HHLRC ghHLRC;

	/* Shape id for shape we will render haptically. */
	HLuint gSphereShapeId;

	 double gCursorScale;
	 int gCursorDisplayList;

		

};





#endif