// Elevator.h: interface for the Elevator class.
//
//////////////////////////////////////////////////////////////////////

#include "People.h"

#if !defined(AFX_ELEVATOR_H__2EBD262D_2469_4FFD_A96D_D897F04692DD__INCLUDED_)
#define AFX_ELEVATOR_H__2EBD262D_2469_4FFD_A96D_D897F04692DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Elevator
{
public:
	Elevator();
	virtual ~Elevator();
	void init();

	//���ӵȴ��˿�
	bool addPeople(People people);
	//ȥ���ȴ��˿�
	bool subPeople(People people);
	//ȥ���ڵ�n¥�ȴ��ĳ˿ͣ�n:0-21��
	bool subPeople(int n);

	//�Ͽ�
	bool inPeople(People people);
	//�Ͽ�,nΪ¥��
	bool inPeople(int n);
	//�Ͽ�,idΪ�˿͵�id
	bool inOnePeople(int id);

	//�¿�
	bool offOnePeople(int id);
	//�¿�,nΪ¥�㣨n:0-21��
	bool offPeople(int n);
	//�ƶ�
	void move();
	void up(int height);
	void down(int height);
	void open();
	void close();
	void keep();
	void stop();
	//����������Ҫ�����¥��
	void updateHigh_Low();

	//����floor_wait_flag,floor_arrive_flag
	void updateFlag();

	//ÿ���ȴ��˿͵ĵȴ�ʱ��+1
	void waittime_inc();
	//����ƽ���ȴ�ʱ��
	void cal_aveWaitTime();

	//���м���������
	float runToEnd();
	float runToEnd(People);//���н���
	float testRun();//��������
	float testRun(People);
	void runSingleStep();


	int status;//״̬(���¿���ͣ)
	int nextstatus;//��һ��״̬(���¿���ͣ)
	int lastdir;//��һ�ε����з���
	
	People *peoplesin;//�����ڵ���
	People *peoplesout;//���������
	int p_innum;//������(0-15)
	int p_outnum;//������(0-30)

	int floor;//��ǰ¥��(1-22)
	bool floor_wait_flag[22];//ÿ���Ƿ��еȴ��˿�
	bool floor_arrive_flag[22];//ÿ���Ƿ�������

	int highfloor;//��ǰҪ��������¥��(1-22)
	int lowfloor;//��ǰҪ��������¥��(1-22)

	//ͳ�Ʒ�������
	int time;//������ֹ����ʱ��(����)
	int cost;//�ܺģ�UP/DOWNΪ1��COLSEΪ10
	
	int people_hadin;//�˹����ݵ���
	int total_waittime;//���г˿͵��ܵȴ�ʱ��
	float averagetime;//ÿ���˿͵�ƽ���ȴ�ʱ��
	
	
	//������ͼ�е�����
	CRect rect;
};

#endif // !defined(AFX_ELEVATOR_H__2EBD262D_2469_4FFD_A96D_D897F04692DD__INCLUDED_)
