#----------------------------------------------------------------------------
#	Makefile,v 1.4 2000/04/19 22:07:14 coryan Exp
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#	Local macros
#----------------------------------------------------------------------------

INFO    = README

LIB     = libBPRD.a
SHLIB   = libBPRD.$(SOEXT)

BIN     = bpr_thread

PSRC   	= $(addsuffix .cpp,$(BIN))

LSRC  	= Thread_Bounded_Packet_Relay.cpp \
	  BPR_Drivers.cpp

LDLIBS 	= -lBPRD

VLDLIBS = $(LDLIBS:%=%$(VAR))

BUILD = $(VLIB) $(VSHLIB) $(SHLIBA) $(VBIN)

#----------------------------------------------------------------------------
#	Include macros and targets
#----------------------------------------------------------------------------

include		$(ACE_ROOT)/include/makeinclude/wrapper_macros.GNU
include		$(ACE_ROOT)/include/makeinclude/macros.GNU
include		$(ACE_ROOT)/include/makeinclude/rules.common.GNU
include		$(ACE_ROOT)/include/makeinclude/rules.nonested.GNU
include         $(ACE_ROOT)/include/makeinclude/rules.lib.GNU
include		$(ACE_ROOT)/include/makeinclude/rules.bin.GNU
include		$(ACE_ROOT)/include/makeinclude/rules.local.GNU

#----------------------------------------------------------------------------
#	Local targets
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#	Dependencies
#----------------------------------------------------------------------------

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.


