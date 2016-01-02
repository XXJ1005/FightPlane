/******************************************************************************
	Confidential Property of Fork Particle, Inc.
  (c) Copyright 2002-2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#ifndef _frkpanm_h
#define _frkpanm_h

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
// Animation track state flags (8 bits)
#define frkANM_LOOP		0x01
#define frkANM_REVERSE	0x02
#define frkANM_END		0x04
#define frkANM_INTERP	0x08

typedef int (*_t_frkAnmNoteCB) (_t_frkAnmInst* pNoteCBData, _t_frkPNote* pNoteData);
/*****************************************************************************/

/* Animation setup API section */
extern int		frkPAnmGetInstMemSize ();
extern void		frkPAnmInit (_t_frkAnmInst* pAnmInst, _t_frkPEmitter* pEmitter);
extern void		frkPAnmSet (_t_frkAnmInst* pAnmInst, _t_frkAnmTrk* pTrk);
extern void		frkPAnmProcess (_t_frkAnmInst* pAnmInst, float fTCurDelta);

/* Animation handler API section */
extern _t_frkAnmTrk* frkPAnmGetTrk(_t_frkAnmInst* pAnmInst);
extern void		frkPAnmSetSpd (_t_frkAnmInst* pAnmInst, float fSpd);
extern void		frkPAnmSetLoop (_t_frkAnmInst* pAnmInst, int nSwitch);
extern int		frkPAnmIsEnded (_t_frkAnmInst* pAnmInst);
extern void		frkPAnmRestart (_t_frkAnmInst* pAnmInst);
extern int		frkPAnmTrkIsLoop (_t_frkAnmTrk* pTrk);
extern char*	frkPAnmTrkGetName(_t_frkAnmTrk* pTrk);
extern void		frkAnmSetNoteCB (_t_frkAnmInst* pAnmInst, _t_frkAnmNoteCB pCB, void* pData);

/* Animation track API section */
extern void		frkTRKPrepare(void* pTrk);
extern void		frkPAnmIncTrkKeyTracer ();
extern void		frkPAnmResetTrkKeyTracer ();
extern _t_frkPEmitterInfo* frkPAnmGetTrkKeyTracer (_t_frkAnmTrk* pTrk);

/* Event Notes API Section */
extern void		frkPAnmNoteProcess (_t_frkAnmInst* pAnmInst, float fTCurDelta);
extern int		frkPAnmNoteGetFrame(_t_frkPNote* pNote);
extern int		frkPAnmNoteGetID(_t_frkPNote* pNote);
extern char*	frkPAnmNoteGetData(_t_frkPNote* pNote);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif

