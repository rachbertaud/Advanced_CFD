#include <iostream> // needed for cout
#include "Header_Case.h" // needed for the functions
#include "Header_Mesh.h"
#include "Header_Build.h"
#include "Header_EigenSolve.h"

int main()
{

	caseType Case;		//declare case
	readCase(Case);
	dispCase(Case);

	meshType Mesh; 
	readMesh(Mesh);
	dispMesh(Mesh);
	createMesh(Mesh);
	writeMesh(Mesh);


	matrixType A;
	matrixType RHS;
	
	A.init(Mesh);
	RHS.init(Mesh);

	BuildA(A, Mesh, Case);
	BuildRHS(RHS, Mesh, Case);

	int flag = EigenSolve(A, RHS);
	
	return flag;
}
