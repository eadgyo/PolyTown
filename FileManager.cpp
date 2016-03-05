#include "FileManager.h"
FileManager FileManager::INSTANCE=FileManager();

FileManager::FileManager()
{

}

FileManager& FileManager::getInstance()
{
	return INSTANCE;
}

FileManager::~FileManager()
{
}

