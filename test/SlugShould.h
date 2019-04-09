#include <gtest/gtest.h>

#include "../src/Slug.h"


struct SlugShould : public testing::Test
{
    std::unique_ptr<Slug> slug;
    SlugShould()
    {
        slug = std::make_unique<Slug>();
    }
};

