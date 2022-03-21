#pragma once





#include <QFile>
#include <QToolButton>
#include <QPixmap>
#include <QLabel>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QStack>
#include <SunnyTcsGraphicV3.h>
#include <QTableWidget>
#include <QScrollBar>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QHeaderView>


//�û������ӿ�,����֧�ֳ�������������
//����lambda���ʽʵ�������ķ�ʽ����ȻҲ����ʹ�� �̳����̬��ʵ�֣����ǱȽ��鷳
class SunnyTcsUserInterfaceOperation {
public:
	SunnyTcsUserInterfaceOperation() = default;

	template<typename _functor1, typename _functor2, typename _functor3>
	SunnyTcsUserInterfaceOperation(_functor1& rd, _functor2& ud, _functor3& ff)
		:_redoFunc(rd), _undoFunc(ud), _failedFunc(ff) {}

	SunnyTcsUserInterfaceOperation(const SunnyTcsUserInterfaceOperation&) = default;

	virtual ~SunnyTcsUserInterfaceOperation() {
		
	}

	SunnyTcsUserInterfaceOperation& operator=(const SunnyTcsUserInterfaceOperation&) = default;

	void dropOperation() { _failedFunc(); }

	//�ӿ�
	virtual void redo() { _redoFunc(); }
	virtual void undo() { _undoFunc(); }

protected:
	bool _isSuccess;
	std::function<void()> _redoFunc; 
	std::function<void()> _undoFunc;
	//����ʱ���к���
	std::function<void()> _failedFunc;
};