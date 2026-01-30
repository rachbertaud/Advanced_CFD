build_HW1: HW1.cpp 
	g++ -o run_HW1 HW1.cpp

HW1: build_HW1 #info after : declares dependancies
	./run_HW1 10
	./run_HW1 50
	./run_HW1 100

clean: 
	rm -f run_HW1 
