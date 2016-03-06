#pragma once
#include <string>
#include <vector>
#include <set>
#include <SDL2/SDL.h>
#include <iostream>
#include "Graphics/Image.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <SDL2/SDL_image.h>

class FileManager
{
public:
	static FileManager& getInstance();
	inline void test() { std::cout << "test"; };
	void initialize();
	SDL_Surface* getDefTexture(std::string textureName);
	void loadDefTextures();
	SDL_Surface* loadTexture(std::string, bool isInternal);
	bool isFolderExisting(std::string directory);
	bool createFolder(std::string directory);
	bool isFileExisting(std::string directory);
	std::vector<std::string> getAllFilesName(std::string directory, bool isInternal);
	int type(std::string directory, bool isInternal);

private:
	FileManager& operator=(const FileManager&) {return (*this); };
	FileManager(const FileManager&) {};

	FileManager();
	~FileManager();

	const std::string binFolder = "bin_";
	const std::string objectsFolder = binFolder + "/" + "Objects";
	const std::string textureFolder = binFolder + "/" + "pic";

	std::vector<SDL_Surface*> surfaces;
	std::map<std::string, int> names;

	static FileManager INSTANCE;

};

