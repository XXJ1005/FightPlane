#ifndef _frkhavok_h_
#define _frkhavok_h_

struct _t_frkHavokInst;
typedef _t_frkHavokInst	t_frkHavokInst;


// Create the Havok integration instance
extern int frkHavokCreateInst(_t_frkSDK *pSDK, hkpWorld *pHavokWorld, t_frkHavokInst **pOutInst);
// Destroy the Havok integration instance
extern int frkHavokDestroyInst(_t_frkHavokInst *pOutInst);
// Create instance of emitter in the Havok sdk
extern int frkHavokCreateEmitterInst(_t_frkPEmitter *pEmitter, t_frkHavokInst *pInst);
// Tells if Havok is enabled on emitter
extern int frkHavokIsEnabled(_t_frkPEmitter *pEmitter);

#endif
