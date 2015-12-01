########################################################################################
#############               生成 sha128 库文件                            ############## 
########################################################################################
LIST (APPEND sha128_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/SHA1.cpp
    )

          
           
########################################################################################
#############               设置 sha128 库版本号                          ############## 
########################################################################################
set(sha128_LIB_VERSION     "1.0.0")
set(sha128_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Crypto
    ${PROJECT_SOURCE_DIR}/Crypto/SHA128
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
IF (MODULE_sha128)
    #生成动态库  静态库则 STATIC  
    add_library (sha128lib    SHARED          ${sha128_LIB_SRCS})  
    add_library (sha128s      STATIC          ${sha128_LIB_SRCS})  
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(sha128lib   PROPERTIES 
                                    VERSION     ${sha128_LIB_VERSION}
                                    SOVERSION   ${sha128_LIB_SOVERSION} )
ELSE (MODULE_sha128)
    MESSAGE(STATUS "Not Include sha128 module.")
ENDIF (MODULE_sha128)





########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_sha128)
    add_executable(TestSha128.elf  sha128Test.cpp)
    add_dependencies(TestSha128.elf    sha128lib  loglib)
    target_link_libraries(TestSha128.elf   loglib  sha128lib )

ELSE (TEST_MODULE_FLAG AND MODULE_sha128)
    MESSAGE(STATUS "Not Include sha128 module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_sha128)
