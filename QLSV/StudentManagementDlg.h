
// QLSVDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DatabaseConnection.h"

// CStudentManagementDlg dialog
class CStudentManagementDlg : public CDialogEx
{
// Construction
public:
	CStudentManagementDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_QLSV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CListCtrl m_lctrStudentTable;
	CButton m_btnAdd;
	CButton m_btnEdit;
	CButton m_btnDel;
	CButton m_btnExit;
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnExit();
	CButton m_btnConnect;
public:
	afx_msg void OnBnClickedBtnConnect();
private:
	CDatabaseConnection m_DBConnection;
	BOOL m_bIsConnected;
};