.obj/Thread_Bounded_Packet_Relay.o .obj/Thread_Bounded_Packet_Relay.so .shobj/Thread_Bounded_Packet_Relay.o .shobj/Thread_Bounded_Packet_Relay.so: Thread_Bounded_Packet_Relay.cpp \
 Thread_Bounded_Packet_Relay.h \
 $(ACE_ROOT)/ace/Functor.h \
 $(ACE_ROOT)/ace/pre.h \
 $(ACE_ROOT)/ace/ACE.h \
 $(ACE_ROOT)/ace/OS.h \
 $(ACE_ROOT)/ace/post.h \
 $(ACE_ROOT)/ace/ACE_export.h \
 $(ACE_ROOT)/ace/svc_export.h \
 $(ACE_ROOT)/ace/Min_Max.h \
 $(ACE_ROOT)/ace/streams.h \
 $(ACE_ROOT)/ace/Basic_Types.h \
 $(ACE_ROOT)/ace/Basic_Types.i \
 $(ACE_ROOT)/ace/Trace.h \
 $(ACE_ROOT)/ace/OS.i \
 $(ACE_ROOT)/ace/Log_Msg.h \
 $(ACE_ROOT)/ace/Log_Record.h \
 $(ACE_ROOT)/ace/Log_Priority.h \
 $(ACE_ROOT)/ace/Log_Record.i \
 $(ACE_ROOT)/ace/ACE.i \
 $(ACE_ROOT)/ace/Functor.i \
 $(ACE_ROOT)/ace/Functor_T.h \
 $(ACE_ROOT)/ace/Functor_T.i \
 $(ACE_ROOT)/ace/Functor_T.cpp \
 $(ACE_ROOT)/ace/Task.h \
 $(ACE_ROOT)/ace/Service_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.i \
 $(ACE_ROOT)/ace/Event_Handler.h \
 $(ACE_ROOT)/ace/Event_Handler.i \
 $(ACE_ROOT)/ace/Service_Object.i \
 $(ACE_ROOT)/ace/Thread_Manager.h \
 $(ACE_ROOT)/ace/Thread.h \
 $(ACE_ROOT)/ace/Thread.i \
 $(ACE_ROOT)/ace/Synch.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.i \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.i \
 $(ACE_ROOT)/ace/Synch.i \
 $(ACE_ROOT)/ace/Synch_T.h \
 $(ACE_ROOT)/ace/Synch_T.i \
 $(ACE_ROOT)/ace/Atomic_Op.i \
 $(ACE_ROOT)/ace/Synch_T.cpp \
 $(ACE_ROOT)/ace/Containers.h \
 $(ACE_ROOT)/ace/Malloc_Base.h \
 $(ACE_ROOT)/ace/Containers.i \
 $(ACE_ROOT)/ace/Containers_T.h \
 $(ACE_ROOT)/ace/Containers_T.i \
 $(ACE_ROOT)/ace/Containers_T.cpp \
 $(ACE_ROOT)/ace/Malloc.h \
 $(ACE_ROOT)/ace/Based_Pointer_T.h \
 $(ACE_ROOT)/ace/Based_Pointer_T.i \
 $(ACE_ROOT)/ace/Based_Pointer_T.cpp \
 $(ACE_ROOT)/ace/Based_Pointer_Repository.h \
 $(ACE_ROOT)/ace/Singleton.h \
 $(ACE_ROOT)/ace/Singleton.i \
 $(ACE_ROOT)/ace/Singleton.cpp \
 $(ACE_ROOT)/ace/Object_Manager.h \
 $(ACE_ROOT)/ace/Object_Manager.i \
 $(ACE_ROOT)/ace/Managed_Object.h \
 $(ACE_ROOT)/ace/Managed_Object.i \
 $(ACE_ROOT)/ace/Managed_Object.cpp \
 $(ACE_ROOT)/ace/Malloc.i \
 $(ACE_ROOT)/ace/Malloc_T.h \
 $(ACE_ROOT)/ace/Free_List.h \
 $(ACE_ROOT)/ace/Free_List.i \
 $(ACE_ROOT)/ace/Free_List.cpp \
 $(ACE_ROOT)/ace/Malloc_T.i \
 $(ACE_ROOT)/ace/Malloc_T.cpp \
 $(ACE_ROOT)/ace/Memory_Pool.h \
 $(ACE_ROOT)/ace/Signal.h \
 $(ACE_ROOT)/ace/Signal.i \
 $(ACE_ROOT)/ace/Mem_Map.h \
 $(ACE_ROOT)/ace/Mem_Map.i \
 $(ACE_ROOT)/ace/Memory_Pool.i \
 $(ACE_ROOT)/ace/Thread_Manager.i \
 $(ACE_ROOT)/ace/Task.i \
 $(ACE_ROOT)/ace/Task_T.h \
 $(ACE_ROOT)/ace/Message_Queue.h \
 $(ACE_ROOT)/ace/Message_Block.h \
 $(ACE_ROOT)/ace/Message_Block.i \
 $(ACE_ROOT)/ace/Message_Block_T.h \
 $(ACE_ROOT)/ace/Message_Block_T.i \
 $(ACE_ROOT)/ace/Message_Block_T.cpp \
 $(ACE_ROOT)/ace/IO_Cntl_Msg.h \
 $(ACE_ROOT)/ace/Message_Queue_T.h \
 $(ACE_ROOT)/ace/Message_Queue_T.i \
 $(ACE_ROOT)/ace/Message_Queue_T.cpp \
 $(ACE_ROOT)/ace/Strategies.h \
 $(ACE_ROOT)/ace/Strategies_T.h \
 $(ACE_ROOT)/ace/Service_Config.h \
 $(ACE_ROOT)/ace/SString.h \
 $(ACE_ROOT)/ace/SString.i \
 $(ACE_ROOT)/ace/Service_Config.i \
 $(ACE_ROOT)/ace/Reactor.h \
 $(ACE_ROOT)/ace/Handle_Set.h \
 $(ACE_ROOT)/ace/Handle_Set.i \
 $(ACE_ROOT)/ace/Timer_Queue.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.i \
 $(ACE_ROOT)/ace/Timer_Queue_T.cpp \
 $(ACE_ROOT)/ace/Reactor.i \
 $(ACE_ROOT)/ace/Reactor_Impl.h \
 $(ACE_ROOT)/ace/Svc_Conf_Tokens.h \
 $(ACE_ROOT)/ace/Synch_Options.h \
 $(ACE_ROOT)/ace/Synch_Options.i \
 $(ACE_ROOT)/ace/Hash_Map_Manager.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager.i \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.i \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.cpp \
 $(ACE_ROOT)/ace/Strategies_T.i \
 $(ACE_ROOT)/ace/Strategies_T.cpp \
 $(ACE_ROOT)/ace/Service_Repository.h \
 $(ACE_ROOT)/ace/Service_Types.h \
 $(ACE_ROOT)/ace/Service_Types.i \
 $(ACE_ROOT)/ace/Service_Repository.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.h \
 $(ACE_ROOT)/ace/WFMO_Reactor.i \
 $(ACE_ROOT)/ace/Strategies.i \
 $(ACE_ROOT)/ace/Message_Queue.i \
 $(ACE_ROOT)/ace/Task_T.i \
 $(ACE_ROOT)/ace/Task_T.cpp \
 $(ACE_ROOT)/ace/Module.h \
 $(ACE_ROOT)/ace/Module.i \
 $(ACE_ROOT)/ace/Module.cpp \
 $(ACE_ROOT)/ace/Stream_Modules.h \
 $(ACE_ROOT)/ace/Stream_Modules.i \
 $(ACE_ROOT)/ace/Stream_Modules.cpp \
 $(ACE_ROOT)/ace/Timer_Heap_T.h \
 $(ACE_ROOT)/ace/Timer_Heap_T.cpp \
 $(ACE_ROOT)/ace/Timer_Queue_Adapters.h \
 $(ACE_ROOT)/ace/Timer_Queue_Adapters.i \
 $(ACE_ROOT)/ace/Timer_Queue_Adapters.cpp \
 BPR_Drivers.h BPR_Drivers_T.h BPR_Drivers_T.cpp

