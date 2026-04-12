build:
#	g++ -o main main.cpp funcs_*.cpp -I/Users/rachelbertaud/code/eigen-5.0.0 
	g++ -o main_SE main_SE.cpp funcs_*.cpp -I/Users/rachelbertaud/code/eigen-5.0.0 
	g++ -o main_TE main_TE.cpp funcs_*.cpp -I/Users/rachelbertaud/code/eigen-5.0.0 


run:
	./SeSubmit.sh
	./TeSubmit.sh
	python3 plot.py
clean: 
	rm -f main
	rm -f main_SE
	rm -f main_TE
	rm -f xc*
	rm -f yc*
	#rm -f c*
	rm -f T_*
	rm -f *.csv
	rm -f *.png
