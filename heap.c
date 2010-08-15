
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
