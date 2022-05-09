#pragma once
#include "libevent_header.h"


//监听需要的回调函数形式
static void listener2_cb(struct evconnlistener*, evutil_socket_t, struct sockaddr*, int socklen, void* arg) {
	std::cout << "listen a new connection" << std::endl;
}



static void c2_5_event_base_config_test()
{
#ifdef _WIN32
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif

	//打印当前所支持的网络模型
	char const** sptMethod = event_get_supported_methods();
	for (int i = 0; sptMethod[i] != NULL; ++i) {
		std::cout << "spt method " << sptMethod[i] << std::endl;
	}


	//创建一个新的上下文配置
	event_config* conf = event_config_new();
	//给配置设置标志

	//给配置设置特征
	/*
	if (0 != event_config_require_features(conf, EV_FEATURE_ET)) {
		std::cout << "event_config_require_features failed" << std::endl;
	}
	*/
	//给配置设置不想要的网络模型
	event_config_avoid_method(conf, "epoll");

	//给配置设置标志

#ifdef _WIN32
	event_config_set_flag(conf, EVENT_BASE_FLAG_STARTUP_IOCP);//使用IOCP模型
	evthread_use_windows_threads();
	SYSTEM_INFO sinfo;
	GetSystemInfo(&sinfo);
	event_config_set_num_cpus_hint(conf, sinfo.dwNumberOfProcessors);
#endif


	//使用该配置配置上下文对象
	event_base* base = event_base_new_with_config(conf);

	if (!base) {
		std::cout << "event_base_new_with_config failed" << std::endl;
		base = event_base_new();
	}
	else {
		//获取当前模型
		std::cout << "current method is " << event_base_get_method(base) << std::endl;

		std::cout << "event_base_new_with_config success" << std::endl;
		//获取当前的上下文对象的特征
		int f = event_base_get_features(base);
		if (f & EV_FEATURE_ET)
			std::cout << "support EV_FEATURE_ET"<<std::endl;
		if (f & EV_FEATURE_O1) 
			std::cout << "support EV_FEATURE_O1" << std::endl;
		if (f & EV_FEATURE_FDS)
			std::cout << "support EV_FEATURE_O1" << std::endl;
		if (f & EV_FEATURE_EARLY_CLOSE)
			std::cout << "support EV_FEATURE_O1" << std::endl;
	}


	//监听的端口
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));//清空他这个结构体的数据
	sin.sin_family = AF_INET;//设定网络协议 UDP TCP
	sin.sin_port = htons(3456);//设定监听端口

	//设置监听参数和回调函数
	evconnlistener* ev = evconnlistener_new_bind(
		base, //上下文
		listener2_cb,//回调函数
		base,//回调函数获取的参数arg
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,//地址重用，evconnlistener关闭同时关闭socket
		10,//连接队列大小
		(sockaddr*)&sin,//地址与端口
		sizeof(sin)//C语言中用来判定sin类型的方法，就是大小
	);
	if (!ev) {
		std::cout << "listener bind error" << std::endl;
		return;
	}

	event_base_dispatch(base);


	//上下文对象的销毁
	if (base) {
		event_base_free(base);
	}
	//上下文配置的销毁
	event_config_free(conf);

};

