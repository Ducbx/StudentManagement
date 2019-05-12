#pragma once

#include "stdafx.h"
#include "Student.h"
#include <vector>
#include "IDatabase.h"


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
	BOOL SQLSetDataExecute(CString strSQLquery);
	void SQLGetDataExecute(CString strSQLquery);
	_RecordsetPtr GetRecordset();

	virtual std::vector<CStudent> GetStudentInfo();
	virtual BOOL OpenDB();
	virtual BOOL CloseDB();
	virtual BOOL AddStudent(CStudent student);
};

