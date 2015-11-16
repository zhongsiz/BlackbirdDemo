# 设置源文件
SET (INST_SRC instrument/code_db.cpp)
SET (SYS_SRC
    system/cctime.cpp
    system/encoding.cpp
    infrastucture/common_service.cpp
    )
# 编译inst静态库
ADD_LIBRARY (inst SHARED ${INST_SRC})
# 编译sys链接库
ADD_LIBRARY (sys SHARED ${SYS_SRC})
