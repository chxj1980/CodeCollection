########################################################################################
#############               生成 rsa 库文件                            ############## 
########################################################################################
LIST (APPEND rsa_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/RSA.cpp
    )
    
      
           
########################################################################################
#############               设置 rsa 库版本号                          ############## 
########################################################################################
set(rsa_LIB_VERSION     "1.0.0")
set(rsa_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Crypto
    ${PROJECT_SOURCE_DIR}/Crypto/RSA
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
IF (MODULE_rsa)
    #生成动态库  静态库则 STATIC  
    add_library (rsalib SHARED          ${rsa_LIB_SRCS})  
    add_library (rsas   STATIC          ${rsa_LIB_SRCS})  
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(rsalib    PROPERTIES 
                                    VERSION     ${rsa_LIB_VERSION} 
                                    SOVERSION   ${rsa_LIB_SOVERSION} )
ELSE (MODULE_rsa)
    MESSAGE(STATUS "Not Include rsa module.")
ENDIF (MODULE_rsa)




########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_rsa)
    add_executable(TestRsa.elf  rsaTest.cpp)
    add_dependencies(TestRsa.elf    rsalib  loglib)
    target_link_libraries(TestRsa.elf   loglib  rsalib )

ELSE (TEST_MODULE_FLAG AND MODULE_rsa)
    MESSAGE(STATUS "Not Include rsa module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_rsa)

