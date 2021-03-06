// -*- C++ -*-
//
// IIOPC.i,v 1.3 2001/01/17 02:59:45 parsons Exp

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// *************************************************************
// Inline operations for class IIOP::ListenPoint_var
// *************************************************************

ACE_INLINE
IIOP::ListenPoint_var::ListenPoint_var (void) // default constructor
  : ptr_ (0)
{}

ACE_INLINE
IIOP::ListenPoint_var::ListenPoint_var (ListenPoint *p)
  : ptr_ (p)
{}

ACE_INLINE
IIOP::ListenPoint_var::ListenPoint_var (const ::IIOP::ListenPoint_var &p) // copy constructor
{
  if (p.ptr_)
    ACE_NEW (this->ptr_, ::IIOP::ListenPoint (*p.ptr_));
  else
    this->ptr_ = 0;
}

ACE_INLINE
IIOP::ListenPoint_var::~ListenPoint_var (void) // destructor
{
  delete this->ptr_;
}

ACE_INLINE IIOP::ListenPoint_var &
IIOP::ListenPoint_var::operator= (ListenPoint *p)
{
  delete this->ptr_;
  this->ptr_ = p;
  return *this;
}

ACE_INLINE ::IIOP::ListenPoint_var &
IIOP::ListenPoint_var::operator= (const ::IIOP::ListenPoint_var &p)
{
  if (this != &p)
    {
      if (p.ptr_ == 0)
        {
          delete this->ptr_;
          this->ptr_ = 0;
        }
      else
        {
          IIOP::ListenPoint *deep_copy = 
            new IIOP::ListenPoint (*p.ptr_);
          
          if (deep_copy != 0)
            {
              IIOP::ListenPoint *tmp = deep_copy;
              deep_copy = this->ptr_;
              this->ptr_ = tmp;
              delete deep_copy;
            }
        }
    }
  
  return *this;
}

ACE_INLINE const ::IIOP::ListenPoint *
IIOP::ListenPoint_var::operator-> (void) const
{
  return this->ptr_;
}

ACE_INLINE ::IIOP::ListenPoint *
IIOP::ListenPoint_var::operator-> (void)
{
  return this->ptr_;
}

ACE_INLINE
IIOP::ListenPoint_var::operator const ::IIOP::ListenPoint &() const // cast
{
  return *this->ptr_;
}

ACE_INLINE
IIOP::ListenPoint_var::operator ::IIOP::ListenPoint &() // cast 
{
  return *this->ptr_;
}

ACE_INLINE
IIOP::ListenPoint_var::operator ::IIOP::ListenPoint &() const // cast 
{
  return *this->ptr_;
}

// variable-size types only
ACE_INLINE
IIOP::ListenPoint_var::operator ::IIOP::ListenPoint *&() // cast 
{
  return this->ptr_;
}

ACE_INLINE const ::IIOP::ListenPoint &
IIOP::ListenPoint_var::in (void) const
{
  return *this->ptr_;
}

ACE_INLINE ::IIOP::ListenPoint &
IIOP::ListenPoint_var::inout (void)
{
  return *this->ptr_;
}

// mapping for variable size 
ACE_INLINE ::IIOP::ListenPoint *&
IIOP::ListenPoint_var::out (void)
{
  delete this->ptr_;
  this->ptr_ = 0;
  return this->ptr_;
}

ACE_INLINE ::IIOP::ListenPoint *
IIOP::ListenPoint_var::_retn (void)
{
  ::IIOP::ListenPoint *tmp = this->ptr_;
  this->ptr_ = 0;
  return tmp;
}

ACE_INLINE ::IIOP::ListenPoint *
IIOP::ListenPoint_var::ptr (void) const
{
  return this->ptr_;
}

// *************************************************************
// Inline operations for class IIOP::ListenPoint_out
// *************************************************************

ACE_INLINE
IIOP::ListenPoint_out::ListenPoint_out (::IIOP::ListenPoint *&p)
  : ptr_ (p)
{
  this->ptr_ = 0;
}

ACE_INLINE
IIOP::ListenPoint_out::ListenPoint_out (ListenPoint_var &p) // constructor from _var
  : ptr_ (p.out ())
{
  delete this->ptr_;
  this->ptr_ = 0;
}

ACE_INLINE
IIOP::ListenPoint_out::ListenPoint_out (const ::IIOP::ListenPoint_out &p) // copy constructor
  : ptr_ (ACE_const_cast (ListenPoint_out&, p).ptr_)
{}

