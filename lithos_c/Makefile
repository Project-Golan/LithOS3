##-----------------------------------------------------------------------------
##
## Copyright © 2016 Project Golan
##
## See "LICENSE" for more information.
##
##-----------------------------------------------------------------------------
##
## Main Makefile.
##
##-----------------------------------------------------------------------------

##
## Definitions
##

## Compiler

CC=gdcc-cc
LD=gdcc-ld
MAKELIB=gdcc-makelib

## Directories

BIN=../acs
SRC=src
INC=inc
IR=bin

## Compiler flags

TARGET=--bc-target=ZDoom
LFLAGS=$(TARGET) --bc-zdacs-init-delay --bc-zdacs-chunk-STRE
CFLAGS=$(TARGET) -iinc
ALLOCMIN=--alloc-min Sta ""

## Sources

SOURCES= \
   $(SRC)/button.c \
   $(SRC)/context.c \
   $(SRC)/control.c \
   $(SRC)/draw.c \
   $(SRC)/font.c \
   $(SRC)/main.c \
   $(SRC)/stdlib.c \
   $(SRC)/window.c

HEADERS= \
   $(INC)/Lth.h \
   $(INC)/Lth_assert.h \
   $(INC)/Lth_button.h \
   $(INC)/Lth_callback.h \
   $(INC)/Lth_context.h \
   $(INC)/Lth_control.h \
   $(INC)/Lth_draw.h \
   $(INC)/Lth_font.h \
   $(INC)/Lth_hudmessage.h \
   $(INC)/Lth_linklist.h \
   $(INC)/Lth_stdlib.h \
   $(INC)/Lth_types.h \
   $(INC)/Lth_window.h

## Output

OUTPUT=$(SOURCES:$(SRC)/%.c=$(IR)/%.ir)

##
## Rules
##

## all

all: $(BIN)/lithos3l.bin $(BIN)/lithos3.bin

## bin/lithos3*.bin

$(BIN)/lithos3l.bin: $(IR)/libc.ir $(IR)/libGDCC.ir
	$(LD) $(LFLAGS) $(ALLOCMIN) 700000000 $^ -o $@

$(BIN)/lithos3.bin: $(OUTPUT)
	$(LD) $(LFLAGS) $(ALLOCMIN) 7000000000 $^ -o $@ -llithos3l

## ir/*.ir

$(IR)/%.ir: $(SRC)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

## irlib/lib*.ir

$(IR)/libc.ir:
	$(MAKELIB) $(TARGET) -c libc -o $@

$(IR)/libGDCC.ir:
	$(MAKELIB) $(TARGET) -c libGDCC -o $@

## EOF
