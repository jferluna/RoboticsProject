#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RoboticsProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/RoboticsProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=robotics.c Sources/uart.c Sources/servoController.c Sources/sensors.c Sources/timers.c Sources/Motors.c Sources/movements.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/robotics.o ${OBJECTDIR}/Sources/uart.o ${OBJECTDIR}/Sources/servoController.o ${OBJECTDIR}/Sources/sensors.o ${OBJECTDIR}/Sources/timers.o ${OBJECTDIR}/Sources/Motors.o ${OBJECTDIR}/Sources/movements.o
POSSIBLE_DEPFILES=${OBJECTDIR}/robotics.o.d ${OBJECTDIR}/Sources/uart.o.d ${OBJECTDIR}/Sources/servoController.o.d ${OBJECTDIR}/Sources/sensors.o.d ${OBJECTDIR}/Sources/timers.o.d ${OBJECTDIR}/Sources/Motors.o.d ${OBJECTDIR}/Sources/movements.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/robotics.o ${OBJECTDIR}/Sources/uart.o ${OBJECTDIR}/Sources/servoController.o ${OBJECTDIR}/Sources/sensors.o ${OBJECTDIR}/Sources/timers.o ${OBJECTDIR}/Sources/Motors.o ${OBJECTDIR}/Sources/movements.o

# Source Files
SOURCEFILES=robotics.c Sources/uart.c Sources/servoController.c Sources/sensors.c Sources/timers.c Sources/Motors.c Sources/movements.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/RoboticsProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/robotics.o: robotics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/robotics.o.d 
	@${RM} ${OBJECTDIR}/robotics.o 
	@${FIXDEPS} "${OBJECTDIR}/robotics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/robotics.o.d" -o ${OBJECTDIR}/robotics.o robotics.c   
	
${OBJECTDIR}/Sources/uart.o: Sources/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/uart.o.d 
	@${RM} ${OBJECTDIR}/Sources/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/uart.o.d" -o ${OBJECTDIR}/Sources/uart.o Sources/uart.c   
	
${OBJECTDIR}/Sources/servoController.o: Sources/servoController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/servoController.o.d 
	@${RM} ${OBJECTDIR}/Sources/servoController.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/servoController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/servoController.o.d" -o ${OBJECTDIR}/Sources/servoController.o Sources/servoController.c   
	
${OBJECTDIR}/Sources/sensors.o: Sources/sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/sensors.o.d 
	@${RM} ${OBJECTDIR}/Sources/sensors.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/sensors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/sensors.o.d" -o ${OBJECTDIR}/Sources/sensors.o Sources/sensors.c   
	
${OBJECTDIR}/Sources/timers.o: Sources/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/timers.o.d 
	@${RM} ${OBJECTDIR}/Sources/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/timers.o.d" -o ${OBJECTDIR}/Sources/timers.o Sources/timers.c   
	
${OBJECTDIR}/Sources/Motors.o: Sources/Motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/Motors.o.d 
	@${RM} ${OBJECTDIR}/Sources/Motors.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/Motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/Motors.o.d" -o ${OBJECTDIR}/Sources/Motors.o Sources/Motors.c   
	
${OBJECTDIR}/Sources/movements.o: Sources/movements.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/movements.o.d 
	@${RM} ${OBJECTDIR}/Sources/movements.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/movements.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/movements.o.d" -o ${OBJECTDIR}/Sources/movements.o Sources/movements.c   
	
else
${OBJECTDIR}/robotics.o: robotics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/robotics.o.d 
	@${RM} ${OBJECTDIR}/robotics.o 
	@${FIXDEPS} "${OBJECTDIR}/robotics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/robotics.o.d" -o ${OBJECTDIR}/robotics.o robotics.c   
	
${OBJECTDIR}/Sources/uart.o: Sources/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/uart.o.d 
	@${RM} ${OBJECTDIR}/Sources/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/uart.o.d" -o ${OBJECTDIR}/Sources/uart.o Sources/uart.c   
	
${OBJECTDIR}/Sources/servoController.o: Sources/servoController.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/servoController.o.d 
	@${RM} ${OBJECTDIR}/Sources/servoController.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/servoController.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/servoController.o.d" -o ${OBJECTDIR}/Sources/servoController.o Sources/servoController.c   
	
${OBJECTDIR}/Sources/sensors.o: Sources/sensors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/sensors.o.d 
	@${RM} ${OBJECTDIR}/Sources/sensors.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/sensors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/sensors.o.d" -o ${OBJECTDIR}/Sources/sensors.o Sources/sensors.c   
	
${OBJECTDIR}/Sources/timers.o: Sources/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/timers.o.d 
	@${RM} ${OBJECTDIR}/Sources/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/timers.o.d" -o ${OBJECTDIR}/Sources/timers.o Sources/timers.c   
	
${OBJECTDIR}/Sources/Motors.o: Sources/Motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/Motors.o.d 
	@${RM} ${OBJECTDIR}/Sources/Motors.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/Motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/Motors.o.d" -o ${OBJECTDIR}/Sources/Motors.o Sources/Motors.c   
	
${OBJECTDIR}/Sources/movements.o: Sources/movements.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/Sources" 
	@${RM} ${OBJECTDIR}/Sources/movements.o.d 
	@${RM} ${OBJECTDIR}/Sources/movements.o 
	@${FIXDEPS} "${OBJECTDIR}/Sources/movements.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"Headers" -I"Sources" -MMD -MF "${OBJECTDIR}/Sources/movements.o.d" -o ${OBJECTDIR}/Sources/movements.o Sources/movements.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/RoboticsProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/RoboticsProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}           -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/RoboticsProject.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/RoboticsProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/RoboticsProject.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
