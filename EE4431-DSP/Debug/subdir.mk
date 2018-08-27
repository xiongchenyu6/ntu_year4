################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AIC_func.c \
../LCD_FCN.c \
../lcd_disp.c \
../led.c \
../main.c \
../sar.c \
../usbstk5515.c 

CMD_SRCS += \
../lnkx.cmd 

OBJS += \
./AIC_func.obj \
./LCD_FCN.obj \
./lcd_disp.obj \
./led.obj \
./main.obj \
./sar.obj \
./usbstk5515.obj 

C_DEPS += \
./AIC_func.pp \
./LCD_FCN.pp \
./lcd_disp.pp \
./led.pp \
./main.pp \
./sar.pp \
./usbstk5515.pp 

OBJS__QTD += \
".\AIC_func.obj" \
".\LCD_FCN.obj" \
".\lcd_disp.obj" \
".\led.obj" \
".\main.obj" \
".\sar.obj" \
".\usbstk5515.obj" 

C_DEPS__QTD += \
".\AIC_func.pp" \
".\LCD_FCN.pp" \
".\lcd_disp.pp" \
".\led.pp" \
".\main.pp" \
".\sar.pp" \
".\usbstk5515.pp" 

C_SRCS_QUOTED += \
"../AIC_func.c" \
"../LCD_FCN.c" \
"../lcd_disp.c" \
"../led.c" \
"../main.c" \
"../sar.c" \
"../usbstk5515.c" 


# Each subdirectory must supply rules for building sources it contributes
AIC_func.obj: ../AIC_func.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/452_Support" --include_path="C:/EE4413/C5515/Exercises/LED_control/Include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/C5515_Includes" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="AIC_func.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

LCD_FCN.obj: ../LCD_FCN.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/452_Support" --include_path="C:/EE4413/C5515/Exercises/LED_control/Include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/C5515_Includes" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="LCD_FCN.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

lcd_disp.obj: ../lcd_disp.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/452_Support" --include_path="C:/EE4413/C5515/Exercises/LED_control/Include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/C5515_Includes" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="lcd_disp.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

led.obj: ../led.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/452_Support" --include_path="C:/EE4413/C5515/Exercises/LED_control/Include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/C5515_Includes" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="led.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/452_Support" --include_path="C:/EE4413/C5515/Exercises/LED_control/Include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/C5515_Includes" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

sar.obj: ../sar.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/452_Support" --include_path="C:/EE4413/C5515/Exercises/LED_control/Include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/C5515_Includes" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="sar.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

usbstk5515.obj: ../usbstk5515.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/452_Support" --include_path="C:/EE4413/C5515/Exercises/LED_control/Include" --include_path="C:/EE4413 Course Materials/Part 2 of 2_By Prof Joni Lie/EE4413_C515/C5515_Support_Files/C5515_Includes" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="usbstk5515.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


