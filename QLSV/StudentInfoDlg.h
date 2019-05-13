#pragma once
#include "afxwin.h"
#include <cstdint>
#include "windows.h"
#include "Student.h"


// CStudentInfoDlg dialog

class CStudentInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentInfoDlg)

public:
	CStudentInfoDlg(CWnd* pParent = NULL, CStudent* student = NULL);   // standard constructor
	virtual ~CStudentInfoDlg();
	virtual BOOL OnInitDialog();
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
	CEdit m_edtID;
public:
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonOk();
private:
	CStudent *m_student;
	CStudent *m_inputStudent;
};
