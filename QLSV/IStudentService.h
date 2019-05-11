#pragma once
#include "stdafx.h"
#include "Student.h"
#include <vector>

class IStudentService
{
public:
	virtual BOOL OpenDB() = 0;
	virtual BOOL CloseDB() = 0;
	virtual std::vector<CStudent> GetStudentInfo() = 0;
};