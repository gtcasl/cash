#pragma once

// macro primitives

#define CH_COMMA ,
#define CH_REM(...) __VA_ARGS__
#define CH_EAT(...)

#define CH_STRINGIZE_(x) #x
#define CH_STRINGIZE(x) CH_STRINGIZE_(x)

#define CH_CONCAT_(x, ...) x ## __VA_ARGS__
#define CH_CONCAT(x, ...) CH_CONCAT_(x, __VA_ARGS__)

// conditional macro

#define CH_IIF_0(x, y) y
#define CH_IIF_1(x, y) x
#define CH_IIF(c) CH_CONCAT(CH_IIF_, c)

#define CH_PAIR_FIRST(a, b) a
#define CH_PAIR_SECOND(a, b) b

// pair macros

#define CH_PAIR(x) CH_REM x
#define CH_PAIR_HEAD_(x, ...) CH_REM x
#define CH_PAIR_PROBE_(...) (__VA_ARGS__),
#define CH_PAIR_L_(...) CH_PAIR_HEAD_(__VA_ARGS__)
#define CH_PAIR_L(x) CH_PAIR_L_(CH_PAIR_PROBE_ x,)
#define CH_PAIR_R(x) CH_EAT x

// separator macros

#define CH_SEP_COMMA() ,
#define CH_SEP_SEMICOLON() ;
#define CH_SEP_PLUS() +
#define CH_SEP_OR() |
#define CH_SEP_COLON() :
#define CH_SEP_SPACE() /**/

// MAKE_UNIQUE macro

#define CH_MAKE_UNIQUE(x) CH_CONCAT(x, __COUNTER__)

// NARG macro

#define CH_NARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10,_11,_12,_13,_14,_15,_16, \
                  _17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32, \
                  _33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48, \
                  _49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63, N, ...) N
#define CH_NARG_R() 63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48, \
                    47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32, \
                    31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16, \
                    15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define CH_NARG_(...) CH_NARG_N(__VA_ARGS__) 
#define CH_NARG(...)  CH_NARG_(__VA_ARGS__, CH_NARG_R())

// FOR_EACH macro

