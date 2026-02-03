#pragma once
#include "fg/FrameGraph.hpp"
#include "fg/Blackboard.hpp"
class RenderGraph 
{
    FrameGraphBlackboard blackboard;
    FrameGraph graph;
    public:
    auto& GetBlackboard() {return blackboard;}
    auto& GetGraph() {return graph;}
};