########################################################################################
#############              生成 sntp 库文件                               ############## 
########################################################################################
LIST (APPEND sntp_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/sntp.c  
    )

    

########################################################################################
#############               设置 sntp 库版本号                          ############## 
########################################################################################
set(sntp_LIB_VERSION     "1.0.0")
set(sntp_LIB_SOVERSION   "1")

    
    
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Network
    ${PROJECT_SOURCE_DIR}/Network/SNTP
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
IF (MODULE_sntp)

    #生成动态库  静态库则 STATIC  
    add_library (sntplib SHARED      ${sntp_LIB_SRCS})  
    add_library (sntps STATIC        ${sntp_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(sntplib   PROPERTIES 
                                    VERSION     ${sntp_LIB_VERSION} 
                                    SOVERSION   ${sntp_LIB_SOVERSION} )
ELSE (MODULE_sntp)
    MESSAGE(STATUS "Not Include sntp module.")
ENDIF (MODULE_sntp)





########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_sntp)
    add_executable(TestSNTP.elf    sntpTest.c)
    add_dependencies(TestSNTP.elf          sntplib loglib )
    target_link_libraries(TestSNTP.elf     sntplib loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_sntp)
    MESSAGE(STATUS "Not Include sntp module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_sntp)



