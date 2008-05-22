/**
 * \file		petri/Transition.h
 * \brief		The definition of the <b>Transition</b> class.
 * \author		Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date		January, 2005
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

#include <string>
#include <vector>

#ifndef TRANSITION_H
#define TRANSITION_H

/**
 * \class	Transition Transition.h
 * \brief	The <b>Place</b> class.
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	January, 2005
 * 
 * The <b>Transition</b> class. This class defines the data structure to store a
 * <b>transition</b> element in the main memory.
 */
class Transition {
	
	public:
		
		Transition();
		Transition(string lab, int typ, int tar);
		~Transition();
		
		string getLabel();
		int getTarget();
		int getType();
		vector<int> getIn();
		vector<int> getOut();
		
		bool existsIn(int n);
		bool existsOut(int n);
		
		void addIn(int n);
		void addOut(int n);
		
	private:
		
		/** The label of the transition. */
		string label;
		
		/** The target of the transition. */
		int target;
		
		/** The type of the transition. */
		int type;
		
		/** The set of input places. */
		vector<int> in;
		
		/** The set of output places. */
		vector<int> out;
};

#endif /* TRANSITION_H */
