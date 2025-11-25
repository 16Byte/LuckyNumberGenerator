CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = lottery
OBJS = main.o MegaMillionsNumberGenerator.o PowerBallNumberGenerator.o FileManager.o LuckyNumberGenerator.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp MegaMillionsNumberGenerator.hpp PowerBallNumberGenerator.hpp LuckyNumberGenerator.hpp FileManager.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

MegaMillionsNumberGenerator.o: MegaMillionsNumberGenerator.cpp MegaMillionsNumberGenerator.hpp LuckyNumberGenerator.hpp
	$(CXX) $(CXXFLAGS) -c MegaMillionsNumberGenerator.cpp

PowerBallNumberGenerator.o: PowerBallNumberGenerator.cpp PowerBallNumberGenerator.hpp LuckyNumberGenerator.hpp
	$(CXX) $(CXXFLAGS) -c PowerBallNumberGenerator.cpp

FileManager.o: FileManager.cpp FileManager.hpp
	$(CXX) $(CXXFLAGS) -c FileManager.cpp

LuckyNumberGenerator.o: LuckyNumberGenerator.cpp LuckyNumberGenerator.hpp
	$(CXX) $(CXXFLAGS) -c LuckyNumberGenerator.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
