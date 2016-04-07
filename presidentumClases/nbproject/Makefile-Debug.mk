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
<<<<<<< HEAD
	${OBJECTDIR}/ECinematica.o \
	${OBJECTDIR}/EInGame.o \
	${OBJECTDIR}/EIntro.o \
	${OBJECTDIR}/EMenu.o \
	${OBJECTDIR}/EMenuInGame.o \
	${OBJECTDIR}/Escena.o \
	${OBJECTDIR}/Juego.o \
	${OBJECTDIR}/main.o
=======
	${OBJECTDIR}/Camara.o \
	${OBJECTDIR}/EMenu.o \
	${OBJECTDIR}/Jugador.o \
	${OBJECTDIR}/Mapa.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/tinystr.o \
	${OBJECTDIR}/tinyxml.o \
	${OBJECTDIR}/tinyxmlerror.o \
	${OBJECTDIR}/tinyxmlparser.o
>>>>>>> 46bc60a011a73d2d421aba81d3a5685d3c78b415


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
LDLIBSOPTIONS=/C/SFML/lib/libsfml-graphics-d.a /C/SFML/lib/libsfml-window-d.a /C/SFML/lib/libsfml-system-d.a /C/SFML/lib/libsfml-audio-d.a /C/SFML/lib/libsfml-main-d.a /C/SFML/lib/libsfml-network-d.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumclases.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumclases.exe: /C/SFML/lib/libsfml-graphics-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumclases.exe: /C/SFML/lib/libsfml-window-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumclases.exe: /C/SFML/lib/libsfml-system-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumclases.exe: /C/SFML/lib/libsfml-audio-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumclases.exe: /C/SFML/lib/libsfml-main-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumclases.exe: /C/SFML/lib/libsfml-network-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumclases.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumclases ${OBJECTFILES} ${LDLIBSOPTIONS}

<<<<<<< HEAD
${OBJECTDIR}/ECinematica.o: ECinematica.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ECinematica.o ECinematica.cpp

${OBJECTDIR}/EInGame.o: EInGame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EInGame.o EInGame.cpp

${OBJECTDIR}/EIntro.o: EIntro.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EIntro.o EIntro.cpp
=======
${OBJECTDIR}/Camara.o: Camara.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Camara.o Camara.cpp
>>>>>>> 46bc60a011a73d2d421aba81d3a5685d3c78b415

${OBJECTDIR}/EMenu.o: EMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
<<<<<<< HEAD
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EMenu.o EMenu.cpp

${OBJECTDIR}/EMenuInGame.o: EMenuInGame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EMenuInGame.o EMenuInGame.cpp

${OBJECTDIR}/Escena.o: Escena.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Escena.o Escena.cpp

${OBJECTDIR}/Juego.o: Juego.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Juego.o Juego.cpp
=======
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EMenu.o EMenu.cpp

${OBJECTDIR}/Jugador.o: Jugador.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Jugador.o Jugador.cpp

${OBJECTDIR}/Mapa.o: Mapa.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mapa.o Mapa.cpp
>>>>>>> 46bc60a011a73d2d421aba81d3a5685d3c78b415

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/tinystr.o: tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinystr.o tinystr.cpp

${OBJECTDIR}/tinyxml.o: tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxml.o tinyxml.cpp

${OBJECTDIR}/tinyxmlerror.o: tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxmlerror.o tinyxmlerror.cpp

${OBJECTDIR}/tinyxmlparser.o: tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tinyxmlparser.o tinyxmlparser.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/presidentumclases.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
