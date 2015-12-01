########################################################################################
#############               生成 md5lib 库文件                            ############## 
########################################################################################
LIST (APPEND md5lib_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/md5c.c
    )
    
  
           
########################################################################################
#############               设置 md5lib 库版本号                          ############## 
########################################################################################
set(md5lib_LIB_VERSION     "1.0.0")
set(md5lib_LIB_SOVERSION   "1")


  
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/Crypto
    ${PROJECT_SOURCE_DIR}/Crypto/MD5lib
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
IF (MODULE_md5lib)
    #生成动态库  静态库则 STATIC  
    add_library (md5liblib    SHARED          ${md5libc_LIB_SRCS})  
    add_library (md5libs      STATIC          ${md5libc_LIB_SRCS})  
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(md5liblib   PROPERTIES 
                                    VERSION     ${md5lib_LIB_VERSION}
                                    SOVERSION   ${md5lib_LIB_SOVERSION} )
ELSE (MODULE_md5lib)
    MESSAGE(STATUS "Not Include md5libc module.")
ENDIF (MODULE_md5lib)




########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_md5lib)
    add_executable(TestMd5lib.elf  md5libTest.c)
    add_dependencies(TestMd5lib.elf         md5liblib  loglib)
    target_link_libraries(TestMd5lib.elf   md5liblib loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_md5lib)
    MESSAGE(STATUS "Not Include md5c module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_md5lib)



