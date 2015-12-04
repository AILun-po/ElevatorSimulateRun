// Elevator.cpp: implementation of the Elevator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ElevatorGif.h"
#include "Elevator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//电梯的五种状态
const int UP=1;
const int DOWN=-1;
const int OPEN=2;
const int CLOSE=-2;
const int KEEP=0;
const int STOP=4;

const int INELE=3;
const int OUTELE=-3;

Elevator::Elevator()
{
	this->peoplesin=new People[15];
	this->peoplesout=new People[30];
	this->init();
}

void Elevator::init(){
	//初始化内外人数
	this->p_innum=0;
	this->p_outnum=0;
	
	//初始化楼层及每层楼是否有人等待
	this->floor=1;
	for(int i=0;i<22;i++){
		this->floor_wait_flag[i]=false;
		this->floor_arrive_flag[i]=false;
	}
	
	//初始化电梯状态
	this->status=KEEP;
	this->nextstatus=KEEP;
	this->lastdir=UP;

	//初始化电梯所在区域
	this->rect.SetRect(0,0,1,1);

	//初始化最低和最高要到达的楼层
	this->highfloor=1;
	this->lowfloor=1;

	//初始化起止时间(步数)
	this->time=0;
	//初始化能耗
	this->cost=0;

	this->people_hadin=0;
	this->total_waittime=0;
	this->averagetime=0;
}

Elevator::~Elevator()
{
	if(this->peoplesin){
		delete []peoplesin;
	}
	if(this->peoplesout){
		delete []peoplesout;
	}
}

//增加等待乘客
bool Elevator::addPeople(People pe){
	if(this->p_outnum>=30){
		return false;
	}
	int i=0;
	for(i=0;i<this->p_outnum;i++){
		if(this->peoplesout[i].id==pe.id)
			return false;
	}

	pe.status=OUTELE;
	this->peoplesout[this->p_outnum]=pe;
	this->p_outnum++;

	//更新最高最低要到达的楼层
	this->updateHigh_Low();
	this->updateFlag();
	
	//考虑是否要在此处计算电梯下一秒状态

	return true;	
}

//去除等待乘客
bool Elevator::subPeople(People pe){
	int i=0,index=-1;
	for(i=0;i<this->p_outnum;i++){
		if(this->peoplesout[i].id==pe.id)
			index=i;
		break;
	}
	if(index>=0&&index<=29){
		for(i=index;i<this->p_outnum-1;i++){
			this->peoplesout[i]=this->peoplesout[i+1];
		}
		this->p_outnum = this->p_outnum-1;

		return true;
	}

	return false;
}

//上客
bool Elevator::inPeople(People pe){
	if(this->p_innum>=15){
		return false;
	}
	int i=0;
	for(i=0;i<this->p_innum;i++){
		if(this->peoplesin[i].id==pe.id)
			return false;
	}

	pe.status=INELE;
	this->peoplesin[this->p_innum]=pe;
	this->p_innum++;

	this->people_hadin += 1;
	this->total_waittime += pe.waittime;

	//去除等待乘客
	this->subPeople(pe);
	//更新
	this->updateHigh_Low();
	this->updateFlag();
	
	//考虑是否要在此处计算电梯下一秒状态

	return true;
}

//上客,n为楼层(1-22)
bool Elevator::inPeople(int n){
	bool flag=false;
	if(n==this->floor){
		int i=0;
		People p;
		int dir=0;
		for(i=0;i<this->p_outnum;i++){
			p=this->peoplesout[i];
			dir=p.endfloor>p.startfloor?UP:DOWN;
			if(p.startfloor==n&&(dir==this->lastdir||this->highfloor==this->floor||this->lowfloor==this->floor))
				flag=this->inPeople(p);
		}

		this->updateHigh_Low();
		this->updateFlag();
		//if(flag=false)
			this->floor_wait_flag[n-1]=false;
	}
	return flag;
}

//上客,id为乘客的id
bool Elevator::inOnePeople(int id){
	int i=0;
	bool flag=false;
	People p;
	for(i=0;i<this->p_outnum;i++){
		p=this->peoplesout[i];
		if(p.id==id){
			flag=this->inPeople(p);
		}
	}
	return flag;
}

