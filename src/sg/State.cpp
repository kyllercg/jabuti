/**
 * \file		sg/State.cpp
 * \brief		The methods of the <b>State</b> class.
 * \author		Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date		May, 2004
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
 * 
 */

using namespace std;

#include "State.h"

#include <iostream>

/**
 * \brief	Class constructor. Creates a new <b>State</b> element.
 * 
 * \fn		State::State(const char *lab, int trg)
 * \param	*lab: the label of the state.
 * \param	trg: the target of the state.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	14/06/2004
 */
State::State(const char *lab, int trg)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " State()" << endl;
	#endif
	
	label = lab;
	target = trg;
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /State()" << endl;
	#endif
}

/**
 * \brief	Class destructor.
 * 
 * \fn		State::~State()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/05/2004
 */
State::~State()
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " ~State()" << endl;
	#endif
}

/**
 * \brief	Gets the label of the state.
 * 
 * \fn		string State::getLabel()
 * \return	A string with the label of the state.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/05/2004
 */
string State::getLabel()
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " getLabel()" << endl;
	#endif
	
	return(label);
}

/**
 * \brief	Gets the target of the state.
 * 
 * \fn		int State::getTarget()
 * \return	An integer with the target of the state.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/05/2004
 */
int State::getTarget()
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " getTarget()" << endl;
	#endif
	
	return(target);
}

/**
 * \brief	Sets the label of the state.
 * 
 * \fn		void State::setLabel(const char *lab)
 * \param	*lab: the new label of the state.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/05/2004
 */
void State::setLabel(const char *lab)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " setLabel()" << endl;
	#endif
	
	string aux = lab;
	label.swap(aux);
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setLabel()" << endl;
	#endif
}
