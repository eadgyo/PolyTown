#pragma once
#include <string>
#include <vector>
#include <set>
#include <SDL2/SDL.h>
#include <iostream>

class FileManager
{
public:
	static FileManager& getInstance();
	inline void test() { std::cout << "test"; };
private:
	FileManager& operator=(const FileManager&) {return (*this); };
	FileManager(const FileManager&) {};

	FileManager();
	~FileManager();

	const std::string binFolder = "bin_";
	const std::string objectsFolder = binFolder + "/" + "Objects";
	const std::string textureFolder = "pic";

	std::vector<SDL_Surface*> textures;
	std::set<std::string, int> names;

	static FileManager INSTANCE;

};

