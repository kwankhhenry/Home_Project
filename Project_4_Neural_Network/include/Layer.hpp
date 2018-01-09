#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include <iostream>
#include <vector>
#include "Neuron.hpp"

using namespace std;

class Layer
{
	public:
        Layer(int size);
		void layer::setVal(int i, double v); 
		
	private:
        int size;

        vector<Neuron *> neurons;
};
#endif
