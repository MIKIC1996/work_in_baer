#pragma once

#include "libevent_header.h"

static long recvCount = 0;
static long sendCount = 0;

static void  client_read_cb(struct bufferevent* be, void* arg) {
	std::cout << "[client_R]" << std::endl;
	char buf[1024] = { 0 };
	bufferevent_read(be, buf, sizeof(buf) - 1);
	std::cout << buf << std::endl;
}

static void client_write_cb(struct bufferevent* be, void* arg) {
	std::cout << "[client_W]" << std::endl;
	FILE* fp = (FILE*)arg;
	char data[1024] = { 0 };
	int len = fread(data, 1, sizeof(data) - 1, fp);
	if (len <= 0)
	{
		//读到结尾或者文件出错
		fclose(fp);
		//立刻清理，可能会造成缓冲数据没有发送结束
		//bufferevent_free(be);
		std::cout << "send end " << sendCount<<std::endl;
		bufferevent_disable(be, EV_WRITE);//禁用写
		return;
	}
	sendCount += len;
	//写入buffer
	bufferevent_write(be, data, len); //这个会再次调用client_write_cb
}


//连接时 ，超时，错误会触发，你可以通过what 位运算来 判断
static void client_event_cb(struct bufferevent* be, short what, void* arg) {
	std::cout << "client_event_cb" << std::endl;
	if (what & BEV_EVENT_TIMEOUT && what & BEV_EVENT_READING) {
		std::cout << " BEV_EVENT_TIMEOUT & BEV_EVENT_READING" << std::endl;
	//	bufferevent_free(be);//不退出，就提示一下
		bufferevent_enable(be,EV_READ); //设置了超时，如果还想继续读，必须重新使能
		return;
	}
	else if (what & BEV_EVENT_TIMEOUT && what & BEV_EVENT_WRITING) {
		std::cout << " BEV_EVENT_TIMEOUT & BEV_EVENT_WRITING" << std::endl;
		bufferevent_free(be);//这里使用写入超时来判断是否已经写完
		return;
	}
	else if (what & BEV_EVENT_ERROR) {
		std::cout << "BEV_EVENT_ERROR" << std::endl;
		bufferevent_free(be);
		return;
	}

	if (what & BEV_EVENT_EOF) { //服务端断开连接
		std::cout << "BEV_EVENT_EOF" << std::endl;
		bufferevent_free(be);
	}

	if (what & BEV_EVENT_CONNECTED) {
		std::cout << "BEV_EVENT_CONNECTED" << std::endl;
		bufferevent_trigger(be, EV_WRITE, 0); //直接触发write;
	}

}



//主函数
static void c4_5_buffer_client_test()
{
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

	bufferevent* be = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
	if (!be) {
		std::cout << "bufferevent_socket_new error" << std::endl;
		return;
	}


	//设置服务端IP 端口
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(5001);
	evutil_inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);

	//打开文件
	FILE* fp = fopen("c4_5_buffer_client.h", "rb");
	if (!fp) {
		std::cout << "fopen error" << std::endl;
		return;
	}

	//设置回调函数
	bufferevent_setcb(be, client_read_cb, client_write_cb, client_event_cb,fp );

	//设置读写使能
	bufferevent_enable(be, EV_READ | EV_WRITE);

	//设置超时
	timeval tv{ 10,0 };
	bufferevent_set_timeouts(be, &tv, &tv); //读写均设置了超时，一旦超时被触发，读写事件将被禁用，变成非待决状态
	
	//开始连接，连接成功会调用 事件回调函数
	if (0 != bufferevent_socket_connect(be, (sockaddr*)&sin, sizeof(sin))) {
		std::cout<<"bufferevent_socket_connect error"<<std::endl;
		return;
	}

	event_base_dispatch(base);
	event_base_free(base);

};

