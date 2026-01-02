#pragma once
/***********************************************
   > Author: 裴浩东
   > Date: 2026.01.02
   > GitHub: https://github.com/peihaodong/EventCallback.git
   > Remark: 如果对你有帮助，请帮我在GitHub上点个Star
**********************************************/

#include "eventcommon.h"
#include "event.h"

//事件管理者_同步
class Q_DECL_EXPORT EventManager_Sync
{
public:
	~EventManager_Sync();

	static EventManager_Sync* GetInstance();

	//注册
	template<typename T>
	uint64_t Register(uint32_t nEventType, T* pThis, EventCallback<T> pCallback);
	uint64_t Register(uint32_t nEventType, const std::function<void(const PEventInfo&)>& callback);

	//取消
	template<typename T>
	void Cancel(uint32_t nEventType, T* pThis, EventCallback<T> pCallback);
	template<typename T>
	void Cancel(uint32_t nEventType, T* pThis);
	void Cancel(uint32_t nEventType, uint64_t nEventID);
	void Cancel(uint32_t nEventType);

	//通知
	void Notify(const PEventInfo& info);

protected:
	EventManager_Sync();

protected:
	std::shared_ptr<EventManager> m_manager;
};

template<typename T>
uint64_t EventManager_Sync::Register(uint32_t nEventType, T* pThis, EventCallback<T> pCallback)
{
	return m_manager->Register(nEventType, pThis, pCallback);
}

template<typename T>
void EventManager_Sync::Cancel(uint32_t nEventType, T* pThis, EventCallback<T> pCallback)
{
	m_manager->Cancel(nEventType, pThis, pCallback);
}

template<typename T>
void EventManager_Sync::Cancel(uint32_t nEventType, T* pThis)
{
	m_manager->Cancel(nEventType, pThis);
}

//////////////////////////////////////////////////////////////////////////

//事件管理者_线程池
class Q_DECL_EXPORT EventManager_ThreadPool
{
public:
	~EventManager_ThreadPool();

	static EventManager_ThreadPool* GetInstance();

	//注册
	template<typename T>
	uint64_t Register(uint32_t nEventType, T* pThis, EventCallback<T> pCallback);
	uint64_t Register(uint32_t nEventType, const std::function<void(const PEventInfo&)>& callback);

	//取消
	template<typename T>
	void Cancel(uint32_t nEventType, T* pThis, EventCallback<T> pCallback);
	template<typename T>
	void Cancel(uint32_t nEventType, T* pThis);
	void Cancel(uint32_t nEventType, uint64_t nEventID);
	void Cancel(uint32_t nEventType);

	//通知
	void Notify(const PEventInfo& info);

protected:
	EventManager_ThreadPool();

protected:
	std::shared_ptr<EventManager> m_manager;
};

template<typename T>
uint64_t EventManager_ThreadPool::Register(uint32_t nEventType, T* pThis, EventCallback<T> pCallback)
{
	return m_manager->Register(nEventType, pThis, pCallback);
}

template<typename T>
void EventManager_ThreadPool::Cancel(uint32_t nEventType, T* pThis, EventCallback<T> pCallback)
{
	m_manager->Cancel(nEventType, pThis, pCallback);
}

template<typename T>
void EventManager_ThreadPool::Cancel(uint32_t nEventType, T* pThis)
{
	m_manager->Cancel(nEventType, pThis);
}

//////////////////////////////////////////////////////////////////////////

//事件管理者_指定线程
class Q_DECL_EXPORT EventManager_SpecifyThread
{
public:
	~EventManager_SpecifyThread();

	static EventManager_SpecifyThread* GetInstance();

	//注册
	template<typename T>
	uint64_t Register(uint32_t nEventType, T* pThis, EventCallback<T> pCallback);
	uint64_t Register(uint32_t nEventType, const std::function<void(const PEventInfo&)>& callback);

	//取消
	template<typename T>
	void Cancel(uint32_t nEventType, T* pThis, EventCallback<T> pCallback);
	template<typename T>
	void Cancel(uint32_t nEventType, T* pThis);
	void Cancel(uint32_t nEventType, uint64_t nEventID);
	void Cancel(uint32_t nEventType);

	//通知
	void Notify(uint32_t nThreadIndex, const PEventInfo& info);

protected:
	EventManager_SpecifyThread();

protected:
	std::shared_ptr<EventManager> m_manager;
};

template<typename T>
uint64_t EventManager_SpecifyThread::Register(uint32_t nEventType, T* pThis, EventCallback<T> pCallback)
{
	return m_manager->Register(nEventType, pThis, pCallback);
}

template<typename T>
void EventManager_SpecifyThread::Cancel(uint32_t nEventType, T* pThis, EventCallback<T> pCallback)
{
	return m_manager->Cancel(nEventType, pThis, pCallback);
}

template<typename T>
void EventManager_SpecifyThread::Cancel(uint32_t nEventType, T* pThis)
{
	m_manager->Cancel(nEventType, pThis);
}

//////////////////////////////////////////////////////////////////////////

//事件管理者_UI
class Q_DECL_EXPORT EventManager_UI
{
public:
	~EventManager_UI();

	static EventManager_UI* GetInstance();

	void SetUINotify(const std::function<void(PEventInfo)>& notify);
	void DoUITask(const PEventInfo& info);

	//注册
	template<typename T>
	uint64_t Register(uint32_t nEventType, T* pThis, EventCallback<T> pCallback);
	uint64_t Register(uint32_t nEventType, const std::function<void(const PEventInfo&)>& callback);

	//取消
	template<typename T>
	void Cancel(uint32_t nEventType, T* pThis, EventCallback<T> pCallback);
	template<typename T>
	void Cancel(uint32_t nEventType, T* pThis);
	void Cancel(uint32_t nEventType, uint64_t nEventID);
	void Cancel(uint32_t nEventType);

	//通知
	void Notify(const PEventInfo& info);

protected:
	EventManager_UI();

protected:
	std::shared_ptr<EventManager> m_manager;
};

template<typename T>
uint64_t EventManager_UI::Register(uint32_t nEventType, T* pThis, EventCallback<T> pCallback)
{
	return m_manager->Register(nEventType, pThis, pCallback);
}

template<typename T>
void EventManager_UI::Cancel(uint32_t nEventType, T* pThis, EventCallback<T> pCallback)
{
	return m_manager->Cancel(nEventType, pThis, pCallback);
}

template<typename T>
void EventManager_UI::Cancel(uint32_t nEventType, T* pThis)
{
	m_manager->Cancel(nEventType, pThis);
}
