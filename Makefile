all:
	g++ -O -w -std=c++11 main.cpp Program.cpp RamMachine.cpp ITape.cpp OTape.cpp Tape.cpp Memory.cpp -o RamMachine
