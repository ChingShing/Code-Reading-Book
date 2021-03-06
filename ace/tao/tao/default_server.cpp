// default_server.cpp,v 1.75 2001/07/11 21:43:51 oci Exp

#include "tao/default_server.h"
#include "tao/ORB_Core.h"

#if !defined (__ACE_INLINE__)
# include "tao/default_client.i"
#endif /* ! __ACE_INLINE__ */

ACE_RCSID(tao, default_server, "default_server.cpp,v 1.75 2001/07/11 21:43:51 oci Exp")

TAO_Default_Server_Strategy_Factory::TAO_Default_Server_Strategy_Factory (void)
  : activate_server_connections_ (0),
    thread_flags_ (THR_BOUND | THR_DETACHED),
    poa_lock_type_ (TAO_THREAD_LOCK),
    thread_per_connection_use_timeout_ (-1)
{
}

TAO_Default_Server_Strategy_Factory::~TAO_Default_Server_Strategy_Factory (void)
{
  // Perform appropriate cleanup.
}

int
TAO_Default_Server_Strategy_Factory::enable_poa_locking (void)
{
  switch (this->poa_lock_type_)
    {
    case TAO_NULL_LOCK:
      return 0;
    case TAO_THREAD_LOCK:
    default:
      return 1;
    }
}

int
TAO_Default_Server_Strategy_Factory::activate_server_connections (void)
{
  return this->activate_server_connections_;
}

int
TAO_Default_Server_Strategy_Factory::thread_per_connection_timeout (ACE_Time_Value &timeout)
{
  timeout = this->thread_per_connection_timeout_;
  return this->thread_per_connection_use_timeout_;
}

int
TAO_Default_Server_Strategy_Factory::server_connection_thread_flags (void)
{
  return this->thread_flags_;
}

int
TAO_Default_Server_Strategy_Factory::server_connection_thread_count (void)
{
  return 1;
}

