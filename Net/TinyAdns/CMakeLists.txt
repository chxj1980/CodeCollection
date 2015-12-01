########################################################################################
#############              生成 tadns 库文件                               ############## 
########################################################################################
LIST (APPEND tadns_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/tadns.c  
    )



########################################################################################
#############               设置 tadns 库版本号                          ############## 
########################################################################################
set(tadns_LIB_VERSION     "1.42.0")
set(tadns_LIB_SOVERSION   "1")


    
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Network
    ${PROJECT_SOURCE_DIR}/Network/TinyAdns
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
IF (MODULE_tadns)

    #生成动态库  静态库则 STATIC  
    add_library (tadnslib SHARED      ${tadns_LIB_SRCS})  
    add_library (tadnss STATIC        ${tadns_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(tadnslib   PROPERTIES 
                                    VERSION     ${tadns_LIB_VERSION} 
                                    SOVERSION   ${tadns_LIB_SOVERSION} )
ELSE (MODULE_tadns)
    MESSAGE(STATUS "Not Include tadns module.")
ENDIF (MODULE_tadns)





########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_tadns)
    add_executable(TestTinyAdns.elf    tinyadnsTest.c)
    add_dependencies(TestTinyAdns.elf          tadnslib loglib)
    target_link_libraries(TestTinyAdns.elf     tadnslib loglib)

ELSE (TEST_MODULE_FLAG AND MODULE_tadns)
    MESSAGE(STATUS "Not Include tiny adns module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_tadns)


