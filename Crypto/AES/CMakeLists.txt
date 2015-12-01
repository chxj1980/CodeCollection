########################################################################################
#############               生成 aes 库文件                            ############## 
########################################################################################
LIST (APPEND aes_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/aes.c
    )

    
    
########################################################################################
#############               设置 aes 库版本号                          ############## 
########################################################################################
set(aes_LIB_VERSION     "1.0.0")
set(aes_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Crypto
    ${PROJECT_SOURCE_DIR}/Crypto/AES
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
IF (MODULE_aes)
    #生成动态库  静态库则 STATIC  
    add_library (aeslib SHARED          ${aes_LIB_SRCS})  
    add_library (aess   STATIC          ${aes_LIB_SRCS})  
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(aeslib    PROPERTIES 
                                    VERSION     ${aes_LIB_VERSION}
                                    SOVERSION   ${aes_LIB_SOVERSION} )
ELSE (MODULE_aes)
    MESSAGE(STATUS "Not Include aes module.")
ENDIF (MODULE_aes)





########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_aes)

    add_executable(TestAES.elf    aesTest.c)
    add_dependencies(TestAES.elf          aeslib loglib)
    target_link_libraries(TestAES.elf     aeslib loglib)

ELSE (TEST_MODULE_FLAG AND MODULE_aes)
    MESSAGE(STATUS "Not Include aes module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_aes)

