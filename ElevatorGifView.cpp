// ElevatorGifView.cpp : implementation of the CElevatorGifView class
//

#include "StdAfx.h"
#include "ElevatorGif.h"

#include "ElevatorGifDoc.h"
#include "ElevatorGifView.h"

#include "Elevator.h"
#include "People.h"
#include "FileOperator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int UP=1;
const int DOWN=-1;
const int OPEN=2;
const int CLOSE=-2;
const int KEEP=0;
const int STOP=4;

const int INELE=3;
const int OUTELE=-3;

/////////////////////////////////////////////////////////////////////////////
// CElevatorGifView

IMPLEMENT_DYNCREATE(CElevatorGifView, CView)

BEGIN_MESSAGE_MAP(CElevatorGifView, CView)
	//{{AFX_MSG_MAP(CElevatorGifView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElevatorGifView construction/destruction

CElevatorGifView::CElevatorGifView()
{
	// TODO: add construction code here

}

CElevatorGifView::~CElevatorGifView()
{
}

BOOL CElevatorGifView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CElevatorGifView drawing

// CElevatorGifView ����

void CElevatorGifView::init(CDC *pDC)
{

	//���ñ���ɫ
	CRect bgRect(0,0,1366,768);
	CBrush bgBrush(RGB(240,240,240));
	pDC->FillRect(bgRect,&bgBrush);

	this->floor = 22;
	this->elenum = 6;

	this->width = 60;
	this->height = 28;

	//�����ε����Ͻ�����
	this->ex0 = (1360 - this->width*this->elenum) / 2;
	this->ey0 = 10;
	//�����ε����½�����
	this->ex1 = this->ex0 + this->width*this->elenum;
	this->ey1 = this->ey0 + this->height*this->floor;

	//��ʼ������
	CPen pen(PS_SOLID, 2, RGB(0, 0, 255));
	CPen *pPen = pDC->SelectObject(&pen);

	//����������
	CRect rect(ex0,ey0,ex1+1,ey1+1);
	pDC->Rectangle(rect);

	//�����ڲ�����
	int x = ex0, y = ey0;
	int i;
	for (i = 0; i < 5; i++) {
		x += this->width;
		pDC->MoveTo(x, y);
		pDC->LineTo(x, ey1);
	}
	x = ex0;
	y = ey0;
	for (i = 0; i < 21; i++) {
		y += this->height;
		pDC->MoveTo(x, y);
		pDC->LineTo(ex1, y);
	}

	//��ʾ¥��
	CFont *m_Font = new CFont();
	m_Font->CreateFont(24, 20, 0, 0, 100,FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, (LPCTSTR)("����"));
	CFont *old_Font = pDC->SelectObject(m_Font);
	pDC->SetTextColor(RGB(0, 0, 255));

	const char floornum[][3] = { "22","21" ,"20" ,"19", "18", "17" ,"16",
								 "15", "14", "13", "12" ,"11" ,"10" ," 9",
								 " 8" ," 7" ," 6" ," 5" ," 4" ," 3" ," 2" ," 1" };
	for (i = 0; i < 22; i++) {
		pDC->TextOut(440, this->ey0+i*this->height+5, (CString)floornum[i]);
	}

	//��ʾ�������
	const char elevatornum[][3] = {"1","2","3","4","5","6"};
	for(i=0;i<6;i++){
		pDC->TextOut(ex0+20+i*60,this->ey1+4,(CString)elevatornum[i]);
	}
	pDC->SelectObject(old_Font);


	//���Ƶ���
	CBrush mBrush(RGB(0, 0, 255));

	ewidth = width - 10;
	eheight = height - 8;
	int ex, ey;
	ex = ex0 + 5;
	ey = ey1 - height+4;
	for (i = 0; i < 6; i++) {
		this->elevator[i].rect.SetRect(ex, ey, ex + ewidth, ey + eheight);
		pDC->FillRect(elevator[i].rect, &mBrush);
		//Ĭ���ڵ�һ��
		this->eleLocation[i] = 1;
		ex = ex + width;
	}

	//������1һ���˿�
	People p,p1,p2;
	p.elenum=1;
	p.startfloor=5;
	p.endfloor=8;
	p.id=1;
	p.status=OUTELE;
	p.waittime=0;

	p1.elenum=1;
	p1.startfloor=9;
	p1.endfloor=12;
	p1.id=2;
	p1.status=OUTELE;
	p1.waittime=0;

	p2.elenum=1;
	p2.startfloor=9;
	p2.endfloor=4;
	p2.id=3;
	p2.status=OUTELE;
	p2.waittime=0;
	this->elevator[0].addPeople(p);
	this->elevator[0].addPeople(p1);
	this->elevator[0].addPeople(p2);

	People p3,p4,p5;
	p3.elenum=3;
	p3.startfloor=2;
	p3.endfloor=17;
	p3.id=4;
	p3.status=OUTELE;
	p3.waittime=0;

	p4.elenum=3;
	p4.startfloor=7;
	p4.endfloor=22;
	p4.id=5;
	p4.status=OUTELE;
	p4.waittime=0;

	p5.elenum=3;
	p5.startfloor=21;
	p5.endfloor=2;
	p5.id=6;
	p5.status=OUTELE;
	p5.waittime=0;
	this->elevator[0].addPeople(p3);
	this->elevator[0].addPeople(p4);
	this->elevator[0].addPeople(p5);

}

