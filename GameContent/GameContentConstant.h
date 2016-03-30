#pragma once

// Housing
#define HOUSING_FOOD_NEEDS 10
#define HOUSING_INCOME 1000

#define HOUSE_IMAGE_NAME ""
#define HOUSE_IMAGE_COLS 10
#define HOUSE_FRAME_WIDTH 120
#define HOUSE_FRAME_HEIGHT 130
#define HOUSE_FRAME_NUMBER 0
#define HOUSE_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 100, 100)
#define HOUSE_NAME "Maison"

#define HOUSE_COST 1000
#define HOUSE_MAX_INHAB 5
#define HOUSE_WATER_NEEDS 15
#define HOUSE_ENERGY_NEEDS 15

#define LOW_IMPACT8HOUSE_COST 2000
#define LOW_IMPACT_HOUSE_WATER_NEEDS 10
#define LOW_IMPACT_HOUSE_ENERGY_NEEDS 10

#define BUILDING_IMAGE_NAME ""
#define BUILDING_IMAGE_COLS 10
#define BUILDING_FRAME_WIDTH 120
#define BUILDING_FRAME_HEIGHT 130
#define BUILDING_FRAME_NUMBER 0
#define BUILDING_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 150, 150)
#define BUILDING_NAME "Immeuble"

#define BUILDING_COST 5000
#define BUILDING_MAX_INHAB_PER_FLOOR 5
#define BUILDING_WATER_NEEDS 10
#define BUILDING_ENERGY_NEEDS 10
#define BUILDING_FLOOR 5
#define BUILDING_MAX_FLOOR 10

#define LOW_IMPACT_BUILDING_COST 10000
#define LOW_IMPACT_BUILDING_WATER_NEEDS 5
#define LOW_IMPACT_BUILDING_ENERGY_NEEDS 5

// SocialBuilding

#define STADIUM_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 200, 300, (float) (PI*0.5f))
#define STADIUM_NAME "Stade"

#define STADIUM_COST 10000
#define STADIUM_SCORE 10
#define STADIUM_RADIUS 200.0f

#define CINEMA_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 100, 150, (float) (PI*0.5f))
#define CINEMA_NAME "Cin�ma"

#define CINEMA_COST 2000
#define CINEMA_SCORE 10
#define CINEMA_RADIUS 200.0f

#define PARK_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 100, 100)
#define PARK_NAME "Parc"

#define PARK_COST 500
#define PARK_SCORE 10
#define PARK_RADIUS 200.0f

// PoweredSocialBuilding
#define SCHOOL_IMAGE_NAME ""
#define SCHOOL_IMAGE_COLS 10
#define SCHOOL_FRAME_WIDTH 120
#define SCHOOL_FRAME_HEIGHT 130
#define SCHOOL_FRAME_NUMBER 0
#define SCHOOL_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 200, 200)
#define SCHOOL_NAME "�cole"

#define SCHOOL_COST 2000
#define SCHOOL_SCORE 10
#define SCHOOL_RADIUS 200.0f

#define HOSPITAL_IMAGE_NAME ""
#define HOSPITAL_IMAGE_COLS 10
#define HOSPITAL_FRAME_WIDTH 120
#define HOSPITAL_FRAME_HEIGHT 130
#define HOSPITAL_FRAME_NUMBER 1
#define HOSPITAL_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 200, 200)
#define HOSPITAL_NAME "H�pital"

#define HOSPITAL_COST 2000
#define HOSPITAL_SCORE 10
#define HOSPITAL_RADIUS 200.0f

#define FIRE_STATION_IMAGE_NAME ""
#define FIRE_STATION_IMAGE_COLS 10
#define FIRE_STATION_FRAME_WIDTH 120
#define FIRE_STATION_FRAME_HEIGHT 130
#define FIRE_STATION_FRAME_NUMBER 1
#define FIRE_STATION_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 200, 200)
#define FIRE_STATION_NAME "Caserne"

#define FIRE_STATION_COST 2000
#define FIRE_STATION_SCORE 10
#define FIRE_STATION_RADIUS 200.0f

#define POLICE_STATION_IMAGE_NAME ""
#define POLICE_STATION_IMAGE_COLS 10
#define POLICE_STATION_FRAME_WIDTH 120
#define POLICE_STATION_FRAME_HEIGHT 130
#define POLICE_STATION_FRAME_NUMBER 1
#define POLICE_STATION_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 200, 200)
#define POLICE_STATION_NAME "Commissariat"

#define POLICE_STATION_COST 2000
#define POLICE_STATION_SCORE 10
#define POLICE_STATION_RADIUS 200.0f

// Factory
#define SHOP_IMAGE_NAME ""
#define SHOP_IMAGE_COLS 10
#define SHOP_FRAME_WIDTH 120
#define SHOP_FRAME_HEIGHT 130
#define SHOP_FRAME_NUMBER 10
#define SHOP_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 150, 150)
#define SHOP_NAME "Magasin"

#define SHOP_COST 2000
#define SHOP_MAX_WORKERS 20
#define SHOP_INCOME_RATE 10
#define SHOP_ENERGY_NEEDS 5

#define MANUFACTORY_IMAGE_NAME ""
#define MANUFACTORY_IMAGE_COLS 10
#define MANUFACTORY_FRAME_WIDTH 120
#define MANUFACTORY_FRAME_HEIGHT 130
#define MANUFACTORY_FRAME_NUMBER 11
#define MANUFACTORY_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 200, 200)
#define MANUFACTORY_NAME "Usine"

#define MANUFACTORY_COST 2000
#define MANUFACTORY_MAX_WORKERS 50
#define MANUFACTORY_INCOME_RATE 10
#define MANUFACTORY_ENERGY_NEEDS 10
#define MANUFACTORY_WATER_NEEDS 10

#define FARM_IMAGE_NAME ""
#define FARM_IMAGE_COLS 10
#define FARM_FRAME_WIDTH 120
#define FARM_FRAME_HEIGHT 130
#define FARM_FRAME_NUMBER 12
#define FARM_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 400, 400)
#define FARM_NAME "Exploitation agricole"

#define FARM_COST 2000
#define FARM_MAX_WORKERS 10
#define FARM_INCOME_RATE 10
#define FARM_WATER_NEEDS 10
#define FARM_OUTPUT_RATE 100

// Resources
#define POWER_PLANT_IMAGE_NAME ""
#define POWER_PLANT_IMAGE_COLS 10
#define POWER_PLANT_FRAME_WIDTH 120
#define POWER_PLANT_FRAME_HEIGHT 130
#define POWER_PLANT_FRAME_NUMBER 13
#define POWER_PLANT_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 200, 200)
#define POWER_PLANT_NAME "Elect Gen"

#define POWER_PLANT_COST 10000
#define POWER_PLANT_OUTPUT 10000
#define POWER_PLANT_RADIUS 2000.0f

#define WATER_TOWER_IMAGE_NAME ""
#define WATER_TOWER_IMAGE_COLS 10
#define WATER_TOWER_FRAME_WIDTH 120
#define WATER_TOWER_FRAME_HEIGHT 130
#define WATER_TOWER_FRAME_NUMBER 13
#define WATER_TOWER_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 100, 100)
#define WATER_TOWER_NAME "Ch�teau d'eau"

#define WATER_TOWER_COST 10000
#define WATER_TOWER_OUTPUT 10000
#define WATER_TOWER_RADIUS 2000.0f

// Polution

#define WATER_POLLUTION 100
#define WATER_POLLUTION_DECREASE_RATE 2

#define AIR_POLLUTION 150
#define AIR_POLLUTION_DECREASE_RATE 3