.obj/BPR_Drivers.o .obj/BPR_Drivers.so .shobj/BPR_Drivers.o .shobj/BPR_Drivers.so: BPR_Drivers.cpp BPR_Drivers.h \
 $(ACE_ROOT)/ace/Functor.h \
 $(ACE_ROOT)/ace/pre.h \
 $(ACE_ROOT)/ace/ACE.h \
 $(ACE_ROOT)/ace/OS.h \
 $(ACE_ROOT)/ace/post.h \
 $(ACE_ROOT)/ace/ACE_export.h \
 $(ACE_ROOT)/ace/svc_export.h \
 $(ACE_ROOT)/ace/Min_Max.h \
 $(ACE_ROOT)/ace/streams.h \
 $(ACE_ROOT)/ace/Basic_Types.h \
 $(ACE_ROOT)/ace/Basic_Types.i \
 $(ACE_ROOT)/ace/Trace.h \
 $(ACE_ROOT)/ace/OS.i \
 $(ACE_ROOT)/ace/Log_Msg.h \
 $(ACE_ROOT)/ace/Log_Record.h \
 $(ACE_ROOT)/ace/Log_Priority.h \
 $(ACE_ROOT)/ace/Log_Record.i \
 $(ACE_ROOT)/ace/ACE.i \
 $(ACE_ROOT)/ace/Functor.i \
 $(ACE_ROOT)/ace/Functor_T.h \
 $(ACE_ROOT)/ace/Functor_T.i \
 $(ACE_ROOT)/ace/Functor_T.cpp \
 $(ACE_ROOT)/ace/Task.h \
 $(ACE_ROOT)/ace/Service_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.i \
 $(ACE_ROOT)/ace/Event_Handler.h \
 $(ACE_ROOT)/ace/Event_Handler.i \
 $(ACE_ROOT)/ace/Service_Object.i \
 $(ACE_ROOT)/ace/Thread_Manager.h \
 $(ACE_ROOT)/ace/Thread.h \
 $(ACE_ROOT)/ace/Thread.i \
 $(ACE_ROOT)/ace/Synch.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.i \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.i \
 $(ACE_ROOT)/ace/Synch.i \
 $(ACE_ROOT)/ace/Synch_T.h \
 $(ACE_ROOT)/ace/Synch_T.i \
 $(ACE_ROOT)/ace/Atomic_Op.i \
 $(ACE_ROOT)/ace/Synch_T.cpp \
 $(ACE_ROOT)/ace/Containers.h \
 $(ACE_ROOT)/ace/Malloc_Base.h \
 $(ACE_ROOT)/ace/Containers.i \
 $(ACE_ROOT)/ace/Containers_T.h \
 $(ACE_ROOT)/ace/Containers_T.i \
 $(ACE_ROOT)/ace/Containers_T.cpp \
 $(ACE_ROOT)/ace/Malloc.h \
 $(ACE_ROOT)/ace/Based_Pointer_T.h \
 $(ACE_ROOT)/ace/Based_Pointer_T.i \
 $(ACE_ROOT)/ace/Based_Pointer_T.cpp \
 $(ACE_ROOT)/ace/Based_Pointer_Repository.h \
 $(ACE_ROOT)/ace/Singleton.h \
 $(ACE_ROOT)/ace/Singleton.i \
 $(ACE_ROOT)/ace/Singleton.cpp \
 $(ACE_ROOT)/ace/Object_Manager.h \
 $(ACE_ROOT)/ace/Object_Manager.i \
 $(ACE_ROOT)/ace/Managed_Object.h \
 $(ACE_ROOT)/ace/Managed_Object.i \
 $(ACE_ROOT)/ace/Managed_Object.cpp \
 $(ACE_ROOT)/ace/Malloc.i \
 $(ACE_ROOT)/ace/Malloc_T.h \
 $(ACE_ROOT)/ace/Free_List.h \
 $(ACE_ROOT)/ace/Free_List.i \
 $(ACE_ROOT)/ace/Free_List.cpp \
 $(ACE_ROOT)/ace/Malloc_T.i \
 $(ACE_ROOT)/ace/Malloc_T.cpp \
 $(ACE_ROOT)/ace/Memory_Pool.h \
 $(ACE_ROOT)/ace/Signal.h \
 $(ACE_ROOT)/ace/Signal.i \
 $(ACE_ROOT)/ace/Mem_Map.h \
 $(ACE_ROOT)/ace/Mem_Map.i \
 $(ACE_ROOT)/ace/Memory_Pool.i \
 $(ACE_ROOT)/ace/Thread_Manager.i \
 $(ACE_ROOT)/ace/Task.i \
 $(ACE_ROOT)/ace/Task_T.h \
 $(ACE_ROOT)/ace/Message_Queue.h \
 $(ACE_ROOT)/ace/Message_Block.h \
 $(ACE_ROOT)/ace/Message_Block.i \
 $(ACE_ROOT)/ace/Message_Block_T.h \
 $(ACE_ROOT)/ace/Message_Block_T.i \
 $(ACE_ROOT)/ace/Message_Block_T.cpp \
 $(ACE_ROOT)/ace/IO_Cntl_Msg.h \
 $(ACE_ROOT)/ace/Message_Queue_T.h \
 $(ACE_ROOT)/ace/Message_Queue_T.i \
 $(ACE_ROOT)/ace/Message_Queue_T.cpp \
 $(ACE_ROOT)/ace/Strategies.h \
 $(ACE_ROOT)/ace/Strategies_T.h \
 $(ACE_ROOT)/ace/Service_Config.h \
 $(ACE_ROOT)/ace/SString.h \
 $(ACE_ROOT)/ace/SString.i \
 $(ACE_ROOT)/ace/Service_Config.i \
 $(ACE_ROOT)/ace/Reactor.h \
 $(ACE_ROOT)/ace/Handle_Set.h \
 $(ACE_ROOT)/ace/Handle_Set.i \
 $(ACE_ROOT)/ace/Timer_Queue.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.i \
 $(ACE_ROOT)/ace/Timer_Queue_T.cpp \
 $(ACE_ROOT)/ace/Reactor.i \
 $(ACE_ROOT)/ace/Reactor_Impl.h \
 $(ACE_ROOT)/ace/Svc_Conf_Tokens.h \
 $(ACE_ROOT)/ace/Synch_Options.h \
 $(ACE_ROOT)/ace/Synch_Options.i \
 $(ACE_ROOT)/ace/Hash_Map_Manager.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager.i \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.i \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.cpp \
 $(ACE_ROOT)/ace/Strategies_T.i \
 $(ACE_ROOT)/ace/Strategies_T.cpp \
 $(ACE_ROOT)/ace/Service_Repository.h \
 $(ACE_ROOT)/ace/Service_Types.h \
 $(ACE_ROOT)/ace/Service_Types.i \
 $(ACE_ROOT)/ace/Service_Repository.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.h \
 $(ACE_ROOT)/ace/WFMO_Reactor.i \
 $(ACE_ROOT)/ace/Strategies.i \
 $(ACE_ROOT)/ace/Message_Queue.i \
 $(ACE_ROOT)/ace/Task_T.i \
 $(ACE_ROOT)/ace/Task_T.cpp \
 $(ACE_ROOT)/ace/Module.h \
 $(ACE_ROOT)/ace/Module.i \
 $(ACE_ROOT)/ace/Module.cpp \
 $(ACE_ROOT)/ace/Stream_Modules.h \
 $(ACE_ROOT)/ace/Stream_Modules.i \
 $(ACE_ROOT)/ace/Stream_Modules.cpp \
 BPR_Drivers_T.h BPR_Drivers_T.cpp

