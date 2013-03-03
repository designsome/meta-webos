# (c) Copyright 2012-2013 Hewlett-Packard Development Company, L.P.
# (c) Copyright 2013 LG Electronics

require conf/distro/include/webos-filesystem-paths.inc

require conf/distro/include/webos-component-head.inc
require conf/distro/include/webos-preferred-providers.inc
require conf/distro/include/webos-preferred-versions.inc
require conf/distro/include/webos-features.inc
require conf/distro/include/webos-toolchain.inc

SDK_NAME = "${DISTRO}-${TCLIBC}-${SDK_ARCH}-${TARGET_ARCH}"
SDKPATH = "/opt/${DISTRO}/${SDK_VERSION}"

EXTRAOPKGCONFIG = ""

# Override these in webOS based distros to modify DISTRO_EXTRA_R*
WEBOS_DEFAULT_EXTRA_RDEPENDS = "packagegroup-core-boot"
WEBOS_DEFAULT_EXTRA_RRECOMMENDS = ""

DISTRO_EXTRA_RDEPENDS += " ${WEBOS_DEFAULT_EXTRA_RDEPENDS}"
DISTRO_EXTRA_RRECOMMENDS += " ${WEBOS_DEFAULT_EXTRA_RRECOMMENDS}"

WEBOSQEMUDEPS = "${@base_contains("INCOMPATIBLE_LICENSE", "GPLv3", "", "qemu-config",d)}"
DISTRO_EXTRA_RDEPENDS_append_qemuarm = " ${WEBOSQEMUDEPS}"
DISTRO_EXTRA_RDEPENDS_append_qemux86 = " ${WEBOSQEMUDEPS}"

CACHE = "${TMPDIR}/cache/${TCMODE}-${TCLIBC}${@['', '/' + str(d.getVar('MACHINE', True))][bool(d.getVar('MACHINE', True))]}${@['', '/' + str(d.getVar('SDKMACHINE', True))][bool(d.getVar('SDKMACHINE', True))]}"

USER_CLASSES ?= ""

# opkglibdir is used in rootfs-ipk, change that to
# OPKGLIBDIR_webos := "${libdir}"
# and remove opkg*bbappends when oe-core is upgraded to revision which includes this:
# http://lists.linuxtogo.org/pipermail/openembedded-core/2013-February/035407.html 
opkglibdir_webos = "${libdir}/opkg"
PACKAGE_CLASSES ?= "package_ipk"
INHERIT_INSANE ?= "insane"
INHERIT_DISTRO ?= "debian devshell sstate license webos_base"
INHERIT += "${PACKAGE_CLASSES} ${USER_CLASSES} ${INHERIT_INSANE} ${INHERIT_DISTRO}"

QEMU_TARGETS ?= "arm i386"

OPENWEBOS_GIT_REPO ?= "git://github.com/openwebos"
ISIS_PROJECT_GIT_REPO ?= "git://github.com/isis-project"
ISIS_PROJECT_DOWNLOAD ?= "https://github.com/downloads/isis-project"
ENYOJS_GIT_REPO ?= "git://github.com/enyojs"

# Default WEBOS_TARGET_* values (see webos_cmake.bbclass)
WEBOS_TARGET_CORE_OS ?= "rockhopper"
WEBOS_TARGET_MACHINE_IMPL ?= "emulator"


# The Open webOS distro is packaged into these image types:
IMAGE_FSTYPES ?= "tar.bz2 ext3"

# Only create a vmdk image when we're building for the (32-bit Intel
# architecture) emulator, i.e. when MACHINE is qemux86.
# NB. If IMAGE_FSTYPES_append_qemux86 = " vmdk" is used, the inherit of
# image-vmdk.bbclass in image.bbclass doesn't happen.
IMAGE_FSTYPES += "${@ 'vmdk' if '${MACHINE}' == 'qemux86' else '' }"


# Redirect console output to keep it from spewing all over the VirtualBox window
# (This is added to qemux86 kernel cmdline by openembedded-core/meta/classes/syslinux.bbclass)
APPEND_append_qemux86 = " console=ttyS0"

MIRRORS =+ "\
ftp://.*/.*      http://downloads.yoctoproject.org/mirror/sources/ \n \
http://.*/.*     http://downloads.yoctoproject.org/mirror/sources/ \n \
https://.*/.*    http://downloads.yoctoproject.org/mirror/sources/ \n"

# The CONNECTIVITY_CHECK_URI's are used to test whether we can succesfully
# fetch from the network (and warn you if not). To disable the test set
# the variable to be empty.
CONNECTIVITY_CHECK_URIS ?= "git://git.yoctoproject.org/yocto-firewall-test;protocol=git;rev=HEAD \
                          https://eula-downloads.yoctoproject.org/index.php \
                          http://bugzilla.yoctoproject.org/report.cgi"

# TODO can check on all these host machines.
SANITY_TESTED_DISTROS ?= " \
            Ubuntu 12.04.1 LTS \n \
            Ubuntu 12.04.2 LTS \n \
            Ubuntu 12.10 \n \
            "