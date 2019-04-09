#include <gtest/gtest.h>

#include "SlugShould.h"

TEST_F(SlugShould, ProperlyInitiateSlug)
{
    EXPECT_NE(slug, nullptr);
}

