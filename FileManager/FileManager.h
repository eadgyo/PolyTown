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
	
	SDL_Surface* getDefTexture(std::string textureName);
	void loadDefTextures();
	SDL_Surface* loadTexture(std::string path, bool isInternal);
	TTF_Font* loadFont(std::string path, unsigned size);
	bool isFolderExisting(std::string directory);
	bool createFolder(std::string directory);
	bool isFileExisting(std::string directory);
	std::vector<std::string> getAllFilesName(std::string directory, bool isInternal);
	int type(std::string directory, bool isInternal);
	unsigned sizeSurfaces() { return names.size(); };

	inline std::map<std::string, SDL_Surface*>::iterator mapBegin() { return names.begin();};
	inline std::map<std::string, SDL_Surface*>::iterator mapEnd() { return names.end(); };

private:
	void initialize();

	FileManager& operator=(const FileManager&) {return (*this); };
	FileManager(const FileManager&) {};

	FileManager();
	~FileManager();

	const std::string binFolder = "bin";
	const std::string objectsFolder = binFolder + "/" + "Objects";
	const std::string textureFolder = binFolder + "/" + "pic";
	const std::string ttfFolder = binFolder + "/" + "ttf";

	std::map<std::string, SDL_Surface*> names;

	bool isInitilialized;
	static FileManager& INSTANCE;

};

