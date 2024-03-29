#ifndef FRUITWORK_TEST_SCENE_INDEX_H
#define FRUITWORK_TEST_SCENE_INDEX_H

#include "Scene.h"

namespace fruitwork
{
    class TestSceneIndex : public Scene {
    public:
        static TestSceneIndex *getInstance() { return &instance; }

        bool enter() override;

        bool exit() override;

    private:
        static TestSceneIndex instance;

        TestSceneIndex() = default;
    };

} // fruitwork

#endif //FRUITWORK_TEST_SCENE_INDEX_H
