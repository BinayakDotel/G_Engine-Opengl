#include <tiny_gltf.h>
#include <print.h>
#include <Window.h>
#include <GLTFData.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace tinygltf;

class LoadGLTF {
private:
    Model model;
    TinyGLTF gltf_ctx;
    std::string err;
    std::string warn;
    std::string input_filename;
    std::string ext;
    bool ret;
    std::vector<m_BufferView> m_buffer;
    std::vector<m_Draw> m_draw;
    VertexArray vertex_array;
    VertexBuffer vertex_buffer;

    //IndexBuffer index_buffer;

public:
    bool loadModel(tinygltf::Model& model, const char* filename);

    std::map<int, GLuint> bindMesh(std::map<int, unsigned int> vbos,
        tinygltf::Model& model, tinygltf::Mesh& mesh);

    // bind models
    void bindModelNodes(std::map<int, unsigned int> vbos, tinygltf::Model& model,
        tinygltf::Node& node);
    unsigned int bindModel(tinygltf::Model& model);
    void drawMesh(tinygltf::Model& model, tinygltf::Mesh& mesh);

    // recursively draw node and children nodes of model
    void drawModelNodes(tinygltf::Model& model, tinygltf::Node& node);
    void drawModel(unsigned int vao, tinygltf::Model& model);
    void dbgModel(tinygltf::Model& model);

    /*glm::mat4 genView(glm::vec3 pos, glm::vec3 lookat);
    glm::mat4 genMVP(glm::mat4 view_mat, glm::mat4 model_mat, float fov, int w,
        int h);
        */
    void displayLoop(Window& window, const std::string& filename);
    static void error_callback(int error, const char* description);
};
