########################################################################################
#############              生成 dhcp 库文件                               ############## 
########################################################################################
LIST (APPEND dhcp_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/dualserverd.cpp  
    )


########################################################################################
#############               设置 dhcp 库版本号                          ############## 
########################################################################################
set(dhcp_LIB_VERSION     "1.0.0")
set(dhcp_LIB_SOVERSION   "1")

    
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Network 
    ${PROJECT_SOURCE_DIR}/Network/DHCP
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
IF (MODULE_dhcp)

    #生成动态库  静态库则 STATIC  
    add_library (dhcplib SHARED      ${dhcp_LIB_SRCS})  
    add_library (dhcps STATIC        ${dhcp_LIB_SRCS})  
    
    # 设置依赖关系，如果当前库是最底层的共享库，则不需要设置
    add_dependencies (dhcplib  loglib  pthread)
    add_dependencies (dhcps    loglib  pthread)
    
    # 添加要链接的共享库, 库的顺序就是编译器的链接时顺序
    target_link_libraries (dhcplib  loglib pthread)
    target_link_libraries (dhcps    loglib pthread)

    # 设置版本号，SOVERSION为API版本号
    set_target_properties(dhcplib   PROPERTIES 
                                    VERSION     ${dhcp_LIB_VERSION} 
                                    SOVERSION   ${dhcp_LIB_SOVERSION} )
ELSE (MODULE_dhcp)
    MESSAGE(STATUS "Not Include dhcp module.")
ENDIF (MODULE_dhcp)




########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_dns)
    add_executable(TestDHCP.elf    dhcpTest.cpp)
    add_dependencies(TestDHCP.elf          dhcplib loglib pthread)
    target_link_libraries(TestDHCP.elf     dhcplib loglib pthread)

ELSE (TEST_MODULE_FLAG AND MODULE_dns)
    MESSAGE(STATUS "Not Include dhcp module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_dns)

