PROJECT = tiny_kiss
CC = gcc
CC_FLAGS = -W -Wall

# .c files
C_SOURCE = $(wildcard src/*.c)

# .h files
H_SOURCE = $(wildcard headers/*.h)

# .o files
OBJ = $(subst .c,.o,$(subst src,build,$(C_SOURCE)))

build: $(PROJECT)

$(PROJECT): $(OBJ)
	@ echo 'Building final binary: $@'
	$(CC) -o $(PROJECT) $(OBJ)
	@ echo ' '
	@ echo 'Compilation completed: $@'
	@ echo ' '

build/%.o: src/%.c $(H_SOURCE)
	@ echo 'Bulding file: $<'
	$(CC) $(CC_FLAGS) -c $< -o $@
	@ echo ' '

clean:
	@ rm -rf $(wildcard build/*.o) $(PROJECT)

run:
	@ ./$(PROJECT)