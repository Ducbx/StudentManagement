
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
	ON_MESSAGE(UWM_SEND_STUDENT_INFO_TO_PARENT, OnReceiveStudentInforToAdd)
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
	m_listCtrlStudent.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_listCtrlStudent.SetExtendedStyle(LVS_EX_GRIDLINES);

	CRect rect;
	m_listCtrlStudent.GetClientRect(&rect);
	int nColInterval = rect.Width() / 5;

	m_listCtrlStudent.InsertColumn(
		0,              // Rank/order of item 
		L"ID",          // Caption for this header 
		LVCFMT_CENTER,    // Relative position of items under header 
		(int)(0.5*nColInterval));           // Width of items under header
	m_listCtrlStudent.InsertColumn(1, L"Name", LVCFMT_CENTER, (int)(1.75*nColInterval));
	m_listCtrlStudent.InsertColumn(2, L"Age", LVCFMT_CENTER, (int)(0.5*nColInterval));
	m_listCtrlStudent.InsertColumn(3, L"Sex", LVCFMT_CENTER, (int)(0.5*nColInterval));
	m_listCtrlStudent.InsertColumn(4, L"Phone Number", LVCFMT_CENTER, (int)(1.75*nColInterval));

	/*int nItem = m_listCtrlStudent.InsertItem(0, L"1");
	m_listCtrlStudent.SetItemText(nItem, 1, L"Mark");
	m_listCtrlStudent.SetItemText(nItem, 2, L"45");
	m_listCtrlStudent.SetItemText(nItem, 3, L"Address 1");
	m_listCtrlStudent.SetItemText(nItem, 4, L"Address 2");

	nItem = m_listCtrlStudent.InsertItem(1, L"2");
	m_listCtrlStudent.SetItemText(nItem, 1, L"Mark");
	m_listCtrlStudent.SetItemText(nItem, 2, L"45");
	m_listCtrlStudent.SetItemText(nItem, 3, L"Address 1");
	m_listCtrlStudent.SetItemText(nItem, 4, L"Address 2");*/


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
	//CString strSQL = _T("insert into dbo.QLSV(StudentID, Name, Sex, Age, PhoneNumber) values('8', 'Phu VK', 'Male', '27', '09888888')");
	//m_DBConnection.SQLSetDataExecute(strSQL);
	/*CString strSQL = _T("SELECT * FROM dbo.QLSV");
	m_DBConnection.SQLGetDataExecute(strSQL);

	std::vector<CStudent> listStudent;
	listStudent = m_DBConnection.GetStudentInfo();*/
	
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
		m_listCtrlStudent.SetItemText(i, 2, strAge);
		m_listCtrlStudent.SetItemText(i, 3, listStudent[i].GetSex());
		m_listCtrlStudent.SetItemText(i, 4, listStudent[i].GetPhone());
	}
}

//receive student info from dlg
LRESULT CStudentManagementDlg::OnReceiveStudentInforToAdd(WPARAM wParam, LPARAM lParam)
{
	//Student 
	/*int temp = (int)wParam;
	m_progressStatus.SetPos(temp);
	int rate = 100 * temp / m_iTotalFileNumber;*/
	//get info of student need add
	//m_pStudentService->AddStudent(student);
	CStudent *student = (CStudent*)wParam;
	//day xuong database
	m_pStudentService->AddStudent(*student);
	
	m_listCtrlStudent.DeleteAllItems();
	LoadDBToListControl();
	return 0L;
}