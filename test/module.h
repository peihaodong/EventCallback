#pragma once

#include <QObject>
#include "eventcommon.h"

class Module  : public QObject
{
	Q_OBJECT

public:
	Module(QObject *parent = nullptr);
	~Module();

protected:
	void cmdQuertName(const PEventInfo& info);
	void cmdQuertSex(const PEventInfo& info);
	void cmdQuertAge(const PEventInfo& info);

protected:
	void Init();

protected:
	std::map<uint32_t, uint64_t> m_mapRegister;
};
