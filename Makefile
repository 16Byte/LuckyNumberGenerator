CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
TARGET = lottery
OBJDIR = Object
OBJS = $(OBJDIR)/main.o $(OBJDIR)/MegaMillionsNumberGenerator.o $(OBJDIR)/PowerBallNumberGenerator.o $(OBJDIR)/FileManager.o $(OBJDIR)/LuckyNumberGenerator.o

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJDIR)/main.o: src/main.cpp include/MegaMillionsNumberGenerator.hpp include/PowerBallNumberGenerator.hpp include/LuckyNumberGenerator.hpp include/FileManager.hpp include/raygui.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/MegaMillionsNumberGenerator.o: src/MegaMillionsNumberGenerator.cpp include/MegaMillionsNumberGenerator.hpp include/LuckyNumberGenerator.hpp
	$(CXX) $(CXXFLAGS) -c src/MegaMillionsNumberGenerator.cpp -o $(OBJDIR)/MegaMillionsNumberGenerator.o

$(OBJDIR)/PowerBallNumberGenerator.o: src/PowerBallNumberGenerator.cpp include/PowerBallNumberGenerator.hpp include/LuckyNumberGenerator.hpp
	$(CXX) $(CXXFLAGS) -c src/PowerBallNumberGenerator.cpp -o $(OBJDIR)/PowerBallNumberGenerator.o

$(OBJDIR)/FileManager.o: src/FileManager.cpp include/FileManager.hpp
	$(CXX) $(CXXFLAGS) -c src/FileManager.cpp -o $(OBJDIR)/FileManager.o

$(OBJDIR)/LuckyNumberGenerator.o: src/LuckyNumberGenerator.cpp include/LuckyNumberGenerator.hpp
	$(CXX) $(CXXFLAGS) -c src/LuckyNumberGenerator.cpp -o $(OBJDIR)/LuckyNumberGenerator.o

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
