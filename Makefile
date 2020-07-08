OBJ = main.o
MAIN = main.exe

$(MAIN): $(OBJ)
	$(CXX) -g -std=c++11 -o $(MAIN) $(OBJ) -static-libstdc++

main.o: main.cpp grade.h
	$(CXX) -g -std=c++11 -c main.cpp

clean: 
	del -f $(OBJ) $(MAIN)