ACE_INLINE IIOP::ListenPoint_out &
IIOP::ListenPoint_out::operator= (const ::IIOP::ListenPoint_out &p)
{
  this->ptr_ = ACE_const_cast (ListenPoint_out&, p).ptr_;
  return *this;
}

ACE_INLINE IIOP::ListenPoint_out &
IIOP::ListenPoint_out::operator= (ListenPoint *p)
{
  this->ptr_ = p;
  return *this;
}

ACE_INLINE 
IIOP::ListenPoint_out::operator ::IIOP::ListenPoint *&() // cast
{
  return this->ptr_;
}

ACE_INLINE ::IIOP::ListenPoint *&
IIOP::ListenPoint_out::ptr (void) // ptr
{
  return this->ptr_;
}

ACE_INLINE ::IIOP::ListenPoint *
IIOP::ListenPoint_out::operator-> (void)
{
  return this->ptr_;
}


#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
  
#if !defined (__TAO_UNBOUNDED_SEQUENCE_IIOP_LISTENPOINTLIST_CI_)
#define __TAO_UNBOUNDED_SEQUENCE_IIOP_LISTENPOINTLIST_CI_

  // = Static operations.
  ACE_INLINE IIOP::ListenPoint *
  IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::allocbuf (CORBA::ULong size)
  // Allocate storage for the sequence.
  {
    IIOP::ListenPoint *retval = 0;
    ACE_NEW_RETURN (retval, IIOP::ListenPoint[size], 0);
    return retval;
  }
  
  ACE_INLINE void IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::freebuf (IIOP::ListenPoint *buffer)
  // Free the sequence.
  {
    delete [] buffer;
  }
  
  ACE_INLINE
  IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::_TAO_Unbounded_Sequence_IIOP_ListenPointList (void) // Default constructor.
  {
  }
  
  ACE_INLINE
  IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::_TAO_Unbounded_Sequence_IIOP_ListenPointList (CORBA::ULong maximum) // Constructor using a maximum length value.
    : TAO_Unbounded_Base_Sequence (maximum, _TAO_Unbounded_Sequence_IIOP_ListenPointList::allocbuf (maximum))
  {
  }
  
  ACE_INLINE
  IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::_TAO_Unbounded_Sequence_IIOP_ListenPointList (CORBA::ULong maximum,
    CORBA::ULong length,
    IIOP::ListenPoint *data,
    CORBA::Boolean release)
  : TAO_Unbounded_Base_Sequence (maximum, length, data, release)
  {
  }
  
  ACE_INLINE
  IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::_TAO_Unbounded_Sequence_IIOP_ListenPointList (const _TAO_Unbounded_Sequence_IIOP_ListenPointList &rhs)
  // Copy constructor.
    : TAO_Unbounded_Base_Sequence (rhs)
  {
    if (rhs.buffer_ != 0)
    {
      IIOP::ListenPoint *tmp1 = _TAO_Unbounded_Sequence_IIOP_ListenPointList::allocbuf (this->maximum_);
      IIOP::ListenPoint * const tmp2 = ACE_reinterpret_cast (IIOP::ListenPoint * ACE_CAST_CONST, rhs.buffer_);
      
      for (CORBA::ULong i = 0; i < this->length_; ++i)
        tmp1[i] = tmp2[i];
      
      this->buffer_ = tmp1;
    }
    else
    {
      this->buffer_ = 0;
    }
  }
  
  ACE_INLINE IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList &
  IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::operator= (const _TAO_Unbounded_Sequence_IIOP_ListenPointList &rhs)
  // Assignment operator.
  {
    if (this == &rhs)
      return *this;
    
    if (this->release_)
    {
      if (this->maximum_ < rhs.maximum_)
      {
        // free the old buffer
        IIOP::ListenPoint *tmp = ACE_reinterpret_cast (IIOP::ListenPoint *, this->buffer_);
        _TAO_Unbounded_Sequence_IIOP_ListenPointList::freebuf (tmp);
        this->buffer_ = _TAO_Unbounded_Sequence_IIOP_ListenPointList::allocbuf (rhs.maximum_);
      }
    }
    else
      this->buffer_ = _TAO_Unbounded_Sequence_IIOP_ListenPointList::allocbuf (rhs.maximum_);
    
    TAO_Unbounded_Base_Sequence::operator= (rhs);
    
    IIOP::ListenPoint *tmp1 = ACE_reinterpret_cast (IIOP::ListenPoint *, this->buffer_);
    IIOP::ListenPoint * const tmp2 = ACE_reinterpret_cast (IIOP::ListenPoint * ACE_CAST_CONST, rhs.buffer_);
    
    for (CORBA::ULong i = 0; i < this->length_; ++i)
      tmp1[i] = tmp2[i];
    
    return *this;
  }
  
  // = Accessors.
  ACE_INLINE IIOP::ListenPoint &
  IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::operator[] (CORBA::ULong i)
  // operator []
  {
    ACE_ASSERT (i < this->maximum_);
    IIOP::ListenPoint* tmp = ACE_reinterpret_cast(IIOP::ListenPoint*,this->buffer_);
    return tmp[i];
  }
  
  ACE_INLINE const IIOP::ListenPoint &
  IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::operator[] (CORBA::ULong i) const
  // operator []
  {
    ACE_ASSERT (i < this->maximum_);
    IIOP::ListenPoint * const tmp = ACE_reinterpret_cast (IIOP::ListenPoint* ACE_CAST_CONST, this->buffer_);
    return tmp[i];
  }
  
  // Implement the TAO_Base_Sequence methods (see Sequence.h)
  
  ACE_INLINE IIOP::ListenPoint *
  IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::get_buffer (CORBA::Boolean orphan)
  {
    IIOP::ListenPoint *result = 0;
    if (orphan == 0)
    {
      // We retain ownership.
      if (this->buffer_ == 0)
      {
        result = _TAO_Unbounded_Sequence_IIOP_ListenPointList::allocbuf (this->length_);
        this->buffer_ = result;
        this->release_ = 1;
      }
      else
      {
        result = ACE_reinterpret_cast (IIOP::ListenPoint*, this->buffer_);
      }
    }
    else // if (orphan == 1)
    {
      if (this->release_ != 0)
      {
        // We set the state back to default and relinquish
        // ownership.
        result = ACE_reinterpret_cast(IIOP::ListenPoint*,this->buffer_);
        this->maximum_ = 0;
        this->length_ = 0;
        this->buffer_ = 0;
        this->release_ = 0;
      }
    }
    return result;
  }
  
  ACE_INLINE const IIOP::ListenPoint *
  IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::get_buffer (void) const
  {
    return ACE_reinterpret_cast(const IIOP::ListenPoint * ACE_CAST_CONST, this->buffer_);
  }
  
  ACE_INLINE void
  IIOP::_TAO_Unbounded_Sequence_IIOP_ListenPointList::replace (CORBA::ULong max,
  CORBA::ULong length,
  IIOP::ListenPoint *data,
  CORBA::Boolean release)
  {
    this->maximum_ = max;
    this->length_ = length;
    if (this->buffer_ && this->release_ == 1)
    {
      IIOP::ListenPoint *tmp = ACE_reinterpret_cast(IIOP::ListenPoint*,this->buffer_);
      _TAO_Unbounded_Sequence_IIOP_ListenPointList::freebuf (tmp);
    }
    this->buffer_ = data;
    this->release_ = release;
  }
  
