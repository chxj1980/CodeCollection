########################################################################################
#############               生成 base64cpp 库文件                            ############## 
########################################################################################
LIST (APPEND base64cpp_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/base64.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cdecode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cencode.c
    )
    
   
       
########################################################################################
#############               设置 base64cpp 库版本号                          ############## 
########################################################################################
set(base64cpp_LIB_VERSION     "1.2.1")
set(base64cpp_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Crypto
    ${PROJECT_SOURCE_DIR}/Crypto/Base64Cpp
    ${PROJECT_SOURCE_DIR}/Crypto/Base64Cpp/includes   
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
IF (MODULE_base64cpp)

    #生成动态库  静态库则 STATIC  
    add_library (base64cpplib  SHARED          ${base64cpp_LIB_SRCS})  
    add_library (base64cpps    STATIC          ${base64cpp_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(base64cpplib     PROPERTIES 
                                        VERSION     ${base64cpp_LIB_VERSION} 
                                        SOVERSION   ${base64cpp_LIB_SOVERSION} )
ELSE (MODULE_base64cpp)
    MESSAGE(STATUS "Not Include base64cpp module.")
ENDIF (MODULE_base64cpp)




########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_base64cpp)
    add_executable(TestBase64cpp.elf    test/base64cppTest.c)
    add_dependencies(TestBase64cpp.elf          base64cpplib loglib)
    target_link_libraries(TestBase64cpp.elf     base64cpplib loglib)

ELSE (TEST_MODULE_FLAG AND MODULE_base64cpp)
    MESSAGE(STATUS "Not Include base64c module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_base64cpp)






