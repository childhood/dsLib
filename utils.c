/**
 * utility functions for dsLib
 * Copyright (c) 2011, Gaurav Mathur <narainmg@gmail.com>
 *   
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *   
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *   
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * See README and COPYING for more details.
 */


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DSLIB_UTILS_UT


/**
 * @brief seed random number generator
 * 
 * @return n.a.
 */
void dslib_srandom (void)
{
   int fd;
#define SEED_BUF_SIZE   8   
   char buf[SEED_BUF_SIZE];
   unsigned int seed = 0;

   /* todo - try opening other rand devices that might be present on *nix
    * systems
    */   
   fd = open ("/dev/random", O_RDONLY | O_CLOEXEC);
   assert (fd != -1);            
   if (SEED_BUF_SIZE != read (fd, buf, SEED_BUF_SIZE)) /* seed raw material */
      fprintf (stderr, "%s:%d not read %d bytes of seed materialn\n", __FUNCTION__,
               __LINE__, SEED_BUF_SIZE);   
   close (fd);

   /* construct the seed from the raw material */
   seed = seed | buf[0];
   seed = seed << 8;
   seed = seed | buf[1];
   seed = seed << 8;
   seed = seed | buf[2];
   seed = seed << 8;
   seed = seed | buf[3];
   seed = seed << 8;

   /* seed the PRNG */
   srandom (seed);
}

/**
 * @brief generate random number
 * 
 * @return n.a.
 */

unsigned long dslib_random (unsigned int max)
{
   return (random()%(max+1));
}

#ifdef DSLIB_UTILS_UT

#endif
