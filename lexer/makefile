CFLAGS=-std=c++11
CXX = g++
all: clean kuntac
	echo "Compiling..."
	#./kuntac ../votechain.kscript
	./kuntac ../simple.kscript
	#./kuntac ../total.kscript
kuntac: kuntac.o ks.o lexer.o exprtk.o json.o
	$(CXX) $(CFLAGS) kuntac.o ks.o lexer.o -o kuntac
	#$(CXX) $(CFLAGS) kuntac.o ks.o lexer.o exprtk.o -o kuntac
kuntac.o: kuntac.h kuntac.cpp
	$(CXX) $(CFLAGS) -c kuntac.cpp 
lexer.o: lexer.h lexer.cpp
	$(CXX) $(CFLAGS) -c lexer.cpp
ks.o: ks.h ks.cpp
	$(CXX) $(CFLAGS) -c ks.cpp
exprtk.o: exprtk.hpp exprtk.cpp 
	#$(CXX) $(CFLAGS) -c exprtk.cpp
json.o: json.hpp
	$(CXX) $(CFLAGS) -c json.hpp
clean:
	echo "cleaning..."
	rm -f *.o ks *.o *.bin kuntac kuntac.o

