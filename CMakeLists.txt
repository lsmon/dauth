cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0115 NEW)
project(dauth VERSION 0.1.0 LANGUAGES C CXX)

message(STATUS ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include(external/CMakeLists.txt)
set(PROPERTY ${CMAKE_BINARY_DIR}/resources/logging.properties)
set(LOG_CONFIG ${CMAKE_SOURCE_DIR}/include/logconfig.h)
set(CONFIG ${CMAKE_SOURCE_DIR}/include/config.h)

configure_file(logconfig.h.in ${LOG_CONFIG})
configure_file(logging.properties.in ${PROPERTY})
configure_file(config.h.in ${CONFIG})

include(cmake/logpp.cmake)
include(cmake/netpp.cmake)
include(cmake/json.cmake)

include_directories(include)

set(DAUTH_INC 
    include/auth/crypto/StringEncoder.hpp
    include/auth/crypto/AuthCrypto.hpp
    include/auth/crypto/Hash.hpp)

set(DAUTH_SRC 
    sources/auth/crypto/StringEncoder.cpp
    sources/auth/crypto/AuthCrypto.cpp
    sources/auth/crypto/Hash.cpp)

set(DSERVER_INC
    include/auth/DServer.hpp
    include/auth/EndpointHandlers.hpp)

set(DSERVER_SRC
    sources/auth/DServer.cpp
    sources/auth/EndpointHandlers.cpp)

add_library(_${PROJECT_NAME}-${PROJECT_VERSION} ${CONFIG} ${LOG_INC} ${JSON_INC} ${NETPP_INC} ${DAUTH_INC} ${DAUTH_SRC} ${DSERVER_INC} ${DSERVER_SRC})

find_package(OpenSSL REQUIRED)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME}_test test/main.cpp ${CONFIG} ${LOG_INC} ${JSON_INC} ${NETPP_INC} ${DAUTH_INC} ${DAUTH_SRC})

add_executable(${PROJECT_NAME} main.cpp ${CONFIG} ${LOG_INC} ${JSON_INC} ${NETPP_INC} ${DAUTH_INC} ${DSERVER_INC})

if(OPENSSL_FOUND)
    message(STATUS "OPENSSL_INCLUDE_DIR:    ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "OPENSSL_LIBRARIES:      ${OPENSSL_LIBRARIES}")

    include_directories(${OPENSSL_INCLUDE_DIR})

    target_link_libraries(_${PROJECT_NAME}-${PROJECT_VERSION} PRIVATE
        OpenSSL::SSL 
        OpenSSL::Crypto 
        ${OPENMSSL_LIBRARIES}
        ${LOGPP_LIBRARY}
        ${NETPP_LIBRARY}
        ${JSON_LIBRARY}
    )
    target_include_directories(_${PROJECT_NAME}-${PROJECT_VERSION} PUBLIC ${OPENSSL_INCLUDE_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

    target_link_libraries(${PROJECT_NAME}_test PRIVATE
        OpenSSL::SSL 
        OpenSSL::Crypto 
        ${OPENMSSL_LIBRARIES}
        ${LOGPP_LIBRARY}
        ${NETPP_LIBRARY}
        ${JSON_LIBRARY}
    )
    target_include_directories(${PROJECT_NAME}_test PUBLIC ${OPENSSL_INCLUDE_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenSSL::SSL 
        OpenSSL::Crypto 
        ${OPENMSSL_LIBRARIES}
        ${LOGPP_LIBRARY}
        ${NETPP_LIBRARY}
        ${JSON_LIBRARY}
        _${PROJECT_NAME}-${PROJECT_VERSION}
    )
    target_include_directories(${PROJECT_NAME} PUBLIC ${OPENSSL_INCLUDE_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

else()
    message(FATAL_ERROR "OpenSSL not found")
endif()

add_test(TEST_ENCRYPT ${PROJECT_NAME}_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)