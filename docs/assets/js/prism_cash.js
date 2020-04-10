
(function (Prism) {
    Prism.languages.cash = Prism.languages.extend('cpp', {
        // highlight built-in macros
        'cash-macros': {
            pattern: /\b(?:ch_false|ch_true|ch_cout|__io|__sio|__flip|__in|__out|__interface|__enum|__struct|__union|__if|__elif|__else|__switch|__case|__default|__tap|__assert|__requires)\b/,
            alias: 'constant'
        },
        // highlight built-in types
        'cash-types': {
            pattern: /\b(?:ch_width_v|ch_signed_v|ch_direction_v|ch_system_t|ch_logic_t|ch_flags|ch_ostream|ch_system_io|ch_logic_io|ch_flip_io|ch_in|ch_out|ch_direction|ch_bool|ch_sbool|ch_bit[0-9]*|ch_sbit[0-9]*|ch_int[0-9]*|ch_sint[0-9]*|ch_uint[0-9]*|ch_suint[0-9]*|ch_fixed|ch_float|ch_reg|ch_vec|ch_rom|ch_mem|ch_device|ch_module|ch_udf_comb|ch_udf_seq|ch_simulator|ch_tracer|ch_tick)\b/,
            alias: 'keyword'
        },
        // highlight built-in functions
        'cash-functions-arithm': {
            pattern: /\b(?:ch_eq|ch_ne|ch_lt|ch_le|ch_gt|ch_ge|ch_not|ch_andl|ch_orl|ch_inv|ch_and|ch_or|ch_xor|ch_shl|ch_shr|ch_neg|ch_add|ch_sub|ch_mul|ch_div|ch_mod|ch_abs|ch_andr|ch_orr|ch_xorr|ch_rotl|ch_rotr|ch_slice|ch_aslice|ch_resize|ch_pad|ch_cat|ch_dup|ch_shuffle)\b/,
            alias: 'function'
        },
        'cash-functions-sequential': {
            pattern: /\b(?:ch_next|ch_nextEn|ch_dealy|ch_clock|ch_reset|ch_pushcd|ch_popcd|ch_cd)\b/,
            alias: 'function'
        },
        'cash-functions-select': {
            pattern: /\b(?:ch_sel|ch_case|ch_if|ch_switch|ch_min|ch_max)\b/,
            alias: 'function'
        },
        'cash-functions-cast': {
            pattern: /\b(?:ch_as|ch_ref|ch_sliceref|ch_asliceref|ch_tie)\b/,
            alias: 'function'
        },
        'cash-functions-debug': {
            pattern: /\b(?:ch_print|ch_println|ch_assert|ch_tap|ch_now)\b/,
            alias: 'function'
        },
        'cash-functions-hof': {
            pattern: /\b(?:ch_map|ch_fold|ch_zip|ch_scan)\b/,
            alias: 'function'
        },
        'cash-functions-miscs': {
            pattern: /\b(?:ch_clone)\b/,
            alias: 'function'
        },
        'cash-functions-system': {
            pattern: /\b(?:ch_read|ch_write|ch_stats|ch_toVerilog|ch_toFIRRTL|ch_setflags|ch_getflags)\b/,
            alias: 'function'
        }
    });    
}(Prism));