#define CH_FOR_EACH_1(what, sep, x, ...)   what(0, x)
#define CH_FOR_EACH_2(what, sep, x, ...)   what(1, x) sep() CH_FOR_EACH_1(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_3(what, sep, x, ...)   what(2, x) sep() CH_FOR_EACH_2(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_4(what, sep, x, ...)   what(3, x) sep() CH_FOR_EACH_3(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_5(what, sep, x, ...)   what(4, x) sep() CH_FOR_EACH_4(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_6(what, sep, x, ...)   what(5, x) sep() CH_FOR_EACH_5(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_7(what, sep, x, ...)   what(6, x) sep() CH_FOR_EACH_6(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_8(what, sep, x, ...)   what(7, x) sep() CH_FOR_EACH_7(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_9(what, sep, x, ...)   what(8, x) sep() CH_FOR_EACH_8(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_10(what, sep, x, ...)  what(9, x) sep() CH_FOR_EACH_9(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_11(what, sep, x, ...)  what(10, x) sep() CH_FOR_EACH_10(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_12(what, sep, x, ...)  what(11, x) sep() CH_FOR_EACH_11(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_13(what, sep, x, ...)  what(12, x) sep() CH_FOR_EACH_12(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_14(what, sep, x, ...)  what(13, x) sep() CH_FOR_EACH_13(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_15(what, sep, x, ...)  what(14, x) sep() CH_FOR_EACH_14(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_16(what, sep, x, ...)  what(15, x) sep() CH_FOR_EACH_15(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_17(what, sep, x, ...)  what(16, x) sep() CH_FOR_EACH_16(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_18(what, sep, x, ...)  what(17, x) sep() CH_FOR_EACH_17(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_19(what, sep, x, ...)  what(18, x) sep() CH_FOR_EACH_18(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_20(what, sep, x, ...)  what(19, x) sep() CH_FOR_EACH_19(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_21(what, sep, x, ...)  what(20, x) sep() CH_FOR_EACH_20(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_22(what, sep, x, ...)  what(21, x) sep() CH_FOR_EACH_21(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_23(what, sep, x, ...)  what(22, x) sep() CH_FOR_EACH_22(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_24(what, sep, x, ...)  what(23, x) sep() CH_FOR_EACH_23(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_25(what, sep, x, ...)  what(24, x) sep() CH_FOR_EACH_24(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_26(what, sep, x, ...)  what(25, x) sep() CH_FOR_EACH_25(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_27(what, sep, x, ...)  what(26, x) sep() CH_FOR_EACH_26(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_28(what, sep, x, ...)  what(27, x) sep() CH_FOR_EACH_27(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_29(what, sep, x, ...)  what(28, x) sep() CH_FOR_EACH_28(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_30(what, sep, x, ...)  what(29, x) sep() CH_FOR_EACH_29(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_31(what, sep, x, ...)  what(30, x) sep() CH_FOR_EACH_30(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_32(what, sep, x, ...)  what(31, x) sep() CH_FOR_EACH_31(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_33(what, sep, x, ...)  what(32, x) sep() CH_FOR_EACH_32(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_34(what, sep, x, ...)  what(33, x) sep() CH_FOR_EACH_33(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_35(what, sep, x, ...)  what(34, x) sep() CH_FOR_EACH_34(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_36(what, sep, x, ...)  what(35, x) sep() CH_FOR_EACH_35(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_37(what, sep, x, ...)  what(36, x) sep() CH_FOR_EACH_36(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_38(what, sep, x, ...)  what(37, x) sep() CH_FOR_EACH_37(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_39(what, sep, x, ...)  what(38, x) sep() CH_FOR_EACH_38(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_40(what, sep, x, ...)  what(39, x) sep() CH_FOR_EACH_39(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_41(what, sep, x, ...)  what(40, x) sep() CH_FOR_EACH_40(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_42(what, sep, x, ...)  what(41, x) sep() CH_FOR_EACH_41(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_43(what, sep, x, ...)  what(42, x) sep() CH_FOR_EACH_42(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_44(what, sep, x, ...)  what(43, x) sep() CH_FOR_EACH_43(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_45(what, sep, x, ...)  what(44, x) sep() CH_FOR_EACH_44(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_46(what, sep, x, ...)  what(45, x) sep() CH_FOR_EACH_45(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_47(what, sep, x, ...)  what(46, x) sep() CH_FOR_EACH_46(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_48(what, sep, x, ...)  what(47, x) sep() CH_FOR_EACH_47(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_49(what, sep, x, ...)  what(48, x) sep() CH_FOR_EACH_48(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_50(what, sep, x, ...)  what(49, x) sep() CH_FOR_EACH_49(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_51(what, sep, x, ...)  what(50, x) sep() CH_FOR_EACH_50(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_52(what, sep, x, ...)  what(51, x) sep() CH_FOR_EACH_51(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_53(what, sep, x, ...)  what(52, x) sep() CH_FOR_EACH_52(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_54(what, sep, x, ...)  what(53, x) sep() CH_FOR_EACH_53(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_55(what, sep, x, ...)  what(54, x) sep() CH_FOR_EACH_54(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_56(what, sep, x, ...)  what(55, x) sep() CH_FOR_EACH_55(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_57(what, sep, x, ...)  what(56, x) sep() CH_FOR_EACH_56(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_58(what, sep, x, ...)  what(57, x) sep() CH_FOR_EACH_57(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_59(what, sep, x, ...)  what(58, x) sep() CH_FOR_EACH_58(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_60(what, sep, x, ...)  what(59, x) sep() CH_FOR_EACH_59(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_61(what, sep, x, ...)  what(60, x) sep() CH_FOR_EACH_60(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_62(what, sep, x, ...)  what(61, x) sep() CH_FOR_EACH_61(what, sep, __VA_ARGS__)
#define CH_FOR_EACH_63(what, sep, x, ...)  what(62, x) sep() CH_FOR_EACH_62(what, sep, __VA_ARGS__)

#define CH_FOR_EACH_(N, what, sep, ...) CH_CONCAT(CH_FOR_EACH_, N)(what, sep, __VA_ARGS__)
#define CH_FOR_EACH(what, sep, ...) CH_FOR_EACH_(CH_NARG(__VA_ARGS__), what, sep, __VA_ARGS__)

// REVERSE_FOR_EACH macro

