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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/13a2d6a6/ejemlo.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/C/SFML/lib/libsfml-graphics-d.a /C/SFML/lib/libsfml-graphics.a /C/SFML/lib/libsfml-window-d.a /C/SFML/lib/libsfml-window.a /C/SFML/lib/libsfml-system-d.a /C/SFML/lib/libsfml-system.a /C/SFML/lib/libsfml-audio-d.a /C/SFML/lib/libsfml-audio.a /C/SFML/lib/libsfml-main-d.a /C/SFML/lib/libsfml-main.a /C/SFML/lib/libsfml-network-d.a /C/SFML/lib/libsfml-network.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-graphics-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-graphics.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-window-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-window.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-system-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-system.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-audio-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-audio.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-main-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-main.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-network-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: /C/SFML/lib/libsfml-network.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/13a2d6a6/ejemlo.o: /C/Users/cesarposas/Documents/NetBeansProjects/transicionPresidentum/ejemlo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/13a2d6a6
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/13a2d6a6/ejemlo.o /C/Users/cesarposas/Documents/NetBeansProjects/transicionPresidentum/ejemlo.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/transicionpresidentum.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
