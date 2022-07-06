#include "SunnyTcsLocationEditWidget.h"



SunnyTcsLocationEditWidget::SunnyTcsLocationEditWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.addLineTbtn, SIGNAL(clicked()), this, SLOT(onAddTbtnClicked()));
	connect(ui.decLineTbtn, SIGNAL(clicked()), this, SLOT(onDecTbtnClicked()));
	connect(ui.clearLineTbtn, SIGNAL(clicked()), this, SLOT(onClearTbtnClicked()));

	connect(ui.saveTbtn, SIGNAL(clicked()), this, SLOT(onSaveBtnClicked()));
	connect(ui.resetTbtn, SIGNAL(clicked()), this, SLOT(onResetBtnClicked()));

}

void SunnyTcsLocationEditWidget::init(SunnyTcsGraphicsLocation * loc)
{
	Q_ASSERT(loc);
	_currentLoc = loc;
	onClearTbtnClicked(); // 清除所有
	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(0);
	QVector<E_ARG_TYPE> paramTypes = loc->getParamsType();
	qint32 paramTypeCount = paramTypes.count();


	ui.tableWidget->setColumnCount(paramTypeCount + 1);
	QStringList headerList;
	headerList << QSTRING_GBK("指令码");
	for (int i = 0; i < paramTypeCount; ++i) {
		QString decp = SunnyTcsTypeArg::supportArgTyps.value(paramTypes[i]);
		headerList << QSTRING_GBK("参数%1(%2)").arg(QString::number(1 + i)).arg(decp);
	}
	ui.tableWidget->setHorizontalHeaderLabels(headerList);

	for (SunnyTcsAction& ac : *loc) {
		onAddTbtnClicked();
		QComboBox* cbox = qobject_cast<QComboBox*>(ui.tableWidget->cellWidget(ui.tableWidget->rowCount() - 1, 0));
		cbox->setCurrentIndex(SunnyTcsAction::actionSample.keys().indexOf(ac.getCommandCode()));
		for (int i = 0; i < paramTypeCount; ++i) {
			QSpinBox* sbox = qobject_cast<QSpinBox*>(ui.tableWidget->cellWidget(ui.tableWidget->rowCount() - 1, i + 1));
			SunnyTcsArg&& arg = ac.getParam(i);
			bool ok = true;
			sbox->setValue(arg.toDataString().toInt(&ok));
			Q_ASSERT(ok);
		}
	}
	resizeTable();

}

void SunnyTcsLocationEditWidget::resizeTable()
{
	//resize
	if (ui.tableWidget->columnCount() == 0)return;
	qint32 columnWidth = (ui.tableWidget->width() * 0.9) / (ui.tableWidget->columnCount());
	for (int i = 0; i < ui.tableWidget->columnCount(); ++i) {
		ui.tableWidget->setColumnWidth(i, columnWidth);
	}
}
