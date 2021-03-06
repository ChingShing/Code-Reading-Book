#	$NetBSD: Makefile,v 1.22.8.2 1997/11/27 08:17:02 mellon Exp $

# The ``rm -rf''s used below are safe because rm doesn't follow symbolic
# links.

SUBDIR+= arch/${MACHINE}

.if (${MACHINE_ARCH} != "alpha" && ${MACHINE_ARCH} != "mips" && \
     ${MACHINE_ARCH} != "powerpc")
SUBDIR+= lkm
.endif

LFILES=	errno.h fcntl.h md5.h poll.h syslog.h termios.h
MFILES=	float.h frame.h stdarg.h varargs.h
LDIRS=	dev isofs net netatalk netinet netccitt netiso netns netnatm nfs miscfs \
	sys ufs vm 

# Change SYS_INCLUDE in bsd.own.mk or /etc/mk.conf to "symlinks" if you
# don't want copies
.include <bsd.own.mk>
SYS_INCLUDE?=	copies

# If DESTDIR is set, we're probably building a release, so force "copies".
.if defined(DESTDIR) && (${DESTDIR} != "/" && !empty(DESTDIR))
SYS_INCLUDE=	copies
.endif

.PHONY:	includes
includes: ${SYS_INCLUDE}
	@echo installing ${LFILES}
	@-for i in ${LFILES}; do \
		rm -f ${DESTDIR}/usr/include/$$i; \
		ln -s sys/$$i ${DESTDIR}/usr/include/$$i; \
	done
	@echo installing ${MFILES}
	@-for i in ${MFILES}; do \
		rm -f ${DESTDIR}/usr/include/$$i; \
		ln -s machine/$$i ${DESTDIR}/usr/include/$$i; \
	done

.PHONY:	copies
copies:
	@echo copies: ${LDIRS}
	@-for i in ${LDIRS}; do \
		rm -rf ${DESTDIR}/usr/include/$$i; \
		${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m 755 \
			${DESTDIR}/usr/include/$$i ; \
	done
	pax -rw -pa -L \
	    `find ${LDIRS} -follow -type f -name '*.h' '!' -path \
	    'netiso/xebec/*' -print` ${DESTDIR}/usr/include
	(cd ${DESTDIR}/usr/include; find ${LDIRS} -type f | \
		xargs chmod a=r)
	(cd ${DESTDIR}/usr/include; find ${LDIRS} -type d | \
		xargs chmod u=rwx,go=rx)
	rm -rf ${DESTDIR}/usr/include/machine
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m 755 \
		${DESTDIR}/usr/include/machine
	pax -rw -pa -s "|arch/${MACHINE}/include||" \
	    arch/${MACHINE}/include/*.h \
	    ${DESTDIR}/usr/include/machine   
	(cd ${DESTDIR}/usr/include; find machine -type f | \
		xargs chmod a=r)
	(cd ${DESTDIR}/usr/include; find machine -type d | \
		xargs chmod u=rwx,go=rx)
	rm -rf ${DESTDIR}/usr/include/${MACHINE_ARCH}
	if test ${MACHINE} != ${MACHINE_ARCH} -a \
	    -d arch/${MACHINE_ARCH}/include; then \
		${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m 755 \
		${DESTDIR}/usr/include/${MACHINE_ARCH}; \
		pax -rw -pa -s "|arch/${MACHINE_ARCH}/include||" \
		    arch/${MACHINE_ARCH}/include/*.h \
		    ${DESTDIR}/usr/include/${MACHINE_ARCH}; \
		(cd ${DESTDIR}/usr/include; find ${MACHINE_ARCH} -type f | \
			xargs chmod a=r); \
		(cd ${DESTDIR}/usr/include; find ${MACHINE_ARCH} -type d | \
			xargs chmod u=rwx,go=rx); \
	else \
		ln -s machine ${DESTDIR}/usr/include/${MACHINE_ARCH}; \
	fi

.PHONY:	symlinks
symlinks:
	@echo symlinks: ${LDIRS}
	@for i in ${LDIRS}; do \
		rm -rf ${DESTDIR}/usr/include/$$i; \
		ln -s /sys/$$i ${DESTDIR}/usr/include/$$i; \
	done
	rm -rf ${DESTDIR}/usr/include/machine
	ln -s /sys/arch/${MACHINE}/include ${DESTDIR}/usr/include/machine
	rm -rf ${DESTDIR}/usr/include/${MACHINE_ARCH}
	if test ${MACHINE} != ${MACHINE_ARCH} -a \
	    -d arch/${MACHINE_ARCH}/include ; then \
		ln -s /sys/arch/${MACHINE_ARCH}/include \
		    ${DESTDIR}/usr/include/${MACHINE_ARCH} ; \
	else \
		ln -s machine ${DESTDIR}/usr/include/${MACHINE_ARCH} ; \
	fi

.include <bsd.subdir.mk>
