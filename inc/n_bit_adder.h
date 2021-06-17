#pragma once

#include <tuple>
#include "basic_adders.h"

namespace Circuits {
    template <std::size_t N, typename BS1, typename BS2, typename BS3, Binary::IsBinary Ci>
    struct NbitAdderHelper;

    template <Binary::IsBinary... S1, Binary::IsBinary... S2, Binary::IsBinary... S3, Binary::IsBinary Ci>
    struct NbitAdderHelper<sizeof...(S1), Binary::BinarySeq<S1...>, Binary::BinarySeq<S2...>, Binary::BinarySeq<S3...>, Ci> {
        static_assert(sizeof...(S1) == sizeof...(S2) && sizeof...(S1) == sizeof...(S3), "Bit length not matched.");
        static constexpr const std::size_t N = sizeof...(S1);
        using A = std::tuple_element_t<N-1, std::tuple<S1...>>;
        using B = std::tuple_element_t<N-1, std::tuple<S2...>>;
        using HAdder = Circuits::HalfAdder<A, B>;

        using Ss = typename NbitAdderHelper<N-1, Binary::BinarySeq<S1...>, Binary::BinarySeq<S2...>, typename Binary::BinarySeq<S3...>::template Set<typename HAdder::X, N-1>, typename HAdder::Y>::Ss;
    };

    template <std::size_t N, Binary::IsBinary... S1, Binary::IsBinary... S2, Binary::IsBinary... S3, Binary::IsBinary Ci>
    struct NbitAdderHelper<N, Binary::BinarySeq<S1...>, Binary::BinarySeq<S2...>, Binary::BinarySeq<S3...>, Ci> {
        static_assert(sizeof...(S1) == sizeof...(S2) && sizeof...(S1) == sizeof...(S3), "Bit length not matched.");
        using A = std::tuple_element_t<N-1, std::tuple<S1...>>;
        using B = std::tuple_element_t<N-1, std::tuple<S2...>>;
        using FAdder = Circuits::FullAdder<A, B, Ci>;

        using Ss = typename NbitAdderHelper<N-1, Binary::BinarySeq<S1...>, Binary::BinarySeq<S2...>, typename Binary::BinarySeq<S3...>::template Set<typename FAdder::X, N-1>, typename FAdder::Y>::Ss;
    };

    template <Binary::IsBinary... S1, Binary::IsBinary... S2, Binary::IsBinary... S3, Binary::IsBinary Ci>
    struct NbitAdderHelper<0, Binary::BinarySeq<S1...>, Binary::BinarySeq<S2...>, Binary::BinarySeq<S3...>, Ci> {
        static_assert(sizeof...(S1) == sizeof...(S2) && sizeof...(S1) == sizeof...(S3), "Bit length not matched.");
        using Ss = Binary::BinarySeq<Ci, S3...>;
    };

    template <typename BS1, typename BS2>
    using NbitAdder = NbitAdderHelper<BS1::size, BS1, BS2, typename Binary::GenBinarySeq<Binary::O, BS1::size>::type, Binary::O>;
}
