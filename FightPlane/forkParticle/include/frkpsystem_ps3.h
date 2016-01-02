/******************************************************************************
	Confidential Property of Fork Particle, Inc.
  (c) Copyright 2002-2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#ifndef frkpsystem_ps3_h
#define frkpsystem_ps3_h

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
extern int			frkPEnableSpursPS3(CellSpurs* pSpurs, int nMaxContention, uint8_t aWorkLoadPriorities[8], 
						unsigned int nDMATag1, unsigned int nDMATag2, int bJobChain, int nMaxSPUGrabbedJobs);

/* Additional API for advanced initiaziation. */
extern void			frkSetSpursModulePS3(uintptr_t pBinaryStart, uint32_t nBinarySize);
extern int			frkSetSpursUserDataPS3(void* pUserData, int nSize);
extern uint32_t		frkSetSpursJobIOSizePS3(uint32_t nSize);
extern uint64_t*	frkGetSpursCommandListPS3(_t_frkPSystem* pSystem);
extern void			frkSetSpursCommandNextPS3(_t_frkPSystem* pPSystem, uint64_t nCommand);
extern CellSpursJobList* frkGetSpursJobListPS3(_t_frkPSystem* pPSystem);
extern CellSpursJob128* frkGetSpursJobEventPS3(_t_frkPSystem* pPSystem);

/******************************************************************************/
#ifdef __cplusplus
}
#endif

#endif



