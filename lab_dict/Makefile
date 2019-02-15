EXE = anagram_finder
TEST = test

EXE_OBJ = anagram_finder.o
OBJS = anagram_finder.o anagram_dict.o fib.o pronounce_dict.o cartalk_puzzle.o common_words.o

OBJS_DIR = .objs

# other executables
EXE_FIB = fib_generator
OBJS_FIB = $(OBJS_DIR)/fib_generator.o $(OBJS_DIR)/fib.o
EXE_FAC = fac
OBJS_FAC = $(OBJS_DIR)/fac.o
EXE_HOMOPHONE = homophone_puzzle
OBJS_HOMOPHONE = $(OBJS_DIR)/homophone_puzzle.o $(OBJS_DIR)/pronounce_dict.o $(OBJS_DIR)/cartalk_puzzle.o
EXE_COMMON_WORDS = find_common_words
OBJS_COMMON_WORDS = $(OBJS_DIR)/find_common_words.o $(OBJS_DIR)/common_words.o

CLEAN_RM = $(EXE_FIB) $(EXE_FAC) $(EXE_HOMOPHONE) $(EXE_COMMON_WORDS)

# Change each semester this lab is released
TERM = fa2018

include cs225/make/cs225.mk

data:
	wget https://courses.engr.illinois.edu/cs225/$(TERM)/labs/dict/lab_dict_data.tar && tar -xf lab_dict_data.tar && rm lab_dict_data.tar && mv lab_dict_data data

$(EXE_FIB): $(OBJS_FIB)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_FAC): $(OBJS_FAC)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_HOMOPHONE): $(OBJS_HOMOPHONE)
	$(LD) $^ $(LDFLAGS) -o $@

$(EXE_COMMON_WORDS): $(OBJS_COMMON_WORDS)
	$(LD) $^ $(LDFLAGS) -o $@
