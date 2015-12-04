// People.cpp: implementation of the People class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ElevatorGif.h"
#include "People.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int INELE=3;
const int OUTELE=-3;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

People::People()
{
	this->id=0;
	this->status=OUTELE;
	this->startfloor=1;
	this->endfloor=1;
	this->waittime=0;
	this->elenum=0;
}

People::~People()
{
	
}
