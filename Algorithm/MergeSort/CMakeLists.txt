########################################################################################
#############              生成 mergesort 库文件                               ############## 
########################################################################################
LIST (APPEND mergesort_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/LLMSort.c
    ${CMAKE_CURRENT_SOURCE_DIR}/MergeSort.c
    ${CMAKE_CURRENT_SOURCE_DIR}/StaticMergeSort.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/
    )



########################################################################################
#############               设置 mergesort 库版本号                          ############## 
########################################################################################
set(mergesort_LIB_VERSION     "1.0.0")
set(mergesort_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Settings
    ${PROJECT_SOURCE_DIR}/Settings/MergeSort
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
IF (MODULE_mergesort)

    #生成动态库  静态库则 STATIC  
    add_library (mergesortlib     SHARED      ${mergesort_LIB_SRCS})  
    add_library (mergesorts       STATIC        ${mergesort_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(mergesortlib    PROPERTIES 
                                        VERSION     ${mergesort_LIB_VERSION} 
                                        SOVERSION   ${mergesort_LIB_SOVERSION} )
ELSE (MODULE_mergesort)
    MESSAGE(STATUS "Not Include mergesort module.")
ENDIF (MODULE_mergesort)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_mergesort)
    add_executable(TestMergeSort.elf  testMergeSort.c)
    add_dependencies(TestMergeSort.elf        mergesortlib  loglib)
    target_link_libraries(TestMergeSort.elf   mergesortlib  loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_mergesort)
    MESSAGE(STATUS "Not Include mergesort module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_mergesort)




