// SPDX-FileCopyrightText: 2023 Jonathan Poelen <jonathan.poelen@gmail.com>
// SPDX-License-Identifier: MIT
#pragma once

#include "jln/mp/number/numbers.hpp"

namespace ut
{
namespace
{
  namespace ints
  {
    struct bad_number
    {
      class a {};
      constexpr static a value {};
    };

    using seq_bad = jln::mp::list<bad_number>;
    using seq_bad_bad = jln::mp::list<bad_number, bad_number>;

    using _0 = jln::mp::number<0>;
    using _1 = jln::mp::number<1>;
    using _2 = jln::mp::number<2>;
    using _3 = jln::mp::number<3>;
    using _4 = jln::mp::number<4>;
    using _5 = jln::mp::number<5>;
    using _6 = jln::mp::number<6>;
    using _7 = jln::mp::number<7>;
    using _8 = jln::mp::number<8>;
    using _9 = jln::mp::number<9>;
    using _10 = jln::mp::number<10>;
    using _11 = jln::mp::number<11>;
    using _12 = jln::mp::number<12>;
    using _13 = jln::mp::number<13>;
    using _14 = jln::mp::number<14>;
    using _15 = jln::mp::number<15>;
    using _16 = jln::mp::number<16>;
    using _17 = jln::mp::number<17>;
    using _18 = jln::mp::number<18>;
    using _19 = jln::mp::number<19>;
    using _20 = jln::mp::number<20>;
    using _21 = jln::mp::number<21>;
    using _22 = jln::mp::number<22>;
    using _23 = jln::mp::number<23>;
    using _24 = jln::mp::number<24>;
    using _25 = jln::mp::number<25>;
    using _26 = jln::mp::number<26>;
    using _27 = jln::mp::number<27>;
    using _28 = jln::mp::number<28>;
    using _29 = jln::mp::number<29>;
    using _30 = jln::mp::number<30>;
    using _31 = jln::mp::number<31>;
    using _32 = jln::mp::number<32>;
    using _33 = jln::mp::number<33>;
    using _34 = jln::mp::number<34>;
    using _35 = jln::mp::number<35>;
    using _36 = jln::mp::number<36>;
    using _37 = jln::mp::number<37>;
    using _38 = jln::mp::number<38>;
    using _39 = jln::mp::number<39>;
    using _40 = jln::mp::number<40>;
    using _41 = jln::mp::number<41>;
    using _42 = jln::mp::number<42>;
    using _43 = jln::mp::number<43>;
    using _44 = jln::mp::number<44>;
    using _45 = jln::mp::number<45>;
    using _46 = jln::mp::number<46>;
    using _47 = jln::mp::number<47>;
    using _48 = jln::mp::number<48>;
    using _49 = jln::mp::number<49>;
    using _50 = jln::mp::number<50>;
    using _51 = jln::mp::number<51>;
    using _52 = jln::mp::number<52>;
    using _53 = jln::mp::number<53>;
    using _54 = jln::mp::number<54>;
    using _55 = jln::mp::number<55>;
    using _56 = jln::mp::number<56>;
    using _57 = jln::mp::number<57>;
    using _58 = jln::mp::number<58>;
    using _59 = jln::mp::number<59>;
    using _60 = jln::mp::number<60>;
    using _61 = jln::mp::number<61>;
    using _62 = jln::mp::number<62>;
    using _63 = jln::mp::number<63>;
    using _64 = jln::mp::number<64>;
    using _65 = jln::mp::number<65>;
    using _66 = jln::mp::number<66>;
    using _67 = jln::mp::number<67>;
    using _68 = jln::mp::number<68>;
    using _69 = jln::mp::number<69>;
    using _70 = jln::mp::number<70>;
    using _71 = jln::mp::number<71>;
    using _72 = jln::mp::number<72>;
    using _73 = jln::mp::number<73>;
    using _74 = jln::mp::number<74>;
    using _75 = jln::mp::number<75>;
    using _76 = jln::mp::number<76>;
    using _77 = jln::mp::number<77>;
    using _78 = jln::mp::number<78>;
    using _79 = jln::mp::number<79>;
    using _80 = jln::mp::number<80>;
    using _81 = jln::mp::number<81>;
    using _82 = jln::mp::number<82>;
    using _83 = jln::mp::number<83>;
    using _84 = jln::mp::number<84>;
    using _85 = jln::mp::number<85>;
    using _86 = jln::mp::number<86>;
    using _87 = jln::mp::number<87>;
    using _88 = jln::mp::number<88>;
    using _89 = jln::mp::number<89>;
    using _90 = jln::mp::number<90>;
    using _91 = jln::mp::number<91>;
    using _92 = jln::mp::number<92>;
    using _93 = jln::mp::number<93>;
    using _94 = jln::mp::number<94>;
    using _95 = jln::mp::number<95>;
    using _96 = jln::mp::number<96>;
    using _97 = jln::mp::number<97>;
    using _98 = jln::mp::number<98>;
    using _99 = jln::mp::number<99>;
    using _100 = jln::mp::number<100>;
    using _101 = jln::mp::number<101>;
    using _102 = jln::mp::number<102>;
    using _103 = jln::mp::number<103>;
    using _104 = jln::mp::number<104>;
    using _105 = jln::mp::number<105>;
    using _106 = jln::mp::number<106>;
    using _107 = jln::mp::number<107>;
    using _108 = jln::mp::number<108>;
    using _109 = jln::mp::number<109>;

