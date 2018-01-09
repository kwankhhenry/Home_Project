#include <iostream>
#include "../include/Neuron.hpp"
#include "../include/Matrix.hpp"

using namespace std;

int main(int argc, char **argv){
	Neuron *n = new Neuron(1.5);

    cout << "Val: " << n->getVal() << endl;
    cout << "Activated Val: " << n->getActivatedVal() << endl;
    cout << "Derived Val: " << n->getDerivedVal() << endl;

    Matrix *m = new Matrix(3, 2, true);
    m->printToConsole();

    cout << "-------------" << endl;

    Matrix *mT = m->transpose();
    mT->printToConsole();

	return 0;
}
