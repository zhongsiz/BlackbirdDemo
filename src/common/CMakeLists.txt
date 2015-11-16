# 设置源文件
SET (INST_SRC instrument/code_db.cpp)
SET (SYS_SRC
    system/cctime.cpp
    system/encoding.cpp
    infrastucture/common_service.cpp
    )
# 编译inst静态库
ADD_LIBRARY (inst SHARED ${INST_SRC})
TARGET_LINK_LIBRARIES(inst boost_system)
SET_TARGET_PROPERTIES(inst PROPERTIES OUTPUT_NAME "inst")
# 编译sys链接库
ADD_LIBRARY (sys SHARED ${SYS_SRC})
IF(CYGWIN)
    TARGET_LINK_LIBRARIES(sys iconv boost_program_options ${LIBEV_LIB}/libev.a)
ENDIF(CYGWIN)
