#include "SunnyTcsRoute_graphic.h"


namespace graphic {


	//��̬����
	QHash<E_SunnyTcsRouteStatus, QString> SunnyTcsRoute_graphic::_status_string_hash;//��������״̬
	QHash<E_SunnyTcsRouteStatus, QColor> SunnyTcsRoute_graphic::_status_color_hash;//����״̬ ��ʾ��������ɫ
	const QString SunnyTcsRoute_graphic::_statusPrefix = "Status : ";
	const QString SunnyTcsRoute_graphic::_agvPrefix = "Vehicle : ";
	const qreal SunnyTcsRoute_graphic::_lineWid = 2; //�߿�
	const qreal SunnyTcsRoute_graphic::_wid = 300; //���
	const qreal SunnyTcsRoute_graphic::_height = 200; //���
	const qreal SunnyTcsRoute_graphic::_tabHeight = 35; //ͷ��tab��
	const qreal SunnyTcsRoute_graphic::_rectRadius = 20; //Բ�ǰ��
	const QColor SunnyTcsRoute_graphic::_lineColor = QColor(30, 30, 30,0); //�߿���ɫ
	const QColor SunnyTcsRoute_graphic::_tabLeftColor = QColor(0,255,0,100); //tab��ɫ
	const QColor SunnyTcsRoute_graphic::_tabRightColor = QColor(120, 50, 50, 100);//tab��ɫ
	const QColor SunnyTcsRoute_graphic::_tabBackColor = QColor(230, 230, 230, 200); //tab����ɫ
	const QColor SunnyTcsRoute_graphic::_tabBackColor_to = QColor(230, 230, 230, 0);
	const QColor SunnyTcsRoute_graphic::_tabShadowColor = QColor(50, 50, 50, 120);
	const QColor SunnyTcsRoute_graphic::_selectedColor = Qt::yellow;
	const QColor SunnyTcsRoute_graphic::_leftColor = QColor(45, 45, 45,200); //������ɫ
	const QColor SunnyTcsRoute_graphic::_rightColor = QColor(30, 30, 30, 200);//������ɫ 
	bool SunnyTcsRoute_graphic::_inited = SunnyTcsRoute_graphic::init(); //���Դ�����ʼ������


	bool SunnyTcsRoute_graphic::init()
	{
		/*

		E_CRAFT_ORDERCENTER =0,				//δ������գ�  --��������				   -- ����ģ�壬�ɶ��������й�

		E_ORDER_INIT_ORDERCENTER = 1,       //����״̬       -- ��������				   -- �������״̬������

		E_ORDER_LOGIC_MODEL = 2,             //�߼��ж�״̬   -- ģ��                       -- �߼��ж���

		E_ORDER_DISPATCHING_DISPATCHER = 3,   //������         -- ������                     -- ���������д���

		E_ORDER_DISPATCHED_MODEL = 4,         //�������       -- ģ��                       -- ģ�Ͷ��Ѿ����䣬���Ǳ���Ҫģ��ȷ�ϣ���Ϊ
																						//ʹ��actualData�ӿڣ��õ���С��״̬��һ��
																						//��ʵʱ��,

		E_ORDER_ROUTING_ROUTER = 5,				//·���滮		 -- �滮��					   -- ·���滮����·�����й滮

		E_ORDER_ROUTED_MODEL = 6,				//·���滮���   -- ģ��					   -- ģ�Ͷ�·���滮���м�飬û����ʹ���ָ���ת�빤��

		E_ORDER_WORKING_MODEL = 7,				//������		 -- ģ��					   -- ģ�͸���ָ��

		E_ORDER_FINISHED_ORDERCENTER = 8,		//���			 -- ��������				   -- �������

		E_ORDER_FAILED_ORDERCENTER = 9,			//ʧ��			 -- ����ִ����				   -- ����ʧ���ˣ�����ִ���������Խ�����תΪ��״̬

		E_ORDER_CANCELING_ORDERCENTER = 10,		//������������	 -- ��������				   -- �������Ľ��յ��ⲿ�ĳ������󣬸�Ϊ��״̬����ִ

		E_ORDER_CANCELED_ORDERCENTER = 11		//�������ָ�״̬���ͷ����Ըö���������

		*/
		_status_string_hash.insert(E_CRAFT_ORDERCENTER, QString("unactived"));
		_status_string_hash.insert(E_ORDER_INIT_ORDERCENTER, QString("actived"));
		_status_string_hash.insert(E_ORDER_LOGIC_MODEL, QString("logic"));
		_status_string_hash.insert(E_ORDER_DISPATCHING_DISPATCHER, QString("dispatching"));
		_status_string_hash.insert(E_ORDER_DISPATCHED_MODEL, QString("dispatched"));
		_status_string_hash.insert(E_ORDER_ROUTING_ROUTER, QString("routing"));
		_status_string_hash.insert(E_ORDER_ROUTED_MODEL, QString("routed"));
		_status_string_hash.insert(E_ORDER_WORKING_MODEL, QString("working"));
		_status_string_hash.insert(E_ORDER_FINISHED_ORDERCENTER, QString("finished"));
		_status_string_hash.insert(E_ORDER_FAILED_ORDERCENTER, QString("failed"));
		_status_string_hash.insert(E_ORDER_CANCELING_ORDERCENTER, QString("cancel"));
		_status_string_hash.insert(E_ORDER_CANCELED_ORDERCENTER, QString("canceled"));
		return false;
	}

