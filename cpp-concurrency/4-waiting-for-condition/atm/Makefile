CXX = g++
CXXFLAGS = -std=c++17 -pthread -Wall

atm: main.cpp message/message.h atm.cpp bank.cpp ui.cpp
	$(CXX) $(CXXFLAGS) -o atm main.cpp

clean:
	rm -f atm

.PHONY: clean
