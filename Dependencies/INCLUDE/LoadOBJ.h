#pragma once
//#include "Vertex.h"
#include <print.h>
#include "glm.hpp"
#include <stdlib.h>
#include <fstream>
#include <vector>

class LoadOBJ {
 private:
    FILE* file;
    //std::vector<glm::vec3> &out_vertex;

 public:
      LoadOBJ(const std::string& path){
            fopen_s(&file, path.c_str(), "rb");
            if (file == NULL) {
                print("Cannot load file");
            }
      }
      std::vector<glm::vec3> readObject() const {
          std::vector< glm::vec3 > temp_vertices;
          char buffer[100];
          while (!feof(file)) {
              /*
              fread(buffer, sizeof(buffer), 1, file);
              print(buffer);
              if (strcmp(buffer, "v") == 0) {
                  print("Found");
              }
              */
              
              int res = fscanf_s(file, "%s", buffer, _countof(buffer));
              //print(buffer);
              if (strcmp(buffer, "v") == 0) {
                  glm::vec3 vertex;
                  fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                  temp_vertices.push_back(vertex);
              }
          }
          /*
          for (unsigned int i=0; i < temp_vertices.size(); i++) {
              std::cout << "(x, y, z): ("<<temp_vertices[i].x <<", "<< temp_vertices[i].y <<", "<< temp_vertices[i].y<<")" << std::endl;
          }
          */
          return temp_vertices;
      }
};