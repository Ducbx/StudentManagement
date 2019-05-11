// StudentInfo.cpp : implementation file
//

#include "stdafx.h"
#include "StudentManagement.h"
#include "StudentInfoDlg.h"
#include "afxdialogex.h"


// CStudentInfoDlg dialog

IMPLEMENT_DYNAMIC(CStudentInfoDlg, CDialogEx)

CStudentInfoDlg::CStudentInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStudentInfoDlg::IDD, pParent)
{

}

CStudentInfoDlg::~CStudentInfoDlg()
{
}

void CStudentInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edtName);
	DDX_Control(pDX, IDC_COMBO_SEX, m_ccbSex);
	DDX_Control(pDX, IDC_EDIT_AGE, m_edtAge);
	DDX_Control(pDX, IDC_EDIT_PHONE, m_edtPhone);
	DDX_Control(pDX, IDC_BUTTON_OK, m_btnOk);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CStudentInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CStudentInfoDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CStudentInfoDlg message handlers


void CStudentInfoDlg::OnBnClickedButtonCancel()
{
	this->OnCancel();
}
