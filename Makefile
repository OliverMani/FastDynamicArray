AR = ar
AR_FLAGS = rcs
RM = rm -f
GCC = gcc -Wall
GPP = g++
AS = as
CP = cp
LIBPATH = /lib/
LD = gcc
TARGET = libFastDynamicArray.a
C_SOURCE = fastdynamicarray.c
ASM_SOURCE = optimize/floorlog2.S optimize/calculations.S optimize/power.S
ASMFLAGS = 
OBJECTS = $(ASM_SOURCE:.S=.o) $(C_SOURCE:.c=.o)
CPPTEST = cpptest.cpp
CPPFLAGS = -L. -lFastDynamicArray
CPP_TARGET = bin/test3

all: $(OBJECTS)
	$(AR) $(AR_FLAGS) $(TARGET) $(OBJECTS)
	$(CP) $(TARGET) $(LIBPATH)

%.o: %.c
	gcc -c $< -o $@ -fPIE
%.o: %.S
	$(AS) $(ASMFLAGS) $< -o $@

clean:
	$(RM) *.o
	$(RM) optimize/*.o
	$(RM) libFastDynamicArray.a

test:
	$(GPP) -o $(CPP_TARGET) $(CPPTEST) $(CPPFLAGS) 
test2:
	$(GCC) $(CPPFLAGS) -c test2.c -o test2.o -fPIE
	$(LD) -o bin/test2 test2.o -L. -lFastDynamicArray