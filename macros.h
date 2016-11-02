#pragma once

// macro primitives
#define CHDL_COMMA ,
#define CHDL_REM(...) __VA_ARGS__
#define CHDL_EAT(...)
#define CHDL_STRINGIZE(x) #x
#define CHDL_CONCAT_(x, ...) x ## __VA_ARGS__
#define CHDL_CONCAT(x, ...) CHDL_CONCAT_(x, __VA_ARGS__)

// pair macros
#define CHDL_PAIR(x) CHDL_REM x
#define CHDL_PAIR_HEAD_(x, ...) CHDL_REM x
#define CHDL_PAIR_PROBE_(...) (__VA_ARGS__),
#define CHDL_PAIR_L_(...) CHDL_PAIR_HEAD_(__VA_ARGS__)
#define CHDL_PAIR_L(x) CHDL_PAIR_L_(CHDL_PAIR_PROBE_ x,)
#define CHDL_PAIR_R(x) CHDL_EAT x

// separator macros
#define CHDL_SEP_COMMA() ,
#define CHDL_SEP_SEMICOLON() ;
#define CHDL_SEP_PLUS() +
#define CHDL_SEP_COLON() :

// MAKE_UNIQUE macro
#define CHDL_MAKE_UNIQUE(x) CHDL_CONCAT(x, __COUNTER__)

// NARG macro
#define CHDL_NARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9,_10,_11,_12,_13,_14,_15,_16, \
                   _17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32, \
                   _33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48, \
                   _49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,  N, ...) N 
#define CHDL_NARG_R() 63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48, \
                      47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32, \
                      31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16, \
                      15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define CHDL_NARG_(...) CHDL_NARG_N(__VA_ARGS__) 
#define CHDL_NARG(...)  CHDL_NARG_(__VA_ARGS__, CHDL_NARG_R())

