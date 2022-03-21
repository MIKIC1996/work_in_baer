#pragma once


#include "SunnyTcsSupervisoryV3_general.h"

class SunnyTcsActionTableWidget;

class SunnyTcsActionTableHeaderView : public QHeaderView
{
	Q_OBJECT
public:
	friend class SunnyTcsActionTableWidget;

	SunnyTcsActionTableHeaderView(
		Qt::Orientation orientation = Qt::Horizontal,
		QWidget * parent = 0) :
		QHeaderView(orientation, parent)
	{

	}

	// 获取当前comboBox文字;
	QString getCurrentComboBoxText(int i)
	{
		return _paramsComboBox.at(i)->currentText();
	}

protected:
	void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
	{
		if (logicalIndex == 0)
		{
			QHeaderView::paintSection(painter, rect, logicalIndex);
		}
		else
		{
			if (logicalIndex >= _paramsComboBox.count()) {
				QHeaderView::paintSection(painter, rect, logicalIndex);
			}
			else {
				_paramsComboBox.at(logicalIndex)->setGeometry(rect);
			}
		}
	}

private:
	QList<QComboBox*> _paramsComboBox;
};



class SunnyTcsActionTableWidget : public QTableWidget {
	Q_OBJECT
public:
	SunnyTcsActionTableWidget(QWidget* parent = nullptr) :QTableWidget(parent) {

		this->setAlternatingRowColors(true);
		this->setColumnCount(7);
		this->setSelectionMode(QAbstractItemView::SingleSelection);
		this->setEditTriggers(QAbstractItemView::NoEditTriggers);
		this->setSelectionBehavior(QAbstractItemView::SelectRows);

		_headView = new SunnyTcsActionTableHeaderView();
		this->setHorizontalHeader(_headView);
		this->setHorizontalHeaderLabels(QStringList() << "指令名");

		for (int i = 0; i < 7; ++i) {
			QComboBox* cbox = new QComboBox(parent);
			cbox->addItem("111");
			cbox->addItem("222");
			cbox->addItem("333");
			_headView->_paramsComboBox.append(cbox);
		}
	}


	SunnyTcsActionTableHeaderView* _headView;

protected:

};
