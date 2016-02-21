#include "stdafx.h"
#include "ProcHaptics.h"



ProcHaptics::ProcHaptics()
{

	nCurBtn		= 0;
	nLastBtn	= 0;


	bTakingRest		= TRUE;
	bInit			= FALSE;
	loc			= "";

	gPos[0] = 0;
	gPos[1] = 0;
	gPos[2] = 0;

	gForce[0] = 0;
	gForce[1] = 0;
	gForce[2] = 0;
		
	/* Haptic device and rendering context handles. */
	ghHD = HD_INVALID_HANDLE;
	ghHLRC = 0;

	
	gCursorDisplayList = 0;

}

ProcHaptics::~ProcHaptics()
{

}


void ProcHaptics::initHL()
{
    HDErrorInfo error;

    ghHD = hdInitDevice(HD_DEFAULT_DEVICE);
    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        hduPrintError(stderr, &error, "Failed to initialize haptic device");
        AfxMessageBox("Failed to initialize haptic device !!!");
        return;
    }
    
    ghHLRC = hlCreateContext(ghHD);
    hlMakeCurrent(ghHLRC);

    // Enable optimization of the viewing parameters when rendering
    // geometry for OpenHaptics.
    hlEnable(HL_HAPTIC_CAMERA_VIEW);

    // Generate id's for the three shapes.
    gSphereShapeId = hlGenShapes(1);

    hlTouchableFace(HL_FRONT_AND_BACK);


	bInit = TRUE;
}



void ProcHaptics::ToggleTakingRest()
{

	bTakingRest ^= 1;
	
	if(bTakingRest)
	{
		SaveDevTraj();
	}
}

void ProcHaptics::TakeRest(BOOL bRest)
{
	bTakingRest = bRest;

}

void ProcHaptics::GetPosDevice()
{
	
	double pos[3]; double f[3];
	GetPosition(pos);
	GetForce(f);

	//GetDevicePosition(pos);

	DevState dev;
	dev.t = m_tm.End();

	for(int i=0; i<3; i++)
	{
		
		//dev.motor_dac_values[i] = state.force[i];//motor_dac_values
		dev.position[i]			= pos[i];
		dev.force[i]			= f[i];

		gPos[i]					= pos[i];
		gForce[i]				= f[i];
		//dev.vel[i]				= state.velocity[i];
	}

	if(!bTakingRest)
	traj_dev.Add(dev);
}

void ProcHaptics::GetForce(double *force)
{
//	hlGetDoublev(HD_CURRENT_FORCE, force);


  // add the resulting force and torque to the rendered force.
  //HDdouble force[3];
  hdGetDoublev( HD_CURRENT_FORCE, force );


}

void ProcHaptics::GetPosition(double* pos) 
{
     hlGetDoublev(HL_PROXY_POSITION, pos);

	 /*
 	hlBeginFrame();

    hlDisable(HL_PROXY_RESOLUTION);
    hlProxydv(HL_PROXY_POSITION, startPos);

    hlEndFrame();
	*/
}

//////////////////////////////////////////////////////////////////////

void ProcHaptics::GetDevicePosition(double* pos) 
{
     hlGetDoublev(HL_DEVICE_POSITION, pos);
	
}





int	ProcHaptics::SaveDevTraj()
{

	int n  = traj_dev.GetSize();
	if(n==0) 
	{
		Dbg("Skipping saving....");
		return 0;
	}

	if(loc.Compare("")==0)
	{
		loc = ExpUtil::CreateFolder("output1");
	}

	CString fname, tmp;

	ExpUtil::MakeFileNameWithDateTime(&tmp);
	fname.Format("%straj_%s.txt", loc, tmp);
	
	FILE *fp;
	fp=fopen(fname,"w+");

	int i;
	fprintf(fp,"%cTime\tCUR\tCUR\tPOS\tPOS\tPOS\tvel\tvel\tvel\tMotor\tMotor\tMotor\n",37);
	for(i=0; i<n; i++)
	{
		fprintf(fp,"%.3f\t %.3f\t%.3f\t%.3f\t %.3f\t%.3f\t%.3f\n", 
				traj_dev.GetAt(i).t-traj_dev.GetAt(0).t, 
				traj_dev.GetAt(i).position[0], traj_dev.GetAt(i).position[1], traj_dev.GetAt(i).position[2] ,
				traj_dev.GetAt(i).force[0], traj_dev.GetAt(i).force[1], traj_dev.GetAt(i).force[2] 
			);
		
	}

	fclose(fp);
	Dbg("SAVED TRAJ : "+fname);

	traj_dev.RemoveAll();
	return n;

}