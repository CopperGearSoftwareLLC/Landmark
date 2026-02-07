#include "World.hpp"
#include "Graphics/Command/IGraphicsCommandList.hpp"
#include "Graphics/GPUHandle.hpp"
#include "Graphics/GraphicsEnums.hpp"
#include "Graphics/RenderGraph/FGTexture.hpp"
#include "Graphics/RenderGraph/RenderGraphContext.hpp"
#include "LandmarkEngine.hpp"
#include "Math.hpp"
#include "Render/RenderSystem.hpp"
#include "fg/FrameGraphResource.hpp"
World::World()
    : render_graph(
          LandmarkEngine::Get().GetSystem<RenderSystem>()->NewRenderGraph())
{
    test345();
    Test512();

    struct RenderTriangleData
    {
        FrameGraphResource target;
    };

    RenderTriangleData tri_data =
        render_graph->GetGraph().addCallbackPass<RenderTriangleData>(
            "SimplePass",
            [&](FrameGraph::Builder &builder, RenderTriangleData &data)
            {
                data.target = builder.create<FGTexture>(
                    "Texture", FGTexture::Desc{{ivec2(100, 100)}});
                data.target = builder.write(data.target);
            },
            [=](const RenderTriangleData &data,
                FrameGraphPassResources &resources, void *ctx)
            {
                RenderGraphContext &context = *(RenderGraphContext *)ctx;
                auto &cmd_list =
                    context.GetCommandList<GraphicsCmdPipeline::eGraphics>();

                auto &texture = resources.get<FGTexture>(data.target);
                cmd_list.RenderPass([&](auto &rp) { rp.DrawElements(5); });
            });
    struct PresentData
    {
        FrameGraphResource texture;
        FrameGraphResource read_tex;
    };
    PresentData pres_data =
        render_graph->GetGraph().addCallbackPass<PresentData>(
            "SimplePass",
            [&](FrameGraph::Builder &builder, PresentData &data)
            {
                data.texture = builder.create<FGTexture>(
                    "screen buffer", FGTexture::Desc{{ivec2(100, 100)}});
                data.texture = builder.write(data.texture);
                data.read_tex = builder.read(tri_data.target);
                builder.setSideEffect();
            },
            [=](const PresentData &data, FrameGraphPassResources &resources,
                void *ctx)
            {
                RenderGraphContext &context = *(RenderGraphContext *)ctx;
                auto &cmd_list =
                    context.GetCommandList<GraphicsCmdPipeline::eTransfer,
                                           ePresent>();
                cmd_list.Blit(0, 1);
                cmd_list.Present(5);
            });

    GPUHandle<eTexture> test_texture =
        LandmarkEngine::Get().GetGraphicsBackend().GetAllocator().CreateTexture(
            ITexture::Desc{.dimensions = ivec2{100, 100},
                           .IsArrayType = false});
}
void World::RenderViews()
{
    RenderGraphContext ctx;
    render_graph->GetGraph().compile();
    render_graph->GetGraph().execute(&ctx);
    for (auto it = views.begin(); it != views.end(); it++)
    {
        if ((*it).expired())
        {
            views.erase(it);
        }
        else
        {
            (*it).lock()->Render();
        }
    }
}
std::shared_ptr<WorldView> World::MakeView()
{
    std::shared_ptr<WorldView> view = std::make_shared<WorldView>();
    views.push_back(view);
    return view;
}
