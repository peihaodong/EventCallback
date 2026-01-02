#include <QtWidgets/QApplication>
#include "application.h"
#include "mainwindow.h"
#include "module.h"
#include <memory>
#include "eventmanager.h"

int main(int argc, char *argv[])
{
	Application a(argc, argv);

	EventManager_UI::GetInstance()->SetUINotify([&](PEventInfo info) {
		a.DoUITask(info);
	});

	std::shared_ptr<Module> m = std::make_shared<Module>();

	MainWindow w;
	w.show();

    return a.exec();
}
