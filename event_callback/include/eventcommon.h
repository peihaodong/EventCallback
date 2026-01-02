#pragma once
/***********************************************
   > Author: 裴浩东
   > Date: 2026.01.02
   > GitHub: https://github.com/peihaodong/EventCallback.git
   > Remark: 如果对你有帮助，请帮我在GitHub上点个Star
**********************************************/

#include <QtGlobal>
#include <memory>
#include <string>
#include <functional>
#include <string>

class Q_DECL_EXPORT Data : public std::enable_shared_from_this<Data>
{
public:
	Data();
	virtual ~Data();

protected:
	std::string m_strClassName;
};
using PData = std::shared_ptr<Data>;

struct Q_DECL_EXPORT EventInfo
{
public:
	explicit EventInfo(uint32_t nEventType);
	~EventInfo();

	static std::shared_ptr<EventInfo> Create(uint32_t nEventType);

	uint32_t m_nEventType = 0;	//事件类型
	PData m_data;				//事件所携带的数据
	void* m_informer = nullptr;	//事件的通知者this指针
};
using PEventInfo = std::shared_ptr<EventInfo>;

//类函数指针
template<typename T>
using EventCallback = void(T::*)(const PEventInfo&);