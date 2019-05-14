#pragma once
#include "Resource.h"
#include "afxwin.h"

// CSortDialog dialog

class CSortDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSortDialog)

public:
	CSortDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSortDialog();

	//virtual void OnFinalRelease();

// Dialog Data
	enum { IDD = IDD_SORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	/*DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()*/
public:
	CButton m_chkID;
	CButton m_chkName;
	CButton m_chkSex;
	CButton m_chkAge;
	CButton m_chkPhone;
	CButton m_btnOk;
	CButton m_btnCancel;
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
	int m_check;

	enum State
	{
		eID = 0,
		eName,
		eSex,
		eAge,
		ePhone
	};
};
