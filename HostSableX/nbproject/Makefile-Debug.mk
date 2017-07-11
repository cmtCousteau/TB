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
CCC=gcc
CXX=gcc
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
	${OBJECTDIR}/SaBLExAPI_IncomingMsg_Common.o \
	${OBJECTDIR}/SaBLExAPI_IncomingMsg_Peripheral.o \
	${OBJECTDIR}/SaBLExAPI_OutgoingMsg_Common.o \
	${OBJECTDIR}/SaBLExAPI_OutgoingMsg_Peripheral.o \
	${OBJECTDIR}/SaBLExAPI_Shared.o \
	${OBJECTDIR}/command.o \
	${OBJECTDIR}/json.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/rs232.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hostsablex.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hostsablex.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hostsablex ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/SaBLExAPI_IncomingMsg_Common.o: SaBLExAPI_IncomingMsg_Common.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SaBLExAPI_IncomingMsg_Common.o SaBLExAPI_IncomingMsg_Common.c

${OBJECTDIR}/SaBLExAPI_IncomingMsg_Peripheral.o: SaBLExAPI_IncomingMsg_Peripheral.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SaBLExAPI_IncomingMsg_Peripheral.o SaBLExAPI_IncomingMsg_Peripheral.c

${OBJECTDIR}/SaBLExAPI_OutgoingMsg_Common.o: SaBLExAPI_OutgoingMsg_Common.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SaBLExAPI_OutgoingMsg_Common.o SaBLExAPI_OutgoingMsg_Common.c

${OBJECTDIR}/SaBLExAPI_OutgoingMsg_Peripheral.o: SaBLExAPI_OutgoingMsg_Peripheral.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SaBLExAPI_OutgoingMsg_Peripheral.o SaBLExAPI_OutgoingMsg_Peripheral.c

${OBJECTDIR}/SaBLExAPI_Shared.o: SaBLExAPI_Shared.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SaBLExAPI_Shared.o SaBLExAPI_Shared.c

${OBJECTDIR}/command.o: command.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/command.o command.c

${OBJECTDIR}/json.o: json.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/json.o json.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/rs232.o: rs232.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c99 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rs232.o rs232.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
