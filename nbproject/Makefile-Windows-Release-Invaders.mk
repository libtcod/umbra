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
CND_CONF=Windows-Release-Invaders
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/invaders/notification.o \
	${OBJECTDIR}/src/umbra/imod_bsod.o \
	${OBJECTDIR}/src/invaders/utilities.o \
	${OBJECTDIR}/src/umbra/module.o \
	${OBJECTDIR}/src/invaders/entities.o \
	${OBJECTDIR}/src/umbra/font.o \
	${OBJECTDIR}/src/umbra/imod_speed.o \
	${OBJECTDIR}/src/umbra/engine.o \
	${OBJECTDIR}/src/umbra/config.o \
	${OBJECTDIR}/src/umbra/callback.o \
	${OBJECTDIR}/src/umbra/widget.o \
	${OBJECTDIR}/src/umbra/widget_button.o \
	${OBJECTDIR}/src/invaders/main.o \
	${OBJECTDIR}/src/umbra/widget_checkbox.o \
	${OBJECTDIR}/src/invaders/gameview.o \
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
	"${MAKE}"  -f nbproject/Makefile-Windows-Release-Invaders.mk ./umbra.exe

./umbra.exe: ../libtcod/lib/libtcod-mingw.a

./umbra.exe: ${OBJECTFILES}
	${MKDIR} -p .
	${LINK.cc} -o ./umbra ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/invaders/notification.o: src/invaders/notification.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/notification.o src/invaders/notification.cpp

${OBJECTDIR}/src/umbra/imod_bsod.o: src/umbra/imod_bsod.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/imod_bsod.o src/umbra/imod_bsod.cpp

${OBJECTDIR}/src/invaders/utilities.o: src/invaders/utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/utilities.o src/invaders/utilities.cpp

${OBJECTDIR}/src/umbra/module.o: src/umbra/module.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/module.o src/umbra/module.cpp

${OBJECTDIR}/src/invaders/entities.o: src/invaders/entities.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/entities.o src/invaders/entities.cpp

${OBJECTDIR}/src/umbra/font.o: src/umbra/font.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/font.o src/umbra/font.cpp

${OBJECTDIR}/src/umbra/imod_speed.o: src/umbra/imod_speed.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/imod_speed.o src/umbra/imod_speed.cpp

${OBJECTDIR}/src/umbra/engine.o: src/umbra/engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/engine.o src/umbra/engine.cpp

${OBJECTDIR}/src/umbra/config.o: src/umbra/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/config.o src/umbra/config.cpp

${OBJECTDIR}/src/umbra/callback.o: src/umbra/callback.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/callback.o src/umbra/callback.cpp

${OBJECTDIR}/src/umbra/widget.o: src/umbra/widget.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/widget.o src/umbra/widget.cpp

${OBJECTDIR}/src/umbra/widget_button.o: src/umbra/widget_button.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/widget_button.o src/umbra/widget_button.cpp

${OBJECTDIR}/src/invaders/main.o: src/invaders/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/main.o src/invaders/main.cpp

${OBJECTDIR}/src/umbra/widget_checkbox.o: src/umbra/widget_checkbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/widget_checkbox.o src/umbra/widget_checkbox.cpp

${OBJECTDIR}/src/invaders/gameview.o: src/invaders/gameview.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/gameview.o src/invaders/gameview.cpp

${OBJECTDIR}/src/umbra/error.o: src/umbra/error.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -O2 -I../libtcod/include -Isrc/umbra -Isrc/demo -Isrc/fov -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/error.o src/umbra/error.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Windows-Release-Invaders
	${RM} ./umbra.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