#define CH_REVERSE_FOR_EACH_1(what, sep, x, ...)   what(0, x)
#define CH_REVERSE_FOR_EACH_2(what, sep, x, ...)   CH_REVERSE_FOR_EACH_1(what, sep, __VA_ARGS__) sep() what(1, x)
#define CH_REVERSE_FOR_EACH_3(what, sep, x, ...)   CH_REVERSE_FOR_EACH_2(what, sep, __VA_ARGS__) sep() what(2, x)
#define CH_REVERSE_FOR_EACH_4(what, sep, x, ...)   CH_REVERSE_FOR_EACH_3(what, sep, __VA_ARGS__) sep() what(3, x)
#define CH_REVERSE_FOR_EACH_5(what, sep, x, ...)   CH_REVERSE_FOR_EACH_4(what, sep, __VA_ARGS__) sep() what(4, x)
#define CH_REVERSE_FOR_EACH_6(what, sep, x, ...)   CH_REVERSE_FOR_EACH_5(what, sep, __VA_ARGS__) sep() what(5, x)
#define CH_REVERSE_FOR_EACH_7(what, sep, x, ...)   CH_REVERSE_FOR_EACH_6(what, sep, __VA_ARGS__) sep() what(6, x)
#define CH_REVERSE_FOR_EACH_8(what, sep, x, ...)   CH_REVERSE_FOR_EACH_7(what, sep, __VA_ARGS__) sep() what(7, x)
#define CH_REVERSE_FOR_EACH_9(what, sep, x, ...)   CH_REVERSE_FOR_EACH_8(what, sep, __VA_ARGS__) sep() what(8, x)
#define CH_REVERSE_FOR_EACH_10(what, sep, x, ...)  CH_REVERSE_FOR_EACH_9(what, sep, __VA_ARGS__) sep() what(9, x)
#define CH_REVERSE_FOR_EACH_11(what, sep, x, ...)  CH_REVERSE_FOR_EACH_10(what, sep, __VA_ARGS__) sep() what(10, x)
#define CH_REVERSE_FOR_EACH_12(what, sep, x, ...)  CH_REVERSE_FOR_EACH_11(what, sep, __VA_ARGS__) sep() what(11, x)
#define CH_REVERSE_FOR_EACH_13(what, sep, x, ...)  CH_REVERSE_FOR_EACH_12(what, sep, __VA_ARGS__) sep() what(12, x)
#define CH_REVERSE_FOR_EACH_14(what, sep, x, ...)  CH_REVERSE_FOR_EACH_13(what, sep, __VA_ARGS__) sep() what(13, x)
#define CH_REVERSE_FOR_EACH_15(what, sep, x, ...)  CH_REVERSE_FOR_EACH_14(what, sep, __VA_ARGS__) sep() what(14, x)
#define CH_REVERSE_FOR_EACH_16(what, sep, x, ...)  CH_REVERSE_FOR_EACH_15(what, sep, __VA_ARGS__) sep() what(15, x)
#define CH_REVERSE_FOR_EACH_17(what, sep, x, ...)  CH_REVERSE_FOR_EACH_16(what, sep, __VA_ARGS__) sep() what(16, x)
#define CH_REVERSE_FOR_EACH_18(what, sep, x, ...)  CH_REVERSE_FOR_EACH_17(what, sep, __VA_ARGS__) sep() what(17, x)
#define CH_REVERSE_FOR_EACH_19(what, sep, x, ...)  CH_REVERSE_FOR_EACH_18(what, sep, __VA_ARGS__) sep() what(18, x)
#define CH_REVERSE_FOR_EACH_20(what, sep, x, ...)  CH_REVERSE_FOR_EACH_19(what, sep, __VA_ARGS__) sep() what(19, x)
#define CH_REVERSE_FOR_EACH_21(what, sep, x, ...)  CH_REVERSE_FOR_EACH_20(what, sep, __VA_ARGS__) sep() what(20, x)
#define CH_REVERSE_FOR_EACH_22(what, sep, x, ...)  CH_REVERSE_FOR_EACH_21(what, sep, __VA_ARGS__) sep() what(21, x)
#define CH_REVERSE_FOR_EACH_23(what, sep, x, ...)  CH_REVERSE_FOR_EACH_22(what, sep, __VA_ARGS__) sep() what(22, x)
#define CH_REVERSE_FOR_EACH_24(what, sep, x, ...)  CH_REVERSE_FOR_EACH_23(what, sep, __VA_ARGS__) sep() what(23, x)
#define CH_REVERSE_FOR_EACH_25(what, sep, x, ...)  CH_REVERSE_FOR_EACH_24(what, sep, __VA_ARGS__) sep() what(24, x)
#define CH_REVERSE_FOR_EACH_26(what, sep, x, ...)  CH_REVERSE_FOR_EACH_25(what, sep, __VA_ARGS__) sep() what(25, x)
#define CH_REVERSE_FOR_EACH_27(what, sep, x, ...)  CH_REVERSE_FOR_EACH_26(what, sep, __VA_ARGS__) sep() what(26, x)
#define CH_REVERSE_FOR_EACH_28(what, sep, x, ...)  CH_REVERSE_FOR_EACH_27(what, sep, __VA_ARGS__) sep() what(27, x)
#define CH_REVERSE_FOR_EACH_29(what, sep, x, ...)  CH_REVERSE_FOR_EACH_28(what, sep, __VA_ARGS__) sep() what(28, x)
#define CH_REVERSE_FOR_EACH_30(what, sep, x, ...)  CH_REVERSE_FOR_EACH_29(what, sep, __VA_ARGS__) sep() what(29, x)
#define CH_REVERSE_FOR_EACH_31(what, sep, x, ...)  CH_REVERSE_FOR_EACH_30(what, sep, __VA_ARGS__) sep() what(30, x)
#define CH_REVERSE_FOR_EACH_32(what, sep, x, ...)  CH_REVERSE_FOR_EACH_31(what, sep, __VA_ARGS__) sep() what(31, x)
#define CH_REVERSE_FOR_EACH_33(what, sep, x, ...)  CH_REVERSE_FOR_EACH_32(what, sep, __VA_ARGS__) sep() what(32, x)
#define CH_REVERSE_FOR_EACH_34(what, sep, x, ...)  CH_REVERSE_FOR_EACH_33(what, sep, __VA_ARGS__) sep() what(33, x)
#define CH_REVERSE_FOR_EACH_35(what, sep, x, ...)  CH_REVERSE_FOR_EACH_34(what, sep, __VA_ARGS__) sep() what(34, x)
#define CH_REVERSE_FOR_EACH_36(what, sep, x, ...)  CH_REVERSE_FOR_EACH_35(what, sep, __VA_ARGS__) sep() what(35, x)
#define CH_REVERSE_FOR_EACH_37(what, sep, x, ...)  CH_REVERSE_FOR_EACH_36(what, sep, __VA_ARGS__) sep() what(36, x)
#define CH_REVERSE_FOR_EACH_38(what, sep, x, ...)  CH_REVERSE_FOR_EACH_37(what, sep, __VA_ARGS__) sep() what(37, x)
#define CH_REVERSE_FOR_EACH_39(what, sep, x, ...)  CH_REVERSE_FOR_EACH_38(what, sep, __VA_ARGS__) sep() what(38, x)
#define CH_REVERSE_FOR_EACH_40(what, sep, x, ...)  CH_REVERSE_FOR_EACH_39(what, sep, __VA_ARGS__) sep() what(39, x)
#define CH_REVERSE_FOR_EACH_41(what, sep, x, ...)  CH_REVERSE_FOR_EACH_40(what, sep, __VA_ARGS__) sep() what(40, x)
#define CH_REVERSE_FOR_EACH_42(what, sep, x, ...)  CH_REVERSE_FOR_EACH_41(what, sep, __VA_ARGS__) sep() what(41, x)
#define CH_REVERSE_FOR_EACH_43(what, sep, x, ...)  CH_REVERSE_FOR_EACH_42(what, sep, __VA_ARGS__) sep() what(42, x)
#define CH_REVERSE_FOR_EACH_44(what, sep, x, ...)  CH_REVERSE_FOR_EACH_43(what, sep, __VA_ARGS__) sep() what(43, x)
#define CH_REVERSE_FOR_EACH_45(what, sep, x, ...)  CH_REVERSE_FOR_EACH_44(what, sep, __VA_ARGS__) sep() what(44, x)
#define CH_REVERSE_FOR_EACH_46(what, sep, x, ...)  CH_REVERSE_FOR_EACH_45(what, sep, __VA_ARGS__) sep() what(45, x)
#define CH_REVERSE_FOR_EACH_47(what, sep, x, ...)  CH_REVERSE_FOR_EACH_46(what, sep, __VA_ARGS__) sep() what(46, x)
#define CH_REVERSE_FOR_EACH_48(what, sep, x, ...)  CH_REVERSE_FOR_EACH_47(what, sep, __VA_ARGS__) sep() what(47, x)
#define CH_REVERSE_FOR_EACH_49(what, sep, x, ...)  CH_REVERSE_FOR_EACH_48(what, sep, __VA_ARGS__) sep() what(48, x)
#define CH_REVERSE_FOR_EACH_50(what, sep, x, ...)  CH_REVERSE_FOR_EACH_49(what, sep, __VA_ARGS__) sep() what(49, x)
#define CH_REVERSE_FOR_EACH_51(what, sep, x, ...)  CH_REVERSE_FOR_EACH_50(what, sep, __VA_ARGS__) sep() what(50, x)
#define CH_REVERSE_FOR_EACH_52(what, sep, x, ...)  CH_REVERSE_FOR_EACH_51(what, sep, __VA_ARGS__) sep() what(51, x)
#define CH_REVERSE_FOR_EACH_53(what, sep, x, ...)  CH_REVERSE_FOR_EACH_52(what, sep, __VA_ARGS__) sep() what(52, x)
#define CH_REVERSE_FOR_EACH_54(what, sep, x, ...)  CH_REVERSE_FOR_EACH_53(what, sep, __VA_ARGS__) sep() what(53, x)
#define CH_REVERSE_FOR_EACH_55(what, sep, x, ...)  CH_REVERSE_FOR_EACH_54(what, sep, __VA_ARGS__) sep() what(54, x)
#define CH_REVERSE_FOR_EACH_56(what, sep, x, ...)  CH_REVERSE_FOR_EACH_55(what, sep, __VA_ARGS__) sep() what(55, x)
#define CH_REVERSE_FOR_EACH_57(what, sep, x, ...)  CH_REVERSE_FOR_EACH_56(what, sep, __VA_ARGS__) sep() what(56, x)
#define CH_REVERSE_FOR_EACH_58(what, sep, x, ...)  CH_REVERSE_FOR_EACH_57(what, sep, __VA_ARGS__) sep() what(57, x)
#define CH_REVERSE_FOR_EACH_59(what, sep, x, ...)  CH_REVERSE_FOR_EACH_58(what, sep, __VA_ARGS__) sep() what(58, x)
#define CH_REVERSE_FOR_EACH_60(what, sep, x, ...)  CH_REVERSE_FOR_EACH_59(what, sep, __VA_ARGS__) sep() what(59, x)
#define CH_REVERSE_FOR_EACH_61(what, sep, x, ...)  CH_REVERSE_FOR_EACH_60(what, sep, __VA_ARGS__) sep() what(60, x)
#define CH_REVERSE_FOR_EACH_62(what, sep, x, ...)  CH_REVERSE_FOR_EACH_61(what, sep, __VA_ARGS__) sep() what(61, x)
#define CH_REVERSE_FOR_EACH_63(what, sep, x, ...)  CH_REVERSE_FOR_EACH_62(what, sep, __VA_ARGS__) sep() what(62, x)

