/******************************************************************************
	Confidential Property of Fork Particle, Inc.
  (c) Copyright 2002-2008 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#ifndef frkpsystem_win32_h
#define frkpsystem_win32_h

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
typedef int (*_t_frkSetEventCB) (void* pEvent);
typedef int (*_t_frkSetThreadPriorityCB) (void* pThread, int nPriority);
typedef int (*_t_frkCloseHandleCB) (void* pObject);
typedef unsigned long (*_t_frkResumeThreadCB) (void* pThread);
typedef unsigned long (*_t_frkWaitForSingleObjectCB) (void* pEvent, unsigned long nMilliSeconds);
typedef unsigned long (*_t_frkSimThreadCB)(void *pData);
typedef void* (*_t_frkCreateEventCB) (int nManualReset, int nInitialState, const char *pName);
typedef void* (*_t_frkCreateThreadCB) (_t_frkSimThreadCB pThreadCB, void* lpParameter, 
									   int nCreateSuspended, unsigned long *pThreadID);
/******************************************************************************/
extern int frkPEnableMultiCoreWin32(int							 nThreadPriority,
									_t_frkCreateThreadCB		 pCreateThreadCB,
									_t_frkCreateEventCB			 pCreateEventCB,
									_t_frkWaitForSingleObjectCB  pWaitForSingleObjectCB,
									_t_frkSetEventCB			 pSetEventCB,
									_t_frkSetThreadPriorityCB	 pSetThreadPriorityCB,
									_t_frkResumeThreadCB		 pResumeThreadCB,
									_t_frkCloseHandleCB			 pCloseHandleCB);

/******************************************************************************/
#ifdef __cplusplus
}
#endif

#endif



