//#include "sectordescriptorcreator.h"
//#include "freesectordescriptorstore_full.h"
//#include "freesectordescriptorstore.h"
#include "stdlib.h"
#include "stdio.h"
#include "sectordescriptor.h"
#include "block.h"
#include "pid.h"
#include "freesectordescriptorstore.h"
#include "diskdevice.h"
#include "voucher.h"
#include "freesectordescriptorstore_full.h"
#include "sectordescriptorcreator.h"
#include "BoundedBuffer.h"
#include "unistd.h"
#include "pthread.h"

/*
 * This file is a component of the test harness and/or sample solution
 * to the DiskDriver exercise developed in February 2008 for use in
 * assessing the OS3 module in undergraduate Computing Science at the
 * University of Glasgow.
 */

/*
 * Define the interface to the DiskDriver module that mediates access to
 * a disk device
 */



// let Voucher be a pointer type on struct Voucher_s 
struct Voucher_s{
    // 1 if read request, 0 if write request
    int read;

    // signalled when request written to or read from the drive
    pthread_cond_t condition;
    pthread_mutex_t m;

    // -1 if still waiting, 0 if failure 1 if success
    int successful;
    
    // hold on to the sd from request, we have to fill it or return it to store.
    SectorDescriptor* sd; 
};

//allocates and initialised the voucher
struct Voucher_s* malloc_voucher(){
    struct Voucher_s* returned = (struct Voucher_s*) malloc(sizeof(struct Voucher_s));
    returned->read = -1;
    pthread_mutex_init(&(returned->m), NULL);
    pthread_cond_init(&(returned->condition), NULL);
    returned->successful = -1;
    returned->sd = (SectorDescriptor*) malloc(sizeof(SectorDescriptor));
    return returned;
}

/*
 * the following calls must be implemented by the students
 */

/*
 * called before any other methods to allow you to initialize data
 * structures and to start any internal threads.
 *
 * Arguments:
 *   dd: the DiskDevice that you must drive
 *   mem_start, mem_length: some memory for SectorDescriptors
 *   fsds_ptr: you hand back a FreeSectorDescriptorStore constructed
 *             from the memory provided in the two previous arguments
 */

//useful globals.
static DiskDevice DISK;
static const int BUFFER_SIZE = 3000;
static BoundedBuffer BUFFER;
static pthread_t READER_ID;
static FreeSectorDescriptorStore STORE;

void consumer_thread(){
    while(1){
        struct Voucher_s* v = (struct Voucher_s*) (Voucher) blockingReadBB(BUFFER);
        if(v->read == 1){
            v->successful = read_sector(DISK, v->sd);
            pthread_cond_broadcast(&(v->condition));
        } else if (v->read == 0) {
            v->successful = write_sector(DISK, v->sd);
            pthread_cond_broadcast(&(v->condition));
        } else {
            printf("error in reader_thread\n");
            exit(1);
        }
    }
}

void init_disk_driver(DiskDevice dd, void *mem_start, unsigned long mem_length,
        FreeSectorDescriptorStore *fsds_ptr){
    
    STORE = create_fsds();
    create_free_sector_descriptors(STORE, mem_start, mem_length);
    *fsds_ptr = STORE;
    DISK = dd;
    
    BUFFER = createBB(BUFFER_SIZE);
    
    
    pthread_create(&READER_ID, NULL, (void*(*)(void*)) &consumer_thread, NULL);
    //sleep(1);
    
    //wait_on_cond();

    //pthread_join(id0, NULL);
    //disk_writer
    
}

/*
 * the following calls are used to write a sector to the disk
 * the nonblocking call must return promptly, returning 1 if successful at
 * queueing up the write, 0 if not (in case internal buffers are full)
 * the blocking call will usually return promptly, but there may be
 * a delay while it waits for space in your buffers.
 * neither call should delay until the sector is actually written to the disk
 * for a successful nonblocking call and for the blocking call, a voucher is
 * returned that is required to determine the success/failure of the write
 */
void blocking_write_sector(SectorDescriptor sd, Voucher *v){
    struct Voucher_s* voucher = malloc_voucher();
    *(voucher->sd) = sd;
    voucher->read = 0;
    *v = (Voucher) voucher;
    blockingWriteBB(BUFFER, voucher);
}
int nonblocking_write_sector(SectorDescriptor sd, Voucher *v){
    struct Voucher_s* voucher = malloc_voucher();
    *(voucher->sd) = sd;
    voucher->read = 0;
    *v = (Voucher) voucher;
    return nonblockingWriteBB(BUFFER, voucher);

}

/*
 * the following calls are used to initiate the read of a sector from the disk
 * the nonblocking call must return promptly, returning 1 if successful at
 * queueing up the read, 0 if not (in case internal buffers are full)
 * the blocking callwill usually return promptly, but there may be
 * a delay while it waits for space in your buffers.
 * neither call should delay until the sector is actually read from the disk
 * for successful nonblocking call and for the blocking call, a voucher is
 * returned that is required to collect the sector after the read completes.
 */
void blocking_read_sector(SectorDescriptor sd, Voucher *v){
    struct Voucher_s* voucher = malloc_voucher();
    *(voucher->sd) = sd;
    voucher->read = 1;
    *v = (Voucher) voucher;
    blockingWriteBB(BUFFER, voucher);
}
int nonblocking_read_sector(SectorDescriptor sd, Voucher *v){
    struct Voucher_s* voucher = malloc_voucher();
    *(voucher->sd) = sd;
    voucher->read = 1;
    *v = (Voucher) voucher;
    return nonblockingWriteBB(BUFFER, voucher);
}

/*
 * the following call is used to retrieve the status of the read or write
 * the return value is 1 if successful, 0 if not
 * the calling application is blocked until the read/write has completed
 * if a successful read, the associated SectorDescriptor is returned in sd
 */
//int redeem_voucher(Voucher v, SectorDescriptor *sd){return 0;}

int redeem_voucher(Voucher v, SectorDescriptor *sd){
    struct Voucher_s* voucher = (struct Voucher_s*) v;
    pthread_mutex_lock(&(voucher->m));
    while(voucher->successful == -1){
        pthread_cond_wait(&(voucher->condition), &(voucher->m));
    }
    pthread_mutex_unlock(&(voucher->m));
    if (voucher->successful == 1 && voucher->read == 1){
        *sd = *(voucher->sd);
    }else {
        blocking_put_sd(STORE, *(voucher->sd));
    }
    int cache_success = voucher->successful;
    free(voucher->sd);
    pthread_cond_destroy(&(voucher->condition));
    pthread_mutex_destroy(&(voucher->m));
    free(voucher);
    return cache_success;
}

