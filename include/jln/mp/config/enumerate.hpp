#pragma once

#define JLN_MP_NIL

#define JLN_MP_GEN_XS_16_64_256_1024(func) \
  func(16, JLN_MP_XS_16)                   \
  func(64, JLN_MP_XS_64)                   \
  func(256, JLN_MP_XS_256)                 \
  func(1024, JLN_MP_XS_1024)

#define JLN_MP_GEN_XS_16_64_256(func) \
  func(16, JLN_MP_XS_16)              \
  func(64, JLN_MP_XS_64)              \
  func(256, JLN_MP_XS_256)

#define JLN_MP_XS_0(before, after)

#define JLN_MP_XS_1(before, after) before _0 after

#define JLN_MP_XS_4(before, after)                                    \
  before _0 after, before _1 after, before _2 after, before _3 after  \

#define JLN_MP_XS_16(before, after)                                     \
  before _0 after, before _1 after, before _2 after, before _3 after,   \
  before _4 after, before _5 after, before _6 after, before _7 after,   \
  before _8 after, before _9 after, before _10 after, before _11 after, \
  before _12 after, before _13 after, before _14 after, before _15 after

#define JLN_MP_XS_64(before, after) JLN_MP_XS_16(before, after),          \
  before _16 after, before _17 after, before _18 after, before _19 after, \
  before _20 after, before _21 after, before _22 after, before _23 after, \
  before _24 after, before _25 after, before _26 after, before _27 after, \
  before _28 after, before _29 after, before _30 after, before _31 after, \
  before _32 after, before _33 after, before _34 after, before _35 after, \
  before _36 after, before _37 after, before _38 after, before _39 after, \
  before _40 after, before _41 after, before _42 after, before _43 after, \
  before _44 after, before _45 after, before _46 after, before _47 after, \
  before _48 after, before _49 after, before _50 after, before _51 after, \
  before _52 after, before _53 after, before _54 after, before _55 after, \
  before _56 after, before _57 after, before _58 after, before _59 after, \
  before _60 after, before _61 after, before _62 after, before _63 after

#define JLN_MP_XS_256(before, after) JLN_MP_XS_64(before, after),             \
  before _64 after, before _65 after, before _66 after, before _67 after,     \
  before _68 after, before _69 after, before _70 after, before _71 after,     \
  before _72 after, before _73 after, before _74 after, before _75 after,     \
  before _76 after, before _77 after, before _78 after, before _79 after,     \
  before _80 after, before _81 after, before _82 after, before _83 after,     \
  before _84 after, before _85 after, before _86 after, before _87 after,     \
  before _88 after, before _89 after, before _90 after, before _91 after,     \
  before _92 after, before _93 after, before _94 after, before _95 after,     \
  before _96 after, before _97 after, before _98 after, before _99 after,     \
  before _100 after, before _101 after, before _102 after, before _103 after, \
  before _104 after, before _105 after, before _106 after, before _107 after, \
  before _108 after, before _109 after, before _110 after, before _111 after, \
  before _112 after, before _113 after, before _114 after, before _115 after, \
  before _116 after, before _117 after, before _118 after, before _119 after, \
  before _120 after, before _121 after, before _122 after, before _123 after, \
  before _124 after, before _125 after, before _126 after, before _127 after, \
  before _128 after, before _129 after, before _130 after, before _131 after, \
  before _132 after, before _133 after, before _134 after, before _135 after, \
  before _136 after, before _137 after, before _138 after, before _139 after, \
  before _140 after, before _141 after, before _142 after, before _143 after, \
  before _144 after, before _145 after, before _146 after, before _147 after, \
  before _148 after, before _149 after, before _150 after, before _151 after, \
  before _152 after, before _153 after, before _154 after, before _155 after, \
  before _156 after, before _157 after, before _158 after, before _159 after, \
  before _160 after, before _161 after, before _162 after, before _163 after, \
  before _164 after, before _165 after, before _166 after, before _167 after, \
  before _168 after, before _169 after, before _170 after, before _171 after, \
  before _172 after, before _173 after, before _174 after, before _175 after, \
  before _176 after, before _177 after, before _178 after, before _179 after, \
  before _180 after, before _181 after, before _182 after, before _183 after, \
  before _184 after, before _185 after, before _186 after, before _187 after, \
  before _188 after, before _189 after, before _190 after, before _191 after, \
  before _192 after, before _193 after, before _194 after, before _195 after, \
  before _196 after, before _197 after, before _198 after, before _199 after, \
  before _200 after, before _201 after, before _202 after, before _203 after, \
  before _204 after, before _205 after, before _206 after, before _207 after, \
  before _208 after, before _209 after, before _210 after, before _211 after, \
  before _212 after, before _213 after, before _214 after, before _215 after, \
  before _216 after, before _217 after, before _218 after, before _219 after, \
  before _220 after, before _221 after, before _222 after, before _223 after, \
  before _224 after, before _225 after, before _226 after, before _227 after, \
  before _228 after, before _229 after, before _230 after, before _231 after, \
  before _232 after, before _233 after, before _234 after, before _235 after, \
  before _236 after, before _237 after, before _238 after, before _239 after, \
  before _240 after, before _241 after, before _242 after, before _243 after, \
  before _244 after, before _245 after, before _246 after, before _247 after, \
  before _248 after, before _249 after, before _250 after, before _251 after, \
  before _252 after, before _253 after, before _254 after, before _255 after

