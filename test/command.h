#pragma once
#include "eventcommon.h"

enum EEventType
{
	ET_NULL,

	ET_Query_UserName,
	ET_Query_UserSex,
	ET_Query_UserAge,

	ET_Reply_UserName,
	ET_Reply_UserSex,
	ET_Reply_UserAge,
};

class StringData : public Data
{
public:
	StringData();

	std::string m_str;
};
