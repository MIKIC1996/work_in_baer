#pragma once

#include <QWidget>
#include "ui_SunnyTcsLocationEditWidget.h"
#include "SunnyTcsSupervisoryV3_general.h"







class SunnyTcsLocationEditWidget : public QWidget
{
	Q_OBJECT
public:

	SunnyTcsLocationEditWidget(QWidget *parent = Q_NULLPTR);

	virtual ~SunnyTcsLocationEditWidget() {}
	
	void init(SunnyTcsGraphicsLocation* loc);
	
protected:
	void resizeTable();
	virtual void resizeEvent(QResizeEvent* event)override {resizeTable();}


private slots:



	void onAddTbtnClicked() {
		qDebug() << "onAddTbtnClicked";
		ui.tableWidget->setRowCount(ui.tableWidget->rowCount() + 1);
		qint32 columnCount = ui.tableWidget->columnCount();
		qint32 rowIndex = ui.tableWidget->rowCount() - 1;
		QComboBox* cbox = new QComboBox(this);
		for (const SunnyTcsAction& ter : SunnyTcsAction::actionSample.values()) {
			cbox->addItem(ter.getDescription());
		}
		ui.tableWidget->setCellWidget(rowIndex, 0, cbox);
		for (int i = 1; i < columnCount; ++i) {
			ui.tableWidget->setCellWidget(rowIndex, i, new QSpinBox(this));
		}
	}



	void onDecTbtnClicked() {
		if (ui.tableWidget->rowCount() == 0)return;
		qint32 currentIndex = ui.tableWidget->currentRow();
		qint32 columnCount = ui.tableWidget->columnCount();
		delete dynamic_cast<QComboBox*>(ui.tableWidget->cellWidget(currentIndex, 0));
		for (int i = 1; i < columnCount; ++i) {
			delete dynamic_cast<QSpinBox*>(ui.tableWidget->cellWidget(currentIndex, i));
		}
		ui.tableWidget->removeRow(currentIndex);
		if (ui.tableWidget->rowCount() > 0) {
			ui.tableWidget->setCurrentCell(ui.tableWidget->rowCount()-1, 0);
		}
	}
	

	void onClearTbtnClicked() {
		while (ui.tableWidget->rowCount() > 0) {
			ui.tableWidget->setCurrentCell(0, 0);
			onDecTbtnClicked();
		}
	}

	void onMoveUpTbtnClicked() {
	
	
	}

	void onMoveDownTbtnClicked() {
	
	
	}

	void onMoveTopTbtnClicked() {
	
	}


	void onMoveBottomTbtnClicked() {
		
	
	}

	void onSaveBtnClicked() {
		try
		{
			Q_ASSERT(_currentLoc);
			_currentLoc->clear();
			
			QVector<E_ARG_TYPE> paramTypes = _currentLoc->getParamsType();
			qint32 paramCount = paramTypes.count();
			for (int i = 0; i < ui.tableWidget->rowCount(); ++i) {
				SunnyTcsAction ac;
				QComboBox* cbox = qobject_cast<QComboBox*>(ui.tableWidget->cellWidget(i, 0));
				Q_ASSERT(cbox);
				ac.setCommandCode(SunnyTcsAction::actionSample.keys().at(cbox->currentIndex()));
				for (int j = 1; j <= paramCount; ++j) {
					QSpinBox* sbox = qobject_cast<QSpinBox*>(ui.tableWidget->cellWidget(i, j));
					Q_ASSERT(sbox);
					SunnyTcsArg&& arg = ac.getParam(j - 1);
					if (!SunnyTcsTypeArgBuilder::buildTypeArgByString(arg, arg.getType(), QString::number(sbox->value()))) {
						throw QSTRING_GBK("参数错误（%1，%2）");
					}
					ac.setParams(j - 1, arg);
				}
				_currentLoc->append(ac);
			}
			this->hide();
		}
		catch (QString e) {
			QMessageBox::information(this, QSTRING_GBK("提示"), e);
		}

	}


	void onResetBtnClicked() {
		Q_ASSERT(_currentLoc);
	}

	
private:
	Ui::SunnyTcsLocationEditWidget ui;
	SunnyTcsGraphicsLocation* _currentLoc;

};
