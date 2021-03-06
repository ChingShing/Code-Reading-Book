
// mld.cpp,v 1.4 1998/11/15 17:05:29 jcej Exp

#include "mld.h"

ACE_Atomic_Op < ACE_Mutex, int >mld::counter_ (0);

// Increment the counter when a new mld is created...
mld::mld (void)
{
    ++counter_;
}

// and decrement it when the object is destructed.
mld::~mld (void)
{
    --counter_;
}

int mld::value (void)
{
    return counter_.value ();
}
