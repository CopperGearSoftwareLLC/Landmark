#pragma once

enum class GraphicsAPI
{
    eCPU,
    eOpenGL45,
    eVulkan14,
    eDirectX12,
};

enum GraphicsResourceType
{
    eTexture,
    eBuffer,
    eBufferView,
    eSparseTexture
};