#define JLN_MP_XS_1024(before, after) JLN_MP_XS_256(before, after),               \
  before _256 after, before _257 after, before _258 after, before _259 after,     \
  before _260 after, before _261 after, before _262 after, before _263 after,     \
  before _264 after, before _265 after, before _266 after, before _267 after,     \
  before _268 after, before _269 after, before _270 after, before _271 after,     \
  before _272 after, before _273 after, before _274 after, before _275 after,     \
  before _276 after, before _277 after, before _278 after, before _279 after,     \
  before _280 after, before _281 after, before _282 after, before _283 after,     \
  before _284 after, before _285 after, before _286 after, before _287 after,     \
  before _288 after, before _289 after, before _290 after, before _291 after,     \
  before _292 after, before _293 after, before _294 after, before _295 after,     \
  before _296 after, before _297 after, before _298 after, before _299 after,     \
  before _300 after, before _301 after, before _302 after, before _303 after,     \
  before _304 after, before _305 after, before _306 after, before _307 after,     \
  before _308 after, before _309 after, before _310 after, before _311 after,     \
  before _312 after, before _313 after, before _314 after, before _315 after,     \
  before _316 after, before _317 after, before _318 after, before _319 after,     \
  before _320 after, before _321 after, before _322 after, before _323 after,     \
  before _324 after, before _325 after, before _326 after, before _327 after,     \
  before _328 after, before _329 after, before _330 after, before _331 after,     \
  before _332 after, before _333 after, before _334 after, before _335 after,     \
  before _336 after, before _337 after, before _338 after, before _339 after,     \
  before _340 after, before _341 after, before _342 after, before _343 after,     \
  before _344 after, before _345 after, before _346 after, before _347 after,     \
  before _348 after, before _349 after, before _350 after, before _351 after,     \
  before _352 after, before _353 after, before _354 after, before _355 after,     \
  before _356 after, before _357 after, before _358 after, before _359 after,     \
  before _360 after, before _361 after, before _362 after, before _363 after,     \
  before _364 after, before _365 after, before _366 after, before _367 after,     \
  before _368 after, before _369 after, before _370 after, before _371 after,     \
  before _372 after, before _373 after, before _374 after, before _375 after,     \
  before _376 after, before _377 after, before _378 after, before _379 after,     \
  before _380 after, before _381 after, before _382 after, before _383 after,     \
  before _384 after, before _385 after, before _386 after, before _387 after,     \
  before _388 after, before _389 after, before _390 after, before _391 after,     \
  before _392 after, before _393 after, before _394 after, before _395 after,     \
  before _396 after, before _397 after, before _398 after, before _399 after,     \
  before _400 after, before _401 after, before _402 after, before _403 after,     \
  before _404 after, before _405 after, before _406 after, before _407 after,     \
  before _408 after, before _409 after, before _410 after, before _411 after,     \
  before _412 after, before _413 after, before _414 after, before _415 after,     \
  before _416 after, before _417 after, before _418 after, before _419 after,     \
  before _420 after, before _421 after, before _422 after, before _423 after,     \
  before _424 after, before _425 after, before _426 after, before _427 after,     \
  before _428 after, before _429 after, before _430 after, before _431 after,     \
  before _432 after, before _433 after, before _434 after, before _435 after,     \
  before _436 after, before _437 after, before _438 after, before _439 after,     \
  before _440 after, before _441 after, before _442 after, before _443 after,     \
  before _444 after, before _445 after, before _446 after, before _447 after,     \
  before _448 after, before _449 after, before _450 after, before _451 after,     \
  before _452 after, before _453 after, before _454 after, before _455 after,     \
  before _456 after, before _457 after, before _458 after, before _459 after,     \
  before _460 after, before _461 after, before _462 after, before _463 after,     \
  before _464 after, before _465 after, before _466 after, before _467 after,     \
  before _468 after, before _469 after, before _470 after, before _471 after,     \
  before _472 after, before _473 after, before _474 after, before _475 after,     \
  before _476 after, before _477 after, before _478 after, before _479 after,     \
  before _480 after, before _481 after, before _482 after, before _483 after,     \
  before _484 after, before _485 after, before _486 after, before _487 after,     \
  before _488 after, before _489 after, before _490 after, before _491 after,     \
  before _492 after, before _493 after, before _494 after, before _495 after,     \
  before _496 after, before _497 after, before _498 after, before _499 after,     \
  before _500 after, before _501 after, before _502 after, before _503 after,     \
  before _504 after, before _505 after, before _506 after, before _507 after,     \
  before _508 after, before _509 after, before _510 after, before _511 after,     \
  before _512 after, before _513 after, before _514 after, before _515 after,     \
  before _516 after, before _517 after, before _518 after, before _519 after,     \
  before _520 after, before _521 after, before _522 after, before _523 after,     \
  before _524 after, before _525 after, before _526 after, before _527 after,     \
  before _528 after, before _529 after, before _530 after, before _531 after,     \
  before _532 after, before _533 after, before _534 after, before _535 after,     \
  before _536 after, before _537 after, before _538 after, before _539 after,     \
  before _540 after, before _541 after, before _542 after, before _543 after,     \
  before _544 after, before _545 after, before _546 after, before _547 after,     \
  before _548 after, before _549 after, before _550 after, before _551 after,     \
  before _552 after, before _553 after, before _554 after, before _555 after,     \
  before _556 after, before _557 after, before _558 after, before _559 after,     \
  before _560 after, before _561 after, before _562 after, before _563 after,     \
  before _564 after, before _565 after, before _566 after, before _567 after,     \
  before _568 after, before _569 after, before _570 after, before _571 after,     \
  before _572 after, before _573 after, before _574 after, before _575 after,     \
  before _576 after, before _577 after, before _578 after, before _579 after,     \
  before _580 after, before _581 after, before _582 after, before _583 after,     \
  before _584 after, before _585 after, before _586 after, before _587 after,     \
  before _588 after, before _589 after, before _590 after, before _591 after,     \
  before _592 after, before _593 after, before _594 after, before _595 after,     \
  before _596 after, before _597 after, before _598 after, before _599 after,     \
  before _600 after, before _601 after, before _602 after, before _603 after,     \
  before _604 after, before _605 after, before _606 after, before _607 after,     \
  before _608 after, before _609 after, before _610 after, before _611 after,     \
  before _612 after, before _613 after, before _614 after, before _615 after,     \
  before _616 after, before _617 after, before _618 after, before _619 after,     \
  before _620 after, before _621 after, before _622 after, before _623 after,     \
  before _624 after, before _625 after, before _626 after, before _627 after,     \
  before _628 after, before _629 after, before _630 after, before _631 after,     \
  before _632 after, before _633 after, before _634 after, before _635 after,     \
  before _636 after, before _637 after, before _638 after, before _639 after,     \
  before _640 after, before _641 after, before _642 after, before _643 after,     \
  before _644 after, before _645 after, before _646 after, before _647 after,     \
  before _648 after, before _649 after, before _650 after, before _651 after,     \
  before _652 after, before _653 after, before _654 after, before _655 after,     \
  before _656 after, before _657 after, before _658 after, before _659 after,     \
  before _660 after, before _661 after, before _662 after, before _663 after,     \
  before _664 after, before _665 after, before _666 after, before _667 after,     \
  before _668 after, before _669 after, before _670 after, before _671 after,     \
  before _672 after, before _673 after, before _674 after, before _675 after,     \
  before _676 after, before _677 after, before _678 after, before _679 after,     \
  before _680 after, before _681 after, before _682 after, before _683 after,     \
  before _684 after, before _685 after, before _686 after, before _687 after,     \
  before _688 after, before _689 after, before _690 after, before _691 after,     \
  before _692 after, before _693 after, before _694 after, before _695 after,     \
  before _696 after, before _697 after, before _698 after, before _699 after,     \
  before _700 after, before _701 after, before _702 after, before _703 after,     \
  before _704 after, before _705 after, before _706 after, before _707 after,     \
  before _708 after, before _709 after, before _710 after, before _711 after,     \
  before _712 after, before _713 after, before _714 after, before _715 after,     \
  before _716 after, before _717 after, before _718 after, before _719 after,     \
  before _720 after, before _721 after, before _722 after, before _723 after,     \
  before _724 after, before _725 after, before _726 after, before _727 after,     \
  before _728 after, before _729 after, before _730 after, before _731 after,     \
  before _732 after, before _733 after, before _734 after, before _735 after,     \
  before _736 after, before _737 after, before _738 after, before _739 after,     \
  before _740 after, before _741 after, before _742 after, before _743 after,     \
  before _744 after, before _745 after, before _746 after, before _747 after,     \
  before _748 after, before _749 after, before _750 after, before _751 after,     \
  before _752 after, before _753 after, before _754 after, before _755 after,     \
  before _756 after, before _757 after, before _758 after, before _759 after,     \
  before _760 after, before _761 after, before _762 after, before _763 after,     \
  before _764 after, before _765 after, before _766 after, before _767 after,     \
  before _768 after, before _769 after, before _770 after, before _771 after,     \
  before _772 after, before _773 after, before _774 after, before _775 after,     \
  before _776 after, before _777 after, before _778 after, before _779 after,     \
  before _780 after, before _781 after, before _782 after, before _783 after,     \
  before _784 after, before _785 after, before _786 after, before _787 after,     \
  before _788 after, before _789 after, before _790 after, before _791 after,     \
  before _792 after, before _793 after, before _794 after, before _795 after,     \
  before _796 after, before _797 after, before _798 after, before _799 after,     \
  before _800 after, before _801 after, before _802 after, before _803 after,     \
  before _804 after, before _805 after, before _806 after, before _807 after,     \
  before _808 after, before _809 after, before _810 after, before _811 after,     \
  before _812 after, before _813 after, before _814 after, before _815 after,     \
  before _816 after, before _817 after, before _818 after, before _819 after,     \
  before _820 after, before _821 after, before _822 after, before _823 after,     \
  before _824 after, before _825 after, before _826 after, before _827 after,     \
  before _828 after, before _829 after, before _830 after, before _831 after,     \
  before _832 after, before _833 after, before _834 after, before _835 after,     \
  before _836 after, before _837 after, before _838 after, before _839 after,     \
  before _840 after, before _841 after, before _842 after, before _843 after,     \
  before _844 after, before _845 after, before _846 after, before _847 after,     \
  before _848 after, before _849 after, before _850 after, before _851 after,     \
  before _852 after, before _853 after, before _854 after, before _855 after,     \
  before _856 after, before _857 after, before _858 after, before _859 after,     \
  before _860 after, before _861 after, before _862 after, before _863 after,     \
  before _864 after, before _865 after, before _866 after, before _867 after,     \
  before _868 after, before _869 after, before _870 after, before _871 after,     \
  before _872 after, before _873 after, before _874 after, before _875 after,     \
  before _876 after, before _877 after, before _878 after, before _879 after,     \
  before _880 after, before _881 after, before _882 after, before _883 after,     \
  before _884 after, before _885 after, before _886 after, before _887 after,     \
  before _888 after, before _889 after, before _890 after, before _891 after,     \
  before _892 after, before _893 after, before _894 after, before _895 after,     \
  before _896 after, before _897 after, before _898 after, before _899 after,     \
  before _900 after, before _901 after, before _902 after, before _903 after,     \
  before _904 after, before _905 after, before _906 after, before _907 after,     \
  before _908 after, before _909 after, before _910 after, before _911 after,     \
  before _912 after, before _913 after, before _914 after, before _915 after,     \
  before _916 after, before _917 after, before _918 after, before _919 after,     \
  before _920 after, before _921 after, before _922 after, before _923 after,     \
  before _924 after, before _925 after, before _926 after, before _927 after,     \
  before _928 after, before _929 after, before _930 after, before _931 after,     \
  before _932 after, before _933 after, before _934 after, before _935 after,     \
  before _936 after, before _937 after, before _938 after, before _939 after,     \
  before _940 after, before _941 after, before _942 after, before _943 after,     \
  before _944 after, before _945 after, before _946 after, before _947 after,     \
  before _948 after, before _949 after, before _950 after, before _951 after,     \
  before _952 after, before _953 after, before _954 after, before _955 after,     \
  before _956 after, before _957 after, before _958 after, before _959 after,     \
  before _960 after, before _961 after, before _962 after, before _963 after,     \
  before _964 after, before _965 after, before _966 after, before _967 after,     \
  before _968 after, before _969 after, before _970 after, before _971 after,     \
  before _972 after, before _973 after, before _974 after, before _975 after,     \
  before _976 after, before _977 after, before _978 after, before _979 after,     \
  before _980 after, before _981 after, before _982 after, before _983 after,     \
  before _984 after, before _985 after, before _986 after, before _987 after,     \
  before _988 after, before _989 after, before _990 after, before _991 after,     \
  before _992 after, before _993 after, before _994 after, before _995 after,     \
  before _996 after, before _997 after, before _998 after, before _999 after,     \
  before _1000 after, before _1001 after, before _1002 after, before _1003 after, \
  before _1004 after, before _1005 after, before _1006 after, before _1007 after, \
  before _1008 after, before _1009 after, before _1010 after, before _1011 after, \
  before _1012 after, before _1013 after, before _1014 after, before _1015 after, \
  before _1016 after, before _1017 after, before _1018 after, before _1019 after, \
  before _1020 after, before _1021 after, before _1022 after, before _1023 after
