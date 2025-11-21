#pragma once

#ifdef CONFIGURATION_DEBUG
	#define ENABLE_DEBUGGING 1
#endif

#ifdef ENABLE_DEBUGGING
	#define ENABLE_ASSERT 1
	#define ENABLE_LOGGING 1
#endif

#ifdef ENABLE_ASSERT
//#include "Logger.h"
	#define CORE_ASSERT(X, ...) if(!(X)) { __debugbreak(); }
#else
#define CORE_ASSERT(X)
#endif