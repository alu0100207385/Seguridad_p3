#include <ostream>

namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
	FG_ORANGE   = 33,
        FG_BLUE     = 34,
	FG_VIOLET   = 35,
	FG_AQUAMARINE = 36,
	FG_BLUESKY  = 37,
        FG_DEFAULT  = 39,

        BG_RED      = 41,
        BG_GREEN    = 42,
	BG_ORANGE   = 43,
        BG_BLUE     = 44,
	BG_VIOLET   = 45,
	BG_AQUAMARINE = 46,
	BG_BLUESKY  = 47,
        BG_DEFAULT  = 49,
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}
