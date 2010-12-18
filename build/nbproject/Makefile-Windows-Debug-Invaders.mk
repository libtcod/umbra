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
PROC=proc

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
	${OBJECTDIR}/_ext/505160908/utilities.o \
	${OBJECTDIR}/_ext/505160908/notification.o \
	${OBJECTDIR}/_ext/1520178433/umbra_font.o \
	${OBJECTDIR}/_ext/1520178433/umbra_log.o \
	${OBJECTDIR}/_ext/505160908/main.o \
	${OBJECTDIR}/_ext/1520178433/umbra_widget.o \
	${OBJECTDIR}/_ext/1520178433/umbra_config.o \
	${OBJECTDIR}/_ext/1520178433/umbra_widget_button.o \
	${OBJECTDIR}/_ext/1520178433/umbra_widget_checkbox.o \
	${OBJECTDIR}/_ext/1520178433/umbra_module.o \
	${OBJECTDIR}/_ext/1520178433/umbra_imod_speed.o \
	${OBJECTDIR}/_ext/1520178433/umbra_imod_credits.o \
	${OBJECTDIR}/_ext/1520178433/umbra_imod_bsod.o \
	${OBJECTDIR}/_ext/1520178433/umbra_engine.o \
	${OBJECTDIR}/_ext/1520178433/umbra_callback.o \
	${OBJECTDIR}/_ext/1520178433/umbra_stylesheet.o \
	${OBJECTDIR}/_ext/505160908/entities.o \
	${OBJECTDIR}/_ext/505160908/gameview.o


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
LDLIBSOPTIONS=../../libtcod/lib/libtcod-mingw-debug.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Windows-Debug-Invaders.mk ../umbra.exe

../umbra.exe: ../../libtcod/lib/libtcod-mingw-debug.a

../umbra.exe: ${OBJECTFILES}
	${MKDIR} -p ..
	${LINK.cc} -o ../umbra ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/505160908/utilities.o: ../src/invaders/utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/505160908
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/505160908/utilities.o ../src/invaders/utilities.cpp

${OBJECTDIR}/_ext/505160908/notification.o: ../src/invaders/notification.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/505160908
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/505160908/notification.o ../src/invaders/notification.cpp

${OBJECTDIR}/_ext/1520178433/umbra_font.o: ../src/umbra/umbra_font.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_font.o ../src/umbra/umbra_font.cpp

${OBJECTDIR}/_ext/1520178433/umbra_log.o: ../src/umbra/umbra_log.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_log.o ../src/umbra/umbra_log.cpp

${OBJECTDIR}/_ext/505160908/main.o: ../src/invaders/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/505160908
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/505160908/main.o ../src/invaders/main.cpp

${OBJECTDIR}/_ext/1520178433/umbra_widget.o: ../src/umbra/umbra_widget.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_widget.o ../src/umbra/umbra_widget.cpp

${OBJECTDIR}/_ext/1520178433/umbra_config.o: ../src/umbra/umbra_config.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_config.o ../src/umbra/umbra_config.cpp

${OBJECTDIR}/_ext/1520178433/umbra_widget_button.o: ../src/umbra/umbra_widget_button.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_widget_button.o ../src/umbra/umbra_widget_button.cpp

${OBJECTDIR}/_ext/1520178433/umbra_widget_checkbox.o: ../src/umbra/umbra_widget_checkbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_widget_checkbox.o ../src/umbra/umbra_widget_checkbox.cpp

${OBJECTDIR}/_ext/1520178433/umbra_module.o: ../src/umbra/umbra_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_module.o ../src/umbra/umbra_module.cpp

${OBJECTDIR}/_ext/1520178433/umbra_imod_speed.o: ../src/umbra/umbra_imod_speed.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_imod_speed.o ../src/umbra/umbra_imod_speed.cpp

${OBJECTDIR}/_ext/1520178433/umbra_imod_credits.o: ../src/umbra/umbra_imod_credits.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_imod_credits.o ../src/umbra/umbra_imod_credits.cpp

${OBJECTDIR}/_ext/1520178433/umbra_imod_bsod.o: ../src/umbra/umbra_imod_bsod.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_imod_bsod.o ../src/umbra/umbra_imod_bsod.cpp

${OBJECTDIR}/_ext/1520178433/umbra_engine.o: ../src/umbra/umbra_engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_engine.o ../src/umbra/umbra_engine.cpp

${OBJECTDIR}/_ext/1520178433/umbra_callback.o: ../src/umbra/umbra_callback.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_callback.o ../src/umbra/umbra_callback.cpp

${OBJECTDIR}/_ext/1520178433/umbra_stylesheet.o: ../src/umbra/umbra_stylesheet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1520178433
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1520178433/umbra_stylesheet.o ../src/umbra/umbra_stylesheet.cpp

${OBJECTDIR}/_ext/505160908/entities.o: ../src/invaders/entities.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/505160908
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/505160908/entities.o ../src/invaders/entities.cpp

${OBJECTDIR}/_ext/505160908/gameview.o: ../src/invaders/gameview.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/505160908
	${RM} $@.d
	$(COMPILE.cc) -g -Werror -I../../libtcod/include -I../src/umbra -I../src/demo -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/505160908/gameview.o ../src/invaders/gameview.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Windows-Debug-Invaders
	${RM} ../umbra.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
