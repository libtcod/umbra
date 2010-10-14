#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=mingw32-gcc.exe
CCC=mingw32-g++.exe
CXX=mingw32-g++.exe
FC=
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Windows-Release-Demo
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/demo/credits.o \
	${OBJECTDIR}/src/umbra/imod_bsod.o \
	${OBJECTDIR}/src/umbra/module.o \
	${OBJECTDIR}/src/umbra/font.o \
	${OBJECTDIR}/src/umbra/imod_speed.o \
	${OBJECTDIR}/src/umbra/engine.o \
	${OBJECTDIR}/src/umbra/config.o \
	${OBJECTDIR}/src/umbra/callback.o \
	${OBJECTDIR}/src/demo/rabbit.o \
	${OBJECTDIR}/src/umbra/widget.o \
	${OBJECTDIR}/src/umbra/widget_button.o \
	${OBJECTDIR}/src/demo/main.o \
	${OBJECTDIR}/src/demo/demo.o \
	${OBJECTDIR}/src/umbra/widget_checkbox.o \
	${OBJECTDIR}/src/demo/panel.o \
	${OBJECTDIR}/src/demo/matrix.o \
	${OBJECTDIR}/src/umbra/error.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32
CXXFLAGS=-m32

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../libtcod/lib/libtcod-mingw.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Windows-Release-Demo.mk ./umbra.exe

./umbra.exe: ../libtcod/lib/libtcod-mingw.a

./umbra.exe: ${OBJECTFILES}
	${MKDIR} -p .
	${LINK.cc} -o ./umbra ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/demo/credits.o: src/demo/credits.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/demo
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/demo/credits.o src/demo/credits.cpp

${OBJECTDIR}/src/umbra/imod_bsod.o: src/umbra/imod_bsod.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/imod_bsod.o src/umbra/imod_bsod.cpp

${OBJECTDIR}/src/umbra/module.o: src/umbra/module.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/module.o src/umbra/module.cpp

${OBJECTDIR}/src/umbra/font.o: src/umbra/font.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/font.o src/umbra/font.cpp

${OBJECTDIR}/src/umbra/imod_speed.o: src/umbra/imod_speed.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/imod_speed.o src/umbra/imod_speed.cpp

${OBJECTDIR}/src/umbra/engine.o: src/umbra/engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/engine.o src/umbra/engine.cpp

${OBJECTDIR}/src/umbra/config.o: src/umbra/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/config.o src/umbra/config.cpp

${OBJECTDIR}/src/umbra/callback.o: src/umbra/callback.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/callback.o src/umbra/callback.cpp

${OBJECTDIR}/src/demo/rabbit.o: src/demo/rabbit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/demo
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/demo/rabbit.o src/demo/rabbit.cpp

${OBJECTDIR}/src/umbra/widget.o: src/umbra/widget.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/widget.o src/umbra/widget.cpp

${OBJECTDIR}/src/umbra/widget_button.o: src/umbra/widget_button.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/widget_button.o src/umbra/widget_button.cpp

${OBJECTDIR}/src/demo/main.o: src/demo/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/demo
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/demo/main.o src/demo/main.cpp

${OBJECTDIR}/src/demo/demo.o: src/demo/demo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/demo
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/demo/demo.o src/demo/demo.cpp

${OBJECTDIR}/src/umbra/widget_checkbox.o: src/umbra/widget_checkbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/widget_checkbox.o src/umbra/widget_checkbox.cpp

${OBJECTDIR}/src/demo/panel.o: src/demo/panel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/demo
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/demo/panel.o src/demo/panel.cpp

${OBJECTDIR}/src/demo/matrix.o: src/demo/matrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/demo
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/demo/matrix.o src/demo/matrix.cpp

${OBJECTDIR}/src/umbra/error.o: src/umbra/error.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/error.o src/umbra/error.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Windows-Release-Demo
	${RM} ./umbra.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
