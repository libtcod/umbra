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
CND_CONF=Windows-Debug-FOV
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/umbra/umbra_engine.o \
	${OBJECTDIR}/src/fov/fov_setup.o \
	${OBJECTDIR}/src/umbra/umbra_font.o \
	${OBJECTDIR}/src/invaders/notification.o \
	${OBJECTDIR}/src/fov/main.o \
	${OBJECTDIR}/src/umbra/umbra_widget_button.o \
	${OBJECTDIR}/src/umbra/umbra_module.o \
	${OBJECTDIR}/src/umbra/umbra_config.o \
	${OBJECTDIR}/src/umbra/umbra_widget_checkbox.o \
	${OBJECTDIR}/src/umbra/umbra_imod_bsod.o \
	${OBJECTDIR}/src/fov/fov_results.o \
	${OBJECTDIR}/src/umbra/umbra_error.o \
	${OBJECTDIR}/src/fov/bsp_helper.o \
	${OBJECTDIR}/src/umbra/umbra_widget.o \
	${OBJECTDIR}/src/umbra/umbra_callback.o \
	${OBJECTDIR}/src/fov/fov_test.o \
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
	"${MAKE}"  -f nbproject/Makefile-Windows-Debug-FOV.mk ./umbra.exe

./umbra.exe: ../libtcod/lib/libtcod-mingw-debug.a

./umbra.exe: ${OBJECTFILES}
	${MKDIR} -p .
	${LINK.cc} -o ./umbra ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/umbra/umbra_engine.o: src/umbra/umbra_engine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_engine.o src/umbra/umbra_engine.cpp

${OBJECTDIR}/src/fov/fov_setup.o: src/fov/fov_setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/fov
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/fov/fov_setup.o src/fov/fov_setup.cpp

${OBJECTDIR}/src/umbra/umbra_font.o: src/umbra/umbra_font.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_font.o src/umbra/umbra_font.cpp

${OBJECTDIR}/src/invaders/notification.o: src/invaders/notification.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/invaders
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/invaders/notification.o src/invaders/notification.cpp

${OBJECTDIR}/src/fov/main.o: src/fov/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/fov
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/fov/main.o src/fov/main.cpp

${OBJECTDIR}/src/umbra/umbra_widget_button.o: src/umbra/umbra_widget_button.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_widget_button.o src/umbra/umbra_widget_button.cpp

${OBJECTDIR}/src/umbra/umbra_module.o: src/umbra/umbra_module.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_module.o src/umbra/umbra_module.cpp

${OBJECTDIR}/src/umbra/umbra_config.o: src/umbra/umbra_config.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_config.o src/umbra/umbra_config.cpp

${OBJECTDIR}/src/umbra/umbra_widget_checkbox.o: src/umbra/umbra_widget_checkbox.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_widget_checkbox.o src/umbra/umbra_widget_checkbox.cpp

${OBJECTDIR}/src/umbra/umbra_imod_bsod.o: src/umbra/umbra_imod_bsod.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_imod_bsod.o src/umbra/umbra_imod_bsod.cpp

${OBJECTDIR}/src/fov/fov_results.o: src/fov/fov_results.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/fov
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/fov/fov_results.o src/fov/fov_results.cpp

${OBJECTDIR}/src/umbra/umbra_error.o: src/umbra/umbra_error.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_error.o src/umbra/umbra_error.cpp

${OBJECTDIR}/src/fov/bsp_helper.o: src/fov/bsp_helper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/fov
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/fov/bsp_helper.o src/fov/bsp_helper.cpp

${OBJECTDIR}/src/umbra/umbra_widget.o: src/umbra/umbra_widget.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_widget.o src/umbra/umbra_widget.cpp

${OBJECTDIR}/src/umbra/umbra_callback.o: src/umbra/umbra_callback.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_callback.o src/umbra/umbra_callback.cpp

${OBJECTDIR}/src/fov/fov_test.o: src/fov/fov_test.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/fov
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/fov/fov_test.o src/fov/fov_test.cpp

${OBJECTDIR}/src/umbra/umbra_imod_speed.o: src/umbra/umbra_imod_speed.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/umbra
	${RM} $@.d
	$(COMPILE.cc) -g -I../libtcod/include -Isrc/umbra -Isrc/fov -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/umbra/umbra_imod_speed.o src/umbra/umbra_imod_speed.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Windows-Debug-FOV
	${RM} ./umbra.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
