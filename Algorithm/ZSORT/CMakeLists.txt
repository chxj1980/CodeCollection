########################################################################################
#############              生成 zsort 库文件                               ############## 
########################################################################################
LIST (APPEND zsort_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/ZSort.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/
    )



########################################################################################
#############               设置 zsort 库版本号                          ############## 
########################################################################################
set(zsort_LIB_VERSION     "1.0.0")
set(zsort_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Settings
    ${PROJECT_SOURCE_DIR}/Settings/HashTableCpp
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
IF (MODULE_zsort)

    #生成动态库  静态库则 STATIC  
    add_library (zsortlib     SHARED      ${zsort_LIB_SRCS})  
    add_library (zsorts       STATIC        ${zsort_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(zsortlib    PROPERTIES 
                                        VERSION     ${zsort_LIB_VERSION} 
                                        SOVERSION   ${zsort_LIB_SOVERSION} )
ELSE (MODULE_zsort)
    MESSAGE(STATUS "Not Include zsort module.")
ENDIF (MODULE_zsort)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_zsort)
    add_executable(TestZSort.elf  zsortTest.c)
    add_dependencies(TestZSort.elf        zsortlib  loglib)
    target_link_libraries(TestZSort.elf   zsortlib  loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_zsort)
    MESSAGE(STATUS "Not Include jsoncpp module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_zsort)




