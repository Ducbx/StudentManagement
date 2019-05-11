#include "stdafx.h"
#include "Student.h"
#include <vector>
#include "IDatabase.h"

#pragma once
#import "msado15.dll" no_namespace rename("EOF", "EndOfFile")

class CDatabaseConnection : public IDatabase
{
public:
	CDatabaseConnection();
	~CDatabaseConnection();
private:
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;
	BOOL m_bIsConnected;
	BOOL m_bIsRecordOpened;
public:
	BOOL OpenDB();
	BOOL CloseDB();
	BOOL SQLSetDataExecute(CString strSQLquery);
	void SQLGetDataExecute(CString strSQLquery);
	std::vector<CStudent> GetStudentInfo();
	_RecordsetPtr GetRecordset();
};

