#ifndef _frkphysX_h_
#define _frkphysX_h_

struct _t_frkPhysXInst;
typedef _t_frkPhysXInst	t_frkPhysXInst;


// Create the PhysX integration instance
extern int frkPhysXCreateInst(_t_frkSDK *pSDK, NxPhysicsSDK *pPhysXSDK, NxScene	*pScene, t_frkPhysXInst **pOutInst);
// Destroy the PhysX integration instance
extern int frkPhysXDestroyInst(_t_frkPhysXInst *pOutInst);
// Create instance of emitter in the PhysX sdk
extern int frkPhysXCreateEmitterInst(_t_frkPEmitter *pEmitter, t_frkPhysXInst *pInst);
// Tells if PhysX is enabled on emitter
extern int frkPhysXIsEnabled(_t_frkPEmitter *pEmitter);

#endif
