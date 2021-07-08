#include "timer.h"

void	twait(struct timeval *t) {

long	sec = t->tv_sec, usec = t->tv_usec;
long	i;

gettimeofday(t, NULL);
i = (t->tv_sec-sec)*1000000+t->tv_usec-usec;

if(i<CLOCKS_PER_SEC/FRAMERATE)
usleep(CLOCKS_PER_SEC/FRAMERATE-i);

return;}
