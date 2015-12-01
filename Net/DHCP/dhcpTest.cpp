#include <stdio.h>
#include "dualserverd.h"


int main(int argc, char **argv)
{
    
    printf("net dhcp Test ....\n");
    DualDHCPAndDNSServer(argc, argv);
    
    return 0;
}




