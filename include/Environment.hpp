#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include <string>

namespace Env
{
	extern const std::string CCP4M_DIR;
	extern const std::string CCP4M_CONFIG_FILE;
	extern const std::string CCP4M_LICENSE_DIR;
	extern const std::string CCP4M_LOG_DIR;

	extern const std::string CCP4M_PROJECT_CONFIG_FILE;

	extern const std::string LICENSE_URL;

	std::string GetEnvVar( const std::string & key );

	bool SetCurrentDir( const std::string & dir );
	std::string GetCurrentDir();

	std::vector< std::string > GetEnvPathVec();

	void ReplaceTildeWithHome( std::string & str );
}

#endif // ENVIRONMENT_HPP