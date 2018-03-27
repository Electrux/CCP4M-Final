#include <vector>
#include <string>

#include "../include/Core.hpp"
#include "../include/Helps.hpp"
#include "../include/FSFuncs.hpp"
#include "../include/Environment.hpp"
#include "../include/DisplayFuncs.hpp"
#include "../include/UTFChars.hpp"

#include "../include/Project/Config.hpp"
#include "../include/Project/BuildBinary.hpp"

#include "../include/ProjectManager.hpp"

int Project::Handle( const std::vector< std::string > & args )
{
	int err_code = 0;

	if( args.size() < 3 ) {
		Helps::Project( args );
		err_code = 0;
	}
	else if( args[ 2 ] == "new" ) {
		//err_code = Project::New( args );
	}
	else if( args[ 2 ] == "build" ) {
		err_code = Build();
	}
	else if( args[ 2 ] == "run" ) {
		//err_code = Project::Run( args );
	}
	else {
		//err_code = Project::HandleFlags( args );
	}

	return 0;
}

int Project::Build()
{
	Core::logger.AddLogSection( "Project" );
	Core::logger.AddLogSection( "Build" );

	if( !FS::LocExists( Env::CCP4M_PROJECT_CONFIG_FILE ) ) {
		std::string currdir = Env::GetCurrentDir();
		Core::logger.AddLogString( LogLevels::ALL, "No project configuration in directory: " + currdir );
		Display( "{fc}Project configuration file: {sc}" + Env::CCP4M_PROJECT_CONFIG_FILE + "{fc} does not exist in this directory.{0}" );
		return Core::ReturnInt( 1 );
	}

	Display( "{fc}Creating build directories {0}...\n\n" );

	if( !FS::CreateDir( "buildfiles" ) || !FS::CreateDir( "lib" ) || !FS::CreateDir( "bin" ) ) {
		Core::logger.AddLogString( LogLevels::ALL, "Unable to create necessary project build directories" );
		Display( "{fc}Unable to create necessary build directories. Exiting. {br}" + UTF::CROSS + "{0}\n" );
		return Core::ReturnInt( 1 );
	}

	ProjectConfig pconf;

	pconf.LoadFile( Env::CCP4M_PROJECT_CONFIG_FILE );

	if( pconf.GetData().name.empty() ) {
		Core::logger.AddLogString( LogLevels::ALL, "No project name! Unable to continue." );
		return Core::ReturnInt( 1 );
	}

	for( int i = 0; i < pconf.GetData().builds.size(); ++i ) {
		if( pconf.GetData().builds[ i ].type == "bin" ) {
			if( Project::BuildBinary( pconf.GetData(), i ) != 0 )
				return Core::ReturnInt( 1 );
		}
		else if( pconf.GetData().builds[ i ].type == "lib" ) {

		}
	}

	pconf.GetData().build_date = Core::GetCurrDateTime();
	pconf.SaveFile( Env::CCP4M_PROJECT_CONFIG_FILE );

	return Core::ReturnInt( 0 );
}