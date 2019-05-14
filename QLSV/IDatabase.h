#pragma once

#include "stdafx.h"
#include <vector>
#include "Student.h"


//Dinh nghia cac phuong thuc service goi
class IDatabase
{
public:
	virtual BOOL OpenDB() = 0;
	virtual BOOL CloseDB() = 0;
	virtual std::vector<CStudent> GetStudentInfo() = 0;
	virtual BOOL AddStudent(CStudent student) = 0; 
	virtual BOOL EditStudent(CStudent student) = 0;
	virtual BOOL DeleteStudent(int iId) = 0;
};