
proc_fan: proc_fan.o 
	g++ -o proc_fan proc_fan.o 

proc_fan.o: proc_fan.cpp
	g++ -c proc_fan.cpp

clean: 
	rm *.o proc_fan
