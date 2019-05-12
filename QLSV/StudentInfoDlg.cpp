// StudentInfo.cpp : implementation file
//

#include "stdafx.h"
#include "StudentManagement.h"
#include "StudentInfoDlg.h"
#include "afxdialogex.h"
#include "Student.h"
#include "MessageDefine.h"


// CStudentInfoDlg dialog

IMPLEMENT_DYNAMIC(CStudentInfoDlg, CDialogEx)

CStudentInfoDlg::CStudentInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStudentInfoDlg::IDD, pParent)
{
	m_student = new CStudent();
}

CStudentInfoDlg::~CStudentInfoDlg()
{
	if (m_student)
	{
		delete m_student;
		m_student = NULL;
	}
}

BOOL CStudentInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();



	m_ccbSex.AddString(L"Male");
	m_ccbSex.AddString(L"Female");
	m_ccbSex.SetCurSel(1);
	

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
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
	DDX_Control(pDX, IDC_EDT_ID, m_edtID);
}


BEGIN_MESSAGE_MAP(CStudentInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CStudentInfoDlg::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CStudentInfoDlg::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CStudentInfoDlg message handlers


void CStudentInfoDlg::OnBnClickedButtonCancel()
{
	this->OnCancel();
}


void CStudentInfoDlg::OnBnClickedButtonOk()
{
	// get info of student
	//Get ID, Name, age, phone
	CString strTemp;
	m_edtID.GetWindowTextW(strTemp);
	m_student->SetStudentID(_wtoi(strTemp));
	m_edtName.GetWindowTextW(strTemp);
	m_student->SetName(strTemp);
	m_edtAge.GetWindowTextW(strTemp);
	m_student->SetAge(_wtoi(strTemp));
	m_edtPhone.GetWindowTextW(strTemp);
	m_student->SetPhone(strTemp);
	//Get sex
	CString strSex = L"";
	int nSel = m_ccbSex.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_ccbSex.GetWindowTextW(strSex);
	}
	m_student->SetSex(strSex);

	//SEND msg of m_student to parent
	::SendMessage(GetParent()->GetSafeHwnd(), UWM_SEND_STUDENT_INFO_TO_PARENT, (WPARAM)m_student, 0);
	
	this->OnOK();
}