	SunnyTcsRoute_graphic::SunnyTcsRoute_graphic(SunnyTcsCraftIndexer * indexer,QPointF pt )
		:SunnyTcsRoute(indexer),SunnyTcsCraftGraphicsItem(EROUTE)
	{
		this->setZValue(3);
		this->setPos(pt.x(),pt.y());
	}

	SunnyTcsRoute_graphic::~SunnyTcsRoute_graphic()
	{
		qDebug() << "release...";
	}

	QRectF SunnyTcsRoute_graphic::boundingRect() const
	{
		return QRectF(-_wid/2,-_height/2,_wid,_height);
	}

	void SunnyTcsRoute_graphic::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
	{
		painter->setRenderHint(QPainter::Antialiasing, true);

		//���û��ʿ��
		QPen pen = painter->pen();
		pen.setWidth(_lineWid);

		//������߿�
		pen.setColor(this->isSelected() ?  _selectedColor : Qt::black);
		painter->setPen(pen);
		
		painter->drawRoundedRect(QRectF(-_wid / 2, -_height / 2, _wid, _height), _rectRadius, _rectRadius);

		pen.setColor(_lineColor);
		painter->setPen(pen);


		//��������
		QLinearGradient linear(
			QPointF(-_wid / 2, -_height / 2),
			QPointF(_wid / 2, -_height / 2)
		);
		linear.setSpread(QGradient::PadSpread);

		linear.setColorAt(0, _leftColor);
		linear.setColorAt(1, _rightColor);
		painter->setBrush(linear);
		painter->drawRoundedRect(QRectF(-_wid / 2, -_height / 2 + _tabHeight/2, _wid, _height - _tabHeight/2), _rectRadius, _rectRadius);
		painter->drawRoundedRect(QRectF(-_wid / 2, -_height / 2 + _tabHeight / 2, _wid,  _tabHeight / 2), 0, 0);

		
		//���ƶ���
		QLinearGradient linear_top(
			QPointF(-_wid / 2, -_height / 2),
			QPointF(_wid / 2, -_height / 2)
		);
		linear_top.setSpread(QGradient::PadSpread);
		linear_top.setColorAt(0, _tabRightColor);
		QColor topColor = _tabLeftColor;
		topColor.setAlpha(( (qreal)(QDateTime::currentMSecsSinceEpoch() % 3000) / 3000.0) * 150.0 );
		linear_top.setColorAt(0.5, topColor);
		linear_top.setColorAt(1, _tabRightColor);
		painter->setBrush(linear_top);
		painter->drawRoundedRect(QRectF(-_wid / 2, -_height / 2, _wid, _tabHeight), _rectRadius, _rectRadius);


		//������߼�ͷ
		QPolygonF poly;
		poly << QPointF(_wid * 0.4,-_height * 0.05 ) <<
			QPointF(_wid * 0.42, -_height * 0.05) <<
			QPointF(_wid*0.46 , _height*0.01) << 
			QPointF(_wid * 0.42, _height * 0.07)<<
			QPointF(_wid * 0.4, _height * 0.07)<<
			QPointF(_wid * 0.4, -_height * 0.05);
		QPainterPath path;
		path.addPolygon(poly);
		painter->fillPath(path, Qt::green);


		//���ƶ����ϱ߹�װ��Ч��
		QLinearGradient linear2(
			QPointF(-_wid / 2, -_height / 2),
			QPointF(-_wid / 2, -_height / 2 + _tabHeight)
		);
		linear2.setSpread(QGradient::PadSpread);
		linear2.setColorAt(0, _tabBackColor);
		linear2.setColorAt(0.15, _tabBackColor_to);
		painter->setBrush(linear2);
		painter->drawRoundedRect(QRectF(-_wid / 2, -_height / 2 , _wid, _tabHeight), _rectRadius, _rectRadius);
		
	
		//���ƽ���Բ
		pen.setColor(_tabBackColor);
		pen.setWidth(4);
		painter->setPen(pen);
		painter->drawEllipse(QPointF(-_wid* 0.43, -_height / 2 + _tabHeight / 2), 7, 7);
		

		//��������
		pen.setColor(Qt::white);
		painter->setPen(pen);
		QFont font;
		font.setFamily("Microsoft YaHei");//΢���ź�
		font.setPointSize(10);
		painter->setFont(font);
		_name = "unamed";
		//painter->fillRect(QRectF(-_wid * 0.35, -_height / 2 + _tabHeight * 0.15, _wid * 0.8, _tabHeight*0.7), Qt::yellow);
		painter->drawText(QRectF(-_wid * 0.35 , -_height /2.1 , _wid * 0.85 ,_tabHeight), _name);


	//	painter->fillRect(nextTextRect(0), Qt::white);
		painter->drawText(nextTextRect(0), _statusPrefix + _status_string_hash[_status]);
		painter->drawText(nextTextRect(1), _agvPrefix +  (_agvId == 0 ? "none" : QString::number(_agvId)));
		//painter->fillRect(nextTextRect(1), Qt::white);
		//painter->fillRect(nextTextRect(2), Qt::white);
		//painter->fillRect(nextTextRect(3), Qt::white);
	}



