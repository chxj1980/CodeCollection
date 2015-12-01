########################################################################################
#############              生成 tinytcp 库文件                               ############## 
########################################################################################
LIST (APPEND tinytcp_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/arp.c  
    ${CMAKE_CURRENT_SOURCE_DIR}/sed.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyftp.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/tinytcp.c 
    )


    
########################################################################################
#############               设置 tinytcp 库版本号                          ############## 
########################################################################################
set(tinytcp_LIB_VERSION     "1.0.0")
set(tinytcp_LIB_SOVERSION   "1")


    
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Network
    ${PROJECT_SOURCE_DIR}/Network/TinyTCP
)  

########################################################################################
#############               添加 链接库文件目录                           ############## 
########################################################################################
link_directories(  
    /usr/local/lib   
    )  


    
########################################################################################
#############           生成目标库文件 并 标明版本号                      ############## 
########################################################################################
IF (MODULE_tinytcp)

    #生成动态库  静态库则 STATIC  
    add_library (tinytcplib SHARED      ${tinytcp_LIB_SRCS})  
    add_library (tinytcps STATIC        ${tinytcp_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(tinytcplib   PROPERTIES 
                                        VERSION     ${tinytcp_LIB_VERSION} 
                                        SOVERSION   ${tinytcp_LIB_SOVERSION}  )
ELSE (MODULE_tinytcp)
    MESSAGE(STATUS "Not Include tinytcp module.")
ENDIF (MODULE_tinytcp)





########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_tinytcp)
    add_executable(TestTinyTCP.elf    tinytcpTest.c)
    add_dependencies(TestTinyTCP.elf          tinytcplib loglib)
    target_link_libraries(TestTinyTCP.elf     tinytcplib loglib)

ELSE (TEST_MODULE_FLAG AND MODULE_tinytcp)
    MESSAGE(STATUS "Not Include system_instrument module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_tinytcp)



