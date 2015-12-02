
########################################################################################
#############               生成 http_fetch 库文件                           ############## 
########################################################################################
LIST (APPEND http_fetch_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/http_error_codes.c
    ${CMAKE_CURRENT_SOURCE_DIR}/http_fetcher.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    )
    

    
########################################################################################
#############               设置 http_fetch 库版本号                         ############## 
########################################################################################
set(http_fetch_LIB_VERSION     "1.0.0")
set(http_fetch_LIB_SOVERSION   "1")


   
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Network
    ${PROJECT_SOURCE_DIR}/Network/HttpFetcher
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
IF (MODULE_http_fetch)
    #生成动态库  静态库则 STATIC  
    add_library (http_fetchlib SHARED          ${http_fetch_LIB_SRCS})  
    add_library (http_fetchs   STATIC          ${http_fetch_LIB_SRCS})  
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(http_fetchlib     PROPERTIES 
                                            VERSION     ${http_fetch_LIB_VERSION} 
                                            SOVERSION   ${http_fetch_LIB_SOVERSION} )
ELSE (MODULE_http_fetch)
    MESSAGE(STATUS "Not Include http_fetch module.")
ENDIF (MODULE_http_fetch)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_http_fetch)
    add_executable(TestHttpFetcher.elf  test_fetch.c)
    add_dependencies(TestHttpFetcher.elf    http_fetchlib)
    target_link_libraries(TestHttpFetcher.elf   http_fetchlib)

ELSE (TEST_MODULE_FLAG AND MODULE_http_fetch)
    MESSAGE(STATUS "Not Include http_fetch module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_http_fetch)




