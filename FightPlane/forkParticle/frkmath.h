#ifndef _FRKMATH_H
#define _FRKMATH_H

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#define frkMATH_PI 3.14159265f
#define frkDeg2Rad(d) ((frkMATH_PI / 180.0f) * d)
#define frkRad2Deg(r) ((180.0f / frkMATH_PI) * r)

#define MatrixIdentity(m){\
	register float *trgt=(float *)m;\
	*trgt++ = 1.f; *trgt++ = 0.f; *trgt++ = 0.f; *trgt++ = 0.f;	\
	*trgt++ = 0.f; *trgt++ = 1.f; *trgt++ = 0.f; *trgt++ = 0.f;	\
	*trgt++ = 0.f; *trgt++ = 0.f; *trgt++ = 1.f; *trgt++ = 0.f;	\
	*trgt++ = 0.f; *trgt++ = 0.f; *trgt++ = 0.f; *trgt   = 1.f;	\
}\

#define Vec3Set(v, _x, _y, _z)\
{\
(v)->x = (_x);\
(v)->y = (_y);\
(v)->z = (_z);\
}

#define Vec3Dot(a,b)		((a)->x*(b)->x + (a)->y*(b)->y + (a)->z*(b)->z)
#define Vec3Cross(ab, a, b){ \
(ab)->x = (a)->y*(b)->z - (a)->z*(b)->y;\
(ab)->y = (a)->z*(b)->x - (a)->x*(b)->z;\
(ab)->z = (a)->x*(b)->y - (a)->y*(b)->x;\
}
#define Vec3Length(v)		(float)sqrt(Vec3Dot(v,v))
#define Vec3Normalize(d,s)\
{\
	float oomg;\
	oomg = Vec3Length((s));\
	if (oomg != 0.0f) \
	{\
		oomg = 1.0f / oomg;\
		Vec3Set((d), (s)->x*oomg, (s)->y*oomg, (s)->z*oomg);\
	}\
}

#define MatrixRotationAngleAxis(m, pAxis, fRadians){ 	\
	t_frkVector3 vAxis = {(pAxis)->x, (pAxis)->y, (pAxis)->z};	\
	float x, y, z;											\
	float cosa = (float)cos(fRadians);						\
	float sina = (float)sin(fRadians);						\
	Vec3Normalize (&vAxis, &vAxis);						\
	x = vAxis.x;											\
	y = vAxis.y;											\
	z = vAxis.z;											\
	(m)->m00 = cosa + (1 - cosa) * x * x;						\
	(m)->m10 = (1 - cosa) * x * y + sina * z;					\
	(m)->m20 = (1 - cosa) * x * z - sina * y;					\
	(m)->m01 = (1 - cosa) * x * y - z * sina;					\
	(m)->m11 = cosa + (1 - cosa) * y * y;						\
	(m)->m21 = (1 - cosa) * y * z + x * sina;					\
	(m)->m02 = (1 - cosa) * x * z + sina * y;					\
	(m)->m12 = (1 - cosa) * y * z - sina * x;					\
	(m)->m22 = cosa + (1 - cosa) * z * z;						\
}	

#define MatrixVec3MulSub(vout, vin, m)\
{\
	t_frkVector3 tmp;\
	tmp.x	= (vin)->x * (m)->m00 + (vin)->y * (m)->m10 + (vin)->z * (m)->m20;\
	tmp.y   = (vin)->x * (m)->m01 + (vin)->y * (m)->m11 + (vin)->z * (m)->m21;\
	(vout)->z = (vin)->x * (m)->m02 + (vin)->y * (m)->m12 + (vin)->z * (m)->m22;\
	(vout)->x = tmp.x;\
	(vout)->y = tmp.y;\
}

#define Vec3Sub(d, a, b) {(d)->x = (a)->x - (b)->x;(d)->y = (a)->y - (b)->y;(d)->z = (a)->z - (b)->z;}
#define Vec3Add(d, a, b) {(d)->x = (a)->x + (b)->x;(d)->y = (a)->y + (b)->y;(d)->z = (a)->z + (b)->z;}
#define Vec3Scale(d, s, t){(d)->x = (s)->x * t;(d)->y = (s)->y * t;(d)->z = (s)->z * t;}

#define Vec3Dot(a,b)		((a)->x*(b)->x + (a)->y*(b)->y + (a)->z*(b)->z)
#define Vec3Cross(ab, a, b){ \
(ab)->x = (a)->y*(b)->z - (a)->z*(b)->y;\
(ab)->y = (a)->z*(b)->x - (a)->x*(b)->z;\
(ab)->z = (a)->x*(b)->y - (a)->y*(b)->x;\
}

#ifdef __cplusplus
}
#endif
#endif