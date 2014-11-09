################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../IO/File.cpp \
../IO/Image.cpp \
../IO/InputHandler.cpp \
../IO/OBJFile.cpp \
../IO/OIIOFiles.cpp \
../IO/Video.cpp 

OBJS += \
./IO/File.o \
./IO/Image.o \
./IO/InputHandler.o \
./IO/OBJFile.o \
./IO/OIIOFiles.o \
./IO/Video.o 

CPP_DEPS += \
./IO/File.d \
./IO/Image.d \
./IO/InputHandler.d \
./IO/OBJFile.d \
./IO/OIIOFiles.d \
./IO/Video.d 


# Each subdirectory must supply rules for building sources it contributes
IO/%.o: ../IO/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/chao/usr/local/include -I"/home/chao/usr/local/include/bullet" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