#endif /* end #if !defined */


#endif /* !TAO_USE_SEQUENCE_TEMPLATES */ 

#if !defined (_IIOP_LISTENPOINTLIST_CI_)
#define _IIOP_LISTENPOINTLIST_CI_

// *************************************************************
// Inline operations for class IIOP::ListenPointList_var
// *************************************************************

ACE_INLINE
IIOP::ListenPointList_var::ListenPointList_var (void) // default constructor
  : ptr_ (0)
{}

ACE_INLINE
IIOP::ListenPointList_var::ListenPointList_var (ListenPointList *p)
  : ptr_ (p)
{}

ACE_INLINE
IIOP::ListenPointList_var::ListenPointList_var (const ::IIOP::ListenPointList_var &p) // copy constructor
{
  if (p.ptr_)
    ACE_NEW (this->ptr_, ::IIOP::ListenPointList (*p.ptr_));
  else
    this->ptr_ = 0;
}

ACE_INLINE
IIOP::ListenPointList_var::~ListenPointList_var (void) // destructor
{
  delete this->ptr_;
}

ACE_INLINE IIOP::ListenPointList_var &
IIOP::ListenPointList_var::operator= (ListenPointList *p)
{
  delete this->ptr_;
  this->ptr_ = p;
  return *this;
}

