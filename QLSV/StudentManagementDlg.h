
// QLSVDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "IStudentService.h"

// CStudentManagementDlg dialog
class CStudentManagementDlg : public CDialogEx
{
// Construction
public:
	CStudentManagementDlg(IStudentService* pStudentService, CWnd* pParent = NULL);	// standard constructor

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
	CListCtrl m_listCtrlStudent;
	CButton m_btnAdd;
	CButton m_btnEdit;
	CButton m_btnDel;
	CButton m_btnExit;
	CButton m_btnSort;
	CButton m_btnSearch;
	CButton m_btnConnect;
public:
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnExit();
private:
	IStudentService* m_pStudentService;
	BOOL m_bIsConnected;
public:
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBtnConnect();
	afx_msg LRESULT OnReceiveStudentInforToAdd(WPARAM wParam, LPARAM lParam);
	void DisableButton();
	void EnableButton();
	void LoadDBToListControl();
};
