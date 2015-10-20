# 设置包含目录
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

# 设置可执行文件
ADD_EXECUTABLE(mdsim
    mdsim.cpp
    ${ROOT_PATH}/gateway/crawler/src/sina_crawler.cpp
    )

# 增加链接库目录
LINK_DIRECTORIES(
    ${BOOST_LIB}
    ${CURL_LIB}
    ${LIBEV_LIB}
    ${COMMON_LIB}
    )

# 第三方链接库
SET(MDSIM_LIB
    inst
    sys
    boost_system
    boost_filesystem
    boost_program_options
    curl
    ${NCURSESW_LIB}
    )
# 根据平台链接libev库
IF (CYGWIN)
    TARGET_LINK_LIBRARIES(mdsim ${MDSIM_LIB} ${LIBEV_LIB}/libev.a)
ELSE (CYGWIN)
    TARGET_LINK_LIBRARIES(mdsim ${MDSIM_LIB} ev)
ENDIF(CYGWIN)

