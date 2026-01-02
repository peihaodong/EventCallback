#include "eventmanager.h"

/***********************************************
   > Author: 裴浩东
   > Date: 2026.01.02
   > GitHub: https://github.com/peihaodong/EventCallback.git
   > Remark: 如果对你有帮助，请帮我在GitHub上点个Star
**********************************************/

EventManager_Sync::~EventManager_Sync()
{
	m_manager->Release();
}

EventManager_Sync* EventManager_Sync::GetInstance()
{
	static EventManager_Sync inst;
	return &inst;
}

uint64_t EventManager_Sync::Register(uint32_t nEventType, const std::function<void(const PEventInfo&)>& callback)
{
	return m_manager->Register(nEventType, callback);
}

void EventManager_Sync::Cancel(uint32_t nEventType, uint64_t nEventID)
{
	m_manager->Cancel(nEventType, nEventID);
}

void EventManager_Sync::Cancel(uint32_t nEventType)
{
	m_manager->Cancel(nEventType);
}

void EventManager_Sync::Notify(const PEventInfo& info)
{
	m_manager->Notify(info);
}

EventManager_Sync::EventManager_Sync()
{
	m_manager = std::make_shared<EventManager>(EEventManagerType::EMT_Sync);
}

EventManager_ThreadPool::~EventManager_ThreadPool()
{
	m_manager->Release();
}

EventManager_ThreadPool* EventManager_ThreadPool::GetInstance()
{
	static EventManager_ThreadPool inst;
	return &inst;
}

uint64_t EventManager_ThreadPool::Register(uint32_t nEventType, const std::function<void(const PEventInfo&)>& callback)
{
	return m_manager->Register(nEventType, callback);
}

void EventManager_ThreadPool::Cancel(uint32_t nEventType, uint64_t nEventID)
{
	m_manager->Cancel(nEventType, nEventID);
}

void EventManager_ThreadPool::Cancel(uint32_t nEventType)
{
	m_manager->Cancel(nEventType);
}

void EventManager_ThreadPool::Notify(const PEventInfo& info)
{
	m_manager->Notify(info);
}

EventManager_ThreadPool::EventManager_ThreadPool()
{
	m_manager = std::make_shared<EventManager>(EEventManagerType::EMT_ThreadPool);
}

EventManager_SpecifyThread::~EventManager_SpecifyThread()
{
	m_manager->Release();
}

EventManager_SpecifyThread* EventManager_SpecifyThread::GetInstance()
{
	static EventManager_SpecifyThread inst;
	return &inst;
}

uint64_t EventManager_SpecifyThread::Register(uint32_t nEventType, const std::function<void(const PEventInfo&)>& callback)
{
	return m_manager->Register(nEventType, callback);
}

void EventManager_SpecifyThread::Cancel(uint32_t nEventType, uint64_t nEventID)
{
	m_manager->Cancel(nEventType, nEventID);
}

void EventManager_SpecifyThread::Cancel(uint32_t nEventType)
{
	m_manager->Cancel(nEventType);
}

void EventManager_SpecifyThread::Notify(uint32_t nThreadIndex, const PEventInfo& info)
{
	m_manager->Notify(info, nThreadIndex);
}

EventManager_SpecifyThread::EventManager_SpecifyThread()
{
	m_manager = std::make_shared<EventManager>(EEventManagerType::EMT_SpecifyThread);
}

EventManager_UI::~EventManager_UI()
{
	m_manager->Release();
}

EventManager_UI* EventManager_UI::GetInstance()
{
	static EventManager_UI inst;
	return &inst;
}

void EventManager_UI::SetUINotify(const std::function<void(PEventInfo)>& notify)
{
	m_manager->SetUINotify(notify);
}

void EventManager_UI::DoUITask(const PEventInfo& info)
{
	m_manager->DoUITask(info);
}

uint64_t EventManager_UI::Register(uint32_t nEventType, const std::function<void(const PEventInfo&)>& callback)
{
	return m_manager->Register(nEventType, callback);
}

void EventManager_UI::Cancel(uint32_t nEventType, uint64_t nEventID)
{
	m_manager->Cancel(nEventType, nEventID);
}

void EventManager_UI::Cancel(uint32_t nEventType)
{
	m_manager->Cancel(nEventType);
}

void EventManager_UI::Notify(const PEventInfo& info)
{
	m_manager->Notify(info);
}

EventManager_UI::EventManager_UI()
{
	m_manager = std::make_shared<EventManager>(EEventManagerType::EMT_UI);
}
