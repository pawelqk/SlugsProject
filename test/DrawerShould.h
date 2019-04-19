#include <memory>
#include <gtest/gtest.h>

#include "../src/Drawer.h"
#include "mocks/SlugColonyMock.h"

namespace
{
    constexpr uint16_t WIDTH = 100;
    constexpr uint16_t HEIGHT = 100;   
}

struct DrawerShould : testing::Test
{
    std::unique_ptr<Drawer> drawer;
    SlugColonyMock slugColonyMock;
    DrawerShould()
    {
        // drawer = std::make_unique<Drawer>(WIDTH, HEIGHT, std::make_shared<SlugColony>(&slugColonyMock));
    }
};
