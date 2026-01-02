#pragma once

#include <QApplication>
#include "eventcommon.h"

class Application  : public QApplication
{
	Q_OBJECT

public:
#ifdef Q_QDOC
	Application(int &argc, char **argv);
#else
	Application(int &argc, char **argv, int flags = ApplicationFlags);
#endif
	~Application();

	void DoUITask(PEventInfo info);

signals:
	void signalDoUITask(PEventInfo info);

protected slots:
	void slotDoUITask(PEventInfo info);
};
