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

	//增加等待乘客
	bool addPeople(People people);
	//去除等待乘客
	bool subPeople(People people);
	//去除在第n楼等待的乘客（n:0-21）
	bool subPeople(int n);

	//上客
	bool inPeople(People people);
	//上客,n为楼层
	bool inPeople(int n);
	//上客,id为乘客的id
	bool inOnePeople(int id);

	//下客
	bool offOnePeople(int id);
	//下客,n为楼层（n:0-21）
	bool offPeople(int n);
	//移动
	void move();
	void up(int height);
	void down(int height);
	void open();
	void close();
	void keep();
	void stop();
	//计算最低最高要到达的楼层
	void updateHigh_Low();

	//更新floor_wait_flag,floor_arrive_flag
	void updateFlag();

	//每个等待乘客的等待时间+1
	void waittime_inc();
	//计算平均等待时间
	void cal_aveWaitTime();

	//运行即测试运行
	float runToEnd();
	float runToEnd(People);//运行结束
	float testRun();//测试运行
	float testRun(People);
	void runSingleStep();


	int status;//状态(上下开关停)
	int nextstatus;//下一秒状态(上下开关停)
	int lastdir;//上一次的运行方向
	
	People *peoplesin;//电梯内的人
	People *peoplesout;//电梯外的人
	int p_innum;//内人数(0-15)
	int p_outnum;//外人数(0-30)

	int floor;//当前楼层(1-22)
	bool floor_wait_flag[22];//每层是否有等待乘客
	bool floor_arrive_flag[22];//每层是否有人下

	int highfloor;//当前要到达的最高楼层(1-22)
	int lowfloor;//当前要到达的最低楼层(1-22)

	//统计分析数据
	int time;//电梯起止运行时间(步数)
	int cost;//能耗，UP/DOWN为1，COLSE为10
	
	int people_hadin;//乘过电梯的人
	int total_waittime;//所有乘客的总等待时间
	float averagetime;//每个乘客的平均等待时间
	
	
	//电梯在图中的区域
	CRect rect;
};

#endif // !defined(AFX_ELEVATOR_H__2EBD262D_2469_4FFD_A96D_D897F04692DD__INCLUDED_)
