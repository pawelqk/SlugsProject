#include <gmock/gmock.h>
#include <utility>

#include "../../src/SlugColony.h"


class SlugColonyMock: public SlugColony
{
 public:
    MOCK_METHOD1(checkSlugIllness, bool(std::pair<uint16_t, uint16_t>));
}
