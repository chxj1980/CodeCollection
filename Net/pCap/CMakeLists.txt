########################################################################################
#############              生成 pCap 库文件                               ############## 
########################################################################################
LIST (APPEND pCap_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/pCap.c  
    )

    

########################################################################################
#############               设置 pCap 库版本号                          ############## 
########################################################################################
set(pCap_LIB_VERSION     "1.0.0")
set(pCap_LIB_SOVERSION   "1")

    
    
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Network
    ${PROJECT_SOURCE_DIR}/Network/pCap
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
IF (MODULE_pCap)

    #生成动态库  静态库则 STATIC  
    add_library (pCaplib SHARED      ${pCap_LIB_SRCS})  
    add_library (pCaps STATIC        ${pCap_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(pCaplib   PROPERTIES 
                                    VERSION     ${pCap_LIB_VERSION} 
                                    SOVERSION   ${pCap_LIB_SOVERSION} )
ELSE (MODULE_pCap)
    MESSAGE(STATUS "Not Include pCap module.")
ENDIF (MODULE_pCap)





########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_pCap)
    add_executable(TestpCap.elf    pCapTest.c)
    add_dependencies(TestpCap.elf          pCaplib loglib )
    target_link_libraries(TestpCap.elf     pCaplib loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_pCap)
    MESSAGE(STATUS "Not Include pCap module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_pCap)



