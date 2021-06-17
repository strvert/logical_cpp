#pragma once
#include "basic_gates.h"

namespace Circuits {
    template <Binary::IsBinary A, Binary::IsBinary B>
    struct HalfAdder {
        using X = Gates::XORv<A, B>;
        using Y = Gates::ANDv<A, B>;
    };

    template <Binary::IsBinary A, Binary::IsBinary B, Binary::IsBinary C>
    class FullAdder {
        using HA1 = HalfAdder<A, B>;
        using HA2 = HalfAdder<typename HA1::X, C>;
    public:
        using X = typename HA2::X;
        using Y = Gates::ORv<typename HA1::Y, typename HA2::Y>;
    };
}

