#ifndef CONSTANT_H
#define CONSTANT_H

#define NULL 0

// ----- Typedef ----- //
typedef unsigned int p_uint;

// ----- Screen ----- //
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// ----- Keyboard ----- //
#define NUMBER_OF_KEYS 2

#define KEY_CODE_1 SDLK_ESCAPE
#define KEY_CODE_2 SDLK_RETURN

// ----- GameContent ----- //

// Sprites

// Housing
#define HOUSING_FOOD_NEEDS 10

#define HOUSE_IMAGE_NAME "link_sprites.png"
#define HOUSE_IMAGE_COLS 10
#define HOUSE_FRAME_WIDTH 120
#define HOUSE_FRAME_HEIGHT 130
#define HOUSE_FRAME_NUMBER 0
#define HOUSE_RECTANGLE(x, y) myRectangle(Vector3D(x, y), 250, 250)
#define HOUSE_NAME "Maison"
#define HOUSE_MAX_INHAB 1
#define HOUSE_WATER_NEEDS 10
#define HOUSE_ENERGY_NEEDS 10

#define LOW_ENERGY_HOUSE_WATER_NEEDS 10
#define LOW_ENERGY_HOUSE_ENERGY_NEEDS 10

#define BUILDING_NAME "Immeuble"
#define BUILDING_MAX_INHAB_PER_FLOOR 1
#define BUILDING_WATER_NEEDS 10
#define BUILDING_ENERGY_NEEDS 10
#define BUILDING_FLOOR 2
#define BUILDING_MAX_FLOOR 5

#define LOW_ENERGY_BUILDING_WATER_NEEDS 10
#define LOW_ENERGY_BUILDING_ENERGY_NEEDS 10

// SocialBuilding
#define SCHOOL_NAME "Ecole"
#define SCHOOL_SCORE 10
#define SCHOOL_RATIO 0.1f
#define SCHOOL_RADIUS 0.1f

#define HOSPITAL_NAME "Hôpital"
#define HOSPITAL_SCORE 10
#define HOSPITAL_RATIO 0.1f
#define HOSPITAL_RADIUS 0.1f

#define FIRE_STATION_NAME "Caserne"
#define FIRE_STATION_SCORE 10
#define FIRE_STATION_RATIO 0.1f
#define FIRE_STATION_RADIUS 0.1f

#define POLICE_STATION_NAME "Commissariat"
#define POLICE_STATION_SCORE 10
#define POLICE_STATION_RATIO 0.1f
#define POLICE_STATION_RADIUS 0.1f

// Resources

// Factory
#define FARM_OUTPUT_RATE 10
#define SHOP 0
#define MANUFACTORY 0

#endif // !CONSTANT_H