//下客,id为乘客的序号
bool Elevator::offOnePeople(int n){
	if(n>=0&&n<=14){
		int i=0;
		for(i=n;i<this->p_innum-1;i++){
			this->peoplesin[i]=this->peoplesin[i+1];
		}
		this->p_innum = this->p_innum-1;

		return true;
	}

	return false;
}

//下客，n为楼层
bool Elevator::offPeople(int n){
	if(n==this->floor){
		int i=0;
		People p;
		for(i=0;i<this->p_innum;i++){
			p=this->peoplesin[i];
			if(p.endfloor==n)
				this->offOnePeople(i);
		}
		this->updateHigh_Low();
		this->updateFlag();
	}else{
		return false;
	}

	return true;
}

//移动
void Elevator::move(){

	//根据nextstatus移动电梯
	switch(this->nextstatus){
		case UP:
			this->up(28);
			break;
		case DOWN:
			this->down(28);
			break; 
		case KEEP: 
			this->keep();
			break;
		case OPEN:
			this->open();
			break;
		case CLOSE:
			this->close();
			break;
		case STOP:
			this->stop();
			break;
	}
	this->updateFlag();
	this->updateHigh_Low();


	bool arrive=false,start=false;
	int nowfloor=this->floor;
	int nowstatus=KEEP;
	int nextstatus=KEEP;
	arrive = this->floor_arrive_flag[nowfloor-1];
	start = this->floor_wait_flag[nowfloor-1];

	this->status=this->nextstatus;

	//如果有人到达
	if(arrive){
		switch(this->status){
		case UP:
			this->nextstatus=KEEP;
			//this->lastdir=UP;
			break;
		case DOWN:
			this->nextstatus=KEEP;
			break;
		case KEEP: 
			this->nextstatus=OPEN;
			break;
		case OPEN:
			this->offPeople(nowfloor);
			this->nextstatus=OPEN;
			break;
		case CLOSE:
			this->nextstatus=OPEN;
			break;
		case STOP:
			this->nextstatus=KEEP;
			break;
		}
		return;
	}else if(start){//如果有人要乘坐
		switch(this->status){
		case UP:
			this->nextstatus=KEEP;
			break;
		case DOWN:
			this->nextstatus=KEEP;
			break;
		case KEEP: 
			this->nextstatus=OPEN;
			break;
		case OPEN:
			this->inPeople(nowfloor);
			this->nextstatus=OPEN;
			break;
		case CLOSE:
			this->nextstatus=OPEN;
			break;
		case STOP:
			this->nextstatus=OPEN;
			break;
		}
		return;
	}

	//根据当前状态，计算下一状态
	switch(this->status){
		case UP:
			if(this->highfloor > this->floor){
				this->nextstatus=UP;
			}else if(this->lowfloor<this->floor){
				this->nextstatus=DOWN;
			}else{
				this->nextstatus=KEEP;
			}
			break;
		case DOWN:
			if(this->lowfloor < this->floor){
				this->nextstatus=DOWN;
			}else if(this->highfloor>this->floor){
				this->nextstatus=UP;
			}else{
				this->nextstatus=KEEP;
			}
			break;
		case KEEP: 
			switch(this->lastdir){
				case UP:
					if(this->highfloor > this->floor){
						this->nextstatus=UP;
					}else if(this->lowfloor<this->floor){
						this->nextstatus=DOWN;
					}else{
						this->nextstatus=STOP;
					}
					break;
				case DOWN:
					if(this->lowfloor < this->floor){
						this->nextstatus=DOWN;
					}else if(this->highfloor>this->floor){
						this->nextstatus=UP;
					}else{
						this->nextstatus=KEEP;
						this->nextstatus=STOP;
					}
					break;
			}
			break;
		case OPEN:
			this->nextstatus=CLOSE;
			break;
		case CLOSE:
			this->nextstatus=KEEP;
			break;
		case STOP:
			if(this->highfloor > this->floor){
				this->nextstatus=KEEP;
				this->lastdir=UP;
			}else if(this->lowfloor<this->floor){
				this->nextstatus=DOWN;
				this->lastdir=DOWN;
			}else{
				this->nextstatus=STOP;
			}
			break;
	}
	
	//更新乘客的等待时间
	this->waittime_inc();
	this->cal_aveWaitTime();

}

