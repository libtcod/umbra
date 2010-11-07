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
CND_CONF=Windows-Debug-Invaders
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/umbra/umbra_engine.o \
	${OBJECTDIR}/src/umbra/umbra_font.o \
	${OBJECTDIR}/src/invaders/notification.o \
	${OBJECTDIR}/src/umbra/umbra_widget_button.o \
	${OBJECTDIR}/src/invaders/utilities.o \
	${OBJECTDIR}/src/umbra/umbra_imod_credits.o \
	${OBJECTDIR}/src/invaders/entities.o \
	${OBJECTDIR}/src/umbra/umbra_log.o \
	${OBJECTDIR}/src/demo/circle.o \
	${OBJECTDIR}/src/umbra/umbra_module.o \
	${OBJECTDIR}/src/umbra/umbra_widget_checkbox.o \
	${OBJECTDIR}/src/umbra/umbra_config.o \
	${OBJECTDIR}/src/umbra/umbra_imod_bsod.o \
	${OBJECTDIR}/src/invaders/main.o \
	${OBJECTDIR}/src/umbra/umbra_widget.o \
	${OBJECTDIR}/src/umbra/umbra_callback.o \
	${OBJECTDIR}/src/invaders/gameview.o \
	${OBJECTDIR}/src/umbra/umbra_imod_speed.o


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
LDLIBSOPTIONS=../libtcod/lib/libtcod-mingw-debug.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Windows-Debug-Invaders.mk ./umbra.exe

./umbra.exe: ../libtcod/lib/libtcod-mingw-debug.a

./umbra.exe: ${OBJECTFILES}
	${MKDIR} -p .
	${LINK.cc} -o ./umbra ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/umbra/umbra_engine.o: src/umbra/umbra_engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_engine.o src/umbra/umbra_engine.cpp

${OBJECTDIR}/src/umbra/umbra_font.o: src/umbra/umbra_font.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_font.o src/umbra/umbra_font.cpp

${OBJECTDIR}/src/invaders/notification.o: src/invaders/notification.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/notification.o src/invaders/notification.cpp

${OBJECTDIR}/src/umbra/umbra_widget_button.o: src/umbra/umbra_widget_button.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_widget_button.o src/umbra/umbra_widget_button.cpp

${OBJECTDIR}/src/invaders/utilities.o: src/invaders/utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/utilities.o src/invaders/utilities.cpp

${OBJECTDIR}/src/umbra/umbra_imod_credits.o: src/umbra/umbra_imod_credits.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_imod_credits.o src/umbra/umbra_imod_credits.cpp

${OBJECTDIR}/src/invaders/entities.o: src/invaders/entities.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/entities.o src/invaders/entities.cpp

${OBJECTDIR}/src/umbra/umbra_log.o: src/umbra/umbra_log.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_log.o src/umbra/umbra_log.cpp

${OBJECTDIR}/src/demo/circle.o: src/demo/circle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/demo
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/demo/circle.o src/demo/circle.cpp

${OBJECTDIR}/src/umbra/umbra_module.o: src/umbra/umbra_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_module.o src/umbra/umbra_module.cpp

${OBJECTDIR}/src/umbra/umbra_widget_checkbox.o: src/umbra/umbra_widget_checkbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_widget_checkbox.o src/umbra/umbra_widget_checkbox.cpp

${OBJECTDIR}/src/umbra/umbra_config.o: src/umbra/umbra_config.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_config.o src/umbra/umbra_config.cpp

${OBJECTDIR}/src/umbra/umbra_imod_bsod.o: src/umbra/umbra_imod_bsod.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_imod_bsod.o src/umbra/umbra_imod_bsod.cpp

${OBJECTDIR}/src/invaders/main.o: src/invaders/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/main.o src/invaders/main.cpp

${OBJECTDIR}/src/umbra/umbra_widget.o: src/umbra/umbra_widget.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_widget.o src/umbra/umbra_widget.cpp

${OBJECTDIR}/src/umbra/umbra_callback.o: src/umbra/umbra_callback.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_callback.o src/umbra/umbra_callback.cpp

${OBJECTDIR}/src/invaders/gameview.o: src/invaders/gameview.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/gameview.o src/invaders/gameview.cpp

${OBJECTDIR}/src/umbra/umbra_imod_speed.o: src/umbra/umbra_imod_speed.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/invaders -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_imod_speed.o src/umbra/umbra_imod_speed.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Windows-Debug-Invaders
	${RM} ./umbra.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
