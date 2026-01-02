#include "application.h"
#include "eventmanager.h"

#ifdef Q_QDOC
Application::Application(int &argc, char **argv)
	: QApplication(argc, argv)
{
	qRegisterMetaType<PEventInfo>("PEventInfo");
	connect(this, &Application::signalDoUITask, this, &Application::slotDoUITask);
}
#else
Application::Application(int &argc, char **argv, int flags /*= ApplicationFlags*/)
	: QApplication(argc, argv, flags)
{
	qRegisterMetaType<PEventInfo>("PEventInfo");
	connect(this, &Application::signalDoUITask, this, &Application::slotDoUITask);
}
#endif

Application::~Application()
{}

void Application::DoUITask(PEventInfo info)
{
	emit signalDoUITask(info);
}

void Application::slotDoUITask(PEventInfo info)
{
	EventManager_UI::GetInstance()->DoUITask(info);
}
