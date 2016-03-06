#include "FileManager.h"
FileManager FileManager::INSTANCE=FileManager();

FileManager::FileManager()
{
	createFolder(binFolder);
	createFolder(textureFolder);
	//createFolder(objectFolder);

	// Chargement des images
	loadDefTextures();
}

FileManager& FileManager::getInstance()
{
	return INSTANCE;
}

std::vector<std::string> FileManager::getAllFilesName(std::string directory,
		bool isInternal)
{
	std::vector<std::string> namesFiles;
	DIR *dir;
	struct dirent *ent;
	if((dir = opendir(directory.c_str())) != NULL)
	{
		while((ent = readdir(dir)) != NULL)
		{
			if(type(directory + "/" + ent->d_name, isInternal) == 2)
				namesFiles.push_back(ent->d_name);
		}
		closedir (dir);
	}
	else
	{
	  perror ("");
	}
	return namesFiles;
}

int FileManager::type(std::string directory, bool isInternal)
{
	struct stat s;
	if(stat(directory.c_str(), &s) == 0 )
	{
	    if(s.st_mode & S_IFDIR)
	    {
	        return 1;
	    }
	    else if( s.st_mode & S_IFREG )
	    {
	        return 2;
	    }
	    else
	    {
	    	return 3;
	    }
	}
	return 0;
}

FileManager::~FileManager()
{
}

void FileManager::initialize()
{
	createFolder(binFolder);
	loadDefTextures();
}

SDL_Surface* FileManager::getDefTexture(std::string textureName)
{
	if(textureName.compare(""))
		return NULL;

	std::map<std::string, int>::iterator it;

	it = names.find(textureName);
	assert(it != names.end());
	int i = it->second;
	return surfaces[i];
}

void FileManager::loadDefTextures()
{
	std::vector<std::string> names = getAllFilesName(textureFolder, true);
	int j=0;
	for(unsigned i=0; i<names.size(); i++)
	{
		SDL_Surface* texture = loadTexture(textureFolder + "/" + names[i], false);
		if(texture != NULL)
		{
			surfaces.push_back(texture);
			this->names[names[i]] = j;
			j++;
		}
	}
}

SDL_Surface* FileManager::loadTexture(std::string allocator, bool isInternal)
{
	if(isInternal)
	{
		std::cout << "ne fonctionne pas";
		SDL_Surface * texture = IMG_Load(allocator.c_str());
		assert(texture != NULL);
		return texture;
	}
	else
	{
		SDL_Surface * texture = IMG_Load(allocator.c_str());
		assert(texture != NULL);
		return texture;
	}
}

bool FileManager::isFolderExisting(std::string directory)
{
	struct stat buffer;
	return (stat(directory.c_str(), &buffer) == 0);
}

bool FileManager::createFolder(std::string directory)
{
	int result = mkdir(directory.c_str(), 0777);
	return (bool) result;
}

bool FileManager::isFileExisting(std::string directory)
{
	  struct stat buffer;
	  return (stat(directory.c_str(), &buffer) == 0);
}