	//��̬����
	 const QColor SunnyTcsLinkLine_graphic::_lineColor = QColor(255, 165 ,0);
	 const qreal SunnyTcsLinkLine_graphic::_lineWid = 2.0;
	 const QColor SunnyTcsLinkLine_graphic::_lineColor_selected =Qt::yellow;
	 const qreal SunnyTcsLinkLine_graphic::_lineWid_selected =3.0;



	SunnyTcsLinkLine_graphic::SunnyTcsLinkLine_graphic(qint32 index, SunnyTcsRoute_graphic * from, SunnyTcsRoute_graphic * to)
		:SunnyTcsCraftGraphicsItem(ELINKLINE), _index(index),
		_from(from), _to(to), _fromPt(0,0), _toPt(_fromPt)
	{
		qDebug() << "line create;";
		Q_ASSERT(from);//from������ڣ�to ������ʱ������
		if (_from)_fromPt = _from->sendPoint();
		if (_to)_toPt = _to->recvPoint();
		this->setZValue(2);
		this->setFlags((this->flags() &~(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable)));
	}
	


	QRectF SunnyTcsLinkLine_graphic::boundingRect() const
	{
		QPointF start(_fromPt.x() - this->pos().x(), _fromPt.y() - this->pos().y());
		QPointF end(_toPt.x() - this->pos().x(), _toPt.y() - this->pos().y());

		if (_from && _from == _to) {
			return QRectF(end.x()-50 , end.y(), 350, 300);
		}

		return QRectF(start.x() < end.x() ? start.x() : end.x(),
			start.y() < end.y() ? start.y() : end.y(),
			qAbs(end.x() - start.x()),
			qAbs(end.y() - start.y())
		);
	}



