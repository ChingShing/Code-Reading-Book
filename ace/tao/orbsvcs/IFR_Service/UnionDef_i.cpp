/* -*- C++ -*- */
// UnionDef_i.cpp,v 1.8 2001/04/10 02:20:09 parsons Exp

#include "UnionDef_i.h"
#include "Repository_i.h"
#include "Servant_Factory.h"
#include "ace/Auto_Ptr.h"

ACE_RCSID(IFR_Service, UnionDef_i, "UnionDef_i.cpp,v 1.8 2001/04/10 02:20:09 parsons Exp")

TAO_UnionDef_i::TAO_UnionDef_i (TAO_Repository_i *repo,
                                ACE_Configuration_Section_Key section_key)
  : TAO_IRObject_i (repo, section_key),
    TAO_IDLType_i (repo, section_key),
    TAO_Contained_i (repo, section_key),
    TAO_TypedefDef_i (repo, section_key),
    TAO_Container_i (repo, section_key)
{
}

TAO_UnionDef_i::~TAO_UnionDef_i (void)
{
}

CORBA::DefinitionKind
TAO_UnionDef_i::def_kind (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  return CORBA::dk_Union;
}

void 
TAO_UnionDef_i::destroy (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_WRITE_GUARD;

  this->destroy_i (ACE_TRY_ENV);
}

void 
TAO_UnionDef_i::destroy_i (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  // Destroy our members.
  TAO_Container_i::destroy_i (ACE_TRY_ENV);
  ACE_CHECK;
    
  // Destroy ourself.
  TAO_Contained_i::destroy_i (ACE_TRY_ENV);
  ACE_CHECK;
}

CORBA::TypeCode_ptr 
TAO_UnionDef_i::type (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_READ_GUARD_RETURN (CORBA::TypeCode::_nil ());

  return this->type_i (ACE_TRY_ENV);
}

CORBA::TypeCode_ptr 
TAO_UnionDef_i::type_i (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_TString id;
  this->repo_->config ()->get_string_value (this->section_key_,
                                            "id",
                                            id);

  ACE_TString name;
  this->repo_->config ()->get_string_value (this->section_key_,
                                            "name",
                                            name);

  CORBA::TypeCode_var tc = this->discriminator_type_i (ACE_TRY_ENV);
  ACE_CHECK_RETURN (CORBA::TypeCode::_nil ());

  CORBA_UnionMemberSeq_var members = this->members_i (ACE_TRY_ENV);
  ACE_CHECK_RETURN (CORBA::TypeCode::_nil ());

  return this->repo_->tc_factory ()->create_union_tc (id.c_str (),
                                                      name.c_str (),
                                                      tc.in (),
                                                      members.in (),
                                                      ACE_TRY_ENV);
}

CORBA::TypeCode_ptr 
TAO_UnionDef_i::discriminator_type (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_READ_GUARD_RETURN (CORBA::TypeCode::_nil ());

  return this->discriminator_type_i (ACE_TRY_ENV);
}

CORBA::TypeCode_ptr 
TAO_UnionDef_i::discriminator_type_i (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_TString disc_path;
  this->repo_->config ()->get_string_value (this->section_key_,
                                            "disc_path",
                                            disc_path);

  ACE_Configuration_Section_Key disc_key;
  this->repo_->config ()->expand_path (this->repo_->root_key (),
                                       disc_path,
                                       disc_key,
                                       0);

  TAO_IDLType_i *impl = 
    this->repo_->servant_factory ()->create_idltype (disc_key,
                                                     ACE_TRY_ENV);

  auto_ptr<TAO_IDLType_i> safety (impl);

  return impl->type_i (ACE_TRY_ENV);
}

CORBA_IDLType_ptr 
TAO_UnionDef_i::discriminator_type_def (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_READ_GUARD_RETURN (CORBA_IDLType::_nil ());

  return this->discriminator_type_def_i (ACE_TRY_ENV);
}

CORBA_IDLType_ptr 
TAO_UnionDef_i::discriminator_type_def_i (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_TString disc_path;
  this->repo_->config ()->get_string_value (this->section_key_,
                                            "disc_path",
                                            disc_path);

  ACE_Configuration_Section_Key disc_key;
  this->repo_->config ()->expand_path (this->repo_->root_key (),
                                       disc_path,
                                       disc_key,
                                       0);

  u_int kind;
  this->repo_->config ()->get_integer_value (disc_key,
                                             "def_kind",
                                             kind);

  CORBA::DefinitionKind def_kind =
    ACE_static_cast (CORBA::DefinitionKind, kind);

  CORBA::Object_var obj =
    this->repo_->servant_factory ()->create_objref (def_kind,
                                                    disc_path.c_str (),
                                                    ACE_TRY_ENV);
  ACE_CHECK_RETURN (CORBA_IDLType::_nil ());

  return CORBA_IDLType::_narrow (obj.in (),
                                 ACE_TRY_ENV);
}

