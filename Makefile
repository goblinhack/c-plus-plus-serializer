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
    $(OBJDIR)/hexdump.o 		              \
    $(OBJDIR)/basic_example.o 			      \
    $(OBJDIR)/container_example.o 		      \
    $(OBJDIR)/map_example.o 			      \
    $(OBJDIR)/unordered_map_example.o 		      \
    $(OBJDIR)/map_string_to_list_of_strings_example.o \
    $(OBJDIR)/custom_class_example.o 		      \
    $(OBJDIR)/bitfields_in_class_example.o            \
    $(OBJDIR)/map_custom_class_example.o 	      \
    $(OBJDIR)/zipped_container_example.o 	      \
    $(OBJDIR)/quicklz.o 	                      \

EXTRA_CFLAGS=-std=c++11
#EXTRA_CFLAGS+=-DDEBUG_C_PLUS_PLUS_SERIALIZER
#EXTRA_CFLAGS+=-DUSE_SIZE_T

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
# DO NOT DELETE

.o/basic_example.o: c_plus_plus_serializer.h
.o/bitfields_in_class_example.o: c_plus_plus_serializer.h
.o/container_example.o: c_plus_plus_serializer.h
.o/custom_class_example.o: c_plus_plus_serializer.h
.o/hexdump.o: /usr/include/string.h /usr/include/_types.h
.o/hexdump.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/hexdump.o: /usr/include/sys/_symbol_aliasing.h
.o/hexdump.o: /usr/include/sys/_posix_availability.h
.o/hexdump.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/hexdump.o: /usr/include/sys/_pthread/_pthread_types.h
.o/hexdump.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/hexdump.o: /usr/include/sys/_types/_size_t.h
.o/hexdump.o: /usr/include/sys/_types/_null.h
.o/hexdump.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/hexdump.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/hexdump.o: /usr/include/sys/_types/_int16_t.h
.o/hexdump.o: /usr/include/sys/_types/_int32_t.h
.o/hexdump.o: /usr/include/sys/_types/_int64_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int8_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int16_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int32_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int64_t.h
.o/hexdump.o: /usr/include/sys/_types/_intptr_t.h
.o/hexdump.o: /usr/include/sys/_types/_uintptr_t.h
.o/hexdump.o: /usr/include/sys/_types/_errno_t.h
.o/hexdump.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/hexdump.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/hexdump.o: /usr/include/secure/_string.h
.o/map_custom_class_example.o: c_plus_plus_serializer.h
.o/map_example.o: c_plus_plus_serializer.h
.o/map_string_to_list_of_strings_example.o: c_plus_plus_serializer.h
.o/quicklz.o: quicklz.h /usr/include/string.h /usr/include/_types.h
.o/quicklz.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/quicklz.o: /usr/include/sys/_symbol_aliasing.h
.o/quicklz.o: /usr/include/sys/_posix_availability.h
.o/quicklz.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/quicklz.o: /usr/include/sys/_pthread/_pthread_types.h
.o/quicklz.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/quicklz.o: /usr/include/sys/_types/_size_t.h
.o/quicklz.o: /usr/include/sys/_types/_null.h
.o/quicklz.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/quicklz.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/quicklz.o: /usr/include/sys/_types/_int16_t.h
.o/quicklz.o: /usr/include/sys/_types/_int32_t.h
.o/quicklz.o: /usr/include/sys/_types/_int64_t.h
.o/quicklz.o: /usr/include/sys/_types/_u_int8_t.h
.o/quicklz.o: /usr/include/sys/_types/_u_int16_t.h
.o/quicklz.o: /usr/include/sys/_types/_u_int32_t.h
.o/quicklz.o: /usr/include/sys/_types/_u_int64_t.h
.o/quicklz.o: /usr/include/sys/_types/_intptr_t.h
.o/quicklz.o: /usr/include/sys/_types/_uintptr_t.h
.o/quicklz.o: /usr/include/sys/_types/_errno_t.h
.o/quicklz.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/quicklz.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/quicklz.o: /usr/include/secure/_string.h
.o/unordered_map_example.o: c_plus_plus_serializer.h
.o/zipped_container_example.o: c_plus_plus_serializer.h hexdump.h quicklz.h
.o/zipped_container_example.o: /usr/include/string.h /usr/include/_types.h
.o/zipped_container_example.o: /usr/include/sys/_types.h
.o/zipped_container_example.o: /usr/include/sys/cdefs.h
.o/zipped_container_example.o: /usr/include/sys/_symbol_aliasing.h
.o/zipped_container_example.o: /usr/include/sys/_posix_availability.h
.o/zipped_container_example.o: /usr/include/machine/_types.h
.o/zipped_container_example.o: /usr/include/i386/_types.h
.o/zipped_container_example.o: /usr/include/sys/_pthread/_pthread_types.h
.o/zipped_container_example.o: /usr/include/Availability.h
.o/zipped_container_example.o: /usr/include/AvailabilityInternal.h
.o/zipped_container_example.o: /usr/include/sys/_types/_size_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_null.h
.o/zipped_container_example.o: /usr/include/sys/_types/_rsize_t.h
.o/zipped_container_example.o: /usr/include/machine/types.h
.o/zipped_container_example.o: /usr/include/i386/types.h
.o/zipped_container_example.o: /usr/include/sys/_types/_int8_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_int16_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_int32_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_int64_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_u_int8_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_u_int16_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_u_int32_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_u_int64_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_intptr_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_uintptr_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_errno_t.h
.o/zipped_container_example.o: /usr/include/sys/_types/_ssize_t.h
.o/zipped_container_example.o: /usr/include/strings.h
.o/zipped_container_example.o: /usr/include/secure/_strings.h
.o/zipped_container_example.o: /usr/include/secure/_common.h
.o/zipped_container_example.o: /usr/include/secure/_string.h