// Evil macros b/c I'm lazy!
#define TAO_BEGINCHECK  if (0)
#define TAO_CHECKANDSET(sym) \
  else if (ACE_OS::strcmp (flag, #sym) == 0) \
  ACE_SET_BITS (this->thread_flags_, sym)
#define TAO_ENDCHECK

void
TAO_Default_Server_Strategy_Factory::tokenize (char *flag_string)
{
  char *lasts = 0;

  for (char *flag = ACE_OS::strtok_r (flag_string,
                                      "|",
                                      &lasts);
       flag != 0;
       flag = ACE_OS::strtok_r (0,
                                "|",
                                &lasts))
    {
      TAO_BEGINCHECK;
      TAO_CHECKANDSET (THR_DETACHED);
      TAO_CHECKANDSET (THR_BOUND);
      TAO_CHECKANDSET (THR_NEW_LWP);
      TAO_CHECKANDSET (THR_SUSPENDED);
#if !defined (ACE_WIN32)
      TAO_CHECKANDSET (THR_DAEMON);
#endif /* ACE_WIN32 */
      TAO_ENDCHECK;
    }
}

int
TAO_Default_Server_Strategy_Factory::init (int argc, char *argv[])
{
  return this->parse_args (argc, argv);
}

int
TAO_Default_Server_Strategy_Factory::open (TAO_ORB_Core *)
{
  return 0;
}

int
TAO_Default_Server_Strategy_Factory::parse_args (int argc, char *argv[])
{
  ACE_TRACE ("TAO_Default_Server_Strategy_Factory::parse_args");

  int curarg;

  for (curarg = 0; curarg < argc && argv[curarg]; curarg++)
    if (ACE_OS::strcasecmp (argv[curarg],
                            "-ORBConcurrency") == 0)
      {
        curarg++;
        if (curarg < argc)
          {
            char *name = argv[curarg];

            if (ACE_OS::strcasecmp (name,
                                    "reactive") == 0)
              this->activate_server_connections_ = 0;
            else if (ACE_OS::strcasecmp (name,
                                         "thread-per-connection") == 0)
              this->activate_server_connections_ = 1;
            else
              this->report_option_value_error ("-ORBConcurrency", name);
          }
      }

    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBThreadPerConnectionTimeout") == 0)
      {
        curarg++;
        if (curarg < argc)
          {
            char *name = argv[curarg];

            if (ACE_OS::strcasecmp (name,
                                    "infinite") == 0)
              {
                this->thread_per_connection_use_timeout_ = 0;
              }
            else
              {
                this->thread_per_connection_use_timeout_ = 1;
                int milliseconds = ACE_OS::atoi (name);
                this->thread_per_connection_timeout_.set (0,
                                                          1000 * milliseconds);
              }
          }
      }

    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBTableSize") == 0
             || ACE_OS::strcasecmp (argv[curarg],
                                    "-ORBActiveObjectMapSize") == 0)
      {
        curarg++;
        if (curarg < argc)
          this->active_object_map_creation_parameters_.active_object_map_size_ =
            ACE_OS::strtoul (argv[curarg],
                             0,
                             10);
      }
    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBPOAMapSize") == 0)
      {
        curarg++;
        if (curarg < argc)
          this->active_object_map_creation_parameters_.poa_map_size_ =
            ACE_OS::strtoul (argv[curarg],
                             0,
                             10);
      }
    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBActiveHintInIds") == 0)
      {
        curarg++;
        if (curarg < argc)
          {
            char *value = argv[curarg];

            this->active_object_map_creation_parameters_.use_active_hint_in_ids_ =
              ACE_OS::atoi (value);
          }
      }
    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBActiveHintInPOANames") == 0)
      {
        curarg++;
        if (curarg < argc)
          {
            char *value = argv[curarg];

            this->active_object_map_creation_parameters_.use_active_hint_in_poa_names_ =
              ACE_OS::atoi (value);
          }
      }
    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBAllowReactivationOfSystemids") == 0)
      {
        curarg++;
        if (curarg < argc)
          {
            char *value = argv[curarg];

            this->active_object_map_creation_parameters_.allow_reactivation_of_system_ids_ =
              ACE_OS::atoi (value);
          }
      }
    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBUseridPolicyDemuxStrategy") == 0)
      {
        curarg++;
        if (curarg < argc)
          {
            char *name = argv[curarg];

            // Active demux not supported with user id policy.
            if (ACE_OS::strcasecmp (name,
                                    "dynamic") == 0)
              this->active_object_map_creation_parameters_.object_lookup_strategy_for_user_id_policy_ =
                TAO_DYNAMIC_HASH;
            else if (ACE_OS::strcasecmp (name,
                                         "linear") == 0)
              this->active_object_map_creation_parameters_.object_lookup_strategy_for_user_id_policy_ =
                TAO_LINEAR;
            else
              this->report_option_value_error ("-ORBUseridPolicyDemuxStrategy", name);
          }
      }
    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBSystemidPolicyDemuxStrategy") == 0)
      {
        curarg++;
        if (curarg < argc)
          {
            char *name = argv[curarg];

            if (ACE_OS::strcasecmp (name,
                                    "dynamic") == 0)
              this->active_object_map_creation_parameters_.object_lookup_strategy_for_system_id_policy_ =
                TAO_DYNAMIC_HASH;
            else if (ACE_OS::strcasecmp (name,
                                         "linear") == 0)
              this->active_object_map_creation_parameters_.object_lookup_strategy_for_system_id_policy_ =
                TAO_LINEAR;
            else if (ACE_OS::strcasecmp (name,
                                         "active") == 0)
              this->active_object_map_creation_parameters_.object_lookup_strategy_for_system_id_policy_ =
                TAO_ACTIVE_DEMUX;
            else
              this->report_option_value_error ("-ORBSystemidPolicyDemuxStrategy", name);
          }
      }
    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBPersistentidPolicyDemuxStrategy") == 0)
      {
        curarg++;
        if (curarg < argc)
          {
            char *name = argv[curarg];

            // Active demux not supported with user id policy.
            if (ACE_OS::strcasecmp (name,
                                    "dynamic") == 0)
              this->active_object_map_creation_parameters_.poa_lookup_strategy_for_persistent_id_policy_ =
                TAO_DYNAMIC_HASH;
            else if (ACE_OS::strcasecmp (name,
                                         "linear") == 0)
              this->active_object_map_creation_parameters_.poa_lookup_strategy_for_persistent_id_policy_ =
                TAO_LINEAR;
            else
              this->report_option_value_error ("-ORBPersistentidPolicyDemuxStrategy", name);
          }
      }
    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBTransientidPolicyDemuxStrategy") == 0)
      {
        curarg++;
        if (curarg < argc)
          {
            char *name = argv[curarg];

            if (ACE_OS::strcasecmp (name,
                                    "dynamic") == 0)
              this->active_object_map_creation_parameters_.poa_lookup_strategy_for_transient_id_policy_ =
                TAO_DYNAMIC_HASH;
            else if (ACE_OS::strcasecmp (name,
                                         "linear") == 0)
              this->active_object_map_creation_parameters_.poa_lookup_strategy_for_transient_id_policy_ =
                TAO_LINEAR;
            else if (ACE_OS::strcasecmp (name,
                                         "active") == 0)
              this->active_object_map_creation_parameters_.poa_lookup_strategy_for_transient_id_policy_ =
                TAO_ACTIVE_DEMUX;
            else
              this->report_option_value_error ("-ORBTransientidPolicyDemuxStrategy", name);
          }
      }
    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBUniqueidPolicyReverseDemuxStrategy") == 0)
      {
        curarg++;
        if (curarg < argc)
          {
            char *name = argv[curarg];

            if (ACE_OS::strcasecmp (name,
                                    "dynamic") == 0)
              this->active_object_map_creation_parameters_.reverse_object_lookup_strategy_for_unique_id_policy_ =
                TAO_DYNAMIC_HASH;
            else if (ACE_OS::strcasecmp (name,
                                         "linear") == 0)
              this->active_object_map_creation_parameters_.reverse_object_lookup_strategy_for_unique_id_policy_ =
                TAO_LINEAR;
            else
              this->report_option_value_error ("-ORBUniqueidPolicyReverseDemuxStrategy", name);
          }
      }
    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBPOALock") == 0)
      {
        curarg++;
        if (curarg < argc)
          {
            char *name = argv[curarg];

            if (ACE_OS::strcasecmp (name,
                                    "thread") == 0)
              this->poa_lock_type_ = TAO_THREAD_LOCK;
            else if (ACE_OS::strcasecmp (name,
                                         "null") == 0)
              this->poa_lock_type_ = TAO_NULL_LOCK;
            else
              this->report_option_value_error ("-ORBPOALock", name);
          }
      }
    else if (ACE_OS::strcasecmp (argv[curarg],
                                 "-ORBThreadFlags") == 0)
      {
        curarg++;

        if (curarg < argc)
          this->tokenize (argv[curarg]);
      }

    else if (ACE_OS::strncmp (argv[curarg], "-ORB", 4) == 0)
      {
        // Can we assume there is an argument after the option?
        // curarg++;
        ACE_ERROR ((LM_ERROR,
                    "Server_Strategy_Factory - "
                    "unknown option <%s>\n",
                    argv[curarg]));
      }
    else
      {
        ACE_DEBUG ((LM_DEBUG,
                    "Server_Strategy_Factory - "
                    "ignoring option <%s>\n",
                    argv[curarg]));
      }

  return 0;
}

void
TAO_Default_Server_Strategy_Factory::report_option_value_error (
                                 const char* option_name,
                                 const char* option_value)
{
  ACE_DEBUG((LM_DEBUG,
             ACE_TEXT ("Server_Strategy_Factory - unknown argument")
             ACE_TEXT (" <%s> for <%s>\n"),
             option_value, option_name));
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

ACE_STATIC_SVC_DEFINE (TAO_Default_Server_Strategy_Factory,
                       ACE_TEXT ("Server_Strategy_Factory"),
                       ACE_SVC_OBJ_T,
                       &ACE_SVC_NAME (TAO_Default_Server_Strategy_Factory),
                       ACE_Service_Type::DELETE_THIS | ACE_Service_Type::DELETE_OBJ,
                       0)
ACE_FACTORY_DEFINE (TAO, TAO_Default_Server_Strategy_Factory)
