// FileOperator.cpp: implementation of the FileOperator class.
//
//////////////////////////////////////////////////////////////////////
#include <iostream>
//#include <fstream>
//using namespace std;

#include "stdafx.h"
#include "ElevatorGif.h"
#include "FileOperator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//char input[500][81];
//int data[500][3];

FileOperator::FileOperator()
{
	int i=0,j=0;
	this->input=new char*[500];
	for(i=0;i<500;i++){
		input[i]=new char[81];
	}
	this->data=new int*[500];
	for(j=0;j<500;j++){
		data[j]=new int[3];
	}
}

FileOperator::~FileOperator()
{
	int i=0,j=0;
	for(i=0;i<500;i++){
		if(input[i])
			delete []input[i];
	}
	for(j=0;j<500;j++){
		if(data[j])
			delete []data[j];
	}
}


void FileOperator::loadmain()
{
	//int line;
	line=load();
	changeform(line);
	
	//tip:ctrl+k,u;ctrl+k,c
	//��ʽת������
	//AllocConsole();								// ���ٿ���̨
	//SetConsoleTitle(_T("���Դ���"));	  //���ÿ���̨���ڱ���
	//freopen("CONOUT$","w",stdout);	// �ض������
	//freopen( "CONIN$", "r+t", stdin );

	//printf("%d\n",data[0][0]);
	//for (int i=1;i<=line;i++)
	//{
	//	printf("%d\t%d\t%d\n",data[i][0],data[i][1],data[i][2]);
	//}

	//system("pause");
	//FreeConsole();//�ͷſ���̨

}

int FileOperator::load()
{
	char* pszFileName="PassengerList.txt";
	CStdioFile myFile;
	CFileException fileException;
	if(myFile.Open(pszFileName,CFile::typeText|CFile::modeReadWrite),&fileException)
	{

//	AllocConsole();								// ���ٿ���̨
//	SetConsoleTitle(_T("���Դ���"));	  //���ÿ���̨���ڱ���
//	freopen("CONOUT$","w",stdout);	// �ض������
//	freopen( "CONIN$", "r+t", stdin );
		
		int i=-1,j=0,length=0;
		myFile.SeekToBegin();
		CString str1;
		do
		{
			i++;
			myFile.ReadString(str1);
			//AfxMessageBox(str1+str2);
			length=str1.GetLength();
			if(length!=0){
				for(j=0;j<length;j++){
					input[i][j]=str1.GetAt(j);
				}
				input[i][j]='\0';
				//printf("%s\n",input[i]);
			}
			
		}while(str1.GetLength()!=0);
		
		//FreeConsole();//�ͷſ���̨

		myFile.Close();

		return i-1;
	}
	else
	{
		TRACE("Can't open file %s,error=%u\n",pszFileName,fileException.m_cause);
		return 0;
	}
	
}

void FileOperator::changeform(int line)
{
	int num,i,j,count;
	for(i=0;i<=line;i++)
	{
		if(0==i)		//��һ���ַ�����
		{
			num=0;
			for(j=0;j<=80;j++)
			{
				if(input[0][j] >='0' && input[0][j] <='9')
				{
					num=num*10+input[0][j]-48;
				}
				else
				{
					data[0][0]=num;
					break;
				} 
			}//j ѭ������
		}//if ����

		else			//������ǵ�һ�����������ַ�
		{	
			num=0;
			count=0;
			for(j=0;j<80;j++)
			{
				if(3==count)			//����3�����˳�
					break;
				if(input[i][0]=='-')	//�����һ���ǡ�-������һ���ǡ�-1 0 0��
				{
					data[i][0]=-1;
					data[i][1]= 0;
					data[i][2]= 0;
					break;
				}
				
				if(input[i][j] >='0' && input[i][j] <='9')
				{
					num=num*10+input[i][j]-48;
				}
				else
				{
					data[i][count]=num;
					num=0;
					count=count+1;
				}

			}//jѭ������

		}//else����

	}//iѭ������

}