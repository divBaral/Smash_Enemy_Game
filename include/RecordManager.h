/****
 * 
 * writes and reads the history/progress of players to and from a file in hard disk
 * 
 ****/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

enum { L1 , L2, L3, L4, L5, L6 };

class User 
{
public:
	User()
	{
		for ( unsigned i=0; i<total_levels; ++i)
			score[i] = 0;

		max_score[L1] = 3000;
		max_score[L2] = 3000;
		max_score[L3] = 4000;
		max_score[L4] = 4000;
		max_score[L5] = 3000;
		max_score[L6] = 3000;

	}
	
	void updateUserData(std::string name, unsigned  level=1, unsigned long s=0)
	{
		username = name;
		score[level-1] = s;
		saveUserData();
	}

	int savedLevels(std::string name)
	{
		int val;
		username = name;
		
		val = accessUserData();

		if( val == 0 ) return 1; //if username doesn't match start from level 1
		else if( val == 5 ) return 6; //if all the levels were completed
		return (val+1); //else start from the last completed level
	}
	
private:
	void saveUserData()
	{
		bool found = false;

		std::ofstream temp_file;
		record_file.open("userInfo/record.txt");
		temp_file.open("userInfo/temp.txt");

		temp_file.setf(std::ios::left);
		std::string line;

		if( !temp_file )
		{
			std::cerr << "Unable to create a temp file in unserInfo/\n";
		}
		else
		{
			if ( !record_file )
			{
				temp_file << std::setw(16) << "Name" << std::setw(8) << "Level1" << std::setw(8) 
				<< "Level2" << std::setw(8) << "Level3" << std::setw(8) << "Level4" << std::setw(8) 
				<< "Level5" << std::setw(8) << "Level6" << std::endl;
			}
			else 
			{
				getline(record_file, line);
				if( !(line.length() > 0) )
				{
					temp_file << std::setw(16) << "Name" << std::setw(8) << "Level1" << std::setw(8) 
					<< "Level2" << std::setw(8) << "Level3" << std::setw(8) << "Level4" << std::setw(8) 
					<< "Level5" << std::setw(8) << "Level6" << std::endl;
				}
				else
				{
					temp_file << line << std::endl;
				}
			}

			std::stringstream linestream;
			std::string word;

			unsigned long temp_score[total_levels];

			while( getline(record_file, line) )
			{
				linestream.str("");
				linestream << line;
				linestream >> word; //first word of the line

				//if username is found on the progress report
				if (  word == username  )
				{
					temp_file << std::setw(16)<< username ;

					for ( unsigned i =0; i < total_levels; ++i)
					{

						linestream >> temp_score[i];

						if ( temp_score[i] > score[i])
							score[i] = temp_score[i];

						temp_file << std::setw(8) << score[i] ;
								
					}
					temp_file << std::endl;
					found = true;

				}
				else 
				{
					temp_file << line << std::endl;
				}
			}
			if (!found)
			{
				temp_file << std::setw(16)<< username ;

				for ( unsigned i =0; i < total_levels; ++i) 
				{
							
					temp_file  << std::setw(8) << score[i] ;
							
				}
				temp_file << std::endl;
			}
				

			if( record_file )record_file.close();
			temp_file.close();
			
			if ( record_file && remove("userInfo/record.txt") != 0 )
				std::cerr << "\"userInfo/record.txt\"remove failed\n";
			else
				rename("userInfo/temp.txt", "userInfo/record.txt");

		}
	}	

	int accessUserData()
	{
		record_file.open("userInfo/record.txt");
		
		if( record_file )
		{	
			std::string line;
			std::stringstream linestream;
			std::string word;
			bool found = false;
			//reads the header row of the report/table
			getline(record_file, line);

			unsigned long temp_score[total_levels];
			
			//start reading lines from the second line in the file
			while( getline(record_file, line) )
			{
				linestream.str("");
				linestream << line;
				linestream >> word; //first word of the line

				//if username matches
				if (  word == username  )
				{

					for ( unsigned i = 0; i < total_levels; ++i)
					{

						linestream >> temp_score[i];

						if( (temp_score[i] > 0) && (temp_score[i] < max_score[i]) )
						{
							return i;//continue from the same level
						}
						else if( temp_score[i] == 0 )//return the level( levelcount ) whose score is zero
						{
							return i; 
						}	
					}

					found = true;
					break;
				}
			}
			if( !found ) //if username doesn't exist
			{
				return L1;
			}

			record_file.close();

			//Only remaining condition is: if found and all the levels were completed
			return ( total_levels - 1 );//total levels = 6 and our array counting starts from 0
		}

		//if file doesn't exist
		return L1;
	}



	// private data members
	std::ifstream record_file;
	std::string username;
	static const unsigned  total_levels = 6;
	unsigned long score[total_levels];
	unsigned long max_score[total_levels];
};