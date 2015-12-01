########################################################################################
#############               生成 desc 库文件                            ############## 
########################################################################################
LIST (APPEND desc_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/des.c
    )
    
    
           
########################################################################################
#############               设置 desc 库版本号                          ############## 
########################################################################################
set(desc_LIB_VERSION     "1.0.0")
set(desc_LIB_SOVERSION   "1")



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
IF (MODULE_desc)

    #生成动态库  静态库则 STATIC  
    add_library (desclib SHARED          ${desc_LIB_SRCS})  
    add_library (descs   STATIC          ${desc_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(desclib    PROPERTIES 
                                    VERSION     ${desc_LIB_VERSION} 
                                    SOVERSION   ${desc_LIB_SOVERSION} )
ELSE (MODULE_desc)
    MESSAGE(STATUS "Not Include desc module.")
ENDIF (MODULE_desc)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_desc)
    add_executable(TestDesc.elf  descTest.c)
    add_dependencies(TestDesc.elf    desclib  loglib)
    target_link_libraries(TestDesc.elf   loglib  desclib )

ELSE (TEST_MODULE_FLAG AND MODULE_desc)
    MESSAGE(STATUS "Not Include jsoncpp module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_desc)


