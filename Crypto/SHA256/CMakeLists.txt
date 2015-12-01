########################################################################################
#############               生成 sha256 库文件                            ############## 
########################################################################################
LIST (APPEND sha256_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/sha2.c
    )

    
    
########################################################################################
#############               设置 sha2 库版本号                          ############## 
########################################################################################
set(sha2_LIB_VERSION     "1.0.0")
set(sha2_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Crypto
    ${PROJECT_SOURCE_DIR}/Crypto/SHA256
    ${PROJECT_SOURCE_DIR}/Crypto/SHA256/include
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
IF (MODULE_sha256)
    #生成动态库  静态库则 STATIC  
    add_library (sha256lib  SHARED          ${sha256_LIB_SRCS})  
    add_library (sha256s    STATIC          ${sha256_LIB_SRCS})  
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(sha256lib   PROPERTIES 
                                      VERSION     ${sha2_LIB_VERSION} 
                                      SOVERSION   ${sha2_LIB_SOVERSION} )
ELSE (MODULE_sha256)
    MESSAGE(STATUS "Not Include sha256 module.")
ENDIF (MODULE_sha256)





########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_sha256)
    add_executable(TestSha256.elf  sha256Test.c)
    add_dependencies(TestSha256.elf    sha256lib  loglib)
    target_link_libraries(TestSha256.elf   loglib  sha256lib )

ELSE (TEST_MODULE_FLAG AND MODULE_sha256)
    MESSAGE(STATUS "Not Include sha256 module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_sha256)
