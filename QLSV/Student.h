#pragma once
class CStudent
{
public:
	CStudent();
	~CStudent();
	CStudent(int iStudentID, CString strName, CString strSex, int iAge, CString strPhone);
private:
	int m_iStudentID;
	CString m_strName;
	CString m_strSex;
	CString m_strPhone;
	int m_iAge;
public:
	int GetStudentID();
	void SetStudentID(int iStudentID);
	CString GetName();
	void SetName(CString strName);
	CString GetSex();
	void SetSex(CString strSex);
	CString GetPhone();
	void SetPhone(CString strPhone);
	int GetAge();
	void SetAge(int iAge);
};

