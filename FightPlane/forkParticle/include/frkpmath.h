/******************************************************************************
	Confidential Property of Fork Particle, Inc.
  (c) Copyright 2002-2011 Fork Particle, Inc. All rights reserved.
*/
/******************************************************************************/
#ifndef _frkpmath_h
#define _frkpmath_h

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
typedef struct _t_frkvector2 {
	float x, y;
} t_frkVector2;

typedef struct _t_frkvector3 {
	float x, y, z;
} t_frkVector3;

typedef struct _t_frkvector4 {
	float x, y, z, w;
} t_frkVector4;

typedef struct _t_frkrgba {
	float r, g, b, a;
} t_frkRGBA;

typedef struct _t_frkrect2d {
	float x1, y1, x2, y2;
} t_frkRect2d;

typedef struct t_frkrect3d {
	t_frkVector3 Min;
	t_frkVector3 Max;
} t_frkRect3d;

typedef struct _t_frkmatrix4 {
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
} t_frkMatrix4;

typedef struct t_frkptforce {
	t_frkVector4 Pos;
	t_frkVector4 Params;
} t_frkPtForce;
/*****************************************************************************/
#define frkPtForcePos(f)((f)->Pos)
#define frkPtForceMag(f)((f)->Pos.w)
#define frkPtForceRad(f)((f)->Params.x)
#define frkPtForceType(f) ((f)->Params.y)
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif


