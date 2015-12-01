########################################################################################
##########               生成 system_instrumentlib 库文件                    ########### 
########################################################################################
LIST (APPEND system_instrument_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/SystemInstrument.c
    )


########################################################################################
###########              设置 system_instrumentlib 库版本号                  ########### 
########################################################################################
set(system_instrument_LIB_VERSION     "1.0.0")
set(system_instrument_LIB_SOVERSION   "1")



########################################################################################
##########            添加 编译库文件所需的头文件目录                        ########### 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Log   
    ${PROJECT_SOURCE_DIR}/Log/InstrumentFunctions
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
IF (MODULE_system_instrument)
    add_definitions("-finstrument-functions")
    
    #生成动态库  静态库则 STATIC  
    add_library (system_instrumentlib SHARED         ${system_instrument_LIB_SRCS})  
    add_library (system_instruments STATIC            ${system_instrument_LIB_SRCS})  
    
    # 设置依赖关系，如果当前库是最底层的共享库，则不需要设置
    add_dependencies (system_instrumentlib   pthread)
    add_dependencies (system_instruments     pthread)
    
    # 添加要链接的共享库, 库的顺序就是编译器的链接时顺序
    target_link_libraries (system_instrumentlib  pthread)
    target_link_libraries (system_instruments    pthread)
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(system_instrumentlib   PROPERTIES 
                            VERSION     ${system_instrument_LIB_VERSION} 
                            SOVERSION   ${system_instrument_LIB_SOVERSION} )

ELSE (MODULE_system_instrument)
    MESSAGE(STATUS "Not Include system_instrument module.")
ENDIF (MODULE_system_instrument)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_system_instrument)
    add_definitions("-finstrument-functions")

    add_executable(TestSystemInstrument.elf    system_instrumentTest.cpp)
    add_dependencies(TestSystemInstrument.elf          system_instrumentlib loglib pthread)
    target_link_libraries(TestSystemInstrument.elf     system_instrumentlib loglib pthread)

ELSE (TEST_MODULE_FLAG AND MODULE_system_instrument)
    MESSAGE(STATUS "Not Include system_instrument module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_system_instrument)



