#	$NetBSD: Makefile,v 1.13.2.1 1997/11/09 00:59:12 lukem Exp $

.include <bsd.own.mk>			# for ECOFF_TOOLCHAIN definition

CPPFLAGS+=	-DLIBC_SCCS -DPIC -DDYNAMIC -DELFSIZE=64
CPPFLAGS+=	-I${.CURDIR}/../../../libexec/ld.elf_so
COPT+=		-fPIC

.if defined(ECOFF_TOOLCHAIN)
CPPFLAGS+=	-DECOFF_COMPAT
.endif

OBJS=		crt0.o gcrt0.o crtbegin.o crtend.o

CLEANFILES+=	core a.out

all: ${OBJS}

crt0.o: crt0.c
	@echo "${COMPILE.c} -DCRT0 ${.ALLSRC} -o ${.TARGET}"
	@${COMPILE.c} -DCRT0 ${.ALLSRC} -o ${.TARGET}.o
	@${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

gcrt0.o: crt0.c
	@echo "${COMPILE.c} -DMCRT0 ${.ALLSRC} -o ${.TARGET}"
	@${COMPILE.c} -DMCRT0 ${.ALLSRC} -o ${.TARGET}.o
	@${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtbegin.o: crtbegin.c
	@echo "${COMPILE.c} ${.ALLSRC} -o ${.TARGET}"
	@${COMPILE.c} ${.ALLSRC} -o ${.TARGET}.o
	@${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtend.o: crtend.c
	@echo "${COMPILE.c} ${.ALLSRC} -o ${.TARGET}"
	@${COMPILE.c} ${.ALLSRC} -o ${.TARGET}.o
	@${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

install:
	${INSTALL} ${COPY} -o ${BINOWN} -g ${BINGRP} -m 444 ${OBJS} \
	    ${DESTDIR}/usr/lib
	rm -f ${DESTDIR}/usr/lib/crtbeginS.o ${DESTDIR}/usr/lib/crtendS.o
	ln ${DESTDIR}/usr/lib/crtbegin.o ${DESTDIR}/usr/lib/crtbeginS.o
	ln ${DESTDIR}/usr/lib/crtend.o ${DESTDIR}/usr/lib/crtendS.o

.include <bsd.prog.mk>
