
########################################################################################
#############               生成 pic_convertion 库文件                          ############## 
########################################################################################
LIST (APPEND pic_convertion_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/convert.c
    ${CMAKE_CURRENT_SOURCE_DIR}/string_parser.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tools.c
    )
    
    

########################################################################################
#############               添加源码子目录                                ############## 
########################################################################################
#add_subdirectory( Gif_2_HexData )
#add_subdirectory( HexData_2_Gif )
#add_subdirectory( text_split )

#MESSAGE("${CMAKE_CURRENT_SOURCE_DIR} status.")


 
########################################################################################
#############               设置 pic_convertion 库版本号                        ############## 
########################################################################################
set(pic_convertion_LIB_VERSION     "1.0.0")
set(pic_convertion_LIB_SOVERSION   "1")


   
########################################################################################
#############              添加头文件目录                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Views
    ${PROJECT_SOURCE_DIR}/Views/PicConversion
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
IF (MODULE_pic_convertion)
    #生成动态库  静态库则 STATIC  
    add_library (pic_convertionlib SHARED      ${pic_convertion_LIB_SRCS})  
    add_library (pic_convertions   STATIC      ${pic_convertion_LIB_SRCS})  
    
    # 设置版本号，SOVERSION为API版本号
    set_target_properties(pic_convertionlib   PROPERTIES 
                                        VERSION     ${pic_convertion_LIB_VERSION} 
                                        SOVERSION   ${pic_convertion_LIB_SOVERSION} )
ELSE (MODULE_pic_convertion)
    MESSAGE(STATUS "Not Include pic_convertion module.")
ENDIF (MODULE_pic_convertion)



########################################################################################
#############                 生成目标库测试文件                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_pic_convertion)
    add_executable(TestPicConversion.elf    convertTest.c)
    add_dependencies(TestPicConversion.elf      loglib  viewslib pic_convertionlib )
    target_link_libraries(TestPicConversion.elf loglib  viewslib pic_convertionlib )

ELSE (TEST_MODULE_FLAG AND MODULE_pic_convertion)
    MESSAGE(STATUS "Not Include pic_convertion module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_pic_convertion)




