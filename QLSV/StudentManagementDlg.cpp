
// QLSVDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StudentManagement.h"
#include "StudentManagementDlg.h"
#include "afxdialogex.h"
#include "StudentInfoDlg.h"
#include "Student.h"
#include<vector>
#include "MessageDefine.h"
#include "SortDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStudentManagementDlg dialog



CStudentManagementDlg::CStudentManagementDlg(IStudentService* pStudentService, CWnd* pParent /*=NULL*/)
	: CDialogEx(CStudentManagementDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bIsConnected = FALSE;
	m_pStudentService = pStudentService;
	m_iSelectedRow = -1;
}

void CStudentManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ALL_STUDENT, m_listCtrlStudent);
	DDX_Control(pDX, IDC_BTN_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BTN_EDIT, m_btnEdit);
	DDX_Control(pDX, IDC_BTN_DEL, m_btnDel);
	DDX_Control(pDX, IDC_BTN_EXIT, m_btnExit);
	DDX_Control(pDX, IDC_BTN_CONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_BTN_SORT, m_btnSort);
	DDX_Control(pDX, IDC_BTN_SEARCH, m_btnSearch);
}

BEGIN_MESSAGE_MAP(CStudentManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, &CStudentManagementDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CStudentManagementDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CStudentManagementDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CStudentManagementDlg::OnBnClickedBtnEdit)
	ON_MESSAGE(UWM_SEND_STUDENT_INFO_TO_ADD, OnReceiveStudentInforToAdd)
	ON_MESSAGE(UWM_SEND_STUDENT_INFO_TO_EDIT, OnReceiveStudentInforToEdit)
	ON_MESSAGE(UWM_SEND_STUDENT_INFO_TO_SORT, OnReceiveStudentInforToSort)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ALL_STUDENT, &CStudentManagementDlg::OnClickListCtrl)
	ON_BN_CLICKED(IDC_BTN_DEL, &CStudentManagementDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SORT, &CStudentManagementDlg::OnBnClickedBtnSort)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CStudentManagementDlg::OnBnClickedBtnSearch)
END_MESSAGE_MAP()


// CStudentManagementDlg message handlers

BOOL CStudentManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	DisableButton();

	//Init list control
	m_listCtrlStudent.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_SHOWSELALWAYS );
	m_listCtrlStudent.SetExtendedStyle(m_listCtrlStudent.GetExtendedStyle()| LVS_EX_FULLROWSELECT);

	CRect rect;
	m_listCtrlStudent.GetClientRect(&rect);
	int nColInterval = rect.Width() / 5;

	m_listCtrlStudent.InsertColumn(
		0,              // Rank/order of item 
		L"ID",          // Caption for this header 
		LVCFMT_CENTER,    // Relative position of items under header 
		(int)(0.5*nColInterval));           // Width of items under header
	m_listCtrlStudent.InsertColumn(1, L"Name", LVCFMT_CENTER, (int)(1.75*nColInterval));
	m_listCtrlStudent.InsertColumn(2, L"Sex", LVCFMT_CENTER, (int)(0.5*nColInterval));
	m_listCtrlStudent.InsertColumn(3, L"Age", LVCFMT_CENTER, (int)(0.5*nColInterval));
	m_listCtrlStudent.InsertColumn(4, L"Phone Number", LVCFMT_CENTER, (int)(1.75*nColInterval));

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStudentManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStudentManagementDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStudentManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStudentManagementDlg::OnBnClickedBtnAdd()
{
	CStudentInfoDlg *dlgStudent = new CStudentInfoDlg(this);
	dlgStudent->DoModal();
}


void CStudentManagementDlg::OnBnClickedBtnExit()
{
	this->OnOK();
}


void CStudentManagementDlg::OnBnClickedBtnConnect()
{
	if (!m_bIsConnected)
	{
		if (m_pStudentService->OpenDB())
		{
			m_btnConnect.SetWindowTextW(L"Disconnect");
			m_bIsConnected = TRUE;
			EnableButton();
			LoadDBToListControl();
		}
	}
	else
	{
		m_pStudentService->CloseDB();
		m_btnConnect.SetWindowTextW(L"Connect");
		m_bIsConnected = FALSE;
		DisableButton();
	}
	//Sau khi connect ban luon message to update list control
}


