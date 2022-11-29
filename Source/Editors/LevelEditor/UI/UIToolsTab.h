#pragma once
#include "Core/KitUI.h"
#include "KitLight.h"

namespace LevelEditor
{
    class ToolsTab : public KitUI
    {
    public:
        ToolsTab() = default;
        void Draw() override;
    private:
        void DrawLightsTab();
    };
}