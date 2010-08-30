/*  Copyright 2010 Gaurav Mathur

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 *
 * @param[out] x the modified input
 * @param x +1$
 */
int megaFunc( int * x )
{
   return 10;
}

/**
 * The main procedure. It can do the following:
 *  - do nothing
 *  - sleep
 *
 * @code
 * for ( i = 0 ; i < 5 ; i++ ) { megaFunc(i) ; }
 * @endcode
 * Which compute $(x_1,y_1)\f$ sometimes.
 * @param argc the command line
 * @param argv the number of options in the command line.
 * @return whatever
 * @author jb silvy
 */
int heap_main( char ** argc, int argv )
{
return megaFunc( 3 ) ;
}
