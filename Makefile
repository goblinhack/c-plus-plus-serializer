COMPILER_FLAGS=-Werror -g -ggdb3 -O2  # AUTOGEN
    
CLANG_COMPILER_WARNINGS=-Wall -Wall # AUTOGEN
GCC_COMPILER_WARNINGS=-Wall -Wall # AUTOGEN
GXX_COMPILER_WARNINGS=-Wall -Wall # AUTOGEN
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
    $(OBJDIR)/basic_example.o 			      \
    $(OBJDIR)/container_example.o 		      \
    $(OBJDIR)/map_example.o 			      \
    $(OBJDIR)/map_string_to_list_of_strings_example.o \
    $(OBJDIR)/custom_class_example.o 		      \
    $(OBJDIR)/bitfields_in_class_example.o            \
    $(OBJDIR)/map_custom_class_example.o 	      \

EXTRA_CFLAGS=-std=c++11
#EXTRA_CFLAGS+=-DDEBUG_C_PLUS_PLUS_SERIALIZER

$(OBJDIR)/%.o: %.cpp
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

.o/main.o: c_plus_plus_serializer.h
