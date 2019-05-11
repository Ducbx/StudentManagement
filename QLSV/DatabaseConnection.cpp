#include "stdafx.h"
#include "DatabaseConnection.h"


CDatabaseConnection::CDatabaseConnection()
{
	m_pConnection = NULL;
	m_pCommand = NULL;
	m_pRecordset = NULL;
	m_bIsConnected = FALSE;
	m_bIsRecordOpened = FALSE;
}


CDatabaseConnection::~CDatabaseConnection()
{
	CloseDB();
	m_pConnection = NULL;
	m_pCommand = NULL;
	m_pRecordset = NULL;
	m_bIsConnected = FALSE;
	m_bIsRecordOpened = FALSE;
}

BOOL CDatabaseConnection::OpenDB()
{
	// Define string variables for connection
	_bstr_t strCon("Provider='SQLOLEDB.1';Persist Security Info='False';Initial Catalog='StudentManagement';Data Source='DESKTOP-RLFPHMT\\SQLEXPRESS';Integrated Security='SSPI';");
	//_bstr_t strCon("Provider=SQLOLEDB.1;Persist Security Info=False;User ID=username;Password=password;Initial Catalog=databasename;Data Source=(local);Integrated Security=SSPI;");
	
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
		hr = m_pConnection->Open(strCon, "", "", 0);
		if (FAILED(hr))
		{
			AfxMessageBox(L"Error Opening Database object\n");
			CoUninitialize();
			return FALSE;
		}
		//AfxMessageBox(L"Opening Database OK");
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
	if (m_bIsRecordOpened)
	{
		m_pRecordset->Close();
	}
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

BOOL CDatabaseConnection::SQLSetDataExecute(CString strSQLquery)
{
	// Create Command Object
	_variant_t  vtRecordsAffected;
	m_pCommand.CreateInstance(__uuidof(Command));
	m_pCommand->ActiveConnection = m_pConnection;
	m_pCommand->CommandTimeout = 0;

	// Create a test table
	m_pCommand->CommandText = _bstr_t(strSQLquery);
	
	try
	{
		m_pCommand->Execute(&vtRecordsAffected, NULL, adCmdText);
		return TRUE;
	}
	catch (_com_error & ce)
	{
		CString strTemp = ce.Description();
		AfxMessageBox(strTemp);
		return FALSE;
	}
}

void CDatabaseConnection::SQLGetDataExecute(CString strSQLquery)
{
	// Create Command Object
	m_pCommand.CreateInstance(__uuidof(Command));
	m_pCommand->ActiveConnection = m_pConnection;
	m_pCommand->CommandTimeout = 0;

	// Create a Recordset Object
	_variant_t  vtEmpty(DISP_E_PARAMNOTFOUND, VT_ERROR);
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	m_pRecordset->CursorLocation = adUseServer;

	m_pCommand->CommandText = _bstr_t(strSQLquery);

	m_pRecordset->PutRefSource(m_pCommand);
	
	try
	{
		m_pRecordset->Open(vtEmpty, vtEmpty, adOpenStatic, adLockReadOnly, adCmdText);
		m_bIsRecordOpened = TRUE;
	}
	catch (_com_error & ce)
	{
		CString strTemp = ce.Description();
		AfxMessageBox(strTemp);
	}
	return;
}

std::vector<CStudent> CDatabaseConnection::GetStudentInfo()
{
	CString strSQL = _T("SELECT * FROM dbo.QLSV");
	SQLGetDataExecute(strSQL);

	std::vector<CStudent> vtListStudent;
	try
	{
		m_pRecordset->MoveFirst();
		//Loop through the Record set
		if (!m_pRecordset->EndOfFile)
		{
			while (!m_pRecordset->EndOfFile)
			{
				CStudent student;
				student.SetStudentID(m_pRecordset->Fields->GetItem("StudentID")->Value.intVal);
				student.SetName(m_pRecordset->Fields->GetItem("Name")->Value);
				student.SetAge(m_pRecordset->Fields->GetItem("Age")->Value.intVal);
				student.SetSex(m_pRecordset->Fields->GetItem("Sex")->Value);
				student.SetPhone(m_pRecordset->Fields->GetItem("PhoneNumber")->Value);
				vtListStudent.push_back(student);
				m_pRecordset->MoveNext();
			}
		}
	}
	catch (_com_error & ce)
	{
		CString strTemp = ce.Description();
		AfxMessageBox(strTemp);
	}
	return vtListStudent;
}
