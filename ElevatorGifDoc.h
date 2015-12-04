// ElevatorGifDoc.h : interface of the CElevatorGifDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEVATORGIFDOC_H__CA1605E0_BB87_47AE_983E_1CF29EE245D3__INCLUDED_)
#define AFX_ELEVATORGIFDOC_H__CA1605E0_BB87_47AE_983E_1CF29EE245D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CElevatorGifDoc : public CDocument
{
protected: // create from serialization only
	CElevatorGifDoc();
	DECLARE_DYNCREATE(CElevatorGifDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElevatorGifDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CElevatorGifDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CElevatorGifDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEVATORGIFDOC_H__CA1605E0_BB87_47AE_983E_1CF29EE245D3__INCLUDED_)
