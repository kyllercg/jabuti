/**
 * \file		acms/Simulator.cpp
 * \brief		The methods of the <b>Simulator</b> class.
 * \author		Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date		June, 2004
 * \version		$Id$
 * 
 * Copyright (C) 2004, 2008 - Kyller Costa Gorgônio
 * Copyright (C) 2004, 2008 - Universitat Politècnica de Catalunya
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

using namespace std;

#include "Simulator.h"

#include <iostream>
#include <vector>

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * CLASS CONSTRUCTORS / DESTRUCTOR
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * \brief	Class constructor. Creates a new <b>Simulator</b> element.
 * 
 * \fn		Simulator::Simulator(char *filename)
 * \param	*filename: the name of the file containing a description of a 
 * 			process in the <b>Petrify</b> language.
 * 
 * Using this constructor, it will necessary to parse the input file and reads
 * its contents to the main memory.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	22/09/2004
 */
Simulator::Simulator(char *filename)
{
	cout << "TODO: need to implement this!" << endl;
}

/**
 * \brief	Class constructor. Creates a new <b>Simulator</b> element.
 * 
 * \fn		Simulator::Simulator(Process p)
 * \param	p: a process that is in the main memory.
 * 
 * Using this constructor, the process to be simulated is already in the main
 * memory, and it is not necessary to load it before simulating.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	22/09/2004
 */
Simulator::Simulator(Process p)
{
	ACM = &p;
}

/**
 * \brief	Class destructor.
 * 
 * \fn		Simulator::~Simulator()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	22/09/2004
 */
Simulator::~Simulator()
{}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * PUBLIC METHODS
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * \brief	The simulation method.
 * 
 * \fn		void Simulator::Sim(int n)
 * \param	n: number of steps to execute.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	27/09/2004
 */
void Simulator::Sim(int n)
{
	int state = 0;
	int succ;
	vector<int> vsucc;
	
	for (int cont = 0; cont < n; cont++) {
		
		vsucc.clear();
		vsucc = ACM->getSuccessors(state);
		succ = int(vsucc.size() * rand() / (RAND_MAX + 1.0));
		
		cout << ACM->getLabel(state, vsucc[succ]) << endl;
		
		state = vsucc[succ];
	}
}
