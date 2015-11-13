CPP = g++
OPT = -O3
#OPT = -g
WARN = -Wall
CFLAGS = $(OPT) $(INC) $(LIB)

# List all your .cc files here (source files, excluding header files)
SIM_SRC = hybrid.cpp
# List corresponding compiled object files here (.o files)
SIM_OBJ = hybrid.o 
 
#################################

# default rule

all: sim_cache
	@echo "my work is done here..."


# rule for making sim_cache

sim_cache: $(SIM_OBJ)
	$(CPP) -o sim $(CFLAGS) $(SIM_OBJ) -lm
	@echo "-----------DONE WITH SIM_CACHE-----------"


# generic rule for converting any .cc file to any .o file
 
.cpp.o:
	$(CPP) $(CFLAGS)  -c $*.cpp


# type "make clean" to remove all .o files plus the sim_cache binary

clean:
	rm -f *.o sim


# type "make clobber" to remove all .o files (leaves sim_cache binary)

clobber:
	rm -f *.o