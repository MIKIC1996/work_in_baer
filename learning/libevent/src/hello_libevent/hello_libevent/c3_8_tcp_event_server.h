#pragma once
#include "libevent_header.h"

static void client_cb(evutil_socket_t sock, short which, void* arg) {

	event* ev = (event*)(arg);
	if (which & EV_TIMEOUT) {
		std::cout << "time out" << std::endl;
		event_free(ev);
		evutil_closesocket(sock);
		return;
	}

	char buf[1024] = { 0 };
	int len = recv(sock, buf, sizeof(buf) - 1, 0);

	if (len > 0)
	{
		std::cout << buf << std::endl;
		send(sock, "ok", 2, 0);
	}
	else
	{
		//需要清理event
		std::cout << "event_free" <<  std::endl;
		event_free(ev);
		evutil_closesocket(sock);
	}
}




static void listen_cb(evutil_socket_t sock, short which, void* arg) {
	std::cout << "listen_cb" << std::endl;
	sockaddr_in sin;
	socklen_t size = sizeof(sin);
	//读取连接信息
	evutil_socket_t client = accept(sock, (sockaddr*)&sin, &size);
	char ip[16] = { 0 };
	evutil_inet_ntop(AF_INET, &sin.sin_addr, ip, sizeof(ip) - 1);
	std::cout << "client ip is" << ip << std::endl;

	//新的客户端数据读取事件
	event_base* base = (event_base*)(arg);
	//这个事件修改为边缘触发
	event* client_read_ev = event_new(base, client,EV_READ | EV_PERSIST |EV_ET, client_cb, event_self_cbarg());
	timeval t = { 10,0 };
	//为事件设置了超时，也就是10s没有收到数据，就自动断开连接
	event_add(client_read_ev,&t);
}


static void c3_8_tcp_event_server() {
	
#ifdef _WIN32 
	//初始化socket库
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#else
	//忽略管道信号，发送数据给已关闭的socket
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return 1;
#endif

	event_base* base = event_base_new();
	
	//创建windows 的 socket，用evutil_socket_t 类型来接，其实就是个类似linux fd的东西
	evutil_socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock <= 0) {
		std::cerr << "socker error" << std::endl;
	}

	//非阻塞和地址复用

	/*
	一、阻塞非阻塞概念
		阻塞，就是调用我（函数），我（函数）没有接收完数据或者没有得到结果之前，我不会返回。
		非阻塞，就是调用我（函数），我（函数）立即返回，通过select通知调用者。
		同步，就是我调用一个功能，该功能没有结束前，我死等结果。
		异步，就是我调用一个功能，不需要知道该功能结果，该功能有结果后通知我（回调通知）。
	*/	

	evutil_make_socket_nonblocking(sock); //设置socket非阻塞
	evutil_make_listen_socket_reuseable(sock);

	//端口和地址绑定
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(3456);
	if (0 != bind(sock, (sockaddr*)&sin, sizeof(sin)))
	{
		std::cerr << "bind error" << std::flush << std::endl;
		return;
	}
	//开始监听
	listen(sock, 10);

	//连接事件创建，默认水平触发
	event* ev = event_new(base, sock, EV_READ | EV_PERSIST, listen_cb, base);
	event_add(ev, 0);//你也可以设置超时，这样定时调用，检查状态。

	//事件主循环
	event_base_dispatch(base);
	evutil_closesocket(sock);
	event_base_free(base);

	return;


}

