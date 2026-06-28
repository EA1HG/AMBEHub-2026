#pragma once

#include <string>
#include <map>

class Config
{
public:

    bool load(const std::string& filename);

    std::string get(const std::string& key) const;

    int getInt(const std::string& key) const;

private:

    std::map<std::string,std::string> values;
};
