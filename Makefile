COMPILER_FLAGS=-Werror -g -ggdb3 -O2  # AUTOGEN
    
CLANG_COMPILER_WARNINGS=-Wall -fmessage-length=0 -fdiagnostics-print-source-range-info -fdiagnostics-show-category=id -fdiagnostics-parseable-fixits -Wno-trigraphs -Wmissing-prototypes -Wreturn-type -Wparentheses -Wswitch -Wno-unused-parameter -Wunused-variable -Wunused-value -Wno-sign-conversion # AUTOGEN
GCC_COMPILER_WARNINGS=-Wall -fmessage-length=0 -Wno-trigraphs -Wmissing-prototypes -Wreturn-type -Wparentheses -Wswitch -Wno-unused-parameter -Wunused-variable -Wunused-value # AUTOGEN
GXX_COMPILER_WARNINGS=-Wall -fmessage-length=0 -Wno-trigraphs -Wreturn-type -Wparentheses -Wswitch -Wno-unused-parameter -Wunused-variable -Wunused-value # AUTOGEN
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

TARGET_OBJECTS=					\
    $(OBJDIR)/main.o 				\

#    $(OBJDIR)/c_plus_plus_serializer.o 		\

$(OBJDIR)/%.o: %.cpp
	@echo $(CC) $(EXTRA_CFLAGS) $(CFLAGS) -c -o $@ $<
	@$(CC) $(EXTRA_CFLAGS) $(CFLAGS) -c -o $@ $<

#
# link
#
TARGET=$(NAME)$(EXE)
$(TARGET): $(TARGET_OBJECTS)
	$(CC) $(TARGET_OBJECTS) $(LDLIBS) -o $(TARGET)

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
