/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.
	
	Please read that file and understand the license terms
	before using or altering the project.
*/

#ifndef PROJECT_BUILD_TEST_HPP
#define PROJECT_BUILD_TEST_HPP

#include "Config.hpp"

namespace Project
{
	int BuildTest( const Config::ProjectData & data, const int data_i, const bool disp_cmds_only = false );
}

#endif // PROJECT_BUILD_TEST_HPP