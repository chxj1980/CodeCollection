########################################################################################
##########                  生成 general_printf 库文件                       ########### 
########################################################################################
LIST (APPEND general_printf_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneralPrintf.c
    )


    
########################################################################################
###########                 设置 general_printf 库版本号                     ########### 
########################################################################################
set(general_printf_LIB_VERSION     "1.0.0")
set(general_printf_LIB_SOVERSION   "1")



########################################################################################
##########            添加 编译库文件所需的头文件目录                        ########### 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Log   
    ${PROJECT_SOURCE_DIR}/Log/GeneralPrintf
)  
  
  
  
########################################################################################
##########            添加 链接库文件目录                                    ########### 
########################################################################################
link_directories(  
    /usr/local/lib   
    )  

    
    
########################################################################################
##########        生成目标库文件 添加所需要依赖库 设置依赖关系               ########### 
########################################################################################
IF (MODULE_general_printf)
    
    #生成动态库  静态库则 STATIC  
    add_library (general_printflib SHARED          ${general_printf_LIB_SRCS})  
    add_library (general_printfs STATIC            ${general_printf_LIB_SRCS})  
        
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(general_printflib   PROPERTIES 
                                    VERSION     ${general_printf_LIB_VERSION} 
                                    SOVERSION   ${general_printf_LIB_SOVERSION} )

ELSE (MODULE_general_printf)
    MESSAGE(STATUS "Not Include general_printf module.")
ENDIF (MODULE_general_printf)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_general_printf)

    add_executable(TestGeneralPrintf.elf    general_printfTest.c)
    add_dependencies(TestGeneralPrintf.elf          general_printflib loglib)
    target_link_libraries(TestGeneralPrintf.elf     general_printflib loglib)

ELSE (TEST_MODULE_FLAG AND MODULE_general_printf)
    MESSAGE(STATUS "Not Include general_printf module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_general_printf)



