/*
 *  ddmath.h
 *  WorldTest
 *
 *  Created by Darcy1214 on 6/28/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DD_MATH_H
#define DD_MATH_H
#include <math.h>

typedef unsigned int uint32;
typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;

typedef float float32;

/// "Next Largest Power of 2
/// Given a binary integer value x, the next largest power of 2 can be computed by a SWAR algorithm
/// that recursively "folds" the upper bits into the lower bits. This process yields a bit vector with
/// the same most significant 1 as x, but all 1's below it. Adding 1 to that value yields the next
/// largest power of 2. For a 32-bit value:"


inline double square(double x)
{
	return x*x;
}

inline bool ddIsPowerOfTwo(uint32 x)
{
	bool result = x > 0 && (x & (x - 1)) == 0;
	return result;
}


inline uint32 ddNextPowerOfTwo(uint32 x)
{
	if(!ddIsPowerOfTwo(x))
	{
	   x |= (x >> 1);
	   x |= (x >> 2);
	   x |= (x >> 4);
	   x |= (x >> 8);
	   x |= (x >> 16);
		return x + 1;
	}
	else {
		return x;
	}

	   
}

//C:\Users\kimsc\Documents\MATLAB\ETNA_128_2_185_149\imagework\stest.m
//float alpha = sigmoid(20.0, sn_tr.z, 0);
inline double sigmoid(float slope, float x, float center)
{


	return 1.0 / (1.0 + exp(slope*(-x + center)));
	
}


inline void minmax2(float v1, float v2, float v3, float *min, float *max, int *minID, int *maxID)
{
	if (v1 > v2)
	{
		if (v1 > v3)
			*max = v1;
		else
			*max = v3;

		if (v2 < v3)
			*min = v2;
		else
			*min = v3;
	}
	else
	{
		if (v2 > v3)
			*max = v2;
		else
			*max = v3;

		if (v1 < v3)
			*min = v1;
			else
			*min = v3;
	}


	if(*max == v1)
		*maxID = 0;
	else if (*max == v2)
		*maxID =  1;
	else if (*max == v3)
		*maxID = 2;
	else 
		*maxID = -1;




	if(*min == v1)
		*minID = 0;
	else if (*min == v2)
		*minID =  1;
	else if (*min == v3)
		*minID = 2;
	else 
		*minID = -1;



}


inline int minmax(double v1, double v2, double v3, double *min, double *max)
{
	if (v1 > v2)
	{
		if (v1 > v3)
			*max = v1;
		else
			*max = v3;

		if (v2 < v3)
			*min = v2;
		else
			*min = v3;
	}
	else
	{
		if (v2 > v3)
			*max = v2;
		else
			*max = v3;

		if (v1 < v3)
			*min = v1;
			else
			*min = v3;
	}


	if(*max == v1)
		return 0;
	else if (*max == v2)
		return 1;
	else if (*max == v3)
		return 2;
	else return -1;
	
	
	
	//not all control paths return a value
}






#endif
