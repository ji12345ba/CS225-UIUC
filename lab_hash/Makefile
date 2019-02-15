
# Executable names:
EXE = lab_hash
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o hashes.o textfile.o

# Generated files
#CLEAN_RM = out.png

# Use the cs225 makefile template:
include cs225/make/cs225.mk

OBJS_DIR = .objs

TEST_OBJS = hashes.o textfile.o

data:
	wget https://courses.engr.illinois.edu/cs225/sp2018/labs/hash/lab_hash_data.tar && tar -xf lab_hash_data.tar && rm lab_hash_data.tar

