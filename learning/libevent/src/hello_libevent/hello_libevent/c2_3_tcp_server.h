#pragma once



#include "libevent_header.h"


//监听需要的回调函数形式
static void listener_cb(struct evconnlistener*, evutil_socket_t, struct sockaddr*, int socklen, void* arg) {
	std::cout << "listen a new connection" << std::endl;
}


static void tcp_server_test() {

#ifdef _WIN32
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif // _WIN32


	//创建libevent的上下文
	event_base* base = event_base_new();
	if (!base) {
		std::cout << "event base new fail" << std::endl;
		return;
	}

	//监听的端口
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));//清空他这个结构体的数据
	sin.sin_family = AF_INET;//设定网络协议 UDP TCP
	sin.sin_port = htons(3456);//设定监听端口

	//设置监听参数和回调函数
	evconnlistener* ev = evconnlistener_new_bind(
		base, //上下文
		listener_cb,//回调函数
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
	evconnlistener_free(ev);
	event_base_free(base);

	return;
}