.obj/bpr_thread.o .obj/bpr_thread.so .shobj/bpr_thread.o .shobj/bpr_thread.so: bpr_thread.cpp \
 $(ACE_ROOT)/ace/Auto_Ptr.h \
 $(ACE_ROOT)/ace/pre.h \
 $(ACE_ROOT)/ace/ACE.h \
 $(ACE_ROOT)/ace/OS.h \
 $(ACE_ROOT)/ace/post.h \
 $(ACE_ROOT)/ace/ACE_export.h \
 $(ACE_ROOT)/ace/svc_export.h \
 $(ACE_ROOT)/ace/Min_Max.h \
 $(ACE_ROOT)/ace/streams.h \
 $(ACE_ROOT)/ace/Basic_Types.h \
 $(ACE_ROOT)/ace/Basic_Types.i \
 $(ACE_ROOT)/ace/Trace.h \
 $(ACE_ROOT)/ace/OS.i \
 $(ACE_ROOT)/ace/Log_Msg.h \
 $(ACE_ROOT)/ace/Log_Record.h \
 $(ACE_ROOT)/ace/Log_Priority.h \
 $(ACE_ROOT)/ace/Log_Record.i \
 $(ACE_ROOT)/ace/ACE.i \
 $(ACE_ROOT)/ace/Auto_Ptr.i \
 $(ACE_ROOT)/ace/Auto_Ptr.cpp \
 Thread_Bounded_Packet_Relay.h \
 $(ACE_ROOT)/ace/Functor.h \
 $(ACE_ROOT)/ace/Functor.i \
 $(ACE_ROOT)/ace/Functor_T.h \
 $(ACE_ROOT)/ace/Functor_T.i \
 $(ACE_ROOT)/ace/Functor_T.cpp \
 $(ACE_ROOT)/ace/Task.h \
 $(ACE_ROOT)/ace/Service_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.h \
 $(ACE_ROOT)/ace/Shared_Object.i \
 $(ACE_ROOT)/ace/Event_Handler.h \
 $(ACE_ROOT)/ace/Event_Handler.i \
 $(ACE_ROOT)/ace/Service_Object.i \
 $(ACE_ROOT)/ace/Thread_Manager.h \
 $(ACE_ROOT)/ace/Thread.h \
 $(ACE_ROOT)/ace/Thread.i \
 $(ACE_ROOT)/ace/Synch.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.h \
 $(ACE_ROOT)/ace/SV_Semaphore_Simple.i \
 $(ACE_ROOT)/ace/SV_Semaphore_Complex.i \
 $(ACE_ROOT)/ace/Synch.i \
 $(ACE_ROOT)/ace/Synch_T.h \
 $(ACE_ROOT)/ace/Synch_T.i \
 $(ACE_ROOT)/ace/Atomic_Op.i \
 $(ACE_ROOT)/ace/Synch_T.cpp \
 $(ACE_ROOT)/ace/Containers.h \
 $(ACE_ROOT)/ace/Malloc_Base.h \
 $(ACE_ROOT)/ace/Containers.i \
 $(ACE_ROOT)/ace/Containers_T.h \
 $(ACE_ROOT)/ace/Containers_T.i \
 $(ACE_ROOT)/ace/Containers_T.cpp \
 $(ACE_ROOT)/ace/Malloc.h \
 $(ACE_ROOT)/ace/Based_Pointer_T.h \
 $(ACE_ROOT)/ace/Based_Pointer_T.i \
 $(ACE_ROOT)/ace/Based_Pointer_T.cpp \
 $(ACE_ROOT)/ace/Based_Pointer_Repository.h \
 $(ACE_ROOT)/ace/Singleton.h \
 $(ACE_ROOT)/ace/Singleton.i \
 $(ACE_ROOT)/ace/Singleton.cpp \
 $(ACE_ROOT)/ace/Object_Manager.h \
 $(ACE_ROOT)/ace/Object_Manager.i \
 $(ACE_ROOT)/ace/Managed_Object.h \
 $(ACE_ROOT)/ace/Managed_Object.i \
 $(ACE_ROOT)/ace/Managed_Object.cpp \
 $(ACE_ROOT)/ace/Malloc.i \
 $(ACE_ROOT)/ace/Malloc_T.h \
 $(ACE_ROOT)/ace/Free_List.h \
 $(ACE_ROOT)/ace/Free_List.i \
 $(ACE_ROOT)/ace/Free_List.cpp \
 $(ACE_ROOT)/ace/Malloc_T.i \
 $(ACE_ROOT)/ace/Malloc_T.cpp \
 $(ACE_ROOT)/ace/Memory_Pool.h \
 $(ACE_ROOT)/ace/Signal.h \
 $(ACE_ROOT)/ace/Signal.i \
 $(ACE_ROOT)/ace/Mem_Map.h \
 $(ACE_ROOT)/ace/Mem_Map.i \
 $(ACE_ROOT)/ace/Memory_Pool.i \
 $(ACE_ROOT)/ace/Thread_Manager.i \
 $(ACE_ROOT)/ace/Task.i \
 $(ACE_ROOT)/ace/Task_T.h \
 $(ACE_ROOT)/ace/Message_Queue.h \
 $(ACE_ROOT)/ace/Message_Block.h \
 $(ACE_ROOT)/ace/Message_Block.i \
 $(ACE_ROOT)/ace/Message_Block_T.h \
 $(ACE_ROOT)/ace/Message_Block_T.i \
 $(ACE_ROOT)/ace/Message_Block_T.cpp \
 $(ACE_ROOT)/ace/IO_Cntl_Msg.h \
 $(ACE_ROOT)/ace/Message_Queue_T.h \
 $(ACE_ROOT)/ace/Message_Queue_T.i \
 $(ACE_ROOT)/ace/Message_Queue_T.cpp \
 $(ACE_ROOT)/ace/Strategies.h \
 $(ACE_ROOT)/ace/Strategies_T.h \
 $(ACE_ROOT)/ace/Service_Config.h \
 $(ACE_ROOT)/ace/SString.h \
 $(ACE_ROOT)/ace/SString.i \
 $(ACE_ROOT)/ace/Service_Config.i \
 $(ACE_ROOT)/ace/Reactor.h \
 $(ACE_ROOT)/ace/Handle_Set.h \
 $(ACE_ROOT)/ace/Handle_Set.i \
 $(ACE_ROOT)/ace/Timer_Queue.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.h \
 $(ACE_ROOT)/ace/Timer_Queue_T.i \
 $(ACE_ROOT)/ace/Timer_Queue_T.cpp \
 $(ACE_ROOT)/ace/Reactor.i \
 $(ACE_ROOT)/ace/Reactor_Impl.h \
 $(ACE_ROOT)/ace/Svc_Conf_Tokens.h \
 $(ACE_ROOT)/ace/Synch_Options.h \
 $(ACE_ROOT)/ace/Synch_Options.i \
 $(ACE_ROOT)/ace/Hash_Map_Manager.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager.i \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.h \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.i \
 $(ACE_ROOT)/ace/Hash_Map_Manager_T.cpp \
 $(ACE_ROOT)/ace/Strategies_T.i \
 $(ACE_ROOT)/ace/Strategies_T.cpp \
 $(ACE_ROOT)/ace/Service_Repository.h \
 $(ACE_ROOT)/ace/Service_Types.h \
 $(ACE_ROOT)/ace/Service_Types.i \
 $(ACE_ROOT)/ace/Service_Repository.i \
 $(ACE_ROOT)/ace/WFMO_Reactor.h \
 $(ACE_ROOT)/ace/WFMO_Reactor.i \
 $(ACE_ROOT)/ace/Strategies.i \
 $(ACE_ROOT)/ace/Message_Queue.i \
 $(ACE_ROOT)/ace/Task_T.i \
 $(ACE_ROOT)/ace/Task_T.cpp \
 $(ACE_ROOT)/ace/Module.h \
 $(ACE_ROOT)/ace/Module.i \
 $(ACE_ROOT)/ace/Module.cpp \
 $(ACE_ROOT)/ace/Stream_Modules.h \
 $(ACE_ROOT)/ace/Stream_Modules.i \
 $(ACE_ROOT)/ace/Stream_Modules.cpp \
 $(ACE_ROOT)/ace/Timer_Heap_T.h \
 $(ACE_ROOT)/ace/Timer_Heap_T.cpp \
 $(ACE_ROOT)/ace/Timer_Queue_Adapters.h \
 $(ACE_ROOT)/ace/Timer_Queue_Adapters.i \
 $(ACE_ROOT)/ace/Timer_Queue_Adapters.cpp \
 BPR_Drivers.h BPR_Drivers_T.h BPR_Drivers_T.cpp

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
