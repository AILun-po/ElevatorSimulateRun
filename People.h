// People.h: interface for the People class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PEOPLE_H__07DB2A11_0AF6_4297_9A49_35724083423C__INCLUDED_)
#define AFX_PEOPLE_H__07DB2A11_0AF6_4297_9A49_35724083423C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class People  
{
public:
	People();
	virtual ~People();
	
	int id;//客人id
	int status;//状态 内/外
	int startfloor;//起始楼层(1-22)
	int endfloor;//目的楼层(1-22)
	int waittime;//等待时间
	int elenum;//所在电梯
};

#endif // !defined(AFX_PEOPLE_H__07DB2A11_0AF6_4297_9A49_35724083423C__INCLUDED_)
