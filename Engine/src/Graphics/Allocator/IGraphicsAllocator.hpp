#pragma once

#include "Graphics/GraphicsEnums.hpp"
#include "Graphics/IGraphicsResource.hpp"
#include "Graphics/Texture/ITexture.hpp"
#include "boost/multi_index/hashed_index.hpp"
#include "boost/multi_index/indexed_by.hpp"
#include "boost/multi_index/ordered_index.hpp"
#include "boost/multi_index_container_fwd.hpp"
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/multi_index_container.hpp>
#include <cassert>
#include <memory>
#include <queue>
#include <stack>
#include <type_traits>
#include <vector>
class IGraphicsBackend;
template <GraphicsResourceType TYPE> class GPUHandle;
class IGraphicsAllocator
{
    friend IGraphicsBackend;
    enum GPUResourceIndicies
    {
        ByID = 0,
        ByResourceType = 1,
    };

    using ObjectsContainer = boost::multi_index_container<
        std::unique_ptr<IGraphicsResource>,
        boost::multi_index::indexed_by<
            boost::multi_index::hashed_unique<boost::multi_index::const_mem_fun<
                IGraphicsResource, GraphicsResourceID,
                &IGraphicsResource::GetResourceID>>,
            boost::multi_index::ordered_non_unique<
                boost::multi_index::const_mem_fun<
                    IGraphicsResource, GraphicsResourceType,
                    &IGraphicsResource::GetResourceType>>>>;

    ObjectsContainer objects;
    std::stack<GraphicsResourceID> ReleaseIDS;
    GraphicsResourceID NextId = 1;
    IGraphicsBackend &backend;

  private:
    virtual std::unique_ptr<ITexture>
    impl_CreateTexture(GraphicsResourceID ID, const ITexture::Desc &desc) = 0;

    GraphicsResourceID ReserveID()
    {
        if (!ReleaseIDS.empty())
        {
            GraphicsResourceID ID = ReleaseIDS.top();
            ReleaseIDS.pop();
            return ID;
        }
        return NextId++;
    }
    IGraphicsResource &_Get(GraphicsResourceType type, GraphicsResourceID id)
    {

        assert(objects.get<GPUResourceIndicies::ByID>().contains(id) &&
               "Invalid ID");
        auto object = objects.get<GPUResourceIndicies::ByID>().find(id);
        assert(object->get()->GetResourceType() == type &&
               "The ID does not match to the type requested");
        return **object;
    }

  public:
    IGraphicsAllocator(IGraphicsBackend &backend) : backend(backend) {}
    virtual ~IGraphicsAllocator() = default;
    GPUHandle<eTexture> CreateTexture(const ITexture::Desc &desc);

    template <GraphicsResourceType TYPE>
        requires(TYPE == GraphicsResourceType::eTexture)
    ITexture &Get(GraphicsResourceID id);
};
template <GraphicsResourceType TYPE>
    requires(TYPE == GraphicsResourceType::eTexture)
inline ITexture &IGraphicsAllocator::Get(GraphicsResourceID id)
{
    return (ITexture &)_Get(GraphicsResourceType::eTexture, id);
}