ACE_INLINE IIOP::ListenPointList_var &
IIOP::ListenPointList_var::operator= (const ::IIOP::ListenPointList_var &p) // deep copy
{
  if (this != &p)
    {
      if (p.ptr_ == 0)
        {
          delete this->ptr_;
          this->ptr_ = 0;
        }
      else
        {
          IIOP::ListenPointList *deep_copy = 
            new IIOP::ListenPointList (*p.ptr_);
          
          if (deep_copy != 0)
            {
              IIOP::ListenPointList *tmp = deep_copy;
              deep_copy = this->ptr_;
              this->ptr_ = tmp;
              delete deep_copy;
            }
        }
    }
  
  return *this;
}

ACE_INLINE const ::IIOP::ListenPointList *
IIOP::ListenPointList_var::operator-> (void) const
{
  return this->ptr_;
}

ACE_INLINE ::IIOP::ListenPointList *
IIOP::ListenPointList_var::operator-> (void)
{
  return this->ptr_;
}

ACE_INLINE 
IIOP::ListenPointList_var::operator const ::IIOP::ListenPointList &() const // cast
{
  return *this->ptr_;
}

ACE_INLINE 
IIOP::ListenPointList_var::operator ::IIOP::ListenPointList &() // cast 
{
  return *this->ptr_;
}

ACE_INLINE 
IIOP::ListenPointList_var::operator ::IIOP::ListenPointList &() const // cast 
{
  return *this->ptr_;
}

// variable-size types only
ACE_INLINE
IIOP::ListenPointList_var::operator ::IIOP::ListenPointList *&() // cast 
{
  return this->ptr_;
}

ACE_INLINE IIOP::ListenPoint &
IIOP::ListenPointList_var::operator[] (CORBA::ULong index)
{
  return this->ptr_->operator[] (index);
}

ACE_INLINE const IIOP::ListenPoint &
IIOP::ListenPointList_var::operator[] (CORBA::ULong index) const
{
  return ACE_const_cast (const IIOP::ListenPoint &, this->ptr_->operator[] (index));
}

ACE_INLINE const ::IIOP::ListenPointList &
IIOP::ListenPointList_var::in (void) const
{
  return *this->ptr_;
}

ACE_INLINE ::IIOP::ListenPointList &
IIOP::ListenPointList_var::inout (void)
{
  return *this->ptr_;
}

// mapping for variable size 
ACE_INLINE ::IIOP::ListenPointList *&
IIOP::ListenPointList_var::out (void)
{
  delete this->ptr_;
  this->ptr_ = 0;
  return this->ptr_;
}

ACE_INLINE ::IIOP::ListenPointList *
IIOP::ListenPointList_var::_retn (void)
{
  ::IIOP::ListenPointList *tmp = this->ptr_;
  this->ptr_ = 0;
  return tmp;
}

ACE_INLINE ::IIOP::ListenPointList *
IIOP::ListenPointList_var::ptr (void) const
{
  return this->ptr_;
}

// *************************************************************
// Inline operations for class IIOP::ListenPointList_out
// *************************************************************

ACE_INLINE
IIOP::ListenPointList_out::ListenPointList_out (ListenPointList *&p)
  : ptr_ (p)
{
  this->ptr_ = 0;
}

ACE_INLINE
IIOP::ListenPointList_out::ListenPointList_out (ListenPointList_var &p) // constructor from _var
  : ptr_ (p.out ())
{
  delete this->ptr_;
  this->ptr_ = 0;
}

ACE_INLINE
IIOP::ListenPointList_out::ListenPointList_out (const ::IIOP::ListenPointList_out &p) // copy constructor
  : ptr_ (ACE_const_cast (ListenPointList_out&, p).ptr_)
{}

ACE_INLINE ::IIOP::ListenPointList_out &
IIOP::ListenPointList_out::operator= (const ::IIOP::ListenPointList_out &p)
{
  this->ptr_ = ACE_const_cast (ListenPointList_out&, p).ptr_;
  return *this;
}

ACE_INLINE ::IIOP::ListenPointList_out &
IIOP::ListenPointList_out::operator= (ListenPointList *p)
{
  this->ptr_ = p;
  return *this;
}

