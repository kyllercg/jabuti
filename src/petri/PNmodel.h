/**
 * \file		petri/PNmodel.h
 * \brief		The definition of the <b>PNmodel</b> class.
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

#include "Place.h"
#include "Transition.h"

#include <string>
#include <vector>

#ifndef PNMODEL_H
#define PNMODEL_H

/** Internal code for <b>place</b>. */
#define _PN_P									1

/** Internal code for <b>transition</b>. */
#define _PN_T									2

/** Internal code for <code>.output</code> transition. */
#define _PN_T_OUTPUTS							1

/** Internal code for <code>.internal</code> transition. */
#define _PN_T_INTERNAL							2

/** Internal code for <code>.dummy</code> transition. */
#define _PN_T_DUMMY								3

/** Error code: <b>label</b> not found. */
#define _PN_ERROR_CODE_NOT_FOUND				-10

/** Error code: <b>label</b> not inserted before. */
#define _PN_ERROR_CODE_NOT_INSERTED				-20

/**
 * \class	PNmodel PNmodel.h
 * \brief	The <b>PNmodel</b> class.
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	January, 2005
 * 
 * The <b>PNmodel</b> class. This class defines the data structure to store a
 * <b>Petri Net</b> model in the main memory.
 */
class PNmodel {
	
	public:
		
		PNmodel();
		~PNmodel();
		
		string getLabel();
		string getPlaceLabel(int t);
		string getTransitionLabel(int t);
		vector<int> getPlaces();
		vector<int> getTransitions();
		vector<string> getTransitions(int t);
		vector<int> getOutPlaces(int t);
		vector<int> getOutTransitions(int t);
		int getTokens(int t);
		
		void setLabel(string l);
		void setLabel(const char *l);
		void setTokens(string l, int n);
		void setTokens(int t, int n);
		
		void insertArc(int src, int dest, int stype);
		int insertPlace(string l);
		int insertTransition(string l, int t);
		
		int existsPlace(string l);
		int existsTransition(string l);
		
		int typeOf(string l);
		
	private:
		
		/** The set of places. */
		vector<Place *> P;
		
		/** The set of transitions. */
		vector<Transition *> T;
		
		/** The label of the model. */
		string label;
};

#endif /* PNMODEL_H */
