/* -*- C++ -*- */
// LSOCK.i,v 4.3 2000/05/15 22:31:30 othman Exp

// LSOCK.i

// Simple-minded constructor. 

ASYS_INLINE
ACE_LSOCK::ACE_LSOCK (void)
  : aux_handle_ (ACE_INVALID_HANDLE)
{
  ACE_TRACE ("ACE_LSOCK::ACE_LSOCK");
}

// Sets the underlying file descriptor.

ASYS_INLINE void
ACE_LSOCK::set_handle (ACE_HANDLE handle)
{
  ACE_TRACE ("ACE_LSOCK::set_handle");
  this->aux_handle_ = handle;
}

// Gets the underlying file descriptor.

ASYS_INLINE ACE_HANDLE
ACE_LSOCK::get_handle (void) const
{
  ACE_TRACE ("ACE_LSOCK::get_handle");
  return this->aux_handle_;
}

// Sets the underlying file descriptor. 

ASYS_INLINE
ACE_LSOCK::ACE_LSOCK (ACE_HANDLE handle)
  : aux_handle_ (handle)
{
  ACE_TRACE ("ACE_LSOCK::ACE_LSOCK");
}