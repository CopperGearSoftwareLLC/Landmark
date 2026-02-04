#pragma once
#include "Math.hpp"
#include <functional>

class ISystem
{
    public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    protected:


    void DeclareUpdateCustom(uint32 UpdateRateMS,std::function<void()> func)
    {

    }
    
};


