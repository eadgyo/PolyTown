#pragma once
class FileManager;

#include <Windows.h>
#include <GL/glew.h>
#include "../Graphics/Image.h"
#include <string>
#include <vector>
#include <set>
#include <SDL2/SDL.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <windows.h>
#include <SDL2/SDL_image.h>

class FileManager
{
public:
	static FileManager& getInstance();
	inline void test() { std::cout << "test"; };
	void initialize();
	SDL_Surface* getDefTexture(std::string textureName);
	void loadDefTextures();
	SDL_Surface* loadTexture(std::string path, bool isInternal);
	TTF_Font* loadFont(std::string path, unsigned size);
	bool isFolderExisting(std::string directory);
	bool createFolder(std::string directory);
	bool isFileExisting(std::string directory);
	std::vector<std::string> getAllFilesName(std::string directory, bool isInternal);
	int type(std::string directory, bool isInternal);
	unsigned sizeSurfaces() { return surfaces.size(); };
	SDL_Surface* getSurface(int i) { return surfaces[i]; };
	std::string getNameSurface(int i) { return namesStr[i]; };

private:
	FileManager& operator=(const FileManager&) {return (*this); };
	FileManager(const FileManager&) {};

	FileManager();
	~FileManager();

	const std::string binFolder = "bin";
	const std::string objectsFolder = binFolder + "/" + "Objects";
	const std::string textureFolder = binFolder + "/" + "pic";
	const std::string ttfFolder = binFolder + "/" + "ttf";

	std::vector<SDL_Surface*> surfaces;
	std::vector<std::string> namesStr;
	std::map<std::string, int> names;

	static FileManager& INSTANCE;

};