//上行
void Elevator::up(int height){
	if(this->floor<22){
		this->rect.bottom -= height;
		this->rect.top -= height;
		this->floor++;
		this->status=UP;
		this->lastdir=UP;

		this->time++;
		this->cost+=1;
	}
}

//下行
void Elevator::down(int height){
	if(this->floor>1){
		this->rect.bottom += height;
		this->rect.top += height;
		this->floor--;
		this->status=DOWN;
		this->lastdir=DOWN;

		this->time++;
		this->cost+=1;
	}
}

//开门
void Elevator::open(){
	this->status=OPEN;
	this->time++;
}

//关门
void Elevator::close(){
	this->status=CLOSE;
	this->time++;
	this->cost+=10;
}

//保持
void Elevator::keep(){
	this->status=KEEP;
	//this->time++;
}

void Elevator::stop(){
	this->status=STOP;
	this->highfloor=this->lowfloor=this->floor;
	//this->cal_aveWaitTime();
}

//计算最低最高要到达的楼层
void Elevator::updateHigh_Low(){
	int i=0;
	int temp=1,highend=this->floor,lowend=this->floor;
	//遍历电梯内乘客的目的楼层
	if(this->p_innum>0){
		for(i=0;i<this->p_innum;i++){
			temp=this->peoplesin[i].endfloor;
			if(temp>highend){
				highend=temp;
			}
			if(temp<lowend){
				lowend=temp;
			}
		}
	}
	//遍历电梯外乘客的起始楼层
	if(this->p_outnum>0){
		for(i=0;i<this->p_outnum;i++){
			temp=this->peoplesout[i].startfloor;
			if(temp>highend){
				highend=temp;
			}
			if(temp<lowend){
				lowend=temp;
			}
		}
	}
	if(highend==lowend){
		this->highfloor=this->lowfloor=this->floor;
	}else{
		this->highfloor=highend;
		this->lowfloor=lowend;
	}

}

//更新floor_wait_flag,floor_arrive_flag
void  Elevator::updateFlag(){
	int i=0;
	People p;
	for(i=0;i<22;i++){
		this->floor_arrive_flag[i]=false;
		this->floor_wait_flag[i]=false;
	}
	for(i=0;i<this->p_innum;i++){
		p=this->peoplesin[i];
		this->floor_arrive_flag[p.endfloor-1]=true;
	}
	int dir=0;
	for(i=0;i<this->p_outnum;i++){
		p=this->peoplesout[i];
		dir=p.endfloor>p.startfloor?UP:DOWN;
		if(dir==this->lastdir)
			this->floor_wait_flag[p.startfloor-1]=true;
	}
}

//每个等待乘客的等待时间+1
void Elevator::waittime_inc(){
	int i=0;
	for(i=0;i<this->p_outnum;i++){
		this->peoplesout[i].waittime++;
	}
}

void Elevator::cal_aveWaitTime(){
	if(this->people_hadin>0)
		this->averagetime=(float)this->total_waittime/this->people_hadin*1.0;
}


