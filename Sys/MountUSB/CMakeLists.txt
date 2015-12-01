########################################################################################
#############                生成 mountusb 库文件                         ############## 
########################################################################################
LIST (APPEND mountusb_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/mountusb.c
    )
    
    

########################################################################################
#############                设置 mountusb 库版本号                       ############## 
########################################################################################
set(mountusb_LIB_VERSION     "1.42.0")
set(mountusb_LIB_SOVERSION   "1")




########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Systerm
    ${PROJECT_SOURCE_DIR}/Systerm/MountUSB
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
IF (MODULE_mountusb)
    #生成动态库  静态库则 STATIC  
    add_library (mountusblib SHARED      ${mountusb_LIB_SRCS})  
    add_library (mountusbs STATIC        ${mountusb_LIB_SRCS})  
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(mountusblib   PROPERTIES 
                                        VERSION     ${mountusb_LIB_VERSION} 
                                        SOVERSION   ${mountusb_LIB_SOVERSION} )
ELSE (MODULE_mountusb)
    MESSAGE(STATUS "Not Include mountusb module.")
ENDIF (MODULE_mountusb)




########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_mountusb)
    add_executable(TestMountUSB.elf    mountusbTest.c)
    add_dependencies(TestMountUSB.elf          mountusblib loglib)
    target_link_libraries(TestMountUSB.elf     mountusblib loglib)

ELSE (TEST_MODULE_FLAG AND MODULE_mountusb)
    MESSAGE(STATUS "Not Include mount usb module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_mountusb)