void 
TAO_UnionDef_i::discriminator_type_def (
    CORBA_IDLType_ptr discriminator_type_def,
    CORBA::Environment &ACE_TRY_ENV
  )
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_WRITE_GUARD;

  this->discriminator_type_def_i (discriminator_type_def,
                                  ACE_TRY_ENV);
}

void 
TAO_UnionDef_i::discriminator_type_def_i (
    CORBA_IDLType_ptr discriminator_type_def,
    CORBA::Environment &ACE_TRY_ENV
  )
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  PortableServer::ObjectId_var oid = 
    this->repo_->ir_poa ()->reference_to_id (discriminator_type_def,
                                             ACE_TRY_ENV);
  ACE_CHECK;

  CORBA::String_var disc_path =
    PortableServer::ObjectId_to_string (oid.in ());  

  this->repo_->config ()->set_string_value (this->section_key_,
                                            "disc_path",
                                            disc_path.in ());
}

CORBA_UnionMemberSeq *
TAO_UnionDef_i::members (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_READ_GUARD_RETURN (0);

  return this->members_i (ACE_TRY_ENV);
}

CORBA_UnionMemberSeq *
TAO_UnionDef_i::members_i (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_Unbounded_Queue<ACE_Configuration_Section_Key> key_queue;

  ACE_Configuration_Section_Key refs_key;
  this->repo_->config ()->open_section (this->section_key_,
                                        "refs",
                                        0,
                                        refs_key);

  u_int count;
  this->repo_->config ()->get_integer_value (refs_key,
                                             "count",
                                             count);

  for (u_int i = 0; i < count; i++)
    {
      ACE_Configuration_Section_Key member_key;
      CORBA::String_var section_name = this->int_to_string (i);
      if (this->repo_->config ()->open_section (refs_key,
                                                section_name.in (),
                                                0,
                                                member_key)
           == 0)
        {
          ACE_TString path;
          this->repo_->config ()->get_string_value (member_key,
                                                    "path",
                                                    path);

          ACE_Configuration_Section_Key entry_key;

          // This entry may have been removed.
          if (this->repo_->config ()->expand_path (this->repo_->root_key (),
                                                   path,
                                                   entry_key,
                                                   0)
               == 0)
            {
              key_queue.enqueue_tail (member_key);
            }
        }
    }

  size_t size = key_queue.size ();
                    
  CORBA_UnionMemberSeq *members = 0;
  ACE_NEW_THROW_EX (members,
                    CORBA_UnionMemberSeq (size),
                    CORBA::NO_MEMORY ());
  ACE_CHECK_RETURN (0);

  members->length (size);

  CORBA_UnionMemberSeq_var retval = members;

  ACE_TString name, path;
  ACE_Configuration_Section_Key next_key, entry_key;
  u_int kind = 0;
  CORBA::DefinitionKind def_kind = CORBA::dk_none;
  CORBA::Object_var obj;
  TAO_IDLType_i *impl = 0;

  for (size_t k = 0; k < size; k++)
    {
      key_queue.dequeue_head (next_key);

      this->repo_->config ()->get_string_value (next_key,
                                                "name",
                                                name);

      retval[k].name = name.c_str ();

      this->fetch_label (next_key,
                         retval[k],
                         ACE_TRY_ENV);
      ACE_CHECK_RETURN (0);

      this->repo_->config ()->get_string_value (next_key,
                                                "path",
                                                path);

      this->repo_->config ()->expand_path (this->repo_->root_key (),
                                           path,
                                           entry_key,
                                           0);

      this->repo_->config ()->get_integer_value (entry_key,
                                                 "def_kind",
                                                 kind);

      def_kind =
        ACE_static_cast (CORBA::DefinitionKind, kind);

      obj = 
        this->repo_->servant_factory ()->create_objref (def_kind,
                                                        path.c_str (),
                                                        ACE_TRY_ENV);
      ACE_CHECK_RETURN (0);
    
      retval[k].type_def = CORBA_IDLType::_narrow (obj.in (),
                                                   ACE_TRY_ENV);
      ACE_CHECK_RETURN (0);

      impl =
        this->repo_->servant_factory ()->create_idltype (entry_key,
                                                         ACE_TRY_ENV);
      ACE_CHECK_RETURN (0);

      auto_ptr<TAO_IDLType_i> safety (impl);
    
      retval[k].type = impl->type_i (ACE_TRY_ENV);
      ACE_CHECK_RETURN (0);
    }

  return retval._retn ();
}

