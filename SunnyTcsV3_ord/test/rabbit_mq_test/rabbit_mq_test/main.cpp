#include <QtCore/QCoreApplication>

#include <amqp.h>
#include <amqp_framing.h>
#include <amqp_tcp_socket.h>
#include <utils.h>
#include "utils.c"
#include <QThread>
#include <windows.h>

#include <QDebug>


extern void die_on_error(int, const char*);



/*
* ��¼���м��
*
* param[1] : ���Ӷ���
* param[2] : ����������Ĭ��Ϊ0
* param[3] : AMQP��Ϣ֡������С��Ĭ��ֵΪ AMQP_DEFAULT_FRAME_SIZE
* param[4] : ���� ��0Ϊ��������
* param[5] : �û���֤���� �� 
			AMQP_SASL_METHOD_PLAIN , ��� const char* username �� const char* passwd
			AMQP_SASL_METHOD_EXTERNAL, ��� const char* identity
* return : �ɹ����� AMQP_RESPONSE_NORMAL 
*/
extern amqp_rpc_reply_t  amqp_login(amqp_connection_state_t state,char const *vhost, int channel_max,int frame_max, int heartbeat,amqp_sasl_method_enum sasl_method, ...);



/*
* ��һ���µ�Ƶ��
*
* param[1] : ���Ӷ���
* param[2] : Ƶ��ID
* return :  �ṹ��{ ���泤�� �� �����׵�ַ }
*/
extern amqp_channel_open_ok_t * amqp_channel_open(amqp_connection_state_t state, amqp_channel_t channel);



/*
* ���������rpc�ظ�
*
* param[1] : ���Ӷ���
* return :  
*/
extern amqp_rpc_reply_t AMQP_CALL amqp_get_rpc_reply(amqp_connection_state_t state);



/**
* ����һ������
*
* @param [1] ���Ӷ���
* @param [2] Ƶ��
* @param [3] ������
* @param [4] passive
* @param [5] �Ƿ�־û�
* @param [6] ��ǰ���Ӳ���ʱ�������Ƿ��Զ�ɾ��
* @param [7] û��consumerʱ�������Ƿ��Զ�ɾ��
* @param [8] ������չ����
* @returns amqp_queue_declare_ok_t
*/

extern amqp_queue_declare_ok_t * amqp_queue_declare(
	amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t queue,
	amqp_boolean_t passive, amqp_boolean_t durable, amqp_boolean_t exclusive,
	amqp_boolean_t auto_delete, amqp_table_t arguments);






/**
* qos�� quality of service����������ʹ����Ҫ���ڿ���Ԥȡ��Ϣ����������Ϣ���������ȷ��䣬��Ҫ��no_ack���ʹ��
*
* @param [1] ���Ӷ���
* @param [2] Ƶ��
* @param [3] Ԥȡ��Ϣ��С
* @param [4] Ԥȡ��Ϣ��Ŀ
* @param [5] �Ƿ�ȫ��
* @returns amqp_queue_declare_ok_t
*/
amqp_basic_qos_ok_t *AMQP_CALL amqp_basic_qos(amqp_connection_state_t state,
	amqp_channel_t channel,
	uint32_t prefetch_size,
	uint16_t prefetch_count,
	amqp_boolean_t global);



