//#include "sectordescriptorcreator.h"
//#include "freesectordescriptorstore_full.h"
//#include "freesectordescriptorstore.h"
#include "stdlib.h"
#include "stdio.h"
#include "diskdevice_full.h"

#include "diskdriver.c"

int rand_seed = 10;

int main(){
    const int size = 200;
    void *someMemory = malloc(size);
    
    DiskDevice dd = construct_disk_device();
    FreeSectorDescriptorStore *store_p = malloc(sizeof(FreeSectorDescriptorStore));

    init_disk_driver(dd, someMemory, size, store_p);
    SectorDescriptor *sd = (SectorDescriptor*) malloc(sizeof(SectorDescriptor));
    //printf("%d\n", sizeof(*sd));
    //printf("%d\n", sizeof(*store_p));


    blocking_get_sd(*store_p, sd);
    blocking_put_sd(*store_p, *sd);
    blocking_get_sd(*store_p, sd);
    blocking_put_sd(*store_p, *sd);
    blocking_get_sd(*store_p, sd);
    blocking_put_sd(*store_p, *sd);
    blocking_get_sd(*store_p, sd);
    blocking_put_sd(*store_p, *sd);
    blocking_get_sd(*store_p, sd);
    blocking_put_sd(*store_p, *sd);

    //blocking_get_sd(*store_p, sd);
    //blocking_get_sd(*store_p, sd);
    //blocking_get_sd(*store_p, sd);

    //init_sector_descriptor(sd);
    
    
    
    //printf(someMemory);
    return 0;
}
