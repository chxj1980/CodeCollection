########################################################################################
#############               生成 descpp 库文件                            ############## 
########################################################################################
LIST (APPEND descpp_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/DES.cpp
    )
    
    
           
########################################################################################
#############               设置 descpp 库版本号                          ############## 
########################################################################################
set(descpp_LIB_VERSION     "1.0.0")
set(descpp_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Crypto
    ${PROJECT_SOURCE_DIR}/Crypto/DES
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
IF (MODULE_descpp)

    #生成动态库  静态库则 STATIC  
    add_library (descpplib SHARED          ${descpp_LIB_SRCS})  
    add_library (descpps   STATIC          ${descpp_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(descpplib    PROPERTIES 
                                    VERSION     ${descpp_LIB_VERSION} 
                                    SOVERSION   ${descpp_LIB_SOVERSION} )
ELSE (MODULE_descpp)
    MESSAGE(STATUS "Not Include descpp module.")
ENDIF (MODULE_descpp)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_descpp)
    add_executable(TestDescpp.elf  descppTest.cpp)
    add_dependencies(TestDescpp.elf    descpplib  loglib)
    target_link_libraries(TestDescpp.elf   loglib  descpplib )

ELSE (TEST_MODULE_FLAG AND MODULE_descpp)
    MESSAGE(STATUS "Not Include jsoncpp module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_descpp)


