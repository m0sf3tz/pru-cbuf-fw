################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
buffApp.obj: ../buffApp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: PRU Compiler'
	"K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/bin/clpru" -v3 --include_path="K:/ccsv8/ccs_base/pru/include" --include_path="C:/Users/Sam2/workspace_v8/for_real" --include_path="K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/include" --define=am3358 --define=pru0 -g --diag_warning=225 --diag_wrap=off --display_error_number --endian=little --hardware_mac=on --preproc_with_compile --preproc_dependency="buffApp.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

lfsr.obj: ../lfsr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: PRU Compiler'
	"K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/bin/clpru" -v3 --include_path="K:/ccsv8/ccs_base/pru/include" --include_path="C:/Users/Sam2/workspace_v8/for_real" --include_path="K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/include" --define=am3358 --define=pru0 -g --diag_warning=225 --diag_wrap=off --display_error_number --endian=little --hardware_mac=on --preproc_with_compile --preproc_dependency="lfsr.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: PRU Compiler'
	"K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/bin/clpru" -v3 --include_path="K:/ccsv8/ccs_base/pru/include" --include_path="C:/Users/Sam2/workspace_v8/for_real" --include_path="K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/include" --define=am3358 --define=pru0 -g --diag_warning=225 --diag_wrap=off --display_error_number --endian=little --hardware_mac=on --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

shbuf.obj: ../shbuf.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: PRU Compiler'
	"K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/bin/clpru" -v3 --include_path="K:/ccsv8/ccs_base/pru/include" --include_path="C:/Users/Sam2/workspace_v8/for_real" --include_path="K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/include" --define=am3358 --define=pru0 -g --diag_warning=225 --diag_wrap=off --display_error_number --endian=little --hardware_mac=on --preproc_with_compile --preproc_dependency="shbuf.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

shiftParser.obj: ../shiftParser.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: PRU Compiler'
	"K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/bin/clpru" -v3 --include_path="K:/ccsv8/ccs_base/pru/include" --include_path="C:/Users/Sam2/workspace_v8/for_real" --include_path="K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/include" --define=am3358 --define=pru0 -g --diag_warning=225 --diag_wrap=off --display_error_number --endian=little --hardware_mac=on --preproc_with_compile --preproc_dependency="shiftParser.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

spinlock.obj: ../spinlock.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: PRU Compiler'
	"K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/bin/clpru" -v3 --include_path="K:/ccsv8/ccs_base/pru/include" --include_path="C:/Users/Sam2/workspace_v8/for_real" --include_path="K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/include" --define=am3358 --define=pru0 -g --diag_warning=225 --diag_wrap=off --display_error_number --endian=little --hardware_mac=on --preproc_with_compile --preproc_dependency="spinlock.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uartHal.obj: ../uartHal.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: PRU Compiler'
	"K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/bin/clpru" -v3 --include_path="K:/ccsv8/ccs_base/pru/include" --include_path="C:/Users/Sam2/workspace_v8/for_real" --include_path="K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/include" --define=am3358 --define=pru0 -g --diag_warning=225 --diag_wrap=off --display_error_number --endian=little --hardware_mac=on --preproc_with_compile --preproc_dependency="uartHal.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uart_irda_cir.obj: ../uart_irda_cir.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: PRU Compiler'
	"K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/bin/clpru" -v3 --include_path="K:/ccsv8/ccs_base/pru/include" --include_path="C:/Users/Sam2/workspace_v8/for_real" --include_path="K:/ccsv8/tools/compiler/ti-cgt-pru_2.2.1/include" --define=am3358 --define=pru0 -g --diag_warning=225 --diag_wrap=off --display_error_number --endian=little --hardware_mac=on --preproc_with_compile --preproc_dependency="uart_irda_cir.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


