#ifndef _DISK_DEVICE_HDR_
#define _DISK_DEVICE_HDR_

/*
 * This file is a component of the test harness and/or sample solution
 * to the DiskDriver exercise developed in February 2008 for use in
 * assessing the OS3 module in undergraduate Computing Science at the
 * University of Glasgow.
 */

/*
 * header file for DiskDevice ADT
 */

#include "sectordescriptor.h"
#include "block.h"
#include "pid.h"

typedef void *DiskDevice;

/*
 * write sector to disk, returns 1 if successful, 0 if unsuccessful
 * this may take a substantial amount of time to return
 * if unsuccessful, you should return an indication of this lack of
 * success to the application
 */
int write_sector(DiskDevice dd, SectorDescriptor *sd);

/*
 * read sector from disk, returns 1 if successful, 0 if unsuccessful
 * if successful, the sector read is contained in the SectorDescriptor
 * this may take a substantial amount of time to return
 * if unsuccessful, you should return an indication of this lack of
 * success to the application
 */
int read_sector(DiskDevice dd, SectorDescriptor *sd);

#endif /* _DISK_DEVICE_HDR_ */
