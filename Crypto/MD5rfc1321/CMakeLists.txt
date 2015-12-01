########################################################################################
#############               生成 md5 库文件                            ############## 
########################################################################################
LIST (APPEND md5_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/md5.c
    )
    
  
           
########################################################################################
#############               设置 md5 库版本号                          ############## 
########################################################################################
set(md5_LIB_VERSION     "1.0.0")
set(md5_LIB_SOVERSION   "1")


  
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/Crypto
    ${PROJECT_SOURCE_DIR}/Crypto/MD5rfc1321
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
IF (MODULE_md5)
    #生成动态库  静态库则 STATIC  
    add_library (md5lib    SHARED          ${md5_LIB_SRCS})  
    add_library (md5s      STATIC          ${md5_LIB_SRCS})  
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(md5lib   PROPERTIES 
                                    VERSION     ${md5_LIB_VERSION}
                                    SOVERSION   ${md5_LIB_SOVERSION} )
ELSE (MODULE_md5)
    MESSAGE(STATUS "Not Include md5 module.")
ENDIF (MODULE_md5)




########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_md5)
    add_executable(TestMd5rfc1321.elf  md5Test.c)
    add_dependencies(TestMd5rfc1321.elf        md5lib  loglib)
    target_link_libraries(TestMd5rfc1321.elf   md5lib loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_md5)
    MESSAGE(STATUS "Not Include md5 module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_md5)




