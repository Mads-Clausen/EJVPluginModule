#include <dirent.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

std::vector<std::string> listDir(const char *path)
{
    DIR *dir;
    std::vector<std::string> files;
    dirent *pdir;
    dir = opendir(path);
    while((pdir = readdir(dir)))
    {
        // std::cout << "Found file " << pdir->d_name << std::endl;
        files.push_back(std::string(pdir->d_name));
    }

    closedir(dir);

    return files;
}

bool isDir(const char *path)
{
    if(path == 0) return false;

    DIR *dir;
    bool exists = false;

    dir = opendir(path);

    if(dir != 0)
    {
        exists = true;
        (void) closedir(dir);
    }

    return exists;
}

void compileToObjectFiles(const char *dir, std::string &oFiles)
{
    // std::cout << "Reading dir" << std::endl;
    std::vector<std::string> files = listDir(dir);
    // std::cout << "Read dir" << std::endl;

    for(int i = 0; i < files.size(); ++i)
    {
        // std::cout << "Checking files " << files[i].c_str() << std::endl;

        if(files[i].length() > 2 && isDir(std::string(dir + files[i]).c_str()))
        {
            compileToObjectFiles(std::string(dir + files[i] + "/").c_str(), oFiles);
            continue;
        }

        if(files[i].length() < 4 || files[i].substr(files[i].length() - 4) != ".cpp")
            continue;

        if(files[i].length() > 7 && files[i].substr(files[i].length() - 4 - 4) == "main.cpp")
            continue;

        std::cout << "Compiling " << std::string(dir) + std::string(files[i].substr(0, files[i].length() - 4) + ".o...").c_str();
        system(std::string("g++ -DPLUGIN_DEBUG -rdynamic -Wl,-export-dynamic -ldl -I\"/home/mads/EmptyJuiceBox/EmptyJuiceVoxel-master/modules/Rules/PluginManager/include\" -I\"/home/mads/EmptyJuiceBox/EmptyJuiceVoxel-master/modules/Rules/PluginManager/plugins\" -I\"/home/mads/EmptyJuiceBox/EmptyJuiceVoxel-master/include\" -I\"/home/mads/EmptyJuiceBox/EmptyJuiceVoxel-master/modules\" -c -std=c++11 -fPIC -rdynamic -ldl " + std::string(dir) + files[i]  + " -o ./.tmp/" + files[i].substr(0, files[i].length() - 4) + ".o").c_str());
        oFiles += std::string("./.tmp/" + files[i].substr(0, files[i].length() - 4) + ".o ");
        std::cout << "\t\tDone." << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::string oFiles;

    system("mkdir ./.tmp");

    compileToObjectFiles("/home/mads/EmptyJuiceBox/EmptyJuiceVoxel-master/modules/Rules/PluginManager/src/", oFiles);
    // compileToObjectFiles("/home/mads/EmptyJuiceBox/EmptyJuiceVoxel-master/src/", oFiles);

    std::cout << "Compiling and linking " << (argc < 2 ? "libCPluginManager.so" : argv[1]) << "...";
    system(std::string("g++ -shared -rdynamic -Wl,-export-dynamic -ldl -L\"/home/mads/EmptyJuiceBox/EmptyJuiceVoxel-master/bin\" " + oFiles + " -o " + (argc < 2 ? "libCPluginManager.so" : argv[1])).c_str());
    std::cout << "\t\tDone." << std::endl;
    std::cout << "Removing .o files...";
    system(std::string("rm -r ./.tmp").c_str());
    std::cout << "\t\tDone." << std::endl;


    return 0;
}
