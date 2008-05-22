/**
 * \file		petri/Place.h
 * \brief		The definition of the <b>Place</b> class.
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

#ifndef PLACE_H
#define PLACE_H

/**
 * \class	Place Place.h
 * \brief	The <b>Place</b> class.
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	January, 2005
 * 
 * The <b>Place</b> class. This class defines the data structure to store a
 * <b>place</b> element in the main memory.
 */
class Place {
	
	public:
		
		Place();
		Place(string l, int t);
		~Place();
		
		string getLabel();
		int getTarget();
		int getTokens();
		vector<int> getIn();
		vector<int> getOut();
		
		void setTokens(int n);
		
		bool existsIn(int n);
		bool existsOut(int n);
		
		void addIn(int n);
		void addOut(int n);
		
	private:
		
		/** The label of place. */
		string label;
		
		/** The target of place. */
		int target;
		
		/** The number of tokens stored in the place. */
		int tokens;
		
		/** The set of input transitions. */
		vector<int> in;
		
		/** The set of output transitions. */
		vector<int> out;
};

#endif /* PLACE_H */