	void SunnyTcsLinkLine_graphic::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
	{
		if (_from) {
			_fromPt = _from->sendPoint();
		}
		if (_to) {
			_toPt = _to->recvPoint();
		}
		//painter->drawRect(this->boundingRect());

		QPen pen;
		pen.setColor( this->isSelected()? _lineColor_selected : _lineColor );
		pen.setWidth( this->isSelected()? _lineWid_selected : _lineWid );
		pen.setCapStyle(Qt::RoundCap);
		painter->setPen(pen);
		this->setPos((_fromPt.x() + _toPt.x()) / 2, (_fromPt.y() + _toPt.y()) / 2 );
		QPointF start(_fromPt.x() - this->pos().x(), _fromPt.y() - this->pos().y());
		QPointF end(_toPt.x() - this->pos().x(), _toPt.y() - this->pos().y());
		QPointF ctrl_1((start.x() + end.x()) /2, start.y());
		QPointF ctrl_2((start.x() + end.x()) /2, end.y());


		//�Լ�ָ�Լ�
		if (_from&& _from == _to) {
			ctrl_1.setX(start.x() + 300);
			ctrl_1.setY(start.y() + 220);
			ctrl_2.setX(end.x() - 300);
			ctrl_2.setY(end.y() + 400);
		}
		//����ָ
		else if ( (start.x() > end.x())&& _to ) {
			qreal distance = start.x() - end.x();
			ctrl_1.setX(start.x() + distance);
			ctrl_2.setX(end.x() - distance );
		}

		QPointF& arrowStartPoint= ctrl_2;
		if (start.x() == end.x() || start.y() == end.y() ||
				qAbs( start.x()) <=1
			) {
			painter->drawLine(start, end);

			arrowStartPoint = start;
		}
		else {
			QPainterPath path;
			qDebug() << "path move to (" << start.x() << " , " << start.y() << ")";
			path.moveTo(start);
			path.cubicTo(ctrl_1, ctrl_2, end);
			painter->drawPath(path);
		}
		//����ͷ
		pen.setWidth(1);
		painter->setPen(pen);
		QPainterPath arrow;
		arrow.addPolygon(getArrow(arrowStartPoint, end));
		painter->drawPath(arrow);
		painter->fillPath(arrow, this->isSelected() ? _lineColor_selected : _lineColor);
	}



	QPolygonF SunnyTcsLinkLine_graphic::getArrow(QPointF from, QPointF to)
	{
		const qreal len = 13;
		qint32 fromSx = from.x();
		qint32 fromSy = from.y();
		qint32 toSx = to.x();
		qint32 toSy = to.y();
		qreal tan = (qreal)(toSy - fromSy) / (qreal)(toSx - fromSx);
		qreal angle = qAtan(tan);

		qreal ptx = 0;
		qreal pty = 0;
		qreal dx = qAbs(len*qCos(qAbs(angle)));
		qreal dy = qAbs(len*qSin(qAbs(angle)));

		if (toSy - fromSy > 0) {
			pty = toSy - dy;
		}
		else {
			pty = toSy + dy;
		}

		if (toSx - fromSx > 0) {
			ptx = toSx - dx;
		}
		else {
			ptx = toSx + dx;
		}

		qreal deltaX = 0.5* len* qSin(qAbs(angle));
		qreal deltaY = 0.5* len* qCos(qAbs(angle));

		QPointF f1;
		QPointF f2;
		if ((toSy - fromSy > 0 && toSx - fromSx > 0) || (toSy - fromSy < 0 && toSx - fromSx < 0)) {//
			f1.setX(ptx + deltaX);
			f1.setY(pty - deltaY);
			f2.setX(ptx - deltaX);
			f2.setY(pty + deltaY);
		}
		else {
			f1.setX(ptx + deltaX);
			f1.setY(pty + deltaY);
			f2.setX(ptx - deltaX);
			f2.setY(pty - deltaY);
		}
		QPolygonF poly;
		poly << f1 << f2 << to << f1;
		return poly;
	}

}