//����n�����ݰ�dir��ʽ�ƶ�
//dir -1���� 0
void CElevatorGifView::MoveEle_n(CDC *pDC, int n, int dir)
{
	switch (dir) {
	case UP: this->Ele_Up(pDC,n); break;
	case DOWN: this->Ele_Down(pDC,n); break;
	case OPEN: this->Ele_Open(pDC,n); break;
	case CLOSE: this->Ele_Close(pDC,n); break;
	case KEEP: this->elevator[n].keep(); break;
	default: break;
	}
}

//nΪ���ݵ���ţ���1��ʼ
void CElevatorGifView::Ele_Up(CDC *pDC, int n)
{
	n = n - 1;
	if (n >= 0 && n <= 5) {
		//�ڶ���
		if (this->eleLocation[n] == this->floor)
			return;

		//���֮ǰ��ͼ��
		CBrush mBrush1(RGB(255, 255, 255));
		pDC->FillRect(elevator[n].rect, &mBrush1);

		//�ƶ�
		this->eleLocation[n]++;
//			this->elevator[n].rect.bottom -= this->height;
//			this->elevator[n].rect.top -= this->height;
		this->elevator[n].up(this->height);

		CBrush mBrush(RGB(0, 0, 255));
		pDC->FillRect(elevator[n].rect, &mBrush);
	}
	else {
		return;
	}
}

void CElevatorGifView::Ele_Down(CDC *pDC, int n)
{
	n = n - 1;
	if (n >= 0 && n <= 5) {
		//�ڵײ�
		if (this->eleLocation[n] == 1)
			return;

		//���֮ǰ��ͼ��
		CBrush mBrush1(RGB(255, 255, 255));
		pDC->FillRect(elevator[n].rect, &mBrush1);

		//�ƶ�
		this->eleLocation[n]--;
//			this->elevator[n].rect.bottom += this->height;
//			this->elevator[n].rect.top += this->height;
		this->elevator[n].down(this->height);
		CBrush mBrush(RGB(0, 0, 255));
		pDC->FillRect(elevator[n].rect, &mBrush);
	}
	else {
		return;
	}
}

void CElevatorGifView::Ele_Open(CDC *pDC, int n)
{
	n = n - 1;
	if (n >= 0 && n <= 5) {

		this->elevator[n].open();

		int doorwidth = ewidth - 10;
		int doorheight = eheight-4;
		int x = elevator[n].rect.left+5;
		int y = elevator[n].rect.top+2;

		//������
		CBrush mBrush1(RGB(255,255,255));
		CRect rect(x,y,x+doorwidth,y+doorheight);
		pDC->FillRect(rect,&mBrush1);
	}
}

void CElevatorGifView::Ele_Close(CDC *pDC, int n)
{
	n = n - 1;
	if (n >= 0 && n <= 5) {

		this->elevator[n].close();

		CBrush mBrush(RGB(0, 0, 255));
		pDC->FillRect(elevator[n].rect, &mBrush);
	}
}

