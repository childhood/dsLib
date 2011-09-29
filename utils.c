
void dslib_srand(void)
{
   int i;
   FILE* op;
   char buf[8];
   unsigned int seed;

   op = fopen ("/dev/random", "r");
   assert (op != NULL);
   fread (buf, 8, 1, op); /* seed raw material */
   fclose (op);

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

unsigned long dslib_rand (unsigned int max)
{
   return (random()%max);
}
