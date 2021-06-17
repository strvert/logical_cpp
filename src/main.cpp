#include <iostream>
#include <fmt/core.h>
#include <type_traits>

#include "basic_gates.h"

#include "basic_adders.h"
#include "n_bit_adder.h"

using Binary::O;
using Binary::I;

template <Binary::IsBinary T>
struct bitToChar {};

template <Binary::IsZero T>
struct bitToChar<T> { inline static constexpr const char v = '0'; };

template <Binary::IsOne T>
struct bitToChar<T> { inline static constexpr const char v = '1'; };

template <Binary::IsBinary T>
constexpr const char bitToCharV = bitToChar<T>::v;

template <template <typename, typename> typename Gate>
static void printTruthTable(const std::string& title) {
    fmt::print("[{}]\n", title);
    fmt::print("0 0 | {}\n", bitToCharV<Gate<O, O>>);
    fmt::print("0 1 | {}\n", bitToCharV<Gate<O, I>>);
    fmt::print("1 0 | {}\n", bitToCharV<Gate<I, O>>);
    fmt::print("1 1 | {}\n", bitToCharV<Gate<I, I>>);
}

template <template <typename, typename> typename Gate>
static void printTruthTable2_2(const std::string& title) {
    fmt::print("[{}]\n", title);
    fmt::print("A B | Y X\n", title);
    fmt::print("0 0 | {} {}\n", bitToCharV<typename Gate<O, O>::Y>, bitToCharV<typename Gate<O, O>::X>);
    fmt::print("0 1 | {} {}\n", bitToCharV<typename Gate<O, I>::Y>, bitToCharV<typename Gate<O, I>::X>);
    fmt::print("1 0 | {} {}\n", bitToCharV<typename Gate<I, O>::Y>, bitToCharV<typename Gate<I, O>::X>);
    fmt::print("1 1 | {} {}\n", bitToCharV<typename Gate<I, I>::Y>, bitToCharV<typename Gate<I, I>::X>);
}

template <template <typename, typename, typename> typename Gate>
void printTruthTable3_2(const std::string& title)
{
    fmt::print("[{}]\n", title);
    fmt::print("A B C | Y X\n"
               "0 0 0 | {} {}\n0 0 1 | {} {}\n0 1 0 | {} {}\n0 1 1 | {} {}\n"
               "1 0 0 | {} {}\n1 0 1 | {} {}\n1 1 0 | {} {}\n1 1 1 | {} {}\n",
            bitToCharV<typename Gate<O, O, O>::Y>,
            bitToCharV<typename Gate<O, O, O>::X>,
            bitToCharV<typename Gate<O, O, I>::Y>,
            bitToCharV<typename Gate<O, O, I>::X>,
            bitToCharV<typename Gate<O, I, O>::Y>,
            bitToCharV<typename Gate<O, I, O>::X>,
            bitToCharV<typename Gate<O, I, I>::Y>,
            bitToCharV<typename Gate<O, I, I>::X>,
            bitToCharV<typename Gate<I, O, O>::Y>,
            bitToCharV<typename Gate<I, O, O>::X>,
            bitToCharV<typename Gate<I, O, I>::Y>,
            bitToCharV<typename Gate<I, O, I>::X>,
            bitToCharV<typename Gate<I, I, O>::Y>,
            bitToCharV<typename Gate<I, I, O>::X>,
            bitToCharV<typename Gate<I, I, I>::Y>,
            bitToCharV<typename Gate<I, I, I>::X>
            );
}

template <typename Bs>
struct BinarySeqPrintHelper;

template <Binary::IsBinary... S>
struct BinarySeqPrintHelper<Binary::BinarySeq<S...>> {
    static void print() {
        (fmt::print("{}", bitToCharV<S>), ...);
    }
};

template <typename Bs>
struct NbitAdderPrintHelper;

template <Binary::IsBinary... S1, Binary::IsBinary... S2>
struct NbitAdderPrintHelper<Circuits::NbitAdder<Binary::BinarySeq<S1...>, Binary::BinarySeq<S2...>>> {
    static void print_result() {
        (fmt::print("{}", bitToCharV<S1>), ...);
        fmt::print(" + ");
        (fmt::print("{}", bitToCharV<S2>), ...);

        using Adder = Circuits::NbitAdder<Binary::BinarySeq<S1...>, Binary::BinarySeq<S2...>>;
        fmt::print(" = ");
        BinarySeqPrintHelper<typename Adder::Ss>::print();
        fmt::print("\n");
    }
};

int main()
{
    using ASeq = Binary::GenBinarySeq<I, 100>::type;// Binary::BinarySeq<I, I, I, O, O, I, O, I, O, O, I, I, O, I, I, O>;
    using BSeq = Binary::GenBinarySeq<I, 100>::type;// Binary::BinarySeq<I, I, O, I, O, O, I, I, O, I, O, O, O, O, I, I>;
    NbitAdderPrintHelper<Circuits::NbitAdder<ASeq, BSeq>>::print_result();
}

// BinarySeqPrintHelper<Binary::GenBinarySeq<O, 10>::type::Set<I, 2>::Set<I, 1>::Set<I, 8>>::print();
// printTruthTable3to2<Circuits::FullAdder>();
