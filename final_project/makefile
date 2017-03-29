CXX=g++
CXXFLAGS= -std=c++11
OBJ=main.o circuit.o resistor.o capacitor.o inductor.o component.o complex.o

all: output

output: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp component.h resistor.h capacitor.h inductor.h complex.h circuit.h
	$(CXX) $(CXXFLAGS) -c $<

circuit.o: circuit.cpp component.h resistor.h capacitor.h inductor.h complex.h circuit.h
	$(CXX) $(CXXFLAGS) -c $<

resistor.o: resistor.cpp component.h resistor.h complex.h
	$(CXX) $(CXXFLAGS) -c $<

capacitor.o: capacitor.cpp component.h capacitor.h complex.h
	$(CXX) $(CXXFLAGS) -c $<

inductor.o: inductor.cpp component.h inductor.h complex.h
	$(CXX) $(CXXFLAGS) -c $<

component.o: component.cpp component.h complex.h
	$(CXX) $(CXXFLAGS) -c $<

complex.o: complex.cpp complex.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm *.o