void CElevatorGifView::OnDraw(CDC* pDC)
{
	CElevatorGifDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	this->init(pDC);

	//��ʼ��button
	//CRect bRect(1200, 200, 1280, 260);
	//this->cmdButton.Create((LPCTSTR)"hello", WS_CHILD | WS_VISIBLE | WS_BORDER, bRect, this, IDC_DYNAMICBUTTON);
	//this->cmdButton.ShowWindow(SW_SHOWNORMAL);

	//CPen pen(PS_SOLID,2,RGB(0,0,255));
	//CPen pen1(PS_SOLID, 2, RGB(255, 255, 255));
	//CPen *pPen = pDC->SelectObject(&pen);
	//CRect rect(50,50,100,100);
	//CClientDC dc(this);

	//int x0 = 100, y0 = 100, x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	//pDC->Rectangle(100,100,400,500);
	//for (int i = 0; i < 5;i++) {
	//	x1 += 50;
	//	pDC->MoveTo(x0+x1,y0);
	//	pDC->LineTo(x0+x1,500);
	//}
	//for (int i = 0; i < 7; i++) {
	//	y1 += 50;
	//	pDC->MoveTo(x0, y0 + y1);
	//	pDC->LineTo(400, y0 + y1);
	//}

	//for (int i = 0; i < 0; i++) {
	//	//dc.SetROP2(R2_NOT);
	//	//Invalidate();
	//	//i = i % 99;
	//	rect.MoveToX(50 + (i-1)*10);
	//	pPen = pDC->SelectObject(&pen1);
	//	pDC->Rectangle(rect);
	//	rect.MoveToX(50+i*10);
	//	pPen = pDC->SelectObject(&pen);
	//	pDC->Rectangle(rect);
	//	
	//	Sleep(1000);
	//}
}


/////////////////////////////////////////////////////////////////////////////
// CElevatorGifView printing

BOOL CElevatorGifView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CElevatorGifView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CElevatorGifView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CElevatorGifView diagnostics

#ifdef _DEBUG
void CElevatorGifView::AssertValid() const
{
	CView::AssertValid();
}

void CElevatorGifView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CElevatorGifDoc* CElevatorGifView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CElevatorGifDoc)));
	return (CElevatorGifDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CElevatorGifView message handlers

void CElevatorGifView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	FileOperator mfile;
	mfile.loadmain();

	CDC *pDC=GetDC();
	int i,j;

	CBrush mBrush1(RGB(255,255,255));
	CBrush mBrush(RGB(0,0,255));
	CString str;
	Elevator e;
	bool flag=true;
	int time=1;

//		str.Format("�ܺ�(ͣ������): 92\nƽ���ȴ�ʱ��: 9.18\n��������:0");
//		MessageBox(str,"����",MB_OKCANCEL);

	while(true){
		for( j=0; j<6; j++){
			pDC->FillRect(elevator[j].rect,&mBrush1);

			this->elevator[ j].move();

			pDC->FillRect(elevator[j].rect,&mBrush);

			for(i=0;i<6;i++){
				if(this->elevator[i].status==OPEN){
					int doorwidth = ewidth - 10;
					int doorheight = eheight-4;
					int x = elevator[i].rect.left+5;
					int y = elevator[i].rect.top+2;

					//������
					//CBrush mBrush1(RGB(255,255,255));
					CRect rect(x,y,x+doorwidth,y+doorheight);
					pDC->FillRect(rect,&mBrush1);
				}	
			}
		//	if(this->elevator[4].status==OPEN){
					//str.Format("�ܺ�(ͣ������): 92\nƽ���ȴ�ʱ��: 9.18\n��������:0");
					//MessageBox(str,"����",MB_OKCANCEL);
		//		}

		}


			if(this->elevator[0].nextstatus==STOP)
				break;
			
		Sleep(300);
		time++;
	}

//		str.Format("%d ��  %d �ܺ�",this->elevator[0].time,this->elevator[0].cost);
//		MessageBox(str,"����",MB_OKCANCEL);
//		str.Format("�ܵȴ�ʱ��: %d\n ����: %d  ƽ��ʱ��:%.2f",this->elevator[0].total_waittime,this->elevator[0].people_hadin,this->elevator[0].averagetime);
//		MessageBox(str,"����",MB_OKCANCEL);

	//this->PassengerDiv();

	CView::OnLButtonDown(nFlags, point);
}