void 
TAO_UnionDef_i::members (const CORBA_UnionMemberSeq &members,
                         CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  TAO_IFR_WRITE_GUARD;

  this->members_i (members,
                   ACE_TRY_ENV);
}

void 
TAO_UnionDef_i::members_i (const CORBA_UnionMemberSeq &members,
                           CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  // Destroy our old members, both refs and defns.
  TAO_Container_i::destroy_i (ACE_TRY_ENV);
  ACE_CHECK;

  ACE_TString section_name;
  ACE_Configuration_Section_Key refs_key;

  this->repo_->config ()->open_section (this->section_key_,
                                        "refs",
                                        1,
                                        refs_key);

  // Store the new member count of the union.
  CORBA::ULong count = members.length ();
  this->repo_->config ()->set_integer_value (refs_key,
                                             "count",
                                             count);

  // Create a section for each member. We store the member
  // name, its label value, and the path to its database entry.
  for (CORBA::ULong i = 0; i < count; i++)
    {
      ACE_Configuration_Section_Key member_key;
      char *section_name = this->int_to_string (i);
      this->repo_->config ()->open_section (refs_key,
                                            section_name,
                                            1,
                                            member_key);

      this->repo_->config ()->set_string_value (member_key,
                                                "name",
                                                members[i].name.in ());

      PortableServer::ObjectId_var oid = 
        this->repo_->ir_poa ()->reference_to_id (members[i].type_def.in (),
                                                 ACE_TRY_ENV);
      ACE_CHECK;

      CORBA::String_var member_path =
        PortableServer::ObjectId_to_string (oid.in ());

      this->repo_->config ()->set_string_value (member_key,
                                                "path",
                                                member_path.in ());

      this->store_label (member_key,
                         members[i].label,
                         ACE_TRY_ENV);
    }
}

void
TAO_UnionDef_i::fetch_label (const ACE_Configuration_Section_Key member_key,
                             CORBA_UnionMember &member,
                             CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_Configuration::VALUETYPE vt;
  this->repo_->config ()->find_value (member_key,
                                      "label",
                                      vt);

  if (vt == ACE_Configuration::STRING)
    {
      member.label <<= CORBA::Any::from_octet (0);

      return;
    }

  u_int value = 0;
  this->repo_->config ()->get_integer_value (member_key,
                                             "label",
                                             value);

  CORBA::TypeCode_var tc = this->discriminator_type_i (ACE_TRY_ENV);
  ACE_CHECK;

  CORBA::TCKind kind = tc->kind (ACE_TRY_ENV);
  ACE_CHECK;

  switch (kind)
  {
    case CORBA::tk_char:
      member.label <<= CORBA::Any::from_char (ACE_static_cast (CORBA::Char, 
                                                               value));
      break;
    case CORBA::tk_wchar:
      member.label <<= CORBA::Any::from_wchar (ACE_static_cast (CORBA::WChar, 
                                                                value));
      break;
    case CORBA::tk_boolean:
      member.label <<= CORBA::Any::from_boolean (ACE_static_cast (CORBA::Boolean,
                                                                  value));
      break;
    case CORBA::tk_short:
      member.label <<= ACE_static_cast (CORBA::Short, value);
      break;
    case CORBA::tk_ushort:
      member.label <<= ACE_static_cast (CORBA::UShort, value);
      break;
    case CORBA::tk_long:
      member.label <<= ACE_static_cast (CORBA::Long, value);
      break;
    case CORBA::tk_ulong:
      member.label <<= ACE_static_cast (CORBA::ULong, value);
      break;
#if !defined (ACE_LACKS_LONGLONG_T)
    case CORBA::tk_longlong:
      member.label <<= ACE_static_cast (CORBA::LongLong, value);
      break;
#endif /* ACE_LACKS_LONGLONG_T */
    case CORBA::tk_ulonglong:
      member.label <<= ACE_static_cast (CORBA::ULongLong, value);
      break;
    case CORBA::tk_enum:
    {
      TAO_OutputCDR cdr;
      cdr.write_ulong (ACE_static_cast (CORBA::ULong, value));
      member.label._tao_replace (tc.in (),
                                 TAO_ENCAP_BYTE_ORDER,
                                 cdr.begin ());
      break;
    }
    default:
      break;
  }
}

