########################################################################################
#############              生成 hash 库文件                               ############## 
########################################################################################
LIST (APPEND hash_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/hash.c
#    ${CMAKE_CURRENT_SOURCE_DIR}/
    )



########################################################################################
#############               设置 hash 库版本号                          ############## 
########################################################################################
set(hash_LIB_VERSION     "1.0.0")
set(hash_LIB_SOVERSION   "1")



########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Settings
    ${PROJECT_SOURCE_DIR}/Settings/Hash
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
IF (MODULE_hash)

    #生成动态库  静态库则 STATIC  
    add_library (hashlib     SHARED      ${hash_LIB_SRCS})  
    add_library (hashs       STATIC        ${hash_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(hashlib    PROPERTIES 
                                        VERSION     ${hash_LIB_VERSION} 
                                        SOVERSION   ${hash_LIB_SOVERSION} )
ELSE (MODULE_hash)
    MESSAGE(STATUS "Not Include hash module.")
ENDIF (MODULE_hash)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_hash)
    add_executable(TestHash.elf  test.c)
    add_dependencies(TestHash.elf        hashlib  loglib)
    target_link_libraries(TestHash.elf   hashlib  loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_hash)
    MESSAGE(STATUS "Not Include hash module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_hash)




