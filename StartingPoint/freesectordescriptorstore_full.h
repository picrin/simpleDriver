#ifndef _FREE_SECTOR_DESCRIPTOR_STORE_FULL_HDR_
#define _FREE_SECTOR_DESCRIPTOR_STORE_FULL_HDR_

/*
 * This file is a component of the test harness and/or sample solution
 * to the DiskDriver exercise developed in February 2008 for use in
 * assessing the OS3 module in undergraduate Computing Science at the
 * University of Glasgow.
 */

/*
 * extension to header file for FreeSectorDescriptorStore ADT to
 * define constructor and destructor
 */

#include "freesectordescriptorstore.h"

FreeSectorDescriptorStore create_fsds(void);
void destroy_fsds(FreeSectorDescriptorStore fsds);

#endif /* _FREE_SECTOR_DESCRIPTOR_STORE_FULL_HDR_ */