#define CH_REVERSE_FOR_EACH_(N, what, sep, ...) CH_CONCAT(CH_REVERSE_FOR_EACH_, N)(what, sep, __VA_ARGS__)
#define CH_REVERSE_FOR_EACH(what, sep, ...) CH_REVERSE_FOR_EACH_(CH_NARG(__VA_ARGS__), what, sep, __VA_ARGS__)

#define CH_INC(x) CH_INC_ ## x
#define CH_INC_0 1
#define CH_INC_1 2
#define CH_INC_2 3
#define CH_INC_3 4
#define CH_INC_4 5
#define CH_INC_5 6
#define CH_INC_6 7
#define CH_INC_7 8
#define CH_INC_8 9
#define CH_INC_9 10
#define CH_INC_10 11
#define CH_INC_11 12
#define CH_INC_12 13
#define CH_INC_13 14
#define CH_INC_14 15
#define CH_INC_15 16
#define CH_INC_16 17
#define CH_INC_17 18
#define CH_INC_18 19
#define CH_INC_19 20
#define CH_INC_20 21
#define CH_INC_21 22
#define CH_INC_22 23
#define CH_INC_23 24
#define CH_INC_24 25
#define CH_INC_25 26
#define CH_INC_26 27
#define CH_INC_27 28
#define CH_INC_28 29
#define CH_INC_29 30
#define CH_INC_30 31
#define CH_INC_31 32
#define CH_INC_32 33
#define CH_INC_33 34
#define CH_INC_34 35
#define CH_INC_35 36
#define CH_INC_36 37
#define CH_INC_37 38
#define CH_INC_38 39
#define CH_INC_39 40
#define CH_INC_40 41
#define CH_INC_41 42
#define CH_INC_42 43
#define CH_INC_43 44
#define CH_INC_44 45
#define CH_INC_45 46
#define CH_INC_46 47
#define CH_INC_47 48
#define CH_INC_48 49
#define CH_INC_49 50
#define CH_INC_50 51
#define CH_INC_51 52
#define CH_INC_52 53
#define CH_INC_53 54
#define CH_INC_54 55
#define CH_INC_55 56
#define CH_INC_56 57
#define CH_INC_57 58
#define CH_INC_58 59
#define CH_INC_59 60
#define CH_INC_60 61
#define CH_INC_61 62
#define CH_INC_62 63
#define CH_INC_63 64
