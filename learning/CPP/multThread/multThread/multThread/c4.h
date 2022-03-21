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


//期望
//使用期望获取异步任务的返回值

int getAnswer() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return 100;
}


void async_task() {

	std::future<int> ret = std::async(getAnswer); //提交了一个异步任务
	std::cout << ret.get() <<std::endl;

}







//std::promise 是C++11并发编程中常用的一个类，常配合std::future使用。其作用是在一个线程t1中保存一个
//类型typename T的值，可供相绑定的std::future对象在另一线程t2中获取。

std::promise<int>  promise1;

void set_promise_val() {

	try {

		//throw std::logic_error("logic");
		std::this_thread::sleep_for(std::chrono::seconds(5));
		promise1.set_value(100);
		
	}
	catch (...) {
		promise1.set_exception(std::current_exception()); //可以接收异常
	}
}


void promise_test() {

	std::thread t1(set_promise_val);

	std::future<int> fu = promise1.get_future();//也可以得到异常

	int ret = fu.get();//阻塞等待
	std::cout << ret << std::endl;

	t1.join();
}


//多个线程同时等待一个future
void mult_promise_test() {

	std::shared_future<int> sf = promise1.get_future().share();
	std::shared_future <int> sf2 = sf;


	std::thread t1(set_promise_val);

	std::thread t2([&sf] { std::cout << sf.get()<< std::endl;  });
	std::thread t3([&sf2]{ std::cout << sf2.get()<< std::endl;  });
	t1.join();
	t2.join();
	t3.join();
}