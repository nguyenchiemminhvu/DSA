lib_LIBRARIES = libDSA.a
libDSA_a_SOURCES = 
libDSA_a_CXXFLAGS = -I$(top_srcdir)/Algorithms \
                    -I$(top_srcdir)/DataStructures \
                    -Wall
libDSA_a_LDFLAGS = 

libDSA_a_includedir = $(includedir)/DSA
libDSA_a_include_HEADERS = \
    $(top_srcdir)/Algorithms/*/*.h \
    $(top_srcdir)/DataStructures/*/*.h

lib_LTLIBRARIES = libDSA.la
libDSA_la_SOURCES = $(libDSA_a_SOURCES)
libDSA_la_CPPFLAGS = $(libDSA_a_CPPFLAGS)
libDSA_la_LDFLAGS = $(libDSA_a_LDFLAGS)

ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects
