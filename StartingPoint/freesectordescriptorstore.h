#ifndef _FREE_SECTOR_DESCRIPTOR_STORE_HDR_
#define _FREE_SECTOR_DESCRIPTOR_STORE_HDR_

/*
 * This file is a component of the test harness and/or sample solution
 * to the DiskDriver exercise developed in February 2008 for use in
 * assessing the OS3 module in undergraduate Computing Science at the
 * University of Glasgow.
 */

/*
 * header file for FreeSectorDescriptorStore ADT
 */

#include "sectordescriptor.h"

typedef void *FreeSectorDescriptorStore;

/*
 * as usual, the blocking versions only return when they succeed
 * the nonblocking versions return 1 if successful, 0 otherwise
 * the _get_ functions set their final argument if they succeed
 */

void blocking_get_sd(FreeSectorDescriptorStore fsds, SectorDescriptor *sd);
int nonblocking_get_sd(FreeSectorDescriptorStore fsds, SectorDescriptor *sd);

void blocking_put_sd(FreeSectorDescriptorStore fsds, SectorDescriptor sd);
int nonblocking_put_sd(FreeSectorDescriptorStore fsds, SectorDescriptor sd);

#endif /* _FREE_SECTOR_DESCRIPTOR_STORE_HDR_ */
