########################################################################################
#############              ���� dns ���ļ�                               ############## 
########################################################################################
LIST (APPEND dns_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/dns.c  
    )




########################################################################################
#############               ���� dns ��汾��                          ############## 
########################################################################################
set(dns_LIB_VERSION     "1.0.0")
set(dns_LIB_SOVERSION   "1")


    
########################################################################################
#############              ����ͷ�ļ�Ŀ¼                                 ############## 
########################################################################################
include_directories(  
    ${PROJECT_SOURCE_DIR}/includes  
    ${PROJECT_SOURCE_DIR}/Network
    ${PROJECT_SOURCE_DIR}/Network/DNS
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
IF (MODULE_dns)

    #���ɶ�̬��  ��̬���� STATIC  
    add_library (dnslib SHARED      ${dns_LIB_SRCS})  
    add_library (dnss STATIC        ${dns_LIB_SRCS})  
    
    # ���ð汾�ţ�SOVERSIONΪAPI�汾��
    set_target_properties(dnslib   PROPERTIES 
                                    VERSION     ${dns_LIB_VERSION} 
                                    SOVERSION   ${dns_LIB_SOVERSION} )
ELSE (MODULE_dns)
    MESSAGE(STATUS "Not Include dns module.")
ENDIF (MODULE_dns)





########################################################################################
#############                 ����Ŀ�������ļ�                          ############## 
########################################################################################
IF (TEST_MODULE_FLAG AND MODULE_dns)
    add_executable(TestDNS.elf    dnsTest.c)
    add_dependencies(TestDNS.elf          dnslib loglib )
    target_link_libraries(TestDNS.elf     dnslib loglib )

ELSE (TEST_MODULE_FLAG AND MODULE_dns)
    MESSAGE(STATUS "Not Include system_instrument module.")
ENDIF (TEST_MODULE_FLAG AND MODULE_dns)

