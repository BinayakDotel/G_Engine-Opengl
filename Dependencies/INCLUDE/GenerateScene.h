#pragma once
#include <vector>
#include <Object2D.h>
#include <print.h>

class GenerateScene {
private:
	Object2D scene;
	std::vector<unsigned int> offset={ 0 };

public:
	Object2D generateScene(std::vector<Object2D>object);
	void displayFinalSceneData();

	unsigned int getOffset(int index) const;
};
