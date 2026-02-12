#pragma once
#include <QWidget>
#include "ui_more.h"

class MoreUi : public QWidget
{
	Q_OBJECT
public:
	MoreUi();
	~MoreUi();

	Ui::Form ui;
};