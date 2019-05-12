#include "stdafx.h"
#include "StudentService.h"


CStudentService::CStudentService(IDatabase *dbConnection)
{
	m_dbConnection = dbConnection;
}


CStudentService::~CStudentService()
{

}

BOOL CStudentService::OpenDB()
{
	m_dbConnection->OpenDB();
	return TRUE;
}

BOOL CStudentService::CloseDB()
{
	m_dbConnection->CloseDB();
	return TRUE;
}

std::vector<CStudent> CStudentService::GetStudentInfo()
{
	std::vector<CStudent> studentList;
	studentList = m_dbConnection->GetStudentInfo();
	return studentList;
}

BOOL CStudentService::AddStudent(CStudent student)
{
	m_dbConnection->AddStudent(student);
	return TRUE;
}