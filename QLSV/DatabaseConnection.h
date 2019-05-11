#include "stdafx.h"

#pragma once
#import "msado15.dll" no_namespace rename("EOF", "EndOfFile")

class CDatabaseConnection
{
public:
	CDatabaseConnection();
	~CDatabaseConnection();
private:
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRescordset;
	BOOL m_bIsConnected;
public:
	BOOL OpenDB();
	BOOL CloseDB();
	BOOL ExecuteSQL();
};

