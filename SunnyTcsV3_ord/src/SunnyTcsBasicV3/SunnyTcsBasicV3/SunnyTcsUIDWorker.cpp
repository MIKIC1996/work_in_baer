#include "SunnyTcsUIDWorker.h"


namespace basic {


	SunnyTcsUIDWorker* SunnyTcsUIDWorker::m_instance = nullptr;

	SunnyTcsUIDWorker * SunnyTcsUIDWorker::getUIDWorker()
	{
		if (nullptr == m_instance)
		{
			SunnyTcsUIDWorker* temp = new SunnyTcsUIDWorker();
			if (nullptr == m_instance)
				m_instance = temp;
		}
		return m_instance;
	}

	quint64 SunnyTcsUIDWorker::nextId()
	{
		quint64 timeStamp = QDateTime::currentMSecsSinceEpoch();
		if (timeStamp == m_lastTimeStamp)
		{
			m_sequence = (m_sequence + 1) & m_sequenceMask;
			if (m_sequence == 0)//if sequence overflow,should spin wait until next ms
			{
				timeStamp = tillNextMillis();
			}
		}
		else {
			m_sequence = 0L;
		}
		m_lastTimeStamp = timeStamp;
		return ((timeStamp - m_startTimeStamp) << m_sequenceBits) | m_sequence;
	}

	quint64 SunnyTcsUIDWorker::tillNextMillis()
	{
		quint64 timeStamp = QDateTime::currentMSecsSinceEpoch();
		while (timeStamp <= m_lastTimeStamp)
		{
			timeStamp = QDateTime::currentMSecsSinceEpoch();
		}
		return timeStamp;
	}




}

