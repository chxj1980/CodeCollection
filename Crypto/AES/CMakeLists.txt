########################################################################################
#############               ���� aes ���ļ�                            ############## 
########################################################################################
LIST (APPEND aes_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/aes.c
    )

    
    
########################################################################################
#############               ���� aes ��汾��                          ############## 
########################################################################################
set(aes_LIB_VERSION     "1.0.0")
set(aes_LIB_SOVERSION   "1")



########################################################################################
#############              ����ͷ�ļ�Ŀ¼                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Crypto
    ${PROJECT_SOURCE_DIR}/Crypto/AES
)  



########################################################################################
#############               ���� ���ӿ��ļ�Ŀ¼                           ############## 
########################################################################################
link_directories(  
    /usr/local/lib   
    )  


    
########################################################################################
#############           ����Ŀ����ļ� �� �����汾��                      ############## 
########################################################################################
IF (MODULE_aes)
    #���ɶ�̬��  ��̬���� STATIC  
    add_library (aeslib SHARED          ${aes_LIB_SRCS})  
    add_library (aess   STATIC          ${aes_LIB_SRCS})  
    # ���ð汾�ţ�SOVERSIONΪAPI�汾��
    set_target_properties(aeslib    PROPERTIES 
                                    VERSION     ${aes_LIB_VERSION}
                                    SOVERSION   ${aes_LIB_SOVERSION} )
ELSE (MODULE_aes)
    MESSAGE(STATUS "Not Include aes module.")
ENDIF (MODULE_aes)





########################################################################################
#############                 ����Ŀ�������ļ�                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_aes)

    add_executable(TestAES.elf    aesTest.c)
    add_dependencies(TestAES.elf          aeslib loglib)
    target_link_libraries(TestAES.elf     aeslib loglib)

ELSE (TEST_MODULE_FLAG AND MODULE_aes)
    MESSAGE(STATUS "Not Include aes module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_aes)
