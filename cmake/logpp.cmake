
set(LOG_INC_UTIL_FIO 
        )

set(LOG_INC_UTIL_LOGGING 
        )

set(LOG_INC_UTIL_PROPERTIES 
        )

set(LOG_INC_UTIL
        )

set(LOG_INC 
        include/util/fio/LogAppender.hpp
        include/util/fio/PropertiesReader.hpp
        include/util/logging/Level.hpp
        include/util/logging/Log.hpp
        include/util/properties/LogProperties.hpp
        include/util/Date.hpp
        include/util/LogUtil.hpp
        include/logconfig.h)
        
set(LOGPP_LIBRARY ${CMAKE_SOURCE_DIR}/lib/lib_logpp-0.9.2.5.a)

message(STATUS "LOGPP_LIBRARY: ${LOGPP_LIBRARY}")
message(STATUS "LOG_INC: ${LOG_INC}")