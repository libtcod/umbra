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
CND_CONF=Windows-Release-FOV
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/fov/fov_setup.o \
	${OBJECTDIR}/src/invaders/notification.o \
	${OBJECTDIR}/src/fov/main.o \
	${OBJECTDIR}/src/umbra/imod_bsod.o \
	${OBJECTDIR}/src/umbra/module.o \
	${OBJECTDIR}/src/umbra/font.o \
	${OBJECTDIR}/src/umbra/imod_speed.o \
	${OBJECTDIR}/src/umbra/engine.o \
	${OBJECTDIR}/src/umbra/config.o \
	${OBJECTDIR}/src/umbra/callback.o \
	${OBJECTDIR}/src/umbra/widget.o \
	${OBJECTDIR}/src/umbra/widget_button.o \
	${OBJECTDIR}/src/fov/fov_results.o \
	${OBJECTDIR}/src/fov/bsp_helper.o \
	${OBJECTDIR}/src/umbra/widget_checkbox.o \
	${OBJECTDIR}/src/fov/fov_test.o \
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
	"${MAKE}"  -f nbproject/Makefile-Windows-Release-FOV.mk ./umbra.exe

./umbra.exe: ../libtcod/lib/libtcod-mingw.a

./umbra.exe: ${OBJECTFILES}
	${MKDIR} -p .
	${LINK.cc} -o ./umbra ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/fov/fov_setup.o: src/fov/fov_setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/fov
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/fov/fov_setup.o src/fov/fov_setup.cpp

${OBJECTDIR}/src/invaders/notification.o: src/invaders/notification.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/notification.o src/invaders/notification.cpp

${OBJECTDIR}/src/fov/main.o: src/fov/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/fov
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/fov/main.o src/fov/main.cpp

${OBJECTDIR}/src/umbra/imod_bsod.o: src/umbra/imod_bsod.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/imod_bsod.o src/umbra/imod_bsod.cpp

${OBJECTDIR}/src/umbra/module.o: src/umbra/module.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/module.o src/umbra/module.cpp

${OBJECTDIR}/src/umbra/font.o: src/umbra/font.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/font.o src/umbra/font.cpp

${OBJECTDIR}/src/umbra/imod_speed.o: src/umbra/imod_speed.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/imod_speed.o src/umbra/imod_speed.cpp

${OBJECTDIR}/src/umbra/engine.o: src/umbra/engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/engine.o src/umbra/engine.cpp

${OBJECTDIR}/src/umbra/config.o: src/umbra/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/config.o src/umbra/config.cpp

${OBJECTDIR}/src/umbra/callback.o: src/umbra/callback.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/callback.o src/umbra/callback.cpp

${OBJECTDIR}/src/umbra/widget.o: src/umbra/widget.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/widget.o src/umbra/widget.cpp

${OBJECTDIR}/src/umbra/widget_button.o: src/umbra/widget_button.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/widget_button.o src/umbra/widget_button.cpp

${OBJECTDIR}/src/fov/fov_results.o: src/fov/fov_results.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/fov
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/fov/fov_results.o src/fov/fov_results.cpp

${OBJECTDIR}/src/fov/bsp_helper.o: src/fov/bsp_helper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/fov
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/fov/bsp_helper.o src/fov/bsp_helper.cpp

${OBJECTDIR}/src/umbra/widget_checkbox.o: src/umbra/widget_checkbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/widget_checkbox.o src/umbra/widget_checkbox.cpp

${OBJECTDIR}/src/fov/fov_test.o: src/fov/fov_test.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/fov
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/fov/fov_test.o src/fov/fov_test.cpp

${OBJECTDIR}/src/umbra/error.o: src/umbra/error.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/error.o src/umbra/error.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Windows-Release-FOV
	${RM} ./umbra.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
