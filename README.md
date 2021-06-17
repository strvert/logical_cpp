# logical_cpp
コンパイル時Nビット加算回路 on 型システム

```c++:Nbit加算器動作確認
int main()
{
    using ASeq = Binary::BinarySeq<I, I, I, O, O, I, O, I, O, O, I, I, O, I, I, O>;
    using BSeq = Binary::BinarySeq<I, I, O, I, O, O, I, I, O, I, O, O, O, O, I, I>;
    NbitAdderPrintHelper<Circuits::NbitAdder<ASeq, BSeq>>::print_result();
}
```

```:出力
1110010100110110 + 1101001101000011 = 11011100001111001
```
