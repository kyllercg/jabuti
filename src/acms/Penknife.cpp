/**
 * \file		acms/Penknife.cpp
 * \brief		The methods of the <b>Penknife</b> class.
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

#include "Penknife.h"

#include <iostream>

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * PUBLIC METHODS
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * \brief	Class constructor. Creates a new <b>Penknife</b> element.
 * 
 * \fn		Penknife::Penknife()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
Penknife::Penknife()
{}

/**
 * \brief	Class destructor.
 * 
 * \fn		Penknife::~Penknife()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
Penknife::~Penknife()
{}

/**
 * \brief       Prints an error message.
 * 
 * \fn          static void Penknife::pkerrors(char *m)
 * \param       *m: error message.
 * 
 * \author      Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date        10/06/2004
 */
void Penknife::pkerrors(char *m)
{
	cerr << m << endl;
}

/**
 * \brief       Prints an error message.
 * 
 * \fn          static void Penknife::pkerrors(char *m, char *f)
 * \param       *m: error message.
 * \param       *f: identifier related to the error.
 * 
 * \author      Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date        10/06/2004
 */
void Penknife::pkerrors(char *m, char *f)
{
	cerr << m << " <" << f << ">" << endl;
}
