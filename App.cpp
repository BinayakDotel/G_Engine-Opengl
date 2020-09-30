#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>

#include <Shader.h>
#include <vector>
#include <Window.h>
#include <print.h>
#include <Error.h>
#include <OrthoCamera.h>
#include <OrthoCameraController.h>
#include <PrespCamera.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION
#include <tiny_gltf.h>

#define WIDTH 1080
#define HEIGHT 800

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace tinygltf;

int main() {
    //initializing glfw
    if (!glfwInit()) {
        print("Failed to initialize GLFW" + glfwInit());
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Creating Window
    GLFWwindow* window;
    //GLFWmonitor* monitor= glfwGetPrimaryMonitor();
    window = glfwCreateWindow(WIDTH, HEIGHT, "SCENE VIEWER", NULL, NULL);
    //width, height, "Name"

    glViewport(0, 0, WIDTH / 2, HEIGHT / 2);

    //Checking If window is initialized or not?
    if (window == NULL) {
        print("Failed to initialize window");
        glfwTerminate();
        return -1;
    }

    //Creating Window Context
    glfwMakeContextCurrent(window);

    //Initialize GLEW
    glewExperimental = true;

    if (glewInit() != GLEW_OK) {
        print("GLEW is not initialized");
        return -1;
    }
    glfwSwapInterval(1);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    std::string VertexShaderCode =
        "#version 330 core\n\
        layout(location = 0) in vec3 in_vertex;\n\
        \n\
        uniform mat4 MVP;\n\
        \n\
        void main(){\n\
	        gl_Position = MVP * vec4(in_vertex, 1.0f) ;\n\
        }\n\
        ";

    std::string FragmentShaderCode =
        "#version 330 core\n\
        layout (location= 0) out vec4 color;\n\
        \n\
        uniform sampler2D tex;\n\
        uniform vec4 uColor;\n\
        \n\
        void main() {\n\
	        color = uColor;\n\
        }\n\
        ";

    float rot_speed= 2.0f;

    PrespCamera m_camera(45.0f, float(WIDTH / HEIGHT), 0.1f, 100.0f);
    glm::vec3 position= m_camera.getPosition();
    glm::vec3 up= m_camera.getUp();
    glm::vec3 forward= m_camera.getForward();
    const float radius = 10.0f;
    float camX;
    float camZ;

    float pos[]={
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    };
    unsigned int index[]={
        0,1,2,
        2,3,0
    };

    unsigned int vbo, ibo, vao;

    GLCALL(glGenVertexArrays(1, &vao));
    GLCALL(glBindVertexArray(vao));

    GLCALL(glGenBuffers(1, &vbo));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLCALL(glBufferData(GL_ARRAY_BUFFER,
        sizeof(pos),
        pos,
        GL_DYNAMIC_DRAW
    ));

    GLCALL(glEnableVertexAttribArray(0));
    GLCALL(glVertexAttribPointer(0, 3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        0
    ));

    GLCALL(glGenBuffers(1, &ibo));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int) * 6,
        index,
        GL_DYNAMIC_DRAW
    ));

    float pos1[]={
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f, 0.5f, 0.0f,
    };
    unsigned int index1[]={
        0,1,2,
    };
    unsigned int vbo1, ibo1;

    GLCALL(glGenBuffers(1, &vbo1));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo1));
    GLCALL(glBufferData(GL_ARRAY_BUFFER,
        sizeof(pos1),
        pos1,
        GL_DYNAMIC_DRAW
    ));

    GLCALL(glEnableVertexAttribArray(1));
    GLCALL(glVertexAttribPointer(1, 3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        0
    ));

    GLCALL(glGenBuffers(1, &ibo1));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(unsigned int) * 3,
        index1,
        GL_DYNAMIC_DRAW
    ));

    unsigned int count= 3;

    Shader shader(VertexShaderCode, FragmentShaderCode);
    shader.bindShader();

    //GUI PART
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGuiIO& io= ImGui::GetIO();
    ImFont* pFont= io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Tahoma.ttf", 16.0f);

    glm::vec4 background_color={ 0.314f, 0.286f, 0.302f, 1.0f };
    bool set_background_color = false, set_object_color = false, rot=false;
    ImVec4 object_color = ImVec4(1.0f, 0.2f, 0.3f, 1.0f);

    shader.setUniform4f("uColor", object_color.x, object_color.y, object_color.z, object_color.w);

    do {
        //Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLCALL(glClearColor(background_color.x, background_color.y, background_color.z, background_color.w));
        GLCALL(glEnable(GL_DEPTH_TEST));
        GLCALL(glDepthFunc(GL_LESS));

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //ImGui::PushFont(pFont);

        shader.bindShader();
        //shader.setUniformMat4f("MVP", m_cameraController.GetCamera().GetViewProjectionMatrix());
        shader.setUniformMat4f("MVP", m_camera.getModelViewMatrix());

        //DRAW CALL
        /*DrawFile ?
            DrawModel() : print("Cannot Draw");*/
        GLCALL(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0));

        if (glfwGetKey(window, GLFW_KEY_R)) {
            glBindVertexArray(vao);
            GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
            count= 6;
        }
        if (glfwGetKey(window, GLFW_KEY_T)) {
            glBindVertexArray(vao);
            GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1));
            count= 3;
        }

        {
            static float f = 0.0f;
            static int counter = 0;
            bool my_tool_active;
            bool show_confirm=false;
            const ImVec2 button_Size= ImVec2(80.0f, 20.0f);

            ImGui::Begin("Controller", &my_tool_active, ImGuiWindowFlags_MenuBar);
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("Open..", "Ctrl+O")) { print("Open..."); }
                    if (ImGui::MenuItem("Save", "Ctrl+S")) { print("Saved..."); }
                    if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            ImGui::Separator();
            ImGui::Text("CAMERA CONTROLLER");

            ImGui::ColorEdit4("Clear Color", (float*)&object_color);

            if (ImGui::Button("Background Color", button_Size)) {
                background_color.x = object_color.x;
                background_color.y = object_color.y;
                background_color.z = object_color.z;
                background_color.w = object_color.w;
            }
            ImGui::SameLine();
            if (ImGui::Button("Object Color", button_Size)) {
                shader.setUniform4f("uColor", object_color.x, object_color.y, object_color.z, object_color.w);
            }

            ImGui::Separator();
            ImGui::Text("Translation");
            ImGui::SliderFloat("TX", &position.x, -1.0f, 1.0f);
            ImGui::SliderFloat("TY", &position.y, -1.0f, 1.0f);
            ImGui::SliderFloat("TZ", &position.z, 0.1f, 100.0f);
            m_camera.setPosition(position);

            ImGui::Separator();
            ImGui::Text("Up");
            ImGui::SliderFloat("UX", &up.x, -1.0f, 1.0f);
            ImGui::SliderFloat("UY", &up.y, -1.0f, 1.0f);
            ImGui::SliderFloat("UZ", &up.z, 0.1f, 100.0f);
            m_camera.moveUp(up);

            ImGui::Separator();
            ImGui::Text("Forward");
            ImGui::SliderFloat("FX", &forward.x, -1.0f, 1.0f);
            ImGui::SliderFloat("FY", &forward.y, -1.0f, 1.0f);
            ImGui::SliderFloat("FZ", &forward.z, -10.1f, 100.0f);
            ImGui::Separator();
            m_camera.moveForward(forward);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);

            ImGui::End();

            ImGui::Begin("Debug", &my_tool_active, ImGuiWindowFlags_MenuBar);
            ImGui::End();

            if (glfwGetKey(window, GLFW_KEY_P)) {
                m_camera.prt();
            }
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //swap Buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}