void CStudentManagementDlg::OnBnClickedBtnEdit()
{
	if (m_iSelectedRow > -1)
	{
		CStudent std;
		std.SetStudentID(_wtoi(m_listCtrlStudent.GetItemText(m_iSelectedRow, 0)));
		std.SetName(m_listCtrlStudent.GetItemText(m_iSelectedRow, 1));
		std.SetSex(m_listCtrlStudent.GetItemText(m_iSelectedRow, 2));
		std.SetAge(_wtoi(m_listCtrlStudent.GetItemText(m_iSelectedRow, 3)));
		std.SetPhone(m_listCtrlStudent.GetItemText(m_iSelectedRow, 4));

		CStudentInfoDlg *dlg = new CStudentInfoDlg(this, &std);
		dlg->DoModal();
		m_iSelectedRow = -1;
	}
}


void CStudentManagementDlg::EnableButton()
{
	m_btnAdd.EnableWindow(TRUE);
	m_btnDel.EnableWindow(TRUE);
	m_btnSearch.EnableWindow(TRUE);
	m_btnEdit.EnableWindow(TRUE);
	m_btnSort.EnableWindow(TRUE);
}

void CStudentManagementDlg::DisableButton()
{
	m_btnAdd.EnableWindow(FALSE);
	m_btnDel.EnableWindow(FALSE);
	m_btnSearch.EnableWindow(FALSE);
	m_btnEdit.EnableWindow(FALSE);
	m_btnSort.EnableWindow(FALSE);
}

//khong goi truc tiep ma goi qua service
void CStudentManagementDlg::LoadDBToListControl()
{
	//UI khong dc goi thang DB
	std::vector<CStudent> listStudent;
	listStudent = m_pStudentService->GetStudentInfo();

	m_listCtrlStudent.DeleteAllItems();
	for (size_t i = 0; i < listStudent.size(); i++)
	{
		CString strID, strAge;
		strID.Format(_T("%d"), listStudent[i].GetStudentID());
		strAge.Format(_T("%d"), listStudent[i].GetAge());
		m_listCtrlStudent.InsertItem(i, strID);
		m_listCtrlStudent.SetItemText(i, 1, listStudent[i].GetName());
		m_listCtrlStudent.SetItemText(i, 2, listStudent[i].GetSex());
		m_listCtrlStudent.SetItemText(i, 3, strAge);
		m_listCtrlStudent.SetItemText(i, 4, listStudent[i].GetPhone());
	}
}

//receive student info from dlg
LRESULT CStudentManagementDlg::OnReceiveStudentInforToAdd(WPARAM wParam, LPARAM lParam)
{
	//get info of student need add
	CStudent *student = (CStudent*)wParam;
	//day xuong database
	m_pStudentService->AddStudent(*student);
	
	LoadDBToListControl();
	return 0L;
}

LRESULT CStudentManagementDlg::OnReceiveStudentInforToEdit(WPARAM wParam, LPARAM lParam)
{
	//get info of student need add
	CStudent *student = (CStudent*)wParam;
	m_pStudentService->EditStudent(*student);

	LoadDBToListControl();
	return 0L;
}

LRESULT CStudentManagementDlg::OnReceiveStudentInforToSort(WPARAM wParam, LPARAM lParam)
{
	//get info of student need add
	int iCheck = (int)wParam;
	for (int i = 0; iCheck>0; i++)
	{
		int iTemp = iCheck % 2;
		if (iTemp)
		{

		}
		iCheck = iCheck / 2;
	}


	LoadDBToListControl();
	return 0L;
}

void CStudentManagementDlg::OnClickListCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION iPos = m_listCtrlStudent.GetFirstSelectedItemPosition();
	if (iPos)
	{
		m_iSelectedRow = m_listCtrlStudent.GetNextSelectedItem(iPos);
	}
}



void CStudentManagementDlg::OnBnClickedBtnDel()
{
	if (m_iSelectedRow > -1)
	{
		//get id of student need to delete
		int id = _wtoi(m_listCtrlStudent.GetItemText(m_iSelectedRow, 0));
		m_pStudentService->DeleteStudent(id);
		LoadDBToListControl();
		m_iSelectedRow = -1;
	}
}


void CStudentManagementDlg::OnBnClickedBtnSort()
{
	CSortDialog *dlg = new CSortDialog(this);
	dlg->DoModal();
}


void CStudentManagementDlg::OnBnClickedBtnSearch()
{
	// TODO: Add your control notification handler code here
}
