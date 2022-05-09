#pragma once

#include "libevent_header.h"

#define WEBROOT "E:\\code\\work_in_baer\\learning\\libevent\\src\\hello_libevent\\resource" 
#define DEFAULTINDEX "index.html"


struct reqstruct {
	evhttp_request* req;
	std::string uri;
};

static std::queue<reqstruct> reqs;

static  timeval tv_tv{ 10,0 };

static void http_cb(struct evhttp_request* req, void* arg){
	
	

	//��ȡ�������������Ϣ
	//uri
	const char* uri = evhttp_request_get_uri(req);
	//std::cout << "uri : " << uri << std::endl;
	//��������
	std::string cmd_type;
	switch (evhttp_request_get_command(req)) {
	case EVHTTP_REQ_GET:
		cmd_type = "get";
		break;
	case EVHTTP_REQ_POST:
		cmd_type = "post";
		break;
	}
//	std::cout << "cmdtype : " << cmd_type << std::endl;
	
	//��Ϣ��ͷ
	evkeyvalq* headers = evhttp_request_get_input_headers(req);
	//std::cout << "========== headers ============" << std::endl;
	for (evkeyval* iter = headers->tqh_first; 
		iter != NULL; 
		iter = iter->next.tqe_next) {
	//	std::cout << iter->key << " : " << iter->value << std::endl;
	}

	//��������
	evbuffer* inbuf = evhttp_request_get_input_buffer(req);
	char buf[1024] = {0};
	while (evbuffer_get_length(inbuf)) { // �ж��������ĵ�ʣ�೤��
		int n = evbuffer_remove(inbuf, buf, sizeof(buf) - 1);
		if (n > 0) {
			buf[n] = '\0';
		//	std::cout << buf << std::endl;
		}
	}

	reqstruct stt{ req,uri };
	reqs.push(stt);
	std::cout << "http_cb" << std::endl;
}





static void time_cb(evutil_socket_t, short which, void* arg) {
	
	

	event* ev = (event*)arg;
	if (!evtimer_pending(ev, &tv_tv)) {
		evtimer_del(ev);
		evtimer_add(ev, &tv_tv);
	}

	if (reqs.size() < 1)return;

	std::cout << "time cb------------------------------------------------------------------------" << std::endl;

	char buf[1024] = { 0 };

	evhttp_request* req = reqs.front().req;
	std::string uri = reqs.front().uri;
	reqs.pop();




	//�ظ������
//״̬�� ��Ϣ��ͷ ��Ӧ����
	std::string file_path = WEBROOT;
	file_path += uri;
	if (strcmp(uri.c_str(), "/") == 0) {
		file_path += DEFAULTINDEX;
	}


	//��Ϣ��ͷ
	evkeyvalq* out_head = evhttp_request_get_input_headers(req);
	int pos = file_path.rfind('.');
	std::string postfix = file_path.substr(pos + 1, file_path.size() - (pos + 1));

	if (postfix == "jpg") { //��Ϣ��ͷ
		std::string tmp = "image/" + postfix;
		evhttp_add_header(out_head, "Content-type", tmp.c_str()); //���ñ�ͷ���ֶ�
	}
	else if (postfix == "zip") {
		evhttp_add_header(out_head, "Content-type", "application/zip");
	}
	else if (postfix == "html") {
		evhttp_add_header(out_head, "Content-Type", "text/html;charset=UTF8");
	}
	else if (postfix == "css")
	{
		evhttp_add_header(out_head, "Content-Type", "text/css");
	}




	FILE* fp = fopen(file_path.c_str(), "rb"); //��Ӧ����
	if (!fp)
	{
		evhttp_send_reply(req, HTTP_NOTFOUND, "", 0);//����״̬�в��ظ�
		return;
	}
	evbuffer* outbuf = evhttp_request_get_output_buffer(req);
	for (;;)
	{
		int len = fread(buf, 1, sizeof(buf), fp);
		if (len <= 0)break;
		evbuffer_add(outbuf, buf, len);
	}
	fclose(fp);
	evhttp_send_reply(req, HTTP_OK, "", outbuf);


	//evhttp_request_free(req);
}



static void c6_5_http_server_test()
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

	std::cout << "test server" << std::endl;
	//����libevent��������
	event_base* base = event_base_new();
	if (!base) {
		std::cout << "event_base_new error" << std::endl;
		return;
	}

	//����evhttp������
	evhttp* evh = evhttp_new(base);
	if (!evh) {
		std::cout << "evhttp_new error" << std::endl;
		return;
	}

	//�󶨶˿ں͵�ַ
	if (0 != evhttp_bind_socket(evh, "0.0.0.0", 8080) != 0) {
		std::cout << "evhttp_bind_socket" << std::endl;
		return;
	}

	//�趨http�Ļص�����
	evhttp_set_gencb(evh, http_cb, evh);


	//�趨�ظ���ʱ��
	event* time_event = evtimer_new(base, time_cb, event_self_cbarg());
	
	event_add(time_event, &tv_tv);

	//�¼�ѭ��
	event_base_dispatch(base);
	event_base_free(base);
	evhttp_free(evh);

}