// FOR_EACH macro
#define CHDL_FOR_EACH_1(what, sep, x, ...)   what(0, x)
#define CHDL_FOR_EACH_2(what, sep, x, ...)   what(1, x) sep() CHDL_FOR_EACH_1(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_3(what, sep, x, ...)   what(2, x) sep() CHDL_FOR_EACH_2(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_4(what, sep, x, ...)   what(3, x) sep() CHDL_FOR_EACH_3(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_5(what, sep, x, ...)   what(4, x) sep() CHDL_FOR_EACH_4(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_6(what, sep, x, ...)   what(5, x) sep() CHDL_FOR_EACH_5(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_7(what, sep, x, ...)   what(6, x) sep() CHDL_FOR_EACH_6(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_8(what, sep, x, ...)   what(7, x) sep() CHDL_FOR_EACH_7(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_9(what, sep, x, ...)   what(8, x) sep() CHDL_FOR_EACH_8(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_10(what, sep, x, ...)  what(9, x) sep() CHDL_FOR_EACH_9(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_11(what, sep, x, ...)  what(10, x) sep() CHDL_FOR_EACH_10(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_12(what, sep, x, ...)  what(11, x) sep() CHDL_FOR_EACH_11(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_13(what, sep, x, ...)  what(12, x) sep() CHDL_FOR_EACH_12(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_14(what, sep, x, ...)  what(13, x) sep() CHDL_FOR_EACH_13(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_15(what, sep, x, ...)  what(14, x) sep() CHDL_FOR_EACH_14(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_16(what, sep, x, ...)  what(15, x) sep() CHDL_FOR_EACH_15(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_17(what, sep, x, ...)  what(16, x) sep() CHDL_FOR_EACH_16(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_18(what, sep, x, ...)  what(17, x) sep() CHDL_FOR_EACH_17(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_19(what, sep, x, ...)  what(18, x) sep() CHDL_FOR_EACH_18(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_20(what, sep, x, ...)  what(19, x) sep() CHDL_FOR_EACH_19(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_21(what, sep, x, ...)  what(20, x) sep() CHDL_FOR_EACH_20(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_22(what, sep, x, ...)  what(21, x) sep() CHDL_FOR_EACH_21(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_23(what, sep, x, ...)  what(22, x) sep() CHDL_FOR_EACH_22(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_24(what, sep, x, ...)  what(23, x) sep() CHDL_FOR_EACH_23(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_25(what, sep, x, ...)  what(24, x) sep() CHDL_FOR_EACH_24(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_26(what, sep, x, ...)  what(25, x) sep() CHDL_FOR_EACH_25(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_27(what, sep, x, ...)  what(26, x) sep() CHDL_FOR_EACH_26(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_28(what, sep, x, ...)  what(27, x) sep() CHDL_FOR_EACH_27(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_29(what, sep, x, ...)  what(28, x) sep() CHDL_FOR_EACH_28(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_30(what, sep, x, ...)  what(29, x) sep() CHDL_FOR_EACH_29(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_31(what, sep, x, ...)  what(30, x) sep() CHDL_FOR_EACH_30(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_32(what, sep, x, ...)  what(31, x) sep() CHDL_FOR_EACH_31(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_33(what, sep, x, ...)  what(32, x) sep() CHDL_FOR_EACH_32(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_34(what, sep, x, ...)  what(33, x) sep() CHDL_FOR_EACH_33(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_35(what, sep, x, ...)  what(34, x) sep() CHDL_FOR_EACH_34(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_36(what, sep, x, ...)  what(35, x) sep() CHDL_FOR_EACH_35(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_37(what, sep, x, ...)  what(36, x) sep() CHDL_FOR_EACH_36(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_38(what, sep, x, ...)  what(37, x) sep() CHDL_FOR_EACH_37(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_39(what, sep, x, ...)  what(38, x) sep() CHDL_FOR_EACH_38(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_40(what, sep, x, ...)  what(39, x) sep() CHDL_FOR_EACH_39(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_41(what, sep, x, ...)  what(40, x) sep() CHDL_FOR_EACH_40(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_42(what, sep, x, ...)  what(41, x) sep() CHDL_FOR_EACH_41(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_43(what, sep, x, ...)  what(42, x) sep() CHDL_FOR_EACH_42(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_44(what, sep, x, ...)  what(43, x) sep() CHDL_FOR_EACH_43(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_45(what, sep, x, ...)  what(44, x) sep() CHDL_FOR_EACH_44(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_46(what, sep, x, ...)  what(45, x) sep() CHDL_FOR_EACH_45(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_47(what, sep, x, ...)  what(46, x) sep() CHDL_FOR_EACH_46(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_48(what, sep, x, ...)  what(47, x) sep() CHDL_FOR_EACH_47(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_49(what, sep, x, ...)  what(48, x) sep() CHDL_FOR_EACH_48(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_50(what, sep, x, ...)  what(49, x) sep() CHDL_FOR_EACH_49(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_51(what, sep, x, ...)  what(50, x) sep() CHDL_FOR_EACH_50(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_52(what, sep, x, ...)  what(51, x) sep() CHDL_FOR_EACH_51(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_53(what, sep, x, ...)  what(52, x) sep() CHDL_FOR_EACH_52(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_54(what, sep, x, ...)  what(53, x) sep() CHDL_FOR_EACH_53(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_55(what, sep, x, ...)  what(54, x) sep() CHDL_FOR_EACH_54(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_56(what, sep, x, ...)  what(55, x) sep() CHDL_FOR_EACH_55(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_57(what, sep, x, ...)  what(56, x) sep() CHDL_FOR_EACH_56(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_58(what, sep, x, ...)  what(57, x) sep() CHDL_FOR_EACH_57(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_59(what, sep, x, ...)  what(58, x) sep() CHDL_FOR_EACH_58(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_60(what, sep, x, ...)  what(59, x) sep() CHDL_FOR_EACH_59(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_61(what, sep, x, ...)  what(60, x) sep() CHDL_FOR_EACH_60(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_62(what, sep, x, ...)  what(61, x) sep() CHDL_FOR_EACH_61(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH_63(what, sep, x, ...)  what(62, x) sep() CHDL_FOR_EACH_62(what, sep, __VA_ARGS__)

#define CHDL_FOR_EACH_(N, what, sep, ...) CHDL_CONCAT(CHDL_FOR_EACH_, N)(what, sep, __VA_ARGS__)
#define CHDL_FOR_EACH(what, sep, ...) CHDL_FOR_EACH_(CHDL_NARG(__VA_ARGS__), what, sep, __VA_ARGS__)

