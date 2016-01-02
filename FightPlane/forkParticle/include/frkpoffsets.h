#ifndef __FRKPOFFSETS_H__
#define __FRKPOFFSETS_H__

#ifdef SDK_X64
#define		OFFSET_T_FRKPARTICLE_FLIFE			36
#define		OFFSET_T_FRKPARTICLE_POS			40
#define		OFFSET_T_FRKPARTICLE_VEL			56
#define		OFFSET_T_FRKPARTICLE_COLOR			72
#define		OFFSET_T_FRKPARTICLE_FTIME			88
#define		OFFSET_T_FRKPARTICLE_FSCALE			92
#define		OFFSET_T_FRKPARTICLE_FROT			96
#define		OFFSET_T_FRKPARTICLE_NASSETIDX			100
#define		OFFSET_T_FRKPARTICLE_FJITTER		104
#define		OFFSET_T_FRKPARTICLE_PDATA			112

#define		OFFSET_T_FRKASSETINFO_PASSET			280
#define		OFFSET_T_FRKASSETINFO_SIZE				296

#define		OFFSET_T_FRKPEMITTERINFO_NFLAGS			104
#define		OFFSET_T_FRKPEMITTERINFO_SCALE			136
#define		OFFSET_T_FRKPEMITTERINFO_ROT			152
#define		OFFSET_T_FRKPEMITTERINFO_TINT			168
#define		OFFSET_T_FRKPEMITTERINFO_NEBLENDMODE			268
#define		OFFSET_T_FRKPEMITTERINFO_NASSETS			304
#define		OFFSET_T_FRKPEMITTERINFO_PASSET			312
#define		OFFSET_T_FRKPEMITTERINFO_AASSETS			320

#define		OFFSET_T_FRKPEMITTER_SNAME			0
#define		OFFSET_T_FRKPEMITTER_NFLAGS			256
#define		OFFSET_T_FRKPEMITTER_LCSWCS			280
#define		OFFSET_T_FRKPEMITTER_NASSETIDX		360
#define		OFFSET_T_FRKPEMITTER_PINFO			368
#define		OFFSET_T_FRKPEMITTER_PUSRDATA		896

#else

#define		OFFSET_T_FRKPARTICLE_FLIFE			28
#define		OFFSET_T_FRKPARTICLE_POS			32
#define		OFFSET_T_FRKPARTICLE_VEL			48
#define		OFFSET_T_FRKPARTICLE_COLOR			64
#define		OFFSET_T_FRKPARTICLE_FTIME			80
#define		OFFSET_T_FRKPARTICLE_FSCALE			84
#define		OFFSET_T_FRKPARTICLE_FROT			88
#define		OFFSET_T_FRKPARTICLE_NASSETIDX			92
#define		OFFSET_T_FRKPARTICLE_FJITTER		96
#define		OFFSET_T_FRKPARTICLE_PDATA			100

#ifdef SDK_UNI32
#define		OFFSET_T_FRKASSETINFO_PASSET			280
#define		OFFSET_T_FRKASSETINFO_SIZE				296
#else
#define		OFFSET_T_FRKASSETINFO_PASSET			280
#define		OFFSET_T_FRKASSETINFO_SIZE				288
#endif

#define		OFFSET_T_FRKPEMITTERINFO_NFLAGS			104
#define		OFFSET_T_FRKPEMITTERINFO_SCALE			136
#define		OFFSET_T_FRKPEMITTERINFO_ROT			152
#define		OFFSET_T_FRKPEMITTERINFO_TINT			168
#define		OFFSET_T_FRKPEMITTERINFO_NEBLENDMODE			268

#ifdef SDK_UNI32
#define		OFFSET_T_FRKPEMITTERINFO_NASSETS			304
#define		OFFSET_T_FRKPEMITTERINFO_PASSET			312
#define		OFFSET_T_FRKPEMITTERINFO_AASSETS			320
#else
#define		OFFSET_T_FRKPEMITTERINFO_NASSETS			292
#define		OFFSET_T_FRKPEMITTERINFO_PASSET			296
#define		OFFSET_T_FRKPEMITTERINFO_AASSETS			300
#endif

#define		OFFSET_T_FRKPEMITTER_SNAME			0
#define		OFFSET_T_FRKPEMITTER_NFLAGS			256
#define		OFFSET_T_FRKPEMITTER_LCSWCS			272
#define		OFFSET_T_FRKPEMITTER_NASSETIDX			352
#define		OFFSET_T_FRKPEMITTER_PINFO			356
#define		OFFSET_T_FRKPEMITTER_PUSRDATA		796

#endif

#endif

