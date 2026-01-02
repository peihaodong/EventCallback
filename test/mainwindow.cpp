#include "mainwindow.h"
#include <QSettings>
#include "command.h"
#include "eventmanager.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindowClass())
{
	ui->setupUi(this);

	m_strIniPath = QCoreApplication::applicationDirPath() + "/user_info.ini";

	Init();
}

MainWindow::~MainWindow()
{
	delete ui;

	auto manager = EventManager_UI::GetInstance();
	manager->Cancel(ET_Reply_UserName);
	manager->Cancel(ET_Reply_UserSex);
	manager->Cancel(ET_Reply_UserAge);
}

void MainWindow::Init()
{
	connect(ui->pbName, &QPushButton::clicked, this, &MainWindow::slotNameClicked);
	connect(ui->pbSex, &QPushButton::clicked, this, &MainWindow::slotSexClicked);
	connect(ui->pbAge, &QPushButton::clicked, this, &MainWindow::slotAgeClicked);

	auto manager = EventManager_UI::GetInstance();
	manager->Register<MainWindow>(ET_Reply_UserName, this, &MainWindow::cmdReplyLabel);
	manager->Register<MainWindow>(ET_Reply_UserSex, this, &MainWindow::cmdReplyLabel);
	manager->Register<MainWindow>(ET_Reply_UserAge, this, &MainWindow::cmdReplyLabel);
}

void MainWindow::slotNameClicked()
{
	PEventInfo cmd = EventInfo::Create(ET_Query_UserName);
	cmd->m_informer = this;
	std::shared_ptr<StringData> data = std::make_shared<StringData>();
	data->m_str = m_strIniPath.toStdString();
	cmd->m_data = data;
	EventManager_SpecifyThread::GetInstance()->Notify(0, cmd);
}

void MainWindow::slotSexClicked()
{
	PEventInfo cmd = EventInfo::Create(ET_Query_UserSex);
	cmd->m_informer = this;
	std::shared_ptr<StringData> data = std::make_shared<StringData>();
	data->m_str = m_strIniPath.toStdString();
	cmd->m_data = data;
	EventManager_SpecifyThread::GetInstance()->Notify(0, cmd);
}

void MainWindow::slotAgeClicked()
{
	PEventInfo cmd = EventInfo::Create(ET_Query_UserAge);
	cmd->m_informer = this;
	std::shared_ptr<StringData> data = std::make_shared<StringData>();
	data->m_str = m_strIniPath.toStdString();
	cmd->m_data = data;
	EventManager_SpecifyThread::GetInstance()->Notify(0, cmd);
}

void MainWindow::cmdReplyLabel(const PEventInfo& info)
{
	if (!info->m_data)
		return;
	std::shared_ptr<StringData> data = std::dynamic_pointer_cast<StringData>(info->m_data);
	if (!data)
		return;

	QString str = QString::fromStdString(data->m_str);
	ui->label->setText(str);
}


