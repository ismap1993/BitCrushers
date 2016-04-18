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
	${OBJECTDIR}/_ext/476a240/Jugador.o \
	${OBJECTDIR}/ECinematica.o \
	${OBJECTDIR}/EInGame.o \
	${OBJECTDIR}/EIntro.o \
	${OBJECTDIR}/EMenu.o \
	${OBJECTDIR}/EMenuInGame.o \
	${OBJECTDIR}/Enemigo.o \
	${OBJECTDIR}/Escena.o \
	${OBJECTDIR}/Juego.o \
	${OBJECTDIR}/Mundo.o \
	${OBJECTDIR}/NPC.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/pruebasAlfonso.o \
	${OBJECTDIR}/pruebasCarlos.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iadeenemigos.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iadeenemigos.exe: /C/SFML/lib/libsfml-graphics-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iadeenemigos.exe: /C/SFML/lib/libsfml-window-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iadeenemigos.exe: /C/SFML/lib/libsfml-system-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iadeenemigos.exe: /C/SFML/lib/libsfml-audio-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iadeenemigos.exe: /C/SFML/lib/libsfml-main-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iadeenemigos.exe: /C/SFML/lib/libsfml-network-d.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iadeenemigos.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iadeenemigos ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/476a240/Jugador.o: ../presidentumClases2/Jugador.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/476a240
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/476a240/Jugador.o ../presidentumClases2/Jugador.cpp

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

${OBJECTDIR}/EMenu.o: EMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EMenu.o EMenu.cpp

${OBJECTDIR}/EMenuInGame.o: EMenuInGame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EMenuInGame.o EMenuInGame.cpp

${OBJECTDIR}/Enemigo.o: Enemigo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Enemigo.o Enemigo.cpp

${OBJECTDIR}/Escena.o: Escena.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Escena.o Escena.cpp

${OBJECTDIR}/Juego.o: Juego.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Juego.o Juego.cpp

${OBJECTDIR}/Mundo.o: Mundo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Mundo.o Mundo.cpp

${OBJECTDIR}/NPC.o: NPC.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NPC.o NPC.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/pruebasAlfonso.o: pruebasAlfonso.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pruebasAlfonso.o pruebasAlfonso.cpp

${OBJECTDIR}/pruebasCarlos.o: pruebasCarlos.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/C/SFML/include -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pruebasCarlos.o pruebasCarlos.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/iadeenemigos.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
