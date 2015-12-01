
########################################################################################
#############                      生成 unix2dos 库文件                      ############## 
########################################################################################
LIST (APPEND unix2dos_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/readahead.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/unix2dos.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    )
    

    
########################################################################################
#############               设置 unix2dos 库版本号                         ############## 
########################################################################################
set(unix2dos_LIB_VERSION     "1.0.0")
set(unix2dos_LIB_SOVERSION   "1")


   
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Utils
    ${PROJECT_SOURCE_DIR}/Utils/ParserJsonC
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
IF (MODULE_unix2dos)
    #生成动态库  静态库则 STATIC  
    add_library (unix2doslib SHARED          ${unix2dos_LIB_SRCS})  
    add_library (unix2doss   STATIC          ${unix2dos_LIB_SRCS}) 
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(unix2doslib    PROPERTIES 
                                        VERSION ${unix2dos_LIB_VERSION} 
                                        SOVERSION ${unix2dos_LIB_SOVERSION} )
ELSE (MODULE_unix2dos)
    MESSAGE(STATUS "Not Include unix2dos module.")
ENDIF (MODULE_unix2dos)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_unix2dos)
    add_executable(TestUnix2dos.elf     unix2dosTest.cpp)
    add_dependencies(TestUnix2dos.elf       unix2doslib )
    target_link_libraries(TestUnix2dos.elf   unix2doslib )

ELSE (TEST_MODULE_FLAG AND MODULE_unix2dos)
    MESSAGE(STATUS "Not Include unix2dos module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_unix2dos)




