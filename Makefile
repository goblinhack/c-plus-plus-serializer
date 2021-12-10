COMPILER_FLAGS=-Werror -g -ggdb3 -O2 -I . -I examples # AUTOGEN
    
CLANG_COMPILER_WARNINGS=-Wall # AUTOGEN
GCC_COMPILER_WARNINGS=-Wall # AUTOGEN
GXX_COMPILER_WARNINGS=-Wall # AUTOGEN
COMPILER_WARNINGS=$(GCC_COMPILER_WARNINGS) # AUTOGEN
COMPILER_WARNINGS=$(GXX_COMPILER_WARNINGS) # AUTOGEN
COMPILER_WARNINGS=$(CLANG_COMPILER_WARNINGS) # AUTOGEN
CC=clang # AUTOGEN
# CC=gcc # AUTOGEN
# CC=cc # AUTOGEN
# CC=g++ # AUTOGEN
    
EXE= # AUTOGEN
LDLIBS= # AUTOGEN
CFLAGS=$(COMPILER_FLAGS) $(COMPILER_WARNINGS) # AUTOGEN
NAME=c_plus_plus_serializer
OBJDIR=.o

TARGET_OBJECTS=					      \
    $(OBJDIR)/main.o 				      \
    $(OBJDIR)/hexdump.o 		              \
    $(OBJDIR)/basic_example.o 			      \
    $(OBJDIR)/raw_memory.o 			      \
    $(OBJDIR)/container_example.o 		      \
    $(OBJDIR)/map_example.o 			      \
    $(OBJDIR)/unordered_map_example.o 		      \
    $(OBJDIR)/map_string_to_list_of_strings_example.o \
    $(OBJDIR)/custom_class_example.o 		      \
    $(OBJDIR)/template_class_example.o 		      \
    $(OBJDIR)/bitfields_in_class_example.o            \
    $(OBJDIR)/map_custom_class_example.o 	      \
    $(OBJDIR)/zipped_container_example.o 	      \
    $(OBJDIR)/quicklz.o 	                      \

EXTRA_CFLAGS=-std=c++11
#EXTRA_CFLAGS+=-DDEBUG_C_PLUS_PLUS_SERIALIZER
#EXTRA_CFLAGS+=-DUSE_SIZE_T

$(OBJDIR)/%.o: examples/%.cpp
	$(shell echo clang-format -i $<)
	@echo $(CXX) $(EXTRA_CFLAGS) $(CFLAGS) -c -o $@ $<
	@$(CXX) $(EXTRA_CFLAGS) $(CFLAGS) -c -o $@ $<

#
# link
#
TARGET=$(NAME)$(EXE)
$(TARGET): $(TARGET_OBJECTS)
	$(CXX) $(TARGET_OBJECTS) $(LDLIBS) -o $(TARGET)

#
# To force clean and avoid "up to date" warning.
#
.PHONY: clean
.PHONY: clobber

clean:
	rm -rf $(TARGET) $(OBJDIR)/*.o

clobber: clean
	mkdir -p $(OBJDIR)

all: $(TARGET) 

format:
	git diff -U0 HEAD^ | clang-format-diff -i -p1
# DO NOT DELETE
