#pragma once

#include <type_traits>
#include <utility>
#include <tuple>
#include "binary.h"

namespace Binary {
    struct Binary {};
    struct I : public Binary {};
    struct O : public Binary  {};

    template <typename T>
    concept IsBinary = std::is_base_of_v<Binary, T>;

    template <typename T>
    concept IsZero = std::is_same_v<T, O> && IsBinary<T>;

    template <typename T>
    concept IsOne = std::is_same_v<T, I> && IsBinary<T>;

    template <typename T>
    struct IType {
        using type = T;
    };

    template <IsBinary... Bs>
    struct BinarySeq;

    template<typename IndexSeq, IsBinary SetType, std::size_t Pos, std::size_t Len, IsBinary... Ts>
    struct BinarySeqSetHelper;

    template<std::size_t... Indexes, IsBinary SetType, std::size_t Pos, std::size_t Len, IsBinary... Ts>
    struct BinarySeqSetHelper<std::index_sequence<Indexes...>, SetType, Pos, Len, Ts...>
      : IType<BinarySeq<
            std::tuple_element_t<Indexes == Pos ? Len : Indexes, std::tuple<Ts..., SetType>>...>> {
        static_assert(Pos < Len, "out of range");
    };

    template<IsBinary... Bs>
    struct BinarySeq : IType<BinarySeq<Bs...>> {
        static constexpr const std::size_t size = sizeof...(Bs);

        template<IsBinary SetType, std::size_t Pos>
        using Set = typename BinarySeqSetHelper<std::make_index_sequence<sizeof...(Bs)>,
                                 SetType,
                                 Pos,
                                 sizeof...(Bs),
                                 Bs...>::type;
    };

    template<IsBinary B, std::size_t N, IsBinary... Bs>
    struct GenBinarySeq {
        using type = typename GenBinarySeq<B, N - 1, Bs..., B>::type;
    };

    template<IsBinary B, IsBinary... Bs>
    struct GenBinarySeq<B, 0, Bs...> {
        using type = typename IType<BinarySeq<Bs...>>::type;
    };
}
