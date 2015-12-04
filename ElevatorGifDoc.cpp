// ElevatorGifDoc.cpp : implementation of the CElevatorGifDoc class
//

#include "stdafx.h"
#include "ElevatorGif.h"

#include "ElevatorGifDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElevatorGifDoc

IMPLEMENT_DYNCREATE(CElevatorGifDoc, CDocument)

BEGIN_MESSAGE_MAP(CElevatorGifDoc, CDocument)
	//{{AFX_MSG_MAP(CElevatorGifDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElevatorGifDoc construction/destruction

CElevatorGifDoc::CElevatorGifDoc()
{
	// TODO: add one-time construction code here

}

CElevatorGifDoc::~CElevatorGifDoc()
{
}

BOOL CElevatorGifDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CElevatorGifDoc serialization

void CElevatorGifDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CElevatorGifDoc diagnostics

#ifdef _DEBUG
void CElevatorGifDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CElevatorGifDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CElevatorGifDoc commands
