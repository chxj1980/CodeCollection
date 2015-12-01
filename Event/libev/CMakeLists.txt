########################################################################################
#############              生成 libev 库文件                               ############## 
########################################################################################
LIST (APPEND libev_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/ev.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ev_epoll.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ev_kqueue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ev_poll.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ev_port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ev_select.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ev_win32.c
    ${CMAKE_CURRENT_SOURCE_DIR}/event.c
    
#    ${CMAKE_CURRENT_SOURCE_DIR}/
    )



########################################################################################
#############               设置 libev 库版本号                          ############## 
########################################################################################
set(libev_LIB_VERSION     "1.0.0")
set(libev_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Messages
    ${PROJECT_SOURCE_DIR}/Messages/libev
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
IF (MODULE_libev)

    #生成动态库  静态库则 STATIC  
    add_library (libevlib     SHARED      ${libev_LIB_SRCS})  
    add_library (libevs       STATIC        ${libev_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(libevlib    PROPERTIES 
                                        VERSION     ${libev_LIB_VERSION} 
                                        SOVERSION   ${libev_LIB_SOVERSION} )
ELSE (MODULE_libev)
    MESSAGE(STATUS "Not Include libev module.")
ENDIF (MODULE_libev)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_libev)
    add_executable(TestLibev.elf    libevTest.c)
    add_dependencies(TestLibev.elf        libevlib loglib)
    target_link_libraries(TestLibev.elf   libevlib loglib)

ELSE (TEST_MODULE_FLAG AND MODULE_libev)
    MESSAGE(STATUS "Not Include libev module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_libev)




