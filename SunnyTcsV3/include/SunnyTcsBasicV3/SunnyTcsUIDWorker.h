#pragma once
#include "sunnytcsbasicv3_global.h"

namespace basic {


	class SUNNYTCSBASICV3_EXPORT SunnyTcsUIDWorker
	{
	public:
		static SunnyTcsUIDWorker* getUIDWorker();
		static SunnyTcsUIDWorker* m_instance;
		quint64 nextId();

	protected:
		SunnyTcsUIDWorker() {
			m_lastTimeStamp = 0;
		}

		quint64 tillNextMillis();

		quint64 m_sequence = 0L;
		quint64 m_sequenceBits = 20L;
		quint64 m_sequenceMask = -1L ^ (-1L << m_sequenceBits);
		quint64 m_lastTimeStamp = -1L;
		quint64 m_startTimeStamp = 1526572800000L; //from 2018.5.18 00:00:00

	};


}