
	.global		gp_enableCache
	.global		gp_setCpu
	.global		gp_setMMU
	.global		gp_clrScr
	.global		gp_enableIRQ
	.global		gp_disableIRQ
	.global		gp_installSWIIRQ
	.global		gp_removeSWIIRQ
         
gp_enableCache:
				stmfd		r13!,{r5,r6}
				mrc			p15, 0, r5, c1, c0, 0
				bic			r5,r5,#2
				ldr			r6,=0x1004
				orr			r5,r5,r6
				mcr			p15, 0, r5, c1, c0, 0
				ldmfd		r13!,{r5,r6}
				bx			lr

gp_setCpu:
        stmdb   r13!, {r0-r12,lr}
        stmdb   sp!, {r0, r1, r2}
        mov     r0, sp
        swi     #0x0d
        add     sp, sp, #12
        ldmia   r13!, {r0-r12,lr}
        bx      lr
        nop

gp_setMMU:
        stmdb   r13!, {r0-r12,lr}
        swi     #0x02
        mcr 15, 0, r0, cr7, cr7,0
        ldmia   r13!, {r0-r12,lr}
        bx      lr
        nop

gp_clrScr:
        orr			r1,r1,r1,lsl #16
        mov			r2,#38400
	clear:str			r1,[r0],#4
        subs		r2,r2,#1
        bne			clear
        bx			lr

gp_enableIRQ:
				STMDB   r13!,{r0,lr}
				MRS     r0,CPSR
				BIC     r0,r0,#0x80
				MSR     CPSR,r0
				LDMIA   r13!,{r0,pc}
				@MOV    pc,lr

gp_disableIRQ:
				STMDB   r13!,{r0,lr}
				MRS     r0,CPSR
				ORR     r0,r0,#0xc0
				MSR     CPSR,r0
				LDMIA   r13!,{r0,pc}
				@MOV    pc,lr

gp_installSWIIRQ:
				STMDB   r13!,{r14}
				SWI     0x9
				LDMIA   r13!,{pc}

gp_removeSWIIRQ:
				STMDB   r13!,{r14}
				SWI     0xa
				LDMIA   r13!,{pc}
