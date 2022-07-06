#pragma once

#include <QtCore/qglobal.h>
#include <SunnyTcsBasicV3/SunnyTcsGeneralAlgorithm.hpp>
#include <queue>





#ifndef BUILD_STATIC
# if defined(SUNNYTCSALGORITHMV3_LIB)
#  define SUNNYTCSALGORITHMV3_EXPORT Q_DECL_EXPORT
# else
#  define SUNNYTCSALGORITHMV3_EXPORT Q_DECL_IMPORT
# endif
#else
# define SUNNYTCSALGORITHMV3_EXPORT
#endif



#define ALGORITHM_DISPATCH_BASIC_ID 0x01
#define ALGORITHM_DISPATCH_BASIC_DESCRIPTION "basic dispatching algorithm"


#define ALGORITHM_ROUTE_BASIC_ID 0x01
#define ALGORITHM_ROUTE_BASIC_DESCRIPTION "basic routing description algorithm"