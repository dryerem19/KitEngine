//
// Created by Denis on 01.11.2022.
//

#ifndef KITENGINE_TESTLAYER_H
#define KITENGINE_TESTLAYER_H

#include <Core/BaseLayer.h>


#include <Renderer.h>


#include <Graphics/Components/ModelComponent.h>

// TODO: УБРАТЬ
#include <memory>
#include <Loader.h>

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

using namespace KitEngine::Core;
using namespace KitEngine::Graphics::Components;

namespace LevelEditor::Tests
{
    class TestLayer : public KitEngine::Core::BaseLayer
    {
    private:
        std::unique_ptr<Render::VertexArray>  mVertexArray;
        std::unique_ptr<Render::VertexBuffer> mVertexBuffer;
        std::unique_ptr<Render::IndexBuffer>  mIndexBuffer;
        std::unique_ptr<Render::Shader>       mShader;
        std::vector<Render::Texture>      mTextures;

       //Texture testTexture = Texture("res/textures/no_texture.png");
//       Texture testTexture = Texture("res/models/nanosuit/body_dif.png");

        std::unique_ptr<KitEngine::Graphics::Components::ModelComponent> mModel;

        std::vector<KitEngine::Graphics::Components::ModelComponent> mModels;

        glm::mat4                                          mTransform;
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

        GLfloat yaw   = -90.0f;
        GLfloat pitch =   0.0f;
        GLfloat lastX =  800  / 2.0;
        GLfloat lastY =  600 / 2.0;

    public:
        TestLayer() = default;

        void OnStart() override;
        void OnUpdate() override;
        void OnRender(double dt) override;
        void OnUIRender() override;
        void OnFinish() override;

        void DoMovement();
    };
}

#endif //KITENGINE_TESTLAYER_H