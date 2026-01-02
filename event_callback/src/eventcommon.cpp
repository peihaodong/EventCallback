#include "eventcommon.h"

/***********************************************
   > Author: 裴浩东
   > Date: 2026.01.02
   > GitHub: https://github.com/peihaodong/EventCallback.git
   > Remark: 如果对你有帮助，请帮我在GitHub上点个Star
**********************************************/

Data::Data()
	:m_strClassName("Data")
{

}

Data::~Data()
{

}

EventInfo::EventInfo(uint32_t nEventType)
	:m_nEventType(nEventType)
{

}

EventInfo::~EventInfo()
{

}

std::shared_ptr<EventInfo> EventInfo::Create(uint32_t nEventType)
{
	return std::make_shared<EventInfo>(nEventType);
}