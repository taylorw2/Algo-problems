#include<tr1/array>
#include "point_multiset.hpp"
#include "neighbor_iterator.hpp"
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <math.h>
#include "metric.hpp"
#include <fstream>

#define pi 3.14159265358979323846 
using namespace spatial;

const std::string FILENAME = "airport-locations.txt";

int main(){
	struct coord{
		double lat;
		double lon;
		std::string aircode;
		std::string airName;
	};
	
	struct coord_acc
	{
		int operator() (spatial::dimension_type dim, const coord c) const
		{
			switch(dim)
			{
				case 0: return c.lat;
				case 1: return c.lon;
				default: throw std::out_of_range("dim");
			}
		}
	};
	
	struct guacMet 
	{
		/*::*/ /*::  This function converts decimal degrees to radians:*/ /*::*/
		double deg2rad(double deg) const
		{
			return (deg * pi / 180); 
		} 
		/*::*/ /*::  This function converts radians to decimal degrees:*/ /*::*/
		double rad2deg(double rad) const
		{
			return (rad * 180 / pi);
		}
 
		double getDistance(double lat1, double lon1, double lat2, double lon2, char unit) const
		{   
		 double theta, dist;
		 theta = lon1 - lon2;
		 dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) *
			cos(deg2rad(lat2)) * cos(deg2rad(theta));
		 dist = acos(dist);
		 dist = rad2deg(dist);
		 dist = dist * 60 * 1.1515;
		 switch(unit) {
			 case 'M':
				break;
			case 'K':
				dist = dist * 1.609344;
				break;
			case 'N':
				dist = dist * 0.8684;
				break; 
			}
			return (dist);
		} 

		typedef double distance_type; //[1]	
		/*double
		distance_to_key(dimension_type rank,
		const coord& origin, const coord& key) const; //[2], [4]
		
		double
		distance_to_plane(dimension_type rank, dimension_type dim,
		const coord& origin, const coord& key) const; //[3],[4]
		*/
		
		double distance_to_plane(dimension_type rank, dimension_type dim,
		const coord& origin, const coord& key) const{
			return 0.0;
		}
		
		double distance_to_key(dimension_type rank,
		const coord& origin, const coord& key) const{
			//distance_type distance;
			//distance = getDistance(origin.lat, origin.lon, key.lat, key.lon, 'M');
			return getDistance(origin.lat, origin.lon, key.lat, key.lon, 'M');
			
		}
	};
	
	//typedef std::tr1::array<double,2> coord;
	typedef spatial::point_multiset<2, coord, 
		spatial::accessor_less<coord_acc, coord>> tree;
	tree container;
	guacMet metric;
	int count = 0;
	std::string line;
	std::string word;
	std::string sentence;
	std::ifstream infile;
	coord* ptr;
	infile.open(FILENAME);
	getline(infile,line); //reads the title line from the file
	while(getline(infile,line)){
		std::stringstream s(line);
		ptr = new coord;
		count = 0;
		while(s>>word && count < 3){
			switch(count){
				case 0:
					ptr->aircode = word;
					break;
				case 1:
					ptr->lat = atof(word.c_str());
					break;
				case 2:
					ptr->lon = atof(word.c_str());
					break;
			}
			count++;
		}
		if(count >=3){
		while(s>>sentence){
			word = word + ' ' + sentence;
		}
		ptr->airName = word;
		}
		container.insert(*ptr);
		delete ptr;
	}
	coord target;
	target.lat = 32.88;
	target.lon = -87.23;	
	std::cout << container.size() << std::endl;
    neighbor_iterator<tree, guacMet> iter = neighbor_begin(container, metric, target);
	std::cout << (*iter).lat  <<" , " <<  (*iter).lon <<"  , "
		<< distance(iter)<<std::endl;
	std::cout << (*iter).aircode << std::endl;
	std::cout << (*iter).airName << std::endl;
	++iter;
	/*std::cout << (*iter)[0]  <<" , " <<  (*iter)[1]<< std::endl;
	++iter;
	std::cout << (*iter)[0]  <<" , " <<  (*iter)[1] << std::endl;
	
 	*/
	
	
	
	
	//std::cout << tree.find(orgin);
	return 0;
}