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
		//������β�����ļ�����
		fclose(fp);
		//�����������ܻ���ɻ�������û�з��ͽ���
		//bufferevent_free(be);
		std::cout << "send end " << sendCount<<std::endl;
		bufferevent_disable(be, EV_WRITE);//����д
		return;
	}
	sendCount += len;
	//д��buffer
	bufferevent_write(be, data, len); //������ٴε���client_write_cb
}


//����ʱ ����ʱ������ᴥ���������ͨ��what λ������ �ж�
static void client_event_cb(struct bufferevent* be, short what, void* arg) {
	std::cout << "client_event_cb" << std::endl;
	if (what & BEV_EVENT_TIMEOUT && what & BEV_EVENT_READING) {
		std::cout << " BEV_EVENT_TIMEOUT & BEV_EVENT_READING" << std::endl;
	//	bufferevent_free(be);//���˳�������ʾһ��
		bufferevent_enable(be,EV_READ); //�����˳�ʱ������������������������ʹ��
		return;
	}
	else if (what & BEV_EVENT_TIMEOUT && what & BEV_EVENT_WRITING) {
		std::cout << " BEV_EVENT_TIMEOUT & BEV_EVENT_WRITING" << std::endl;
		bufferevent_free(be);//����ʹ��д�볬ʱ���ж��Ƿ��Ѿ�д��
		return;
	}
	else if (what & BEV_EVENT_ERROR) {
		std::cout << "BEV_EVENT_ERROR" << std::endl;
		bufferevent_free(be);
		return;
	}

	if (what & BEV_EVENT_EOF) { //����˶Ͽ�����
		std::cout << "BEV_EVENT_EOF" << std::endl;
		bufferevent_free(be);
	}

	if (what & BEV_EVENT_CONNECTED) {
		std::cout << "BEV_EVENT_CONNECTED" << std::endl;
		bufferevent_trigger(be, EV_WRITE, 0); //ֱ�Ӵ���write;
	}

}



//������
static void c4_5_buffer_client_test()
{
#ifdef _WIN32 
	//��ʼ��socket��
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#else
	//���Թܵ��źţ��������ݸ��ѹرյ�socket
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return 1;
#endif

	event_base* base = event_base_new();

	bufferevent* be = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
	if (!be) {
		std::cout << "bufferevent_socket_new error" << std::endl;
		return;
	}


	//���÷����IP �˿�
	sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(5001);
	evutil_inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);

	//���ļ�
	FILE* fp = fopen("c4_5_buffer_client.h", "rb");
	if (!fp) {
		std::cout << "fopen error" << std::endl;
		return;
	}

	//���ûص�����
	bufferevent_setcb(be, client_read_cb, client_write_cb, client_event_cb,fp );

	//���ö�дʹ��
	bufferevent_enable(be, EV_READ | EV_WRITE);

	//���ó�ʱ
	timeval tv{ 10,0 };
	bufferevent_set_timeouts(be, &tv, &tv); //��д�������˳�ʱ��һ����ʱ����������д�¼��������ã���ɷǴ���״̬
	
	//��ʼ���ӣ����ӳɹ������ �¼��ص�����
	if (0 != bufferevent_socket_connect(be, (sockaddr*)&sin, sizeof(sin))) {
		std::cout<<"bufferevent_socket_connect error"<<std::endl;
		return;
	}

	event_base_dispatch(base);
	event_base_free(base);

};