ACE_INLINE 
IIOP::ListenPointList_out::operator ::IIOP::ListenPointList *&() // cast
{
  return this->ptr_;
}

ACE_INLINE ::IIOP::ListenPointList *&
IIOP::ListenPointList_out::ptr (void) // ptr
{
  return this->ptr_;
}

ACE_INLINE ::IIOP::ListenPointList *
IIOP::ListenPointList_out::operator-> (void)
{
  return this->ptr_;
}

ACE_INLINE IIOP::ListenPoint &
IIOP::ListenPointList_out::operator[] (CORBA::ULong index)
{
  return this->ptr_->operator[] (index);
}


#endif /* end #if !defined */

// *************************************************************
// Inline operations for class IIOP::BiDirIIOPServiceContext_var
// *************************************************************

ACE_INLINE
IIOP::BiDirIIOPServiceContext_var::BiDirIIOPServiceContext_var (void) // default constructor
  : ptr_ (0)
{}

ACE_INLINE
IIOP::BiDirIIOPServiceContext_var::BiDirIIOPServiceContext_var (BiDirIIOPServiceContext *p)
  : ptr_ (p)
{}

ACE_INLINE
IIOP::BiDirIIOPServiceContext_var::BiDirIIOPServiceContext_var (const ::IIOP::BiDirIIOPServiceContext_var &p) // copy constructor
{
  if (p.ptr_)
    ACE_NEW (this->ptr_, ::IIOP::BiDirIIOPServiceContext (*p.ptr_));
  else
    this->ptr_ = 0;
}

ACE_INLINE
IIOP::BiDirIIOPServiceContext_var::~BiDirIIOPServiceContext_var (void) // destructor
{
  delete this->ptr_;
}

ACE_INLINE IIOP::BiDirIIOPServiceContext_var &
IIOP::BiDirIIOPServiceContext_var::operator= (BiDirIIOPServiceContext *p)
{
  delete this->ptr_;
  this->ptr_ = p;
  return *this;
}

ACE_INLINE ::IIOP::BiDirIIOPServiceContext_var &
IIOP::BiDirIIOPServiceContext_var::operator= (const ::IIOP::BiDirIIOPServiceContext_var &p)
{
  if (this != &p)
    {
      if (p.ptr_ == 0)
        {
          delete this->ptr_;
          this->ptr_ = 0;
        }
      else
        {
          IIOP::BiDirIIOPServiceContext *deep_copy = 
            new IIOP::BiDirIIOPServiceContext (*p.ptr_);
          
          if (deep_copy != 0)
            {
              IIOP::BiDirIIOPServiceContext *tmp = deep_copy;
              deep_copy = this->ptr_;
              this->ptr_ = tmp;
              delete deep_copy;
            }
        }
    }
  
  return *this;
}

ACE_INLINE const ::IIOP::BiDirIIOPServiceContext *
IIOP::BiDirIIOPServiceContext_var::operator-> (void) const
{
  return this->ptr_;
}

ACE_INLINE ::IIOP::BiDirIIOPServiceContext *
IIOP::BiDirIIOPServiceContext_var::operator-> (void)
{
  return this->ptr_;
}

ACE_INLINE
IIOP::BiDirIIOPServiceContext_var::operator const ::IIOP::BiDirIIOPServiceContext &() const // cast
{
  return *this->ptr_;
}

ACE_INLINE
IIOP::BiDirIIOPServiceContext_var::operator ::IIOP::BiDirIIOPServiceContext &() // cast 
{
  return *this->ptr_;
}

ACE_INLINE
IIOP::BiDirIIOPServiceContext_var::operator ::IIOP::BiDirIIOPServiceContext &() const // cast 
{
  return *this->ptr_;
}

// variable-size types only
ACE_INLINE
IIOP::BiDirIIOPServiceContext_var::operator ::IIOP::BiDirIIOPServiceContext *&() // cast 
{
  return this->ptr_;
}

ACE_INLINE const ::IIOP::BiDirIIOPServiceContext &
IIOP::BiDirIIOPServiceContext_var::in (void) const
{
  return *this->ptr_;
}

ACE_INLINE ::IIOP::BiDirIIOPServiceContext &
IIOP::BiDirIIOPServiceContext_var::inout (void)
{
  return *this->ptr_;
}

// mapping for variable size 
ACE_INLINE ::IIOP::BiDirIIOPServiceContext *&
IIOP::BiDirIIOPServiceContext_var::out (void)
{
  delete this->ptr_;
  this->ptr_ = 0;
  return this->ptr_;
}

