#define KFC /*살아남음*/
#define BBQ /*살아남음*/

#ifdef KFC
#define MAC /*살아남음*/
#else
#undef BBQ
#undef MAC
#endif

#ifndef MAC
#define MOMS
#endif

#ifdef MOMS
HAHA;
#endif