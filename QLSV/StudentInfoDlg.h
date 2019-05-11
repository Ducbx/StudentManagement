#pragma once
#include "afxwin.h"


// CStudentInfoDlg dialog

class CStudentInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentInfoDlg)

public:
	CStudentInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStudentInfoDlg();

// Dialog Data
	enum { IDD = IDD_STUDENT_INFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CEdit m_edtName;
	CComboBox m_ccbSex;
	CEdit m_edtAge;
	CEdit m_edtPhone;
	CButton m_btnOk;
	CButton m_btnCancel;
public:
	afx_msg void OnBnClickedButtonCancel();
};
