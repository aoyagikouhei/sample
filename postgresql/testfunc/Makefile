SRCS = testfunc.c

MODULE_big =testfunc
OBJS = $(SRCS:.c=.o)
DOCS =
DATA_built = testfunc.sql

ifdef USE_PGXS
PGXS = $(shell pg_config --pgxs)
include $(PGXS)
else
subdir = contrib/testfunc
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif