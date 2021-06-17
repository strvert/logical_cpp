#pragma once

#include "binary.h"

namespace Gates {
    template <Binary::IsBinary A, Binary::IsBinary B>
    struct NAND  {};
    template <Binary::IsZero A, Binary::IsZero B>
    struct NAND<A, B>  { using X = Binary::I; };
    template <Binary::IsZero A, Binary::IsOne B>
    struct NAND<A, B>  { using X = Binary::I; };
    template <Binary::IsOne A, Binary::IsZero B>
    struct NAND<A, B>  { using X = Binary::I; };
    template <Binary::IsOne A, Binary::IsOne B>
    struct NAND<A, B>  { using X = Binary::O; };
    template <Binary::IsBinary A, Binary::IsBinary B>
    using NANDv = typename NAND<A, B>::X;

    template <Binary::IsBinary A>
    using NOT = NAND<A, A>;
    template <Binary::IsBinary A>
    using NOTv = typename NOT<A>::X;

    template <Binary::IsBinary A, Binary::IsBinary B>
    using AND = NOT<NANDv<A, B>>;
    template <Binary::IsBinary A, Binary::IsBinary B>
    using ANDv = typename AND<A, B>::X;

    template <Binary::IsBinary A, Binary::IsBinary B>
    using OR = NAND<NOTv<A>, NOTv<B>>;
    template <Binary::IsBinary A, Binary::IsBinary B>
    using ORv = typename OR<A, B>::X;

    template <Binary::IsBinary A, Binary::IsBinary B>
    using NOR = NOT<ORv<A, B>>;
    template <Binary::IsBinary A, Binary::IsBinary B>
    using NORv = typename NOR<A, B>::X;

    template <Binary::IsBinary A, Binary::IsBinary B>
    using XOR = NAND<NANDv<A, NANDv<A, B>>, NANDv<NANDv<A, B>, B>>;
    template <Binary::IsBinary A, Binary::IsBinary B>
    using XORv = typename XOR<A, B>::X;
}
