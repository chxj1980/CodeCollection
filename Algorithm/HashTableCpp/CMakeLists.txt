########################################################################################
#############              生成 hashtablecpp 库文件                               ############## 
########################################################################################
LIST (APPEND hashtablecpp_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/HTAB.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/
    )



########################################################################################
#############               设置 hashtablecpp 库版本号                          ############## 
########################################################################################
set(hashtablecpp_LIB_VERSION     "1.0.0")
set(hashtablecpp_LIB_SOVERSION   "1")



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
IF (MODULE_hashtablecpp)

    #生成动态库  静态库则 STATIC  
    add_library (hashtablecpplib     SHARED      ${hashtablecpp_LIB_SRCS})  
    add_library (hashtablecpps       STATIC        ${hashtablecpp_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(hashtablecpplib    PROPERTIES 
                                        VERSION     ${hashtablecpp_LIB_VERSION} 
                                        SOVERSION   ${hashtablecpp_LIB_SOVERSION} )
ELSE (MODULE_hashtablecpp)
    MESSAGE(STATUS "Not Include hashtablecpp module.")
ENDIF (MODULE_hashtablecpp)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_hashtablecpp)
    add_executable(TestHashTableCpp.elf  hashtablecppTest.cpp)
    add_dependencies(TestHashTableCpp.elf        hashtablecpplib  loglib)
    target_link_libraries(TestHashTableCpp.elf   hashtablecpplib  loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_hashtablecpp)
    MESSAGE(STATUS "Not Include hashtablecpp module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_hashtablecpp)




