#include "stdafx.h"
#include "DatabaseConnection.h"


CDatabaseConnection::CDatabaseConnection()
{
	m_pConnection = NULL;
	m_pCommand = NULL;
	m_pRescordset = NULL;
	m_bIsConnected = FALSE;
}


CDatabaseConnection::~CDatabaseConnection()
{
	CloseDB();
	m_pConnection = NULL;
	m_pCommand = NULL;
	m_pRescordset = NULL;
}

BOOL CDatabaseConnection::OpenDB()
{
	// Define string variables for connection
	_bstr_t strCon("Provider='SQLOLEDB.1';Persist Security Info='False';Initial Catalog='StudentManagement';Data Source='DESKTOP-RLFPHMT\\SQLEXPRESS';Integrated Security='SSPI';");

	HRESULT hr = S_OK;

	//Initialize the COM Library
	CoInitialize(NULL);

	//Create the Connection pointer
	hr = m_pConnection.CreateInstance((__uuidof(Connection)));
	if (FAILED(hr))
	{
		AfxMessageBox(L"Error instantiating Connection object");
		CoUninitialize();
		return FALSE;
	}

	try
	{
		hr = m_pConnection->Open(strCon, strID, strPws, 0);
		if (FAILED(hr))
		{
			AfxMessageBox(L"Error Opening Database object\n");
			CoUninitialize();
			return FALSE;
		}
		AfxMessageBox(L"Opening Database OK");
		m_bIsConnected = TRUE;
		return TRUE;
	}
	catch (_com_error & ce)
	{
		CString strTemp = ce.Description();
		AfxMessageBox(strTemp);
		CoUninitialize();
		return FALSE;
	}
}

BOOL CDatabaseConnection::CloseDB()
{
	if (m_bIsConnected)
	{
		m_pConnection->Close();
		CoUninitialize();
		m_bIsConnected = FALSE;
	}
	return TRUE;
	/*try
	{
	}
	catch (_com_error & ce)
	{
		CString strTemp = ce.Description();
		AfxMessageBox(strTemp);
		return FALSE;
	}*/
}

BOOL CDatabaseConnection::ExecuteSQL()
{

	return TRUE;
}