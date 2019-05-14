// SortDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SortDialog.h"
#include "afxdialogex.h"
#include "MessageDefine.h"

// CSortDialog dialog

IMPLEMENT_DYNAMIC(CSortDialog, CDialogEx)

CSortDialog::CSortDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSortDialog::IDD, pParent)
{
	m_check = 0;
}

CSortDialog::~CSortDialog()
{

}


void CSortDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ID, m_chkID);
	DDX_Control(pDX, IDC_CHECK_NAME, m_chkName);
	DDX_Control(pDX, IDC_CHECK_SEX, m_chkSex);
	DDX_Control(pDX, IDC_CHECK_AGE, m_chkAge);
	DDX_Control(pDX, IDC_CHECK_PHONE, m_chkPhone);
	DDX_Control(pDX, IDC_BTN_OK, m_btnOk);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CSortDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OK, &CSortDialog::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CSortDialog::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CSortDialog message handlers


void CSortDialog::OnBnClickedBtnOk()
{
	if (m_chkID.GetState())
	{
		m_check += (int)pow(2.0, (State::eID));
	}
	if (m_chkName.GetState())
	{
		m_check += (int)pow(2.0, (State::eName));
	}
	if (m_chkSex.GetState())
	{
		m_check += (int)pow(2.0, (State::eSex));
	}
	if (m_chkAge.GetState())
	{
		m_check += (int)pow(2.0, (State::eAge));
	}
	if (m_chkPhone.GetState())
	{
		m_check += (int)pow(2.0,(State::ePhone));
	}

	::SendMessage(this->GetParent()->GetSafeHwnd(), UWM_SEND_STUDENT_INFO_TO_SORT, m_check, 0);
	this->OnOK();
}


void CSortDialog::OnBnClickedBtnCancel()
{
	this->OnCancel();
}
