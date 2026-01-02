#include "module.h"
#include "eventmanager.h"
#include "command.h"
#include <QSettings>

Module::Module(QObject *parent /*= nullptr*/)
	: QObject(parent)
{
	Init();
}

Module::~Module()
{
	auto manager = EventManager_SpecifyThread::GetInstance();
	manager->Cancel(ET_Query_UserName);
	manager->Cancel(ET_Query_UserSex);
	manager->Cancel(ET_Query_UserAge);
}

void Module::cmdQuertName(const PEventInfo& info)
{
	if (!info->m_data)
		return;
	std::shared_ptr<StringData> data = std::dynamic_pointer_cast<StringData>(info->m_data);
	if (!data)
		return;

	QSettings settings(QString::fromStdString(data->m_str), QSettings::IniFormat);
	QString strValue = settings.value("User/Name").toString();

	PEventInfo cmd = EventInfo::Create(ET_Reply_UserName);
	cmd->m_informer = this;
	std::shared_ptr<StringData> dataReply = std::make_shared<StringData>();
	dataReply->m_str = strValue.toStdString();
	cmd->m_data = dataReply;
	EventManager_UI::GetInstance()->Notify(cmd);
}

void Module::cmdQuertSex(const PEventInfo& info)
{
	if (!info->m_data)
		return;
	std::shared_ptr<StringData> data = std::dynamic_pointer_cast<StringData>(info->m_data);
	if (!data)
		return;

	QSettings settings(QString::fromStdString(data->m_str), QSettings::IniFormat);
	QString strValue = settings.value("User/Sex").toString();

	PEventInfo cmd = EventInfo::Create(ET_Reply_UserSex);
	cmd->m_informer = this;
	std::shared_ptr<StringData> dataReply = std::make_shared<StringData>();
	dataReply->m_str = strValue.toStdString();
	cmd->m_data = dataReply;
	EventManager_UI::GetInstance()->Notify(cmd);
}

void Module::cmdQuertAge(const PEventInfo& info)
{
	if (!info->m_data)
		return;
	std::shared_ptr<StringData> data = std::dynamic_pointer_cast<StringData>(info->m_data);
	if (!data)
		return;

	QSettings settings(QString::fromStdString(data->m_str), QSettings::IniFormat);
	QString strValue = settings.value("User/Age").toString();

	PEventInfo cmd = EventInfo::Create(ET_Reply_UserAge);
	cmd->m_informer = this;
	std::shared_ptr<StringData> dataReply = std::make_shared<StringData>();
	dataReply->m_str = strValue.toStdString();
	cmd->m_data = dataReply;
	EventManager_UI::GetInstance()->Notify(cmd);
}

void Module::Init()
{
	auto manager = EventManager_SpecifyThread::GetInstance();
	manager->Register<Module>(ET_Query_UserName, this, &Module::cmdQuertName);
	manager->Register<Module>(ET_Query_UserSex, this, &Module::cmdQuertSex);
	manager->Register<Module>(ET_Query_UserAge, this, &Module::cmdQuertAge);
}
