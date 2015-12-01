########################################################################################
#############               生成 base64c 库文件                            ############## 
########################################################################################
LIST (APPEND base64c_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/base64.c
    )
    
   
       
########################################################################################
#############               设置 base64c 库版本号                          ############## 
########################################################################################
set(base64c_LIB_VERSION     "1.0.0")
set(base64c_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Crypto
    ${PROJECT_SOURCE_DIR}/Crypto/Base64C   
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
IF (MODULE_base64c)

    #生成动态库  静态库则 STATIC  
    add_library (base64clib  SHARED          ${base64c_LIB_SRCS})  
    add_library (base64cs    STATIC          ${base64c_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(base64clib     PROPERTIES 
                                        VERSION     ${base64c_LIB_VERSION} 
                                        SOVERSION   ${base64c_LIB_SOVERSION} )
ELSE (MODULE_base64c)
    MESSAGE(STATUS "Not Include base64c module.")
ENDIF (MODULE_base64c)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_base64c)
    add_executable(TestBase64c.elf    base64cTest.c)
    add_dependencies(TestBase64c.elf          base64clib loglib)
    target_link_libraries(TestBase64c.elf     base64clib loglib)

ELSE (TEST_MODULE_FLAG AND MODULE_base64c)
    MESSAGE(STATUS "Not Include base64c module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_base64c)



