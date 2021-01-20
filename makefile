project2: main.o Intializer.o IntializerHelper.o Node.o Map.o MapSetup1.o MapSetup2.o Simulator.o
	g++ -std=c++11 main.o Intializer.o IntializerHelper.o Node.o Map.o MapSetup1.o MapSetup2.o Simulator.o -o project2

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

Intializer.o: Intializer.cpp	Intializer.hpp
	g++ -c -std=c++11 Intializer.cpp

IntializerHelper.o: IntializerHelper.cpp IntializerHelper.hpp
	g++ -c -std=c++11 IntializerHelper.cpp

Node.o: Node.cpp Node.hpp
	g++ -c -std=c++11 Node.cpp

Map.o: Map.cpp Map.hpp
	g++ -c -std=c++11 Map.cpp 

MapSetup1.o: MapSetup1.cpp Map.hpp
	g++ -c -std=c++11 MapSetup1.cpp

mapCentrality.o: MapSetup2.cpp Map.hpp
	g++ -c -std=c++11 MapSetup2.cpp

Simulation.o: Simulator.cpp Simulator.hpp
	g++ -c -std=c++11 Simulator.cpp


clean:
	rm *.o project2