// #define KFC
#define BBQ

#ifdef KFC
#define MAC
#else
#undef BBQ
#undef MAC
#endif

#ifndef MAC
#define MOMS /*살아남음*/
#endif

#ifdef MOMS
HAHA; /*살아남음*/
#endif