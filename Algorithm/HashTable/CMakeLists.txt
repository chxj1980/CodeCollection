########################################################################################
#############              生成 hashtable 库文件                               ############## 
########################################################################################
LIST (APPEND hashtable_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/hashtable.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/
    )




########################################################################################
#############               添加源码子目录                                ############## 
########################################################################################
#add_subdirectory( MessageHandler )
#add_subdirectory( libev )




########################################################################################
#############               设置 hashtable 库版本号                          ############## 
########################################################################################
set(hashtable_LIB_VERSION     "1.0.0")
set(hashtable_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Settings
    ${PROJECT_SOURCE_DIR}/Settings/HashTable
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
IF (MODULE_hashtable)

    #生成动态库  静态库则 STATIC  
    add_library (hashtablelib     SHARED      ${hashtable_LIB_SRCS})  
    add_library (hashtables       STATIC        ${hashtable_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(hashtablelib    PROPERTIES 
                                        VERSION     ${hashtable_LIB_VERSION} 
                                        SOVERSION   ${hashtable_LIB_SOVERSION} )
ELSE (MODULE_hashtable)
    MESSAGE(STATUS "Not Include hashtable module.")
ENDIF (MODULE_hashtable)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_hashtable)
    add_executable(TestHashTable.elf  hashtableTest.c)
    add_dependencies(TestHashTable.elf        hashtablelib  loglib)
    target_link_libraries(TestHashTable.elf   hashtablelib  loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_hashtable)
    MESSAGE(STATUS "Not Include hashtable module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_hashtable)




