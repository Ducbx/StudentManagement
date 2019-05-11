#include "stdafx.h"
#include "Student.h"

CStudent::CStudent()
{
	m_iStudentID = 0;
	m_strName = "";
	m_strSex = "";
	m_strPhone = "";
	m_iAge = 0;
}

CStudent::~CStudent()
{

}

CStudent::CStudent(int iStudentID, CString strName, CString strSex, int iAge, CString strPhone)
{
	m_iStudentID = iStudentID;
	m_strName = strName;
	m_strSex = strSex;
	m_iAge = iAge;
	m_strPhone = strPhone;
}

CString CStudent::GetName()
{
	return m_strName;
}

void CStudent::SetName(CString strName)
{
	m_strName = strName;
}

CString CStudent::GetSex()
{
	return m_strSex;
}

void CStudent::SetSex(CString strSex)
{
	m_strSex = strSex;
}

CString CStudent::GetPhone()
{
	return m_strPhone;
}

void CStudent::SetPhone(CString strPhone)
{
	m_strPhone = strPhone;
}

int CStudent::GetAge()
{
	return m_iAge;
}

void CStudent::SetAge(int iAge)
{
	m_iAge = iAge;
}

int CStudent::GetStudentID()
{
	return m_iStudentID;
}

void CStudent::SetStudentID(int iStudentID)
{
	m_iStudentID = iStudentID;
}