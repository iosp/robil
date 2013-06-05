#ifndef _CONVERTER_C22_H_
#define _CONVERTER_C22_H_

#include "C22_GroundRecognitionAndMapping/C22.h"
#include "C22_GroundRecognitionAndMapping/C22C0_PATH.h"
#include "C0_RobilTask/RobilTask.h"
#include "Map.h"
#include "Gps.h"
#include <C22_transformations/MapTransformations.h>


static AltMap extractMap(const C22_GroundRecognitionAndMapping::C22C0_PATH &res, const MapProperties& prop){
	AltMap::MapCreator m;
	size_t h = res.row.size();
	bool size_ok = false;
	if(h){
		size_t w = res.row.at(0).column.size();
		if(w){

			ROS_INFO(STR("start converting message to alt-map ("<<w<<"x"<<h<<")"));

			size_ok = true;
			m.w=w; m.h=h;
			for(size_t y=0;y<h;y++)
				for(size_t x=0;x<w;x++)
					m.data.push_back(res.row.at(y).column.at(x).height);

			//std::cout<<"finish converting message to map ("<<w<<"x"<<h<<")\n"<<m.map()<<std::endl;
			ROS_INFO("... new data converted");
		}
	}
	if(size_ok==false){
		std::cout<<"size of alt-map is wrong"<<std::endl;
		return AltMap(0,0);
	}
	AltMap result_map = m.map();
	return result_map;
};

static ObsMap extractOccupancyGrid(const C22_GroundRecognitionAndMapping::C22C0_PATH &res, const MapProperties& prop){
	ObsMap::MapCreator m;
	size_t h = res.row.size();
	bool size_ok = false;
	if(h){
		size_t w = res.row.at(0).column.size();
		if(w){

			ROS_INFO(STR("start converting message to map ("<<w<<"x"<<h<<")"));

			size_ok = true;
			m.w=w; m.h=h;
			for(size_t y=0;y<h;y++)
				for(size_t x=0;x<w;x++)
					m.data.push_back(ObsMap::filterObstacles( res.row.at(y).column.at(x).status ));

			//std::cout<<"finish converting message to map ("<<w<<"x"<<h<<")\n"<<m.map()<<std::endl;
			ROS_INFO("... new data converted");
		}
	}
	if(size_ok==false){
		std::cout<<"size of map is wrong"<<std::endl;
		return ObsMap(0,0);
	}
	ObsMap result_map = m.map();
	return result_map;
};
static ObsMap extractTerrainGrid(const C22_GroundRecognitionAndMapping::C22C0_PATH &res, const MapProperties& prop){
	ObsMap::MapCreator m;
	size_t h = res.row.size();
	bool size_ok = false;
	if(h){
		size_t w = res.row.at(0).column.size();
		if(w){

			ROS_INFO(STR("start converting message to map ("<<w<<"x"<<h<<")"));

			size_ok = true;
			m.w=w; m.h=h;
			for(size_t y=0;y<h;y++)
				for(size_t x=0;x<w;x++)
					m.data.push_back(ObsMap::filterTerrain( res.row.at(y).column.at(x).status ));

			//std::cout<<"finish converting message to map ("<<w<<"x"<<h<<")\n"<<m.map()<<std::endl;
			ROS_INFO("... new data converted");
		}
	}
	if(size_ok==false){
		std::cout<<"size of map is wrong"<<std::endl;
		return ObsMap(0,0);
	}
	ObsMap result_map = m.map();
	return result_map;
};

static Gps2Grid extractLocation(const C22_GroundRecognitionAndMapping::C22C0_PATH &res, const MapProperties& prop){
	GPSPoint gps(0,0);
	Waypoint wp(0,0);

	size_t h = res.row.size();
	if(h){

		ROS_INFO("start converting message to location : pos=%f,%f   map offset=%f,%f",
				 (float) res.robotPos.x, (float) res.robotPos.y, (float) res.xOffset, (float) res.yOffset);
		//size_t w = res.drivingPath.row.at(0).column.size();

		C22_transform trans;
//		wp.x=( res.robotPos.x - res.xOffset )/ prop.resolution;
//		wp.y=( res.robotPos.y - res.yOffset )/ prop.resolution;
		trans.GlobalToMap(res, res.robotPos, wp);

		gps.x = res.robotPos.x;
		gps.y = res.robotPos.y;
		gps.heaidng = res.robotOri.z;

		ROS_INFO("... new data converted : gps point = %f,%f  related to  grid cell = %i,%i", (float) gps.x, (float) gps.y, (int) wp.x, (int) wp.y);
	}
	return Gps2Grid(gps,wp);
};

static MapProperties extractMapProperties(const C22_GroundRecognitionAndMapping::C22C0_PATH &res){
	GPSPoint gps(0,0);
	Waypoint wp(0,0);
	double cell_resolution_in_meters = 0;

	size_t h = res.row.size();
	if(h){
		ROS_INFO("start converting message to MapProperties : map offset=%f,%f", res.xOffset, res.yOffset);
		//size_t w = res.row.at(0).column.size();
		//wp.x = w/2;

		wp.y = 0;
		wp.x = 0;

		gps.x = res.xOffset;
		gps.y = res.yOffset;
		gps.heaidng = 0; // gotten map is a local window of global map with constant orientation to 0 (north)

		cell_resolution_in_meters = 0.25;

		ROS_INFO("... new data converted : new map anchor is ( cell = 0,0 gps = %f,%f )",  gps.x, gps.y);
	}
	return MapProperties(cell_resolution_in_meters, gps, wp);
};

//=================== from service ===============================

static AltMap extractMap(C22_GroundRecognitionAndMapping::C22::Response &res, const MapProperties& prop){
	return extractMap(res.drivingPath, prop);
};
static ObsMap extractOccupancyGrid(C22_GroundRecognitionAndMapping::C22::Response &res, const MapProperties& prop){
	return extractOccupancyGrid(res.drivingPath, prop);
};
static ObsMap extractTerrainGrid(C22_GroundRecognitionAndMapping::C22::Response &res, const MapProperties& prop){
	return extractTerrainGrid(res.drivingPath, prop);
};


static Gps2Grid extractLocation(C22_GroundRecognitionAndMapping::C22::Response &res, const MapProperties& prop){
	return extractLocation(res.drivingPath, prop);
};

static MapProperties extractMapProperties(C22_GroundRecognitionAndMapping::C22::Response &res){
	return extractMapProperties(res.drivingPath);
};


#endif
