################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Temp/gamedata.cpp \
../Temp/myVideo.cpp 

C_UPPER_SRCS += \
../Temp/Camera.C \
../Temp/OBJFile.C \
../Temp/OIIOFiles.C \
../Temp/Utility.C \
../Temp/Vector.C 

OBJS += \
./Temp/Camera.o \
./Temp/OBJFile.o \
./Temp/OIIOFiles.o \
./Temp/Utility.o \
./Temp/Vector.o \
./Temp/gamedata.o \
./Temp/myVideo.o 

CPP_DEPS += \
./Temp/gamedata.d \
./Temp/myVideo.d 

C_UPPER_DEPS += \
./Temp/Camera.d \
./Temp/OBJFile.d \
./Temp/OIIOFiles.d \
./Temp/Utility.d \
./Temp/Vector.d 


# Each subdirectory must supply rules for building sources it contributes
Temp/%.o: ../Temp/%.C
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/chaorel/Dropbox/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Temp/%.o: ../Temp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/chaorel/Dropbox/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