//
float Elevator::runToEnd(){
	int timet,costt,people_hadint,total_waittimet,averagetimet;
	int statust,nextstatust,lastdirt;
	int p_innumt,p_outnumt;
	People peoplesint[15],peoplesoutt[30];
	int floort;
	bool floor_wait_flagt[22],floor_arrive_flagt[22];
	int lowfloort,highfloort;
	CRect rectt;

	float score;

	//保存
	timet=this->time;
	costt=this->cost;
	people_hadint=this->people_hadin;
	total_waittimet=this->total_waittime;
	averagetimet=this->averagetime;
	statust=status;
	nextstatust=nextstatus;
	lastdirt=lastdir;
	p_innumt=p_innum;
	p_outnumt=p_outnum;
	floort=floor;
	lowfloort=highfloor;
	highfloort=lowfloor;

	int i=0;
	for(i=0;i<p_innumt;i++){
		peoplesint[i]=peoplesin[i];
	}
	for(i=0;i<p_outnumt;i++){
		peoplesoutt[i]=peoplesout[i];
	}
	for(i=0;i<22;i++){
		floor_wait_flagt[i]=floor_wait_flag[i];
		floor_arrive_flagt[i]=floor_arrive_flag[i];
	}

	rectt=this->rect;


	//初始化
	time=0;
	cost=0;
	people_hadin=0;
	total_waittime=0;
	averagetime=0;

	while(true){
		this->move();
		if(this->status==STOP)
			break;
	}

	this->cal_aveWaitTime();
	//评分
	score = this->time*0.3+this->cost*0.3+this->averagetime*0.4;

	//还原
	this->time=timet;
	this->cost=costt;
	this->people_hadin=people_hadint;
	this->total_waittime=total_waittimet;
	this->averagetime=averagetimet;
	
	status=statust;
	nextstatus=nextstatust;
	lastdir=lastdirt;
	p_innum=p_innumt;
	p_outnum=p_outnumt;
	floor=floort;
	lowfloor=highfloort;
	highfloor=lowfloort;

	for(i=0;i<p_innumt;i++){
		peoplesin[i]=peoplesint[i];
	}
	for(i=0;i<p_outnumt;i++){
		peoplesout[i]=peoplesoutt[i];
	}
	for(i=0;i<22;i++){
		floor_wait_flag[i]=floor_wait_flagt[i];
		floor_arrive_flag[i]=floor_arrive_flagt[i];
	}
	this->rect=rectt;

	return score;
}

float Elevator::runToEnd(People pe){
	int timet,costt,people_hadint,total_waittimet,averagetimet;
	int statust,nextstatust,lastdirt;
	int p_innumt,p_outnumt;
	People peoplesint[15],peoplesoutt[30];
	int floort;
	bool floor_wait_flagt[22],floor_arrive_flagt[22];
	int lowfloort,highfloort;
	CRect rectt;

	float score;

	//保存
	timet=this->time;
	costt=this->cost;
	people_hadint=this->people_hadin;
	total_waittimet=this->total_waittime;
	averagetimet=this->averagetime;
	statust=status;
	nextstatust=nextstatus;
	lastdirt=lastdir;
	p_innumt=p_innum;
	p_outnumt=p_outnum;
	floort=floor;
	lowfloort=highfloor;
	highfloort=lowfloor;

	int i=0;
	for(i=0;i<p_innumt;i++){
		peoplesint[i]=peoplesin[i];
	}
	for(i=0;i<p_outnumt;i++){
		peoplesoutt[i]=peoplesout[i];
	}
	for(i=0;i<22;i++){
		floor_wait_flagt[i]=floor_wait_flag[i];
		floor_arrive_flagt[i]=floor_arrive_flag[i];
	}

	rectt=this->rect;


	//初始化
	time=0;
	cost=0;
	people_hadin=0;
	total_waittime=0;
	averagetime=0;
	
	this->addPeople(pe);
	while(true){
		this->move();
		if(this->status==STOP)
			break;
	}

	this->cal_aveWaitTime();
	//评分
	score = this->time*0.3+this->cost*0.3+this->averagetime*0.4;

	//还原
	this->time=timet;
	this->cost=costt;
	this->people_hadin=people_hadint;
	this->total_waittime=total_waittimet;
	this->averagetime=averagetimet;
	
	status=statust;
	nextstatus=nextstatust;
	lastdir=lastdirt;
	p_innum=p_innumt;
	p_outnum=p_outnumt;
	floor=floort;
	lowfloor=highfloort;
	highfloor=lowfloort;

	for(i=0;i<p_innumt;i++){
		peoplesin[i]=peoplesint[i];
	}
	for(i=0;i<p_outnumt;i++){
		peoplesout[i]=peoplesoutt[i];
	}
	for(i=0;i<22;i++){
		floor_wait_flag[i]=floor_wait_flagt[i];
		floor_arrive_flag[i]=floor_arrive_flagt[i];
	}
	this->rect=rectt;

	return score;
}

//测试运行，保存当前状态
float Elevator::testRun(){
	//Elevator e;
	float score;
	//e=*this;
	score=this->runToEnd();
	//*this=e;
	return score;
}

float Elevator::testRun(People pe){
	//Elevator e;
	float score;
	//e=*this;
	score=this->runToEnd(pe);
	//*this=e;
	return score;
}

void Elevator::runSingleStep(){
	this->move();
}