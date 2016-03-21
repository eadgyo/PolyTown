#ifndef CONSTANT_H
#define CONSTANT_H

#define NULL 0

// ----- Typedef ----- //
typedef unsigned int p_uint;

// ----- Screen ----- //
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define FPS 5

// ----- Keyboard ----- //
#define NUMBER_OF_KEYS 2

#define KEY_CODE_1 SDLK_ESCAPE
#define KEY_CODE_2 SDLK_RETURN

// ----- GameContent ----- //

// Sprites

// Game
#define START_MONEY_AMOUNT 10000

// Housing
#define HOUSING_FOOD_NEEDS 10

#define HOUSE_IMAGE_NAME "link_sprites.png"
#define HOUSE_IMAGE_COLS 10
#define HOUSE_FRAME_WIDTH 120
#define HOUSE_FRAME_HEIGHT 130
#define HOUSE_FRAME_NUMBER 0
#define HOUSE_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250) // !!!
#define HOUSE_NAME "Maison"

#define HOUSE_MAX_INHAB 1
#define HOUSE_WATER_NEEDS 10
#define HOUSE_ENERGY_NEEDS 10

#define LOW_IMPACT_HOUSE_WATER_NEEDS 10
#define LOW_IMPACT_HOUSE_ENERGY_NEEDS 10

#define BUILDING_IMAGE_NAME "link_sprites.png"
#define BUILDING_IMAGE_COLS 10
#define BUILDING_FRAME_WIDTH 120
#define BUILDING_FRAME_HEIGHT 130
#define BUILDING_FRAME_NUMBER 1
#define BUILDING_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250) // !!!
#define BUILDING_NAME "Immeuble"

#define BUILDING_MAX_INHAB_PER_FLOOR 1
#define BUILDING_WATER_NEEDS 10
#define BUILDING_ENERGY_NEEDS 10
#define BUILDING_FLOOR 2
#define BUILDING_MAX_FLOOR 5

#define LOW_IMPACT_BUILDING_WATER_NEEDS 10
#define LOW_IMPACT_BUILDING_ENERGY_NEEDS 10

// SocialBuilding
#define SCHOOL_IMAGE_NAME "link_sprites.png"
#define SCHOOL_IMAGE_COLS 10
#define SCHOOL_FRAME_WIDTH 120
#define SCHOOL_FRAME_HEIGHT 130
#define SCHOOL_FRAME_NUMBER 1
#define SCHOOL_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250) // !!!
#define SCHOOL_NAME "Ecole"

#define SCHOOL_SCORE 0
#define SCHOOL_RATIO 0.1f
#define SCHOOL_RADIUS 0.1f

#define HOSPITAL_IMAGE_NAME "link_sprites.png"
#define HOSPITAL_IMAGE_COLS 10
#define HOSPITAL_FRAME_WIDTH 120
#define HOSPITAL_FRAME_HEIGHT 130
#define HOSPITAL_FRAME_NUMBER 1
#define HOSPITAL_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250) // !!!
#define HOSPITAL_NAME "Hôpital"

#define HOSPITAL_SCORE 0
#define HOSPITAL_RATIO 0.1f
#define HOSPITAL_RADIUS 0.1f


#define FIRE_STATION_IMAGE_NAME "link_sprites.png"
#define FIRE_STATION_IMAGE_COLS 10
#define FIRE_STATION_FRAME_WIDTH 120
#define FIRE_STATION_FRAME_HEIGHT 130
#define FIRE_STATION_FRAME_NUMBER 1
#define FIRE_STATION_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250) // !!!
#define FIRE_STATION_NAME "Caserne"

#define FIRE_STATION_SCORE 0
#define FIRE_STATION_RATIO 0.1f
#define FIRE_STATION_RADIUS 0.1f

#define POLICE_STATION_IMAGE_NAME "link_sprites.png"
#define POLICE_STATION_IMAGE_COLS 10
#define POLICE_STATION_FRAME_WIDTH 120
#define POLICE_STATION_FRAME_HEIGHT 130
#define POLICE_STATION_FRAME_NUMBER 1
#define POLICE_STATION_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250) // !!!
#define POLICE_STATION_NAME "Commissariat"

#define POLICE_STATION_SCORE 0
#define POLICE_STATION_RATIO 0.1f
#define POLICE_STATION_RADIUS 0.1f

// Resources

#define POWER_PLANT_IMAGE_NAME "link_sprites.png"
#define POWER_PLANT_IMAGE_COLS 10
#define POWER_PLANT_FRAME_WIDTH 120
#define POWER_PLANT_FRAME_HEIGHT 130
#define POWER_PLANT_FRAME_NUMBER 13
#define POWER_PLANT_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250) // !!!
#define POWER_PLANT_NAME "Centrale"

#define WATER_TOWER_IMAGE_NAME "link_sprites.png"
#define WATER_TOWER_IMAGE_COLS 10
#define WATER_TOWER_FRAME_WIDTH 120
#define WATER_TOWER_FRAME_HEIGHT 130
#define WATER_TOWER_FRAME_NUMBER 13
#define WATER_TOWER_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250) // !!!
#define WATER_TOWER_NAME "Château d'eau"

// Factory
#define SHOP_IMAGE_NAME "link_sprites.png"
#define SHOP_IMAGE_COLS 10
#define SHOP_FRAME_WIDTH 120
#define SHOP_FRAME_HEIGHT 130
#define SHOP_FRAME_NUMBER 10
#define SHOP_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250) // !!!
#define SHOP_NAME "Magasin"

#define SHOP_MAX_WORKERS 0
#define SHOP_INCOME_RATE 0
#define SHOP_ENERGY_NEEDS 0

#define MANUFACTORY_IMAGE_NAME "link_sprites.png"
#define MANUFACTORY_IMAGE_COLS 10
#define MANUFACTORY_FRAME_WIDTH 120
#define MANUFACTORY_FRAME_HEIGHT 130
#define MANUFACTORY_FRAME_NUMBER 11
#define MANUFACTORY_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250) // !!!
#define MANUFACTORY_NAME "Usine"

#define MANUFACTORY_MAX_WORKERS 0
#define MANUFACTORY_INCOME_RATE 0
#define MANUFACTORY_ENERGY_NEEDS 0
#define MANUFACTORY_WATER_NEEDS 0

#define FARM_IMAGE_NAME "link_sprites.png"
#define FARM_IMAGE_COLS 10
#define FARM_FRAME_WIDTH 120
#define FARM_FRAME_HEIGHT 130
#define FARM_FRAME_NUMBER 12
#define FARM_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250) // !!!
#define FARM_NAME "Exploitation agricole"

#define FARM_MAX_WORKERS 0
#define FARM_INCOME_RATE 0
#define FARM_ENERGY_NEEDS 0
#define FARM_OUTPUT_RATE 0

#endif // !CONSTANT_H