    using seq_0 = jln::mp::emp::numbers<0>;
    using seq_1 = jln::mp::emp::numbers<1>;
    using seq_2 = jln::mp::emp::numbers<2>;
    using seq_3 = jln::mp::emp::numbers<3>;
    using seq_4 = jln::mp::emp::numbers<4>;
    using seq_5 = jln::mp::emp::numbers<5>;

    using seq_0_0 = jln::mp::emp::numbers<0, 0>;
    using seq_0_1 = jln::mp::emp::numbers<0, 1>;
    using seq_0_2 = jln::mp::emp::numbers<0, 2>;
    using seq_0_3 = jln::mp::emp::numbers<0, 3>;

    using seq_1_0 = jln::mp::emp::numbers<1, 0>;
    using seq_1_1 = jln::mp::emp::numbers<1, 1>;
    using seq_1_2 = jln::mp::emp::numbers<1, 2>;
    using seq_1_3 = jln::mp::emp::numbers<1, 3>;

    using seq_2_0 = jln::mp::emp::numbers<2, 0>;
    using seq_2_1 = jln::mp::emp::numbers<2, 1>;
    using seq_2_2 = jln::mp::emp::numbers<2, 2>;
    using seq_2_3 = jln::mp::emp::numbers<2, 3>;

    using seq_3_0 = jln::mp::emp::numbers<3, 0>;
    using seq_3_1 = jln::mp::emp::numbers<3, 1>;
    using seq_3_2 = jln::mp::emp::numbers<3, 2>;
    using seq_3_3 = jln::mp::emp::numbers<3, 3>;

    using seq_0_0_0 = jln::mp::emp::numbers<0, 0, 0>;
    using seq_1_1_1 = jln::mp::emp::numbers<1, 1, 1>;
    using seq_2_2_2 = jln::mp::emp::numbers<2, 2, 2>;
    using seq_0_1_2 = jln::mp::emp::numbers<0, 1, 2>;
    using seq_1_2_3 = jln::mp::emp::numbers<1, 2, 3>;
    using seq_2_3_4 = jln::mp::emp::numbers<2, 3, 4>;
    using seq_4_3_2 = jln::mp::emp::numbers<4, 3, 2>;
    using seq_3_2_1 = jln::mp::emp::numbers<3, 2, 1>;
    using seq_2_1_0 = jln::mp::emp::numbers<2, 1, 0>;

    using seq_0_2_4 = jln::mp::emp::numbers<0, 2, 4>;
    using seq_1_3_5 = jln::mp::emp::numbers<1, 3, 5>;

    using seq_0_1_2_3 = jln::mp::emp::numbers<0, 1, 2, 3>;

    using seq_0_1_0_2_0_3_0
      = jln::mp::emp::numbers<0, 1, 0, 2, 0, 3, 0>;

    using seq_0_1_2_3_4_5_6_7_8_9
      = jln::mp::emp::numbers<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>;
    using seq_1_2_3_4_5_6_7_8_9_10
      = jln::mp::emp::numbers<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>;

    using seq_1_3_5_7_9 = jln::mp::emp::numbers<1, 3, 5, 7, 9>;
    using seq_2_4_6_8_10 = jln::mp::emp::numbers<2, 4, 6, 8, 10>;
    using seq_0_2_4_6_8 = jln::mp::emp::numbers<0, 2, 4, 6, 8>;
  }
}
}
