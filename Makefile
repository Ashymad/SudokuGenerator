CXX=g++
CFLAGS=-I. -pthread
DEPS = sudoku.h
OBJ = main.o sudoku.o

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

sudoku: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	-rm sudoku $(OBJ)
