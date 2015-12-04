// FileOperator.h: interface for the FileOperator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEOPERATOR_H__BB07A3ED_C65A_4EBC_95A6_0CB8BE92BA07__INCLUDED_)
#define AFX_FILEOPERATOR_H__BB07A3ED_C65A_4EBC_95A6_0CB8BE92BA07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class FileOperator  
{
public:
	FileOperator();
	virtual ~FileOperator();

//void fileread(int ..);
	int load();
	void changeform(int line);
	void loadmain();

	char **input;
	int **data;
	int line;
};

#endif // !defined(AFX_FILEOPERATOR_H__BB07A3ED_C65A_4EBC_95A6_0CB8BE92BA07__INCLUDED_)
