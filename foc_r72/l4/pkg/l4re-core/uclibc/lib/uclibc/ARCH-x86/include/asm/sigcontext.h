
struct _fpreg {
	unsigned short significand[4];
	unsigned short exponent;
};

struct _fpxreg {
	unsigned short significand[4];
	unsigned short exponent;
	unsigned short padding[3];
};

struct _xmmreg {
	unsigned long element[4];
};

struct _fpstate {
	/* Regular FPU environment */
	unsigned long 	cw;
	unsigned long	sw;
	unsigned long	tag;
	unsigned long	ipoff;
	unsigned long	cssel;
	unsigned long	dataoff;
	unsigned long	datasel;
	struct _fpreg	_st[8];
	unsigned short	status;
	unsigned short	magic;		/* 0xffff = regular FPU data only */

	/* FXSR FPU environment */
	unsigned long	_fxsr_env[6];	/* FXSR FPU env is ignored */
	unsigned long	mxcsr;
	unsigned long	reserved;
	struct _fpxreg	_fxsr_st[8];	/* FXSR FPU reg data is ignored */
	struct _xmmreg	_xmm[8];
	unsigned long	padding[56];
};

#define X86_FXSR_MAGIC		0x0000
#define PC(ctx) (ctx.eip)

struct sigcontext {
	unsigned short gs, __gsh;
	unsigned short fs, __fsh;
	unsigned short es, __esh;
	unsigned short ds, __dsh;
	unsigned long edi;
	unsigned long esi;
	unsigned long ebp;
	unsigned long esp;
	unsigned long ebx;
	unsigned long edx;
	unsigned long ecx;
	unsigned long eax;
	unsigned long trapno;
	unsigned long err;
	unsigned long eip;
	unsigned short cs, __csh;
	unsigned long eflags;
	unsigned long esp_at_signal;
	unsigned short ss, __ssh;
	struct _fpstate * fpstate;
	unsigned long oldmask;
	unsigned long cr2;
};

