/*#include <fstream>
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
*/
/*static std::vector<Mesh> meshes;
static std::vector<Model> models;
static unsigned int vao;
static std::map<int, GLuint> vbos;

static bool loadModel(tinygltf::Model& model, const char* filename) {
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool res = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cout << "ERR: " << err << std::endl;
    }

    if (!res)
        std::cout << "Failed to load glTF: " << filename << std::endl;
    else
        std::cout << "Loaded glTF: " << filename << std::endl;

    return res;
}

static void DrawModel() {
    for (int z=0; z < models.size(); z++) {
        const Model& model= models.at(z);
        for (int j=0; j < meshes.size(); j++) {
            const Mesh& mesh= meshes.at(j);
            for (size_t i = 0; i < mesh.primitives.size(); ++i) {
                tinygltf::Primitive primitive = mesh.primitives[i];
                tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

                GLCALL(glBindVertexArray(vao));
                GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[3]));
                //Renderer;
                GLCALL(glDrawElements(primitive.mode, indexAccessor.count,
                    indexAccessor.componentType,
                    BUFFER_OFFSET(indexAccessor.byteOffset)));
            }
        }
    }
}*/
/*
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
    
    glViewport(0, 0, WIDTH/2, HEIGHT/2);
   
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
    */
    /*std::string path="objects/gltf/squr.gltf";
    bool DrawFile;
    Model model;

    if (!loadModel(model, path.c_str())) { 
        print("FILE NOT SUPPORTED");
        DrawFile= false;
    }
    
    else {
        print("SUPPORTED");
        DrawFile= true;
        models.push_back(model);

        GLCALL(glGenVertexArrays(1, &vao));
        GLCALL(glBindVertexArray(vao));

        for (int i=0; i < model.bufferViews.size(); i++) {
            const BufferView& buffer_view= model.bufferViews.at(i);
            const Buffer& buffer= model.buffers.at(buffer_view.buffer);

            unsigned int vbo;
            GLCALL(glGenBuffers(1, &vbo));
            vbos[i]= vbo;
            GLCALL(glBindBuffer(buffer_view.target, vbo));
            GLCALL(glBufferData(buffer_view.target,
                buffer_view.byteLength,
                &buffer.data.at(0) + buffer_view.byteOffset,
                GL_STATIC_DRAW
            ));
            print("BUFFER GENERATED");
        }
        for (int i=0; i < model.meshes.size();i++) {
            const Mesh& mesh= model.meshes.at(i);
            meshes.push_back(mesh);

            for (int j=0; j < mesh.primitives.size(); j++) {
                const Primitive& primitive= mesh.primitives.at(j);
                const Accessor& indexAccessor= model.accessors.at(primitive.indices);

                for (auto& attrib : primitive.attributes) {
                    tinygltf::Accessor accessor = model.accessors[attrib.second];
                    int byteStride = accessor.ByteStride(model.bufferViews[accessor.bufferView]);
                    
                    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]));

                    int size = 1;
                    if (accessor.type != TINYGLTF_TYPE_SCALAR) {
                        size = accessor.type;
                    }

                    int vaa_index=-1;

                    if (attrib.first.compare("POSITION") == 0) { vaa_index = 0; }
                    if (attrib.first.compare("NORMAL") == 0) { vaa_index = 1; }
                    if (attrib.first.compare("TEXCOORD_0") == 0) { vaa_index = 2; }

                    if (vaa_index > -1){
                        GLCALL(glEnableVertexAttribArray(vaa_index));
                        GLCALL(glVertexAttribPointer(0, size,
                            indexAccessor.componentType,
                            accessor.normalized ? GL_TRUE : GL_FALSE,
                            byteStride,
                            BUFFER_OFFSET(accessor.byteOffset)
                            ));
                        print("ATTRIB ARRAY ENABLED");
                    }
                }
            }
        }
    }*/
    /*std::string VertexShaderCode =
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

    PrespCamera m_camera(45.0f, float(WIDTH/HEIGHT), 0.1f, 100.0f);
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

    shader.setUniform4f("uColor", object_color.x, object_color.y, object_color.z, object_color.w );

    do {
        //Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLCALL(glClearColor(background_color.x,background_color.y,background_color.z,background_color.w ));
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
        DrawFile ?
            DrawModel() : print("Cannot Draw");
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

*/
/*#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>

#include <shade.h>
#include <Window.h>
#include <BufferData.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <print.h>
#include <Error.h>
#include <GLTFData.h>

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION
#include <tiny_gltf.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

bool loadModel(tinygltf::Model &model, const char *filename) {
  tinygltf::TinyGLTF loader;
  std::string err;
  std::string warn;

  bool res = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
  if (!warn.empty()) {
    std::cout << "WARN: " << warn << std::endl;
  }

  if (!err.empty()) {
    std::cout << "ERR: " << err << std::endl;
  }

  if (!res)
    std::cout << "Failed to load glTF: " << filename << std::endl;
  else
    std::cout << "Loaded glTF: " << filename << std::endl;

  return res;
}

std::map<int, GLuint> bindMesh(std::map<int, GLuint> vbos,
                               tinygltf::Model &model, tinygltf::Mesh &mesh){
    for (size_t i = 0; i < model.bufferViews.size(); ++i){

    const tinygltf::BufferView &bufferView = model.bufferViews[i];
    if (bufferView.target == 0) {  // TODO impl drawarrays
      std::cout << "WARN: bufferView.target is zero" << std::endl;
      continue;  
    }

    const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];
    std::cout << "bufferview.target " << bufferView.target << std::endl;
    
    std::cout << "buffer.data.size = " << buffer.data.size()
        << ", bufferview.byteOffset = " << bufferView.byteOffset
        << std::endl;

    std::cout << "DATA TYPE: " << typeid(&buffer.data).name()
        << std::endl;
    std::cout << "&buffer.data: " << &buffer.data << std::endl;
    m_BufferView m_buffer={
        bufferView.target,
        bufferView.byteLength,
        &buffer.data.at(0) + bufferView.byteOffset
    };
    
    unsigned int vbo;
    GLCALL(glGenBuffers(1, &vbo));
    vbos[i]= vbo;
    print(vbo);
    GLCALL(glBindBuffer(m_buffer.target, vbo));
    GLCALL(glBufferData(m_buffer.target, m_buffer.byteLength,
        m_buffer.buffer, GL_STATIC_DRAW));
  }

  for (size_t i = 0; i < mesh.primitives.size(); ++i) {
    tinygltf::Primitive primitive = mesh.primitives[i];
    tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

    for (auto &attrib : primitive.attributes) {
      tinygltf::Accessor accessor = model.accessors[attrib.second];
      int byteStride = accessor.ByteStride(model.bufferViews[accessor.bufferView]);

      glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

      int size = 1;
      if (accessor.type != TINYGLTF_TYPE_SCALAR) {
        size = accessor.type;
      }

      int vaa = -1;
      if (attrib.first.compare("POSITION") == 0) vaa = 0;
      if (attrib.first.compare("NORMAL") == 0) vaa = 1;
      if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 2;
      if (vaa > -1) {
        glEnableVertexAttribArray(vaa);
        glVertexAttribPointer(vaa, size, accessor.componentType,
                              accessor.normalized ? GL_TRUE : GL_FALSE,
                              byteStride, BUFFER_OFFSET(accessor.byteOffset));
       
      } else
        std::cout << "vaa missing: " << attrib.first << std::endl;
    }

    if (model.textures.size() > 0) {
      // fixme: Use material's baseColor
      tinygltf::Texture &tex = model.textures[0];

      if (tex.source > -1) {

        GLuint texid;
        glGenTextures(1, &texid);

        tinygltf::Image &image = model.images[tex.source];

        glBindTexture(GL_TEXTURE_2D, texid);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        GLenum format = GL_RGBA;

        if (image.component == 1) {
          format = GL_RED;
        } else if (image.component == 2) {
          format = GL_RG;
        } else if (image.component == 3) {
          format = GL_RGB;
        } else {
          // ???
        }

        GLenum type = GL_UNSIGNED_BYTE;
        if (image.bits == 8) {
          // ok
        } else if (image.bits == 16) {
          type = GL_UNSIGNED_SHORT;
        } else {
          // ???
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0,
                     format, type, &image.image.at(0));
      }
    }
  }

  return vbos;
}

// bind models
void bindModelNodes(std::map<int, GLuint> vbos, tinygltf::Model &model,
                    tinygltf::Node &node) {
  if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
    bindMesh(vbos, model, model.meshes[node.mesh]);
  }

  for (size_t i = 0; i < node.children.size(); i++) {
    assert((node.children[i] >= 0) && (node.children[i] < model.nodes.size()));
    bindModelNodes(vbos, model, model.nodes[node.children[i]]);
  }
}
GLuint bindModel(tinygltf::Model &model) {
  std::map<int, GLuint> vbos;
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  const tinygltf::Scene &scene = model.scenes[model.defaultScene];
  for (size_t i = 0; i < scene.nodes.size(); ++i) {
    assert((scene.nodes[i] >= 0) && (scene.nodes[i] < model.nodes.size()));
    bindModelNodes(vbos, model, model.nodes[scene.nodes[i]]);
  }

  glBindVertexArray(0);
  // cleanup vbos
  for (size_t i = 0; i < vbos.size(); ++i) {
    glDeleteBuffers(1, &vbos[i]);
  }

  return vao;
}

void drawMesh(tinygltf::Model &model, tinygltf::Mesh &mesh) {
  for (size_t i = 0; i < mesh.primitives.size(); ++i) {
    tinygltf::Primitive primitive = mesh.primitives[i];
    tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

    //Renderer
    glDrawElements(primitive.mode, indexAccessor.count,
                   indexAccessor.componentType,
                   BUFFER_OFFSET(indexAccessor.byteOffset)); 
  }
}

// recursively draw node and children nodes of model
void drawModelNodes(tinygltf::Model &model, tinygltf::Node &node) {
  if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
    drawMesh(model, model.meshes[node.mesh]);
  }
  for (size_t i = 0; i < node.children.size(); i++) {
    drawModelNodes(model, model.nodes[node.children[i]]);
  }
}
void drawModel(GLuint vao, tinygltf::Model &model) {
  glBindVertexArray(vao);

  const tinygltf::Scene &scene = model.scenes[model.defaultScene];
  for (size_t i = 0; i < scene.nodes.size(); ++i) {
    drawModelNodes(model, model.nodes[scene.nodes[i]]);
  }

  glBindVertexArray(0);
}

void dbgModel(tinygltf::Model &model) {
  for (auto &mesh : model.meshes) {
    std::cout << "mesh : " << mesh.name << std::endl;
    for (auto &primitive : mesh.primitives) {
      const tinygltf::Accessor &indexAccessor =
          model.accessors[primitive.indices];

      std::cout << "indexaccessor: count " << indexAccessor.count << ", type "
                << indexAccessor.componentType << std::endl;

      tinygltf::Material &mat = model.materials[primitive.material];
      for (auto &mats : mat.values) {
        std::cout << "mat : " << mats.first.c_str() << std::endl;
      }

      for (auto &image : model.images) {
        std::cout << "image name : " << image.uri << std::endl;
        std::cout << "  size : " << image.image.size() << std::endl;
        std::cout << "  w/h : " << image.width << "/" << image.height
                  << std::endl;
      }

      std::cout << "indices : " << primitive.indices << std::endl;
      std::cout << "mode     : "
                << "(" << primitive.mode << ")" << std::endl;

      for (auto &attrib : primitive.attributes) {
        std::cout << "attribute : " << attrib.first.c_str() << std::endl;
      }
    }
  }
}

glm::mat4 genView(glm::vec3 pos, glm::vec3 lookat) {
  // Camera matrix
  glm::mat4 view = glm::lookAt(
      pos,                // Camera in World Space
      lookat,             // and looks at the origin
      glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
  );

  return view;
}

glm::mat4 genMVP(glm::mat4 view_mat, glm::mat4 model_mat, float fov, int w,
                 int h) {
  glm::mat4 Projection =
      glm::perspective(glm::radians(10.0f), (float)w / (float)h, 0.01f, 1000.0f);

  glm::mat4 mvp = Projection * view_mat * model_mat;

  return mvp;
}

void displayLoop(Window &window, const std::string &filename) {
  shade shader;
  glUseProgram(shader.pid);

  // grab uniforms to modify
  GLuint MVP_u = glGetUniformLocation(shader.pid, "MVP");
  GLuint sun_position_u = glGetUniformLocation(shader.pid, "sun_position");
  GLuint sun_color_u = glGetUniformLocation(shader.pid, "sun_color");

  tinygltf::Model model;
  if (!loadModel(model, filename.c_str())) return;

  GLuint vao = bindModel(model);
  // dbgModel(model); return;

  // Model matrix : an identity matrix (model will be at the origin)
  glm::mat4 model_mat = glm::mat4(1.0f);
  glm::mat4 model_rot = glm::mat4(1.0f);
  glm::vec3 model_pos = glm::vec3(-3, 0, -3);

  // generate a camera view, based on eye-position and lookAt world-position
  glm::mat4 view_mat = genView(glm::vec3(2, 2, 20), model_pos);

  glm::vec3 sun_position = glm::vec3(3.0, 10.0, -5.0);
  glm::vec3 sun_color = glm::vec3(1.0);

  do {
    window.Resize();
    glClearColor(0.2, 0.6, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 trans =
        glm::translate(glm::mat4(1.0f), model_pos);  // reposition model
    model_rot = glm::rotate(model_rot, glm::radians(0.8f),
                            glm::vec3(0, 1, 0));  // rotate model on y axis
    model_mat = trans * model_rot;

    // build a model-view-projection
    GLint w, h;
    glfwGetWindowSize(window.window, &w, &h);
    glm::mat4 mvp = genMVP(view_mat, model_mat, 45.0f, w, h);
    glUniformMatrix4fv(MVP_u, 1, GL_FALSE, &mvp[0][0]);

    glUniform3fv(sun_position_u, 1, &sun_position[0]);
    glUniform3fv(sun_color_u, 1, &sun_color[0]);

    drawModel(vao, model);
    glfwSwapBuffers(window.window);
    glfwPollEvents();
  }while (glfwGetKey(window.window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window.window) == 0);
}

static void error_callback(int error, const char *description) {
  (void)error;
  fprintf(stderr, "Error: %s\n", description);
}

int main() {
  std::string filename = "objects/gltf/squr.gltf";

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) return -1;

  // Force create OpenGL 3.3
  // NOTE(syoyo): Linux + NVIDIA driver segfaults for some reason? commenting out glfwWindowHint will work.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  Window window = Window(800, 600, "TinyGLTF basic example");
  glfwMakeContextCurrent(window.window);

#ifdef __APPLE__
  glewExperimental = GL_TRUE;
#endif

  glewInit();
  std::cout << glGetString(GL_RENDERER) << ", " << glGetString(GL_VERSION)
            << std::endl;

  if (!GLEW_VERSION_3_3) {
    std::cerr << "OpenGL 3.3 is required to execute this app." << std::endl;
    return EXIT_FAILURE;
  }

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  displayLoop(window, filename);

  glfwTerminate();
  return 0;
}*/
