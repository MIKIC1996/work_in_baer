#pragma once


//线程同步与条件变量
#include "stdafx.h"

struct Task {
	int _val;
	std::string _str;
};


std::mutex mut;
std::queue<Task> taskQueue;
std::condition_variable cond;
bool threadSwitch = true;



void insertDataThread() {

	Task t{ 100,"hello world!" };
	
	{
		std::lock_guard<std::mutex> guard(mut);
		taskQueue.push(t);
	}//这里自动将mut解锁

	cond.notify_one();
	
}



void processThread() {

	while (threadSwitch) {
		std::unique_lock<std::mutex> lk(mut); //先锁住
		cond.wait(lk, []()->bool {return !taskQueue.empty(); }); //条件不满足，将lk解锁（unlock）,等待；当被唤醒时，重现获取锁,再判断条件，满足，保持锁获取状态，并返回；
		
		Task tmp = taskQueue.front();
		taskQueue.pop();
		lk.unlock();

		std::cout << tmp._val << " : " << tmp._str.c_str() << std::endl;

	}
}


void condition_vari_test() {


	std::thread t1(processThread);

	while ('q' != getchar()) {
		insertDataThread();
	}
	threadSwitch = false;//关闭开关
	insertDataThread();//将线程唤醒，不然一直处于阻塞状态
	t1.join(); //连接线程，等待退出

}