/**
* ��һ�������߰󶨵�����
*
* @param [in] state connection state
* @param [in] channel the channel to do the RPC on
* @param [in] queue queue
* @param [in] consumer_tag consumer_tag
* @param [in] no_local no_local
* @param [in] �Ƿ�Ҫ��Ϣȷ�Ϻ� �Ŵ� ������ɾ����Ϣ
* @param [in] exclusive exclusive
* @param [in] arguments arguments
* @returns amqp_basic_consume_ok_t
*/
extern amqp_basic_consume_ok_t * amqp_basic_consume(
	amqp_connection_state_t state, amqp_channel_t channel, amqp_bytes_t queue,
	amqp_bytes_t consumer_tag, amqp_boolean_t no_local, amqp_boolean_t no_ack,
	amqp_boolean_t exclusive, amqp_table_t arguments);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	//���½�һ������
	amqp_connection_state_t conn;
	conn = amqp_new_connection();
	//�½�һ���׽���
	amqp_socket_t* socket = nullptr;
	socket = amqp_tcp_socket_new(conn);
	//���׽���
	const char* host_name = "127.0.0.1";
	int port = 5672;
	int socket_status = amqp_socket_open(socket, host_name, port);//���� amqp_status_enum_����
	//��鷵��״̬��ʧ�ܾ�exit���򣬲���ӡ����
	die_on_error(socket_status, "error in open socket");
	//��¼
	auto login_status = amqp_login(conn, "/", 0, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "mikic", "mikic");
	die_on_amqp_error(login_status, "error in login"); //�Է���ֵ���м��
	//��һ���µ�Ƶ��
	int channelId = 1;
	amqp_channel_open(conn, channelId); 
	//����ĳ�����������Զ�̵��ûظ������Լ���Ƿ�����ظ�����,�����channel_open��û�з����Ƿ�ɹ�����������ֻ��������ѯ
	auto rpc_reply  = amqp_get_rpc_reply(conn);
	die_on_amqp_error(rpc_reply, "open channel error"); //��鿪��Ƶ�������Ƿ����
	
	//����һ��������
	amqp_exchange_declare(conn, channelId, amqp_cstring_bytes("kernelExchange"), amqp_cstring_bytes("direct"), 0, 1, 0, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "exchange  error");
	//����һ������,�־û��ģ�����ɾ���Ķ���
	amqp_queue_declare(conn, channelId, amqp_cstring_bytes("kernelQueue"), 0, 1, 0, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "queue  error");
	//�����а󶨵�һ����������
	amqp_queue_bind(conn, channelId, amqp_cstring_bytes("kernelQueue")
		, amqp_cstring_bytes("kernelExchange"), amqp_cstring_bytes("kernelKey"), amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "bind  error");
	qDebug() << "send msg";
	//������Ϣ
	for (int i = 0; i < 300; ++i) {
		//��Ϣ���Ե�����
		amqp_basic_properties_t props;
		props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
		props.content_type = amqp_cstring_bytes("text/plain");
		props.delivery_mode = 2;

		//������Ϣ
		int res = amqp_basic_publish(conn, channelId,
			amqp_cstring_bytes("kernelExchange"),amqp_cstring_bytes("kernelKey"),
			0, 0, &props, amqp_cstring_bytes("jmq message"));
		QThread::msleep(10);
	}


	amqp_basic_qos(conn, channelId, 0, 1, 0);
	//����һ�������߰󶨵�����
	amqp_basic_consume(conn, channelId, amqp_cstring_bytes("kernelQueue"),
		amqp_cstring_bytes("jmq"), 0, 1, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming error");
	
	qDebug() << "get start";
	timeval tim;
	tim.tv_sec = 1;
	tim.tv_usec = 0;
	amqp_envelope_t enve;

	for (int i = 0; i < 400; ++i) {
		std::string msg = "";
		amqp_maybe_release_buffers(conn);
		auto consume_reply =
			amqp_consume_message(conn, &enve, &tim, 0);
		if (consume_reply.reply_type != AMQP_RESPONSE_NORMAL) {
			qDebug() << "amqp_comsume_message error";
		}
		else {
			msg = (char*)enve.message.body.bytes;
			msg = msg.substr(0, enve.message.body.len);
			qDebug() << "msg = " << msg.data() << " num = " << i;
			QThread::msleep(10);
		}

	}

	QThread::msleep(1000);
	amqp_channel_close(conn, channelId, AMQP_REPLY_SUCCESS);
	amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
	amqp_destroy_connection(conn);
		


	/*									
	//����һ������,�־û��ģ�����ɾ���Ķ���
	amqp_queue_declare(conn, channelId, amqp_cstring_bytes("kernelQueue"), 0, 1, 0, 0, amqp_empty_table);
	//Ԥȡ��Ϣ����
	amqp_basic_qos(conn, channelId, 0, 1, 0);
	//����һ�����Ѷ���
	amqp_basic_consume(conn, channelId, amqp_cstring_bytes("kernelQueue"),
		amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
	die_on_amqp_error(amqp_get_rpc_reply(conn), "consuming error");
	*/
	



    return a.exec();
}
