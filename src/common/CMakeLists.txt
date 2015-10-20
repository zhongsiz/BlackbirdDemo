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
# 编译inst动态库
ADD_LIBRARY (inst_static STATIC ${INST_SRC})
TARGET_LINK_LIBRARIES(inst_static boost_system)
# 不除清现在有链接库
SET_TARGET_PROPERTIES(inst PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(inst PROPERTIES OUTPUT_NAME "inst")
SET_TARGET_PROPERTIES(inst_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(inst_static PROPERTIES OUTPUT_NAME "inst")

# 编译sys链接库
ADD_LIBRARY (sys SHARED ${SYS_SRC})
ADD_LIBRARY (sys_static STATIC ${SYS_SRC})
IF(CYGWIN)
    TARGET_LINK_LIBRARIES(sys iconv boost_program_options ${LIBEV_LIB}/libev.a)
    TARGET_LINK_LIBRARIES(sys_static iconv boost_program_options ev)
ENDIF(CYGWIN)

# 设置属性
SET_TARGET_PROPERTIES(sys PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(sys_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(sys_static PROPERTIES OUTPUT_NAME "sys")
