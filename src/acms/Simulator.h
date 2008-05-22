/**
 * \file		acms/Simulator.h
 * \brief		The definition of the <b>Simulator</b> class.
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

#include "config.h"

#include "Process.h"

#ifndef SIMULATOR_H
#define SIMULATOR_H

/**
 * \class	Simulator Simulator.h
 * \brief	The <b>Simulator</b> class.
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	June, 2004
 * 
 * The <b>Simulator</b> class. This class defines the mechanisms to simulate a
 * process.
 */
class Simulator {
	
	public:
		
		/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		 * Public attributes.
		 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
		
		/** The process that will be simulated. */
		Process *ACM;
		
		/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		 * Public methods prototypes.
		 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
		 
		Simulator(char *filename);
		Simulator(Process p);
		~Simulator();
		
		void Sim(int n);
};
#endif /* SIMULATOR_H */
