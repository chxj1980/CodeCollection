########################################################################################
#############              生成 sntplib 库文件                               ############## 
########################################################################################
LIST (APPEND sntplib_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/sntp.c  
    )

    

########################################################################################
#############               设置 sntplib 库版本号                          ############## 
########################################################################################
set(sntplib_LIB_VERSION     "1.0.0")
set(sntplib_LIB_SOVERSION   "1")

    
    
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Network
    ${PROJECT_SOURCE_DIR}/Network/SNTPlib
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
IF (MODULE_sntplib)

    #生成动态库  静态库则 STATIC  
    add_library (sntpliblib SHARED      ${sntplib_LIB_SRCS})  
    add_library (sntplibs STATIC        ${sntplib_LIB_SRCS})  
        
    # 设置依赖关系，如果当前库是最底层的共享库，则不需要设置
    add_dependencies (sntpliblib  loglib  m)
    add_dependencies (sntplibs    loglib  m)
    
    # 添加要链接的共享库, 库的顺序就是编译器的链接时顺序
    target_link_libraries (sntpliblib  loglib m)
    target_link_libraries (sntplibs    loglib m)
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(sntpliblib   PROPERTIES 
                                    VERSION     ${sntplib_LIB_VERSION} 
                                    SOVERSION   ${sntplib_LIB_SOVERSION} )
ELSE (MODULE_sntplib)
    MESSAGE(STATUS "Not Include sntplib module.")
ENDIF (MODULE_sntplib)





########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_sntplib)
    add_executable(TestSNTPlib.elf    sntpliblibTest.c)
    add_dependencies(TestSNTPlib.elf          sntpliblib loglib m)
    target_link_libraries(TestSNTPlib.elf     sntpliblib loglib m)

ELSE (TEST_MODULE_FLAG AND MODULE_sntplib)
    MESSAGE(STATUS "Not Include sntplib module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_sntplib)