void CElevatorGifView::PassengerDiv()
{
	FileOperator mfile;
	mfile.loadmain();

	int num=mfile.data[0][0];	//�˿�����
	int nownum=0;		//�Ѿ����ǵĳ˿�����
	int nowline=1;
	int secnum=0;		//��һ��ĳ˿�����
	int i,j,k,t=0;
	int score;
	int bestscore;		//��ǰ��õ�����
	int bestselect;		//��ǰ��õ�ѡ��	
	//int finselect;		//����ѡ��ĵ���
	bool end=0;			//һ�����

	CString str;

	CDC *pDC=GetDC();
	CBrush mBrush1(RGB(255,255,255));
	CBrush mBrush(RGB(0,0,255));
	Elevator e;
	CRect rect;
	bool flag=true;
	while(nownum<num)
	{
		end=0;
		secnum=0;
		while(0==end)		//�õ���һ��ĳ˿���
		{
			if(-1==mfile.data[nowline+secnum][0]){
				end=1;
			}
			else{
				secnum++;
			}

		}//����while����

	
		if (0==secnum)	//��һ��û����
		{
			for(t=0;t<6;t++)	//k:���ݺ�
			{
				pDC->FillRect(elevator[t].rect,&mBrush1);
				this->elevator[ t].move();
				pDC->FillRect(elevator[t].rect,&mBrush);

				if(this->elevator[t].status==OPEN){
					int doorwidth = ewidth - 10;
					int doorheight = eheight-4;
					int x = elevator[t].rect.left+5;
					int y = elevator[t].rect.top+2;

					//������
					rect.SetRect(x,y,x+doorwidth,y+doorheight);
					pDC->FillRect(rect,&mBrush1);
				}

			}//for����,�Ż�����
			Sleep(100);
		}//if������û���˽���
		else	//�п���
		{
			i=1;//i����һ��ڼ����˿�
			while(i<=secnum)
			{
				bestscore=30000;//

				People pe;
				pe.id++;
				pe.startfloor=mfile.data[nowline+i-1][1];
				pe.endfloor=mfile.data[nowline+i-1][2];
				
				pe.status=OUTELE;
				pe.waittime=0;

				//jѭ�����ֿ��˵�����
				for(j=1;j<=6;j++)	//j:��i�����˷ֵ���j������
				{
					
					//______���ݵ�i�����˵Ĳ���_____
					pe.elenum=j;

					//this->elevator[j-1].addPeople(pe);
					//kѭ�����ֺ��˿��˽��з���
					score=0;
					for(k=1;k<=6;k++)	//k:���ݺ�
					{	
						if(k==j){
							//�������У��������
							score+=this->elevator[j-1].testRun(pe);
						}
						else{
							//�������У��������
							score+=this->elevator[k-1].testRun();
						}

					}//kѭ������

					if(score<bestscore)
					{
						//_____ˢ��¼____
						bestselect=j;
						bestscore=score;
					}

					//__ѡ����õķַ�___
					//finselect=bestselect��

				}//jѭ������

				//�������з���j�����˿ͼ������
				this->elevator[j].addPeople(pe);

				i++;
			}//iѭ������
			
		}//else���� ��һ���Ż�����

		for( t=0; t<6; t++){
			pDC->FillRect(elevator[t].rect,&mBrush1);
			this->elevator[ t].move();
			pDC->FillRect(elevator[t].rect,&mBrush);

			if(this->elevator[t].status==OPEN){
				int doorwidth = ewidth - 10;
				int doorheight = eheight-4;
				int x = elevator[t].rect.left+5;
				int y = elevator[t].rect.top+2;

				//������
				CRect rect(x,y,x+doorwidth,y+doorheight);
				pDC->FillRect(rect,&mBrush1);
			}

		}
		Sleep(100);
				
		nownum=nownum+secnum;
		nowline=nowline+secnum+1;
	}//һ��while���������п��˶�������
	//��ʾ���
	//this->display();
}
