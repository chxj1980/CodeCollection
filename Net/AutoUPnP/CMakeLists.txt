########################################################################################
#############                生成 autoupnp 库文件                         ############## 
########################################################################################
LIST (APPEND autoupnp_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/upnp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/autoupnp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/notify.c
    ${CMAKE_CURRENT_SOURCE_DIR}/registry.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/
    )
    
    

########################################################################################
#############                设置 autoupnp 库版本号                       ############## 
########################################################################################
set(autoupnp_LIB_VERSION     "0.4.4")
set(autoupnp_LIB_SOVERSION   "1")




########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Systerm
    ${PROJECT_SOURCE_DIR}/Systerm/AutoUPnP
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
IF (MODULE_autoupnp)

    #生成动态库  静态库则 STATIC  
    add_library (autoupnplib SHARED      ${autoupnp_LIB_SRCS})  
    add_library (autoupnps STATIC        ${autoupnp_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(autoupnplib   PROPERTIES 
                                        VERSION     ${autoupnp_LIB_VERSION} 
                                        SOVERSION   ${autoupnp_LIB_SOVERSION} )
ELSE (MODULE_autoupnp)
    MESSAGE(STATUS "Not Include autoupnp module.")
ENDIF (MODULE_autoupnp)




########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_autoupnp)
    add_executable(TestAutoUpnp.elf    autoupnpTest.c)
    add_dependencies(TestAutoUpnp.elf          autoupnplib loglib)
    target_link_libraries(TestAutoUpnp.elf     autoupnplib loglib)

ELSE (TEST_MODULE_FLAG AND MODULE_autoupnp)
    MESSAGE(STATUS "Not Include mount usb module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_autoupnp)
