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
	
	int id;//����id
	int status;//״̬ ��/��
	int startfloor;//��ʼ¥��(1-22)
	int endfloor;//Ŀ��¥��(1-22)
	int waittime;//�ȴ�ʱ��
	int elenum;//���ڵ���
};

#endif // !defined(AFX_PEOPLE_H__07DB2A11_0AF6_4297_9A49_35724083423C__INCLUDED_)
