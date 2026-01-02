#include "event.h"
#include <atomic>
#include "threadpool.h"

/***********************************************
   > Author: 裴浩东
   > Date: 2026.01.02
   > GitHub: https://github.com/peihaodong/EventCallback.git
   > Remark: 如果对你有帮助，请帮我在GitHub上点个Star
**********************************************/

bool Listener::FunctionPointerDescriptor::operator==(const FunctionPointerDescriptor& obj) const
{
	if (m_size != obj.m_size)
		return false;
	if (m_addr && obj.m_addr)
	{
		if (memcmp(m_addr, obj.m_addr, m_size) != 0)
			return false;
	}
	return true;
}

Listener::Listener()
{

}

Listener::~Listener()
{
	if (m_desc.m_addr)
		free(m_desc.m_addr);
}

Listener::Ptr Listener::Create()
{
	return std::make_shared<Listener>();
}

EventManager::EventManager(EEventManagerType type)
{
	m_type = type;

	if (m_type == EEventManagerType::EMT_ThreadPool)
	{
		m_tp = ThreadPool::New(3);
	}
	else if (m_type == EEventManagerType::EMT_SpecifyThread)
	{
		m_tp_s = ThreadPool_Specify::New(3);
	}
}

EventManager::~EventManager()
{

}

uint64_t EventManager::Register(uint32_t nEventType, const std::function<void(const PEventInfo&)>& callback)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	//在事件监听队列集合中找到指定事件的监听队列
	auto iterListeners = m_mapListeners.find(nEventType);
	if (iterListeners == m_mapListeners.end())
		iterListeners = (m_mapListeners.insert(std::make_pair(nEventType, std::vector<Listener::Ptr>()))).first;
	std::vector<Listener::Ptr>& vecListener = iterListeners->second;
	
	//创建监听者并赋值
	Listener::Ptr listener = Listener::Create();
	listener->m_func = callback;
	listener->m_nEventID = GetUniqueId();
	//判断该指定事件监听队列是否存在相同的监听者
	{
		auto iterListener = std::find_if(vecListener.begin(), vecListener.end(), [&](const Listener::Ptr& obj) {
			return listener->m_nEventID == obj->m_nEventID;
		});
		if (iterListener != vecListener.end())
			return 0;
	}

	vecListener.push_back(listener);

	return listener->m_nEventID;
}

void EventManager::Cancel(uint32_t nEventType, uint64_t nEventID)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	//在事件监听队列集合中找到指定事件的监听队列
	auto iterListeners = m_mapListeners.find(nEventType);
	if (iterListeners == m_mapListeners.end())
		return;
	std::vector<Listener::Ptr>& vecListener = iterListeners->second;

	//创建监听者并赋值
	Listener::Ptr listener = Listener::Create();
	listener->m_nEventID = nEventID;
	//找到指定事件监听队列中的监听者，并移除
	auto iterListener = std::find_if(vecListener.begin(), vecListener.end(), [&](const Listener::Ptr& obj) {
		return listener->m_nEventID == obj->m_nEventID;
	});
	if (iterListener != vecListener.end())
		vecListener.erase(iterListener);
}

void EventManager::Cancel(uint32_t nEventType)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	//在事件监听队列集合中找到指定事件的监听队列
	auto iterListeners = m_mapListeners.find(nEventType);
	if (iterListeners == m_mapListeners.end())
		return;
	m_mapListeners.erase(iterListeners);
}

void EventManager::Notify(const PEventInfo& info, uint32_t nThreadIndex /*= 0*/)
{
	if (m_type == EEventManagerType::EMT_UI)
	{
		if (m_funcUINotify)
			m_funcUINotify(info);
		return;
	}

	std::unique_lock<std::mutex> lock(m_mutex);

	//在事件监听队列集合中找到指定事件的监听队列
	auto iterListenerQueue = m_mapListeners.find(info->m_nEventType);
	if (iterListenerQueue == m_mapListeners.end())
		return;
	std::vector<Listener::Ptr>& listener_queue = iterListenerQueue->second;
	//执行回调函数
	if (m_type == EEventManagerType::EMT_ThreadPool)
	{
		m_tp->Submit([=]() {
			for (const Listener::Ptr& listener : listener_queue)
			{
				listener->m_func(info);
			}
		});
	}
	else if (m_type == EEventManagerType::EMT_SpecifyThread)
	{
		m_tp_s->Submit(nThreadIndex, [=]() {
			for (const Listener::Ptr& listener : listener_queue)
			{
				listener->m_func(info);
			}
		});
	}
	else
	{
		for (const Listener::Ptr& listener : listener_queue)
		{
			listener->m_func(info);
		}
	}
}

void EventManager::Release()
{
	std::unique_lock<std::mutex> lock(m_mutex);

	if (m_type == EEventManagerType::EMT_ThreadPool)
	{
		m_tp->Release();
	}
	else if (m_type == EEventManagerType::EMT_SpecifyThread)
	{
		m_tp_s->Release();
	}

	m_mapListeners.clear();
}

void EventManager::SetUINotify(const std::function<void(PEventInfo)>& notify)
{
	m_funcUINotify = notify;
}

void EventManager::DoUITask(const PEventInfo& info)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	//在事件监听队列集合中找到指定事件的监听队列
	auto iterListenerQueue = m_mapListeners.find(info->m_nEventType);
	if (iterListenerQueue == m_mapListeners.end())
		return;
	std::vector<Listener::Ptr>& listener_queue = iterListenerQueue->second;
	for (const Listener::Ptr& listener : listener_queue)
	{
		listener->m_func(info);
	}
}

bool EventManager::ListenerIsEqual(const Listener::Ptr& listener1, const Listener::Ptr& listener2)
{
	return listener1->m_this == listener2->m_this && listener1->m_desc == listener2->m_desc;
}

uint64_t EventManager::GetUniqueId() const
{
	static std::atomic<uint64_t> id = 0;
	id++;
	return id;
}
