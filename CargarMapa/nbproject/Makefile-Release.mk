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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Cargar.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/tinyxml2.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-audio.a ../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-graphics.a ../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-main.a ../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-network.a ../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-system.a ../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-window.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cargarmapa.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cargarmapa.exe: ../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-audio.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cargarmapa.exe: ../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-graphics.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cargarmapa.exe: ../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-main.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cargarmapa.exe: ../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-network.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cargarmapa.exe: ../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-system.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cargarmapa.exe: ../../../SFML-GCC-4.8.1-MinGW-master/lib/libsfml-window.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cargarmapa.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cargarmapa ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Cargar.o: Cargar.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../SFML-GCC-4.8.1-MinGW-master/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Cargar.o Cargar.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../SFML-GCC-4.8.1-MinGW-master/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/tinyxml2.o: tinyxml2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../../SFML-GCC-4.8.1-MinGW-master/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml2.o tinyxml2.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cargarmapa.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
