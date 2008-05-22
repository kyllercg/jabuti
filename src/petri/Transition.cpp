/**
 * \file		petri/Transition.cpp
 * \brief		The methods of the <b>Transition</b> class.
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

#include "Transition.h"

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * CLASS CONSTRUCTORS / DESTRUCTOR
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * \brief	Class constructor. Creates a new Transition object.
 * 
 * \fn		Transition::Transition()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
Transition::Transition()
{}

/**
 * \brief	Class constructor. Creates a new Transition object.
 * 
 * \fn		Transition::Transition(string lab, int typ, int tar)
 * \param	lab: the label of the new transition.
 * \param	typ: the type of event modeled by the new transition.
 * \param	tar: the target of the new transition.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
Transition::Transition(string lab, int typ, int tar)
{
	label = lab;
	type = typ;
	target = tar;
}

/**
 * \brief	Class destructor.
 * 
 * \fn		Transition::~Transition()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
Transition::~Transition()
{}

/**
 * \brief	Gets the label of the transition.
 * 
 * \fn		string Transition::getLabel()
 * \return	a string with the label of the transition.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
string Transition::getLabel()
{
	return label;
}

/**
 * \brief	Gets the target of the transition.
 * 
 * \fn		int Transition::getTarget()
 * \return	an integer with the target of the transition.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
int Transition::getTarget()
{
	return target;
}

/**
 * \brief	Gets the type of the event modeled byt the transition.
 * 
 * \fn		int Transition::getType()
 * \return	an integer with the type of the event modeled byt the transition.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
int Transition::getType()
{
	return type;
}

/**
 * \brief	Gets the targets of all input places of the transition.
 * 
 * \fn		vector<int> Transition::getIn()
 * \return	a vector with the targets of all input places.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
vector<int> Transition::getIn()
{
	return in;
}

/**
 * \brief	Gets the targets of all output places of the transition.
 * 
 * \fn		vector<int> Transition::getOut()
 * \return	a vector with the targets of all output places.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
vector<int> Transition::getOut()
{
	return out;
}

/**
 * \brief	Checks if a given input place target is already inserted.
 * 
 * \fn		bool Transition::existsIn(int n)
 * \param	n: the target of the place to be checked.
 * \return	<b><code>true</code></b> if the target is present in the 
 * 			<code>in</code> vector. <b><code>false</code></b> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
bool Transition::existsIn(int n)
{
	vector<int>::iterator i = in.begin();
	
	while (i != in.end()) {
		
		if (*i == n) {
			
			return true;
		}
	}
	
	return false;
}

/**
 * \brief	Checks if a given output place target is already inserted.
 * 
 * \fn		bool Transition::existsOut(int n)
 * \param	n: the target of the place to be checked.
 * \return	<b><code>true</code></b> if the target is present in the 
 * 			<code>out</code> vector. <b><code>false</code></b> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
bool Transition::existsOut(int n)
{
	vector<int>::iterator i = out.begin();
	
	while (i != in.end()) {
		
		if (*i == n) {
			
			return true;
		}
	}
	
	return false;
}

/**
 * \brief	Adds a new input place to the transition.
 * 
 * \fn		void Transition::addIn(int n)
 * \param	n: the target of the input place.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
void Transition::addIn(int n)
{
	in.push_back(n);
}

/**
 * \brief	Adds a new output place to the transition.
 * 
 * \fn		void Transition::addOut(int n)
 * \param	n: the target of the output place.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/01/2005
 */
void Transition::addOut(int n)
{
	out.push_back(n);
}