ACE_INLINE ::IIOP::BiDirIIOPServiceContext *
IIOP::BiDirIIOPServiceContext_var::_retn (void)
{
  ::IIOP::BiDirIIOPServiceContext *tmp = this->ptr_;
  this->ptr_ = 0;
  return tmp;
}

ACE_INLINE ::IIOP::BiDirIIOPServiceContext *
IIOP::BiDirIIOPServiceContext_var::ptr (void) const
{
  return this->ptr_;
}

// *************************************************************
// Inline operations for class IIOP::BiDirIIOPServiceContext_out
// *************************************************************

ACE_INLINE
IIOP::BiDirIIOPServiceContext_out::BiDirIIOPServiceContext_out (::IIOP::BiDirIIOPServiceContext *&p)
  : ptr_ (p)
{
  this->ptr_ = 0;
}

ACE_INLINE
IIOP::BiDirIIOPServiceContext_out::BiDirIIOPServiceContext_out (BiDirIIOPServiceContext_var &p) // constructor from _var
  : ptr_ (p.out ())
{
  delete this->ptr_;
  this->ptr_ = 0;
}

ACE_INLINE
IIOP::BiDirIIOPServiceContext_out::BiDirIIOPServiceContext_out (const ::IIOP::BiDirIIOPServiceContext_out &p) // copy constructor
  : ptr_ (ACE_const_cast (BiDirIIOPServiceContext_out&, p).ptr_)
{}

ACE_INLINE IIOP::BiDirIIOPServiceContext_out &
IIOP::BiDirIIOPServiceContext_out::operator= (const ::IIOP::BiDirIIOPServiceContext_out &p)
{
  this->ptr_ = ACE_const_cast (BiDirIIOPServiceContext_out&, p).ptr_;
  return *this;
}

ACE_INLINE IIOP::BiDirIIOPServiceContext_out &
IIOP::BiDirIIOPServiceContext_out::operator= (BiDirIIOPServiceContext *p)
{
  this->ptr_ = p;
  return *this;
}

ACE_INLINE 
IIOP::BiDirIIOPServiceContext_out::operator ::IIOP::BiDirIIOPServiceContext *&() // cast
{
  return this->ptr_;
}

ACE_INLINE ::IIOP::BiDirIIOPServiceContext *&
IIOP::BiDirIIOPServiceContext_out::ptr (void) // ptr
{
  return this->ptr_;
}

ACE_INLINE ::IIOP::BiDirIIOPServiceContext *
IIOP::BiDirIIOPServiceContext_out::operator-> (void)
{
  return this->ptr_;
}

ACE_INLINE CORBA::Boolean operator<< (TAO_OutputCDR &strm, const IIOP::ListenPoint &_tao_aggregate)
{
  if (
    (strm << _tao_aggregate.host.in ()) &&
    (strm << _tao_aggregate.port)
  )
    return 1;
  else
    return 0;
  
}

ACE_INLINE CORBA::Boolean operator>> (TAO_InputCDR &strm, IIOP::ListenPoint &_tao_aggregate)
{
  if (
    (strm >> _tao_aggregate.host.out ()) &&
    (strm >> _tao_aggregate.port)
  )
    return 1;
  else
    return 0;
  
}


#if !defined _TAO_CDR_OP_IIOP_ListenPointList_I_
#define _TAO_CDR_OP_IIOP_ListenPointList_I_

CORBA::Boolean TAO_Export operator<< (
    TAO_OutputCDR &,
    const IIOP::ListenPointList &
  );
CORBA::Boolean TAO_Export operator>> (
    TAO_InputCDR &,
    IIOP::ListenPointList &
  );

#endif /* _TAO_CDR_OP_IIOP_ListenPointList_I_ */

ACE_INLINE CORBA::Boolean operator<< (TAO_OutputCDR &strm, const IIOP::BiDirIIOPServiceContext &_tao_aggregate)
{
  if (
    (strm << _tao_aggregate.listen_points)
  )
    return 1;
  else
    return 0;
  
}

ACE_INLINE CORBA::Boolean operator>> (TAO_InputCDR &strm, IIOP::BiDirIIOPServiceContext &_tao_aggregate)
{
  if (
    (strm >> _tao_aggregate.listen_points)
  )
    return 1;
  else
    return 0;
  
}

