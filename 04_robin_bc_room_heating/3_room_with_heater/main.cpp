#include "Header_Case.h" // needed for case functions/structs
#include "Header_Mesh.h" // needed for mush functions/structs
#include "Header_matrix.h" //need for initalizing/building A and RHS
#include "Header_EigenSolve.h" // needed for solver (EigenSolve)
#include "Header_ScaSF.h" // needed for flux/phi stuff
#include "Header_Robin.h" // needed for BC 

int main()
{

	caseType Case;		//declare case
	Case.read();
	Case.disp();

	meshType Mesh; 
	Mesh.read();
	//std::cout << "here" << std::endl;
	Mesh.disp();
	//std::cout << "here" << std::endl;
	Mesh.create();
	//std::cout << "here" << std::endl;
	Mesh.write();
	//std::cout << "here" << std::endl;


	matrixType A;
	matrixType RHS;

	BC BC;
	BC.read(); //read BC inputs
	BC.disp(); //display BC inputs
	
	
	
	
	A.init(Mesh);
	RHS.init(Mesh);

	surfaceScalarField Flux;
	Flux.allocate(Mesh);
	Flux.ComputePhix(Mesh, Case);
	Flux.ComputePhiy(Mesh, Case);

	A.BuildA(Mesh, Case, Flux, BC);
	RHS.BuildRHS(Mesh, Case, BC);

	int flag = EigenSolve(A, RHS);
	
	return flag;
}
