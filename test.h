#ifndef TEST_H
#define TEST_H

#include <string>
#include <map>
#include "tinyrenderer.h"

typedef std::map<std::string,class Test*> TestMap; 

class Test
{
public:
    virtual bool Init(){return true;}
    virtual bool Tick(TinyRenderer::Renderer & renderer){ return false; }
    
    static TestMap * GetTestMap()
    {
        static TestMap sTestMap;
        return &sTestMap;
    }
    
    static bool AddTest(Test* test, std::string key)
    {
        TestMap * testMap = GetTestMap();
        testMap->insert(std::pair<std::string,Test*>(key, test));
        return true;
    }
};



#define TEST(x,key) bool x##Registered = Test::AddTest(new x(), std::string(key))

#endif