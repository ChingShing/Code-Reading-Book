#	$NetBSD: Makefile,v 1.1.2.1 1997/12/25 20:32:41 perry Exp $

TOP=		${.CURDIR}/..

# This include just sets REV=XX
.include "${TOP}/Makefile.inc"

IMAGE=	miniroot
#CBIN=	mini_usr

TREE=	${TOP}/common/${IMAGE}.tree

LISTS=	${TOP}/common/${IMAGE}.list \
	${TOP}/common/mini_sbin.list \
	${TOP}/common/mini_bin.list \
	${TOP}/common/mini_usr.list

KERNEL=${SRCSYSDIR}/arch/sun3x/compile/GENERIC/netbsd

MOUNT_POINT=	/mnt
BDEV=		/dev/sd1b
CDEV=		/dev/rsd1b

# These are all the parameters for the miniroot: (8MB)
DISKTYPE=	miniroot
NBLKS=		16384
# old format, minfree, opt, b/i  trks, sects, cpg
NEWFSARGS= -O -m 0 -o space -i 8192 -t 8 -u 32 -c 16

CLEANFILES= ${IMAGE}.gz install.sub

${IMAGE}.gz: ${TREE} ${LISTS} install.sub
	-newfs ${NEWFSARGS} -s ${NBLKS} ${CDEV} ${DISKTYPE}
	mount ${BDEV} ${MOUNT_POINT}
	mtree -def ${TREE} -p ${MOUNT_POINT}/ -u
	cp ${KERNEL} ${MOUNT_POINT}/netbsd
	TOPDIR=${TOP} CURDIR=${.CURDIR} \
	  OBJDIR=${.OBJDIR} TARGDIR=${MOUNT_POINT} \
	  sh ${TOP}/common/RunList.sh ${LISTS}
	sync ; sleep 1 ; sync
	cd ${MOUNT_POINT} ;\
	  usr/mdec/installboot -v ufsboot usr/mdec/bootxx ${CDEV}
	sync
	@echo ""
	@df -i ${MOUNT_POINT}
	@echo ""
	-umount ${MOUNT_POINT}
	dd if=${CDEV} bs=16b count=`expr ${NBLKS} / 16` |\
	  gzip > ${IMAGE}.tmp
	-mv -f ${IMAGE}.tmp ${IMAGE}.gz

# Do not delete this if I change my mind and kill make...
.PRECIOUS: ${IMAGE}.gz

install.sub : ${TOP}/../miniroot/install.sub
	sed -e "/^VERSION=/s/=.*/=${REV}/" < $? > $@

clean cleandir:
	-rm -f a.out core *.core *.o
	-rm -f ${CLEANFILES}

# Standard rules needed by the above...
.include <bsd.obj.mk>
