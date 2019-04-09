#ifndef __LEAF_H__
#define __LEAF_H__

#include <cstdint>

class Leaf
{
 public:
    Leaf();
    explicit Leaf(uint8_t size);
    ~Leaf() = default;

    uint8_t getSize();
    bool getTaken();
    bool getIll();

    void setTaken(bool taken);

    void regenerate();
    void eat();
 private:
    uint8_t size;
    bool taken;
    bool ill;
};

#endif
