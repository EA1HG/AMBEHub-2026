#include "Config.h"

#include <fstream>
#include <sstream>

bool Config::load(const std::string& filename)
{
    std::ifstream file(filename);

    if(!file)
        return false;

    std::string line;
    std::string section;

    while(std::getline(file,line))
    {
        if(line.empty())
            continue;

        if(line[0]=='#')
            continue;

        if(line.front()=='[')
        {
            section=line.substr(1,line.size()-2);
            continue;
        }

        auto pos=line.find('=');

        if(pos==std::string::npos)
            continue;

        std::string key=section+"."+line.substr(0,pos);

        std::string value=line.substr(pos+1);

        values[key]=value;
    }

    return true;
}

std::string Config::get(const std::string& key) const
{
    auto it=values.find(key);

    if(it==values.end())
        return "";

    return it->second;
}

int Config::getInt(const std::string& key) const
{
    return std::stoi(get(key));
}
