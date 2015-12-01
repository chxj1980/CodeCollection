########################################################################################
#############              生成 arp 库文件                               ############## 
########################################################################################
LIST (APPEND arp_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/arp_probe.c  
    )


    
    
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Network
    ${PROJECT_SOURCE_DIR}/Network/arp
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
IF (MODULE_arp)
    #生成动态库  静态库则 STATIC  
    add_library (arplib SHARED      ${arp_LIB_SRCS})  
    add_library (arps STATIC        ${arp_LIB_SRCS})  
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(arplib   PROPERTIES VERSION 1.0.0 SOVERSION 1 )
ELSE (MODULE_arp)
    MESSAGE(STATUS "Not Include arp module.")
ENDIF (MODULE_arp)





########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_arp)
    add_definitions("-finstrument-functions")

    add_executable(TestARP.elf    arpTest.c)
    add_dependencies(TestARP.elf          arplib loglib)
    target_link_libraries(TestARP.elf     arplib loglib)

ELSE (TEST_MODULE_FLAG AND MODULE_arp)
    MESSAGE(STATUS "Not Include arp module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_arp)


