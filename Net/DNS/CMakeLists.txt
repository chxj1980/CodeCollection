########################################################################################
#############              生成 dns 库文件                               ############## 
########################################################################################
LIST (APPEND dns_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/dns.c  
    )




########################################################################################
#############               设置 dns 库版本号                          ############## 
########################################################################################
set(dns_LIB_VERSION     "1.0.0")
set(dns_LIB_SOVERSION   "1")


    
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Network
    ${PROJECT_SOURCE_DIR}/Network/DNS
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
IF (MODULE_dns)

    #生成动态库  静态库则 STATIC  
    add_library (dnslib SHARED      ${dns_LIB_SRCS})  
    add_library (dnss STATIC        ${dns_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(dnslib   PROPERTIES 
                                    VERSION     ${dns_LIB_VERSION} 
                                    SOVERSION   ${dns_LIB_SOVERSION} )
ELSE (MODULE_dns)
    MESSAGE(STATUS "Not Include dns module.")
ENDIF (MODULE_dns)





########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_dns)
    add_executable(TestDNS.elf    dnsTest.c)
    add_dependencies(TestDNS.elf          dnslib loglib )
    target_link_libraries(TestDNS.elf     dnslib loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_dns)
    MESSAGE(STATUS "Not Include system_instrument module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_dns)


