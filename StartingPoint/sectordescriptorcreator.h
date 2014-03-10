#ifndef _SECTOR_DESCRIPTOR_CREATOR_HDR_
#define _SECTOR_DESCRIPTOR_CREATOR_HDR_

/*
 * This file is a component of the test harness and/or sample solution
 * to the DiskDriver exercise developed in February 2008 for use in
 * assessing the OS3 module in undergraduate Computing Science at the
 * University of Glasgow.
 */

/*
 * define the function prototype for create_free_sector_descriptors()
 */

#include "freesectordescriptorstore.h"

void create_free_sector_descriptors( FreeSectorDescriptorStore fsds,
		                     void *mem_start, unsigned long mem_length);

#endif /* _SECTOR_DESCRIPTOR_CREATOR_HDR_ */