// REVERSE_FOR_EACH macro
#define CHDL_REVERSE_FOR_EACH_1(what, sep, x, ...)   what(0, x)
#define CHDL_REVERSE_FOR_EACH_2(what, sep, x, ...)   CHDL_REVERSE_FOR_EACH_1(what, sep, __VA_ARGS__) sep() what(1, x)
#define CHDL_REVERSE_FOR_EACH_3(what, sep, x, ...)   CHDL_REVERSE_FOR_EACH_2(what, sep, __VA_ARGS__) sep() what(2, x)
#define CHDL_REVERSE_FOR_EACH_4(what, sep, x, ...)   CHDL_REVERSE_FOR_EACH_3(what, sep, __VA_ARGS__) sep() what(3, x)
#define CHDL_REVERSE_FOR_EACH_5(what, sep, x, ...)   CHDL_REVERSE_FOR_EACH_4(what, sep, __VA_ARGS__) sep() what(4, x)
#define CHDL_REVERSE_FOR_EACH_6(what, sep, x, ...)   CHDL_REVERSE_FOR_EACH_5(what, sep, __VA_ARGS__) sep() what(5, x)
#define CHDL_REVERSE_FOR_EACH_7(what, sep, x, ...)   CHDL_REVERSE_FOR_EACH_6(what, sep, __VA_ARGS__) sep() what(6, x)
#define CHDL_REVERSE_FOR_EACH_8(what, sep, x, ...)   CHDL_REVERSE_FOR_EACH_7(what, sep, __VA_ARGS__) sep() what(7, x)
#define CHDL_REVERSE_FOR_EACH_9(what, sep, x, ...)   CHDL_REVERSE_FOR_EACH_8(what, sep, __VA_ARGS__) sep() what(8, x)
#define CHDL_REVERSE_FOR_EACH_10(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_9(what, sep, __VA_ARGS__) sep() what(9, x)
#define CHDL_REVERSE_FOR_EACH_11(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_10(what, sep, __VA_ARGS__) sep() what(10, x)
#define CHDL_REVERSE_FOR_EACH_12(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_11(what, sep, __VA_ARGS__) sep() what(11, x)
#define CHDL_REVERSE_FOR_EACH_13(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_12(what, sep, __VA_ARGS__) sep() what(12, x)
#define CHDL_REVERSE_FOR_EACH_14(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_13(what, sep, __VA_ARGS__) sep() what(13, x)
#define CHDL_REVERSE_FOR_EACH_15(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_14(what, sep, __VA_ARGS__) sep() what(14, x)
#define CHDL_REVERSE_FOR_EACH_16(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_15(what, sep, __VA_ARGS__) sep() what(15, x)
#define CHDL_REVERSE_FOR_EACH_17(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_16(what, sep, __VA_ARGS__) sep() what(16, x)
#define CHDL_REVERSE_FOR_EACH_18(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_17(what, sep, __VA_ARGS__) sep() what(17, x)
#define CHDL_REVERSE_FOR_EACH_19(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_18(what, sep, __VA_ARGS__) sep() what(18, x)
#define CHDL_REVERSE_FOR_EACH_20(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_19(what, sep, __VA_ARGS__) sep() what(19, x)
#define CHDL_REVERSE_FOR_EACH_21(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_20(what, sep, __VA_ARGS__) sep() what(20, x)
#define CHDL_REVERSE_FOR_EACH_22(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_21(what, sep, __VA_ARGS__) sep() what(21, x)
#define CHDL_REVERSE_FOR_EACH_23(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_22(what, sep, __VA_ARGS__) sep() what(22, x)
#define CHDL_REVERSE_FOR_EACH_24(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_23(what, sep, __VA_ARGS__) sep() what(23, x)
#define CHDL_REVERSE_FOR_EACH_25(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_24(what, sep, __VA_ARGS__) sep() what(24, x)
#define CHDL_REVERSE_FOR_EACH_26(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_25(what, sep, __VA_ARGS__) sep() what(25, x)
#define CHDL_REVERSE_FOR_EACH_27(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_26(what, sep, __VA_ARGS__) sep() what(26, x)
#define CHDL_REVERSE_FOR_EACH_28(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_27(what, sep, __VA_ARGS__) sep() what(27, x)
#define CHDL_REVERSE_FOR_EACH_29(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_28(what, sep, __VA_ARGS__) sep() what(28, x)
#define CHDL_REVERSE_FOR_EACH_30(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_29(what, sep, __VA_ARGS__) sep() what(29, x)
#define CHDL_REVERSE_FOR_EACH_31(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_30(what, sep, __VA_ARGS__) sep() what(30, x)
#define CHDL_REVERSE_FOR_EACH_32(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_31(what, sep, __VA_ARGS__) sep() what(31, x)
#define CHDL_REVERSE_FOR_EACH_33(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_32(what, sep, __VA_ARGS__) sep() what(32, x)
#define CHDL_REVERSE_FOR_EACH_34(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_33(what, sep, __VA_ARGS__) sep() what(33, x)
#define CHDL_REVERSE_FOR_EACH_35(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_34(what, sep, __VA_ARGS__) sep() what(34, x)
#define CHDL_REVERSE_FOR_EACH_36(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_35(what, sep, __VA_ARGS__) sep() what(35, x)
#define CHDL_REVERSE_FOR_EACH_37(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_36(what, sep, __VA_ARGS__) sep() what(36, x)
#define CHDL_REVERSE_FOR_EACH_38(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_37(what, sep, __VA_ARGS__) sep() what(37, x)
#define CHDL_REVERSE_FOR_EACH_39(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_38(what, sep, __VA_ARGS__) sep() what(38, x)
#define CHDL_REVERSE_FOR_EACH_40(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_39(what, sep, __VA_ARGS__) sep() what(39, x)
#define CHDL_REVERSE_FOR_EACH_41(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_40(what, sep, __VA_ARGS__) sep() what(40, x)
#define CHDL_REVERSE_FOR_EACH_42(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_41(what, sep, __VA_ARGS__) sep() what(41, x)
#define CHDL_REVERSE_FOR_EACH_43(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_42(what, sep, __VA_ARGS__) sep() what(42, x)
#define CHDL_REVERSE_FOR_EACH_44(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_43(what, sep, __VA_ARGS__) sep() what(43, x)
#define CHDL_REVERSE_FOR_EACH_45(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_44(what, sep, __VA_ARGS__) sep() what(44, x)
#define CHDL_REVERSE_FOR_EACH_46(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_45(what, sep, __VA_ARGS__) sep() what(45, x)
#define CHDL_REVERSE_FOR_EACH_47(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_46(what, sep, __VA_ARGS__) sep() what(46, x)
#define CHDL_REVERSE_FOR_EACH_48(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_47(what, sep, __VA_ARGS__) sep() what(47, x)
#define CHDL_REVERSE_FOR_EACH_49(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_48(what, sep, __VA_ARGS__) sep() what(48, x)
#define CHDL_REVERSE_FOR_EACH_50(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_49(what, sep, __VA_ARGS__) sep() what(49, x)
#define CHDL_REVERSE_FOR_EACH_51(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_50(what, sep, __VA_ARGS__) sep() what(50, x)
#define CHDL_REVERSE_FOR_EACH_52(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_51(what, sep, __VA_ARGS__) sep() what(51, x)
#define CHDL_REVERSE_FOR_EACH_53(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_52(what, sep, __VA_ARGS__) sep() what(52, x)
#define CHDL_REVERSE_FOR_EACH_54(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_53(what, sep, __VA_ARGS__) sep() what(53, x)
#define CHDL_REVERSE_FOR_EACH_55(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_54(what, sep, __VA_ARGS__) sep() what(54, x)
#define CHDL_REVERSE_FOR_EACH_56(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_55(what, sep, __VA_ARGS__) sep() what(55, x)
#define CHDL_REVERSE_FOR_EACH_57(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_56(what, sep, __VA_ARGS__) sep() what(56, x)
#define CHDL_REVERSE_FOR_EACH_58(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_57(what, sep, __VA_ARGS__) sep() what(57, x)
#define CHDL_REVERSE_FOR_EACH_59(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_58(what, sep, __VA_ARGS__) sep() what(58, x)
#define CHDL_REVERSE_FOR_EACH_60(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_59(what, sep, __VA_ARGS__) sep() what(59, x)
#define CHDL_REVERSE_FOR_EACH_61(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_60(what, sep, __VA_ARGS__) sep() what(60, x)
#define CHDL_REVERSE_FOR_EACH_62(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_61(what, sep, __VA_ARGS__) sep() what(61, x)
#define CHDL_REVERSE_FOR_EACH_63(what, sep, x, ...)  CHDL_REVERSE_FOR_EACH_62(what, sep, __VA_ARGS__) sep() what(62, x)

#define CHDL_REVERSE_FOR_EACH_(N, what, sep, ...) CHDL_CONCAT(CHDL_REVERSE_FOR_EACH_, N)(what, sep, __VA_ARGS__)
#define CHDL_REVERSE_FOR_EACH(what, sep, ...) CHDL_REVERSE_FOR_EACH_(CHDL_NARG(__VA_ARGS__), what, sep, __VA_ARGS__)

///////////////////////////////////////////////////////////////////////////////

#define CHDL_COUNTOF(a) (sizeof(a) / sizeof(a[0]))
#define CHDL_MAX(a,b) (((a) > (b)) ? (a) : (b))



