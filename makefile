fs: main.o  Environment.o
    g++ main.o Environment.o -o fs

# Depends on the source and header files
bin/main.o: src/main.cpp include/Environment.h
	g++ -c src/main.cpp

# Depends on the source and header files
bin/Environment.o: src/Environment.cpp include/Environment.h include/Commands.h
	g++ -c src/Environment.cpp


# Depends on the source and header files
bin/Commands.o: src/Commands.cpp include/Commands.h include/FileSystem.h
	g++ -c src/Commands.cpp

# Depends on the source and header files
bin/FileSystem.o: src/FileSystem.cpp include/Filesystem.h include/Files.h
	g++ -c src/Filesystem.cpp

# Depends on the source and header files
bin/GlobalVariables.o: src/GlobalVariables.cpp include/GlobalVariables.h
	g++ -c src/GlobalVariables.cpp

# Depends on the source and header files
bin/Files.o: src/Files.cpp include/Files.h
	g++ -c src/Files.cpp

#Clean the build directory
clean:
	rm -f bin/*