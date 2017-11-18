CC = g++
CFLAGS  = -g -Wall -Weffc++ -std=c++11
LFLAGS  = -L/usr/lib

# All Targets
all: fs

# Tool invocations
fs: bin/Commands.o bin/Environment.o bin/main.o bin/Files.o bin/FileSystem.o
	@echo 'Building target: fs'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/fs bin/Commands.o bin/Environment.o bin/main.o bin/Files.o bin/FileSystem.o $(LFLAGS)
	@echo 'Finished building target: fs'
	@echo ' '
bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp
# Depends on the source and header files
bin/Environment.o: src/Environment.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Environment.o src/Environment.cpp
# Depends on the source and header files
bin/Commands.o: src/Commands.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Commands.o src/Commands.cpp
# Depends on the source and header files
bin/Files.o: src/Files.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Files.o src/Files.cpp
# Depends on the source and header files
bin/FileSystem.o: src/FileSystem.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/FileSystem.o src/FileSystem.cpp

#Clean the build directory
clean:
	rm -f bin/*