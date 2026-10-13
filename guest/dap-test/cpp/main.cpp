// SPDX-License-Identifier: GPL-3.0-or-later
namespace geo {
struct Point {
    int x;
    int y;
};

class Scaler {
public:
    int factor;
    int scale(int value) const;
    int scale(int value, int extra) const;
};

template <typename T, int N>
T repeat(T value);
} // namespace geo

struct Named {
    int id;
};

struct Counted {
    int count;
};

struct Shared {
    int tag;
};

struct Item : Named, Counted, virtual Shared {
    int weight;
};

namespace {
int adjust(int &total, int &&delta);
} // namespace

static int inspect(Item &item);
extern int geo::Point::*axis;
extern int (geo::Scaler::*method)(int) const;
extern geo::Point origin;
extern volatile int result;

extern "C" void entry(void)
{
    geo::Scaler scaler;
    scaler.factor = 2;
    Item item;
    item.id = 1;
    item.count = 2;
    item.tag = 3;
    item.weight = 4;
    int value = scaler.scale(5) + scaler.scale(5, 1);
    value += geo::repeat<int, 2>(value) + geo::repeat<short, 3>(1);
    value += adjust(value, 7);
    value += origin.*axis + (scaler.*method)(1);
    result = value + inspect(item);
    __asm__ volatile("1: bra.s 1b");
}

namespace geo {
int Scaler::scale(int value) const
{
    return value * factor;
}

int Scaler::scale(int value, int extra) const
{
    return value * factor + extra;
}

template <typename T, int N>
T repeat(T value)
{
    T total = 0;
    for (int i = 0; i < N; ++i)
        total += value;
    return total;
}
} // namespace geo

namespace {
int adjust(int &total, int &&delta)
{
    total += delta;
    return total;
}
} // namespace

int geo::Point::*axis = &geo::Point::y;
int (geo::Scaler::*method)(int) const = &geo::Scaler::scale;
geo::Point origin = {3, 4};
volatile int result;

static int inspect(Item &item)
{
    return item.id + item.count + item.tag + item.weight;
}

