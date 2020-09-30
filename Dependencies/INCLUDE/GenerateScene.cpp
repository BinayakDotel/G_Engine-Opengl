#pragma once
#include <GenerateScene.h>
/*
Object2D GenerateScene::generateScene(std::vector<Object2D>object) {

	//For determing the offset(i.e vertex size) for generating the final indices of the scene
	for (int i=0; i < object.size(); i++) {
		offset.push_back(offset.at(i) + object.at(i).vertex.size());
	}

	for (int i=0; i < object.at(0).texCoords.size(); i++) {
		scene.texCoords.push_back(object.at(0).texCoords.at(i));
	}

	//Pushing the vertices of all the objects {in object.at(0)} for generating the final vertices of the scene
	for (int i=1; i < object.size(); i++) {
		object.at(0).vertex.insert(object.at(0).vertex.end(), object.at(i).vertex.begin(), object.at(i).vertex.end());
	}

	//Generate the final indices of the scene
	for (int i= 0; i < object.size(); i++) {
		for (int j=0; j < object.at(i).index.size(); j++) {
			std::cout << "Adding: {offset:- " << getOffset(i) << " }, in {object: " << i << " }" << "{ index: " << j << " }" << std::endl;
			object.at(i).index.at(j)+=getOffset(i);
		}
	}

	//Pushing the indices of all the objects {in object.at(0)} for generating the final indices of the scene
	for (int i= 1; i < object.size(); i++) {
		object.at(0).index.insert(object.at(0).index.end(), object.at(i).index.begin(), object.at(i).index.end());
	}

	//Pushing the all datas copied to object.at(0) to the scene Object
	for (int i=0; i < object.at(0).vertex.size(); i++) {
		scene.vertex.push_back({ object.at(0).vertex.at(i).x, object.at(0).vertex.at(i).y, object.at(0).vertex.at(i).z });
		scene.colCoords.push_back({ 0.2f, 0.9f, 0.2f, 1.0f });
	}
	for (int i=0; i < object.at(0).index.size(); i++) {
		scene.index.push_back(object.at(0).index.at(i));
	}

	print("Successfully Generated scene");
	std::cout << "Total objects rendered is: " << object.size() << std::endl;
	return scene;
}

void GenerateScene::displayFinalSceneData() {

	if (scene.vertex.empty()) {
		print("NUll SCENE DATA");
	}
	else {
		//Print the final object data generated to create a scene
		for (int i=0; i < scene.vertex.size(); i++) {
			std::cout << "{ " << scene.vertex.at(i).x << ", " << scene.vertex.at(i).y << " }" << std::endl;
		}
		for (int i=0; i < scene.index.size(); i++) {
			std::cout << scene.index.at(i) << std::endl;
		}
	}
}

unsigned int GenerateScene::getOffset( int index ) const {
	return offset.at(index);
}

*/