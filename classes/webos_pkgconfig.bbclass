# (c) Copyright 2012  Hewlett-Packard Development Company, L.P. 
#
# webos_pkgconfig
#
# This class is to be inherited by the recipe for every component that uses
# pkgconfig when building or installs a pkgconfig (.pc) file. This usually
# happens implicitly by inheriting from webos_library, webos_program,
# or webos_daemon.
#

inherit pkgconfig
