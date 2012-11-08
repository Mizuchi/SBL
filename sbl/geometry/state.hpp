#ifndef _sbl_geometry_state
#define _sbl_geometry_state
#include"../utility/enum.hpp"

namespace sbl { 
namespace state {

struct ContainStateDef {
    enum type { inside, outside, touch, overlap };
};

struct CompareStateDef {
    enum type { greater, equal_to, less, greater_equal, less_equal };
};

struct PositionStateDef {
    enum type { left, right, back, front, reverse, same };
};

typedef Enum<ContainStateDef> Contain;
typedef Enum<CompareStateDef> Compare;
typedef Enum<PositionStateDef> Position;

static const Contain inside   = Contain::inside;
static const Contain outside  = Contain::outside;
static const Contain touch    = Contain::touch;
static const Contain overlap  = Contain::overlap;

static const Compare greater  = Compare::greater;
static const Compare equal_to = Compare::equal_to;
static const Compare less     = Compare::less;

static const Position left    = Position::left;
static const Position right   = Position::right;
static const Position front   = Position::front;
static const Position back    = Position::back;
static const Position reverse = Position::reverse;
static const Position same    = Position::same;

} // namespace state
} // namespace sbl
#endif
