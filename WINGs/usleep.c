

#include "../src/config.h"


#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#endif

#ifdef _AIX
#include <sys/select.h>
#endif

#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif

#if defined(HAVE_SELECT)

 

void
wusleep(unsigned int microsecs)
{
    struct timeval tv;
    fd_set rd, wr, ex;
    FD_ZERO(&rd);
    FD_ZERO(&wr);
    FD_ZERO(&ex);
    tv.tv_sec = microsecs / 1000000u;
    tv.tv_usec = microsecs % 1000000u;
    select(1, &rd, &wr, &ex, &tv);
}

#else /* not HAVE_SELECT */

# ifdef HAVE_POLL 

void 
wusleep(unsigned int microsecs)
{
    poll((struct poll *) 0, (size_t) 0, microsecs/1000);
}

# else /* ! HAVE_POLL */

oops!

# endif /* !HAVE_POLL */
#endif /* !HAVE_SELECT */
