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


//用户操作接口,用以支持撤销与重做功能
//采用lambda表达式实现是最方便的方式，当然也可以使用 继承与多态来实现，但是比较麻烦
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

	//接口
	virtual void redo() { _redoFunc(); }
	virtual void undo() { _undoFunc(); }

protected:
	bool _isSuccess;
	std::function<void()> _redoFunc; 
	std::function<void()> _undoFunc;
	//销毁时运行函数
	std::function<void()> _failedFunc;
};