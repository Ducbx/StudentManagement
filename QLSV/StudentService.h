#pragma once
#include "Student.h"
#include "stdafx.h"
#include <vector>
#include "IStudentService.h"
#include "IDatabase.h"
//Dinh nghia cac ham ma UI goi -> proxy - ket noi UI va DB
//Gom data, tien xu ly

class CStudentService : public IStudentService
{
public:
	CStudentService(IDatabase *dbConnection);
	~CStudentService();
public:
	virtual BOOL OpenDB();
	virtual BOOL CloseDB();
	virtual std::vector<CStudent> GetStudentInfo();
	virtual BOOL AddStudent(CStudent student);
	virtual BOOL EditStudent(CStudent student);
	virtual BOOL DeleteStudent(int iId);
private:
	IDatabase *m_dbConnection;
};

