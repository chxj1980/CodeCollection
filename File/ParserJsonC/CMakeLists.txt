
########################################################################################
#############                      生成 cjson 库文件                      ############## 
########################################################################################
LIST (APPEND cjson_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/cJSON.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    )
    

    
########################################################################################
#############               设置 cjson 库版本号                         ############## 
########################################################################################
set(cjson_LIB_VERSION     "1.0.0")
set(cjson_LIB_SOVERSION   "1")


   
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Utils
    ${PROJECT_SOURCE_DIR}/Utils/ParserJsonC
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
IF (MODULE_cjson)
    #生成动态库  静态库则 STATIC  
    add_library (cjsonlib SHARED          ${cjson_LIB_SRCS})  
    add_library (cjsons   STATIC          ${cjson_LIB_SRCS}) 
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(cjsonlib    PROPERTIES 
                                        VERSION ${cjson_LIB_VERSION} 
                                        SOVERSION ${cjson_LIB_SOVERSION} )
ELSE (MODULE_cjson)
    MESSAGE(STATUS "Not Include cjson module.")
ENDIF (MODULE_cjson)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_cjson)
    add_executable(TestCJson.elf  cJsonTest.c)
    add_dependencies(TestCJson.elf    cjsonlib)
    target_link_libraries(TestCJson.elf   cjsonlib)

ELSE (TEST_MODULE_FLAG AND MODULE_cjson)
    MESSAGE(STATUS "Not Include cjson module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_cjson)




