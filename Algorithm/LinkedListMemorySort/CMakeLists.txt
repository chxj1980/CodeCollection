########################################################################################
#############              生成 llmsort 库文件                               ############## 
########################################################################################
LIST (APPEND llmsort_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/LLMSort.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/
    )



########################################################################################
#############               设置 llmsort 库版本号                          ############## 
########################################################################################
set(llmsort_LIB_VERSION     "1.0.0")
set(llmsort_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Settings
    ${PROJECT_SOURCE_DIR}/Settings/LinkedListMemorySort
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
IF (MODULE_llmsort)

    #生成动态库  静态库则 STATIC  
    add_library (llmsortlib     SHARED      ${llmsort_LIB_SRCS})  
    add_library (llmsorts       STATIC        ${llmsort_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(llmsortlib    PROPERTIES 
                                        VERSION     ${llmsort_LIB_VERSION} 
                                        SOVERSION   ${llmsort_LIB_SOVERSION} )
ELSE (MODULE_llmsort)
    MESSAGE(STATUS "Not Include llmsort module.")
ENDIF (MODULE_llmsort)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_llmsort)
    add_executable(TestLLMSort.elf  llmsortTest.c)
    add_dependencies(TestLLMSort.elf        llmsortlib  loglib)
    target_link_libraries(TestLLMSort.elf   llmsortlib  loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_llmsort)
    MESSAGE(STATUS "Not Include jsoncpp module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_llmsort)




