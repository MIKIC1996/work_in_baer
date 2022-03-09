#pragma once
#include "sunnytcsbasicv3_global.h"
#include "SunnyTcsMessage.h"

namespace basic {


	class SunnyTcsMessageLibrary
	{
	public:

	protected:
		static QHash<qint32, SunnyTcsMessage> _msgs;

		SunnyTcsMessageLibrary();
		~SunnyTcsMessageLibrary();
	};



}



