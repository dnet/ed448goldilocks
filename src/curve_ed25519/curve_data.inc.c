/* Rename table for eventual factoring into .c.inc, MSR ECC style */
#define SCALAR_LIMBS DECAF_255_SCALAR_LIMBS
#define SCALAR_BITS DECAF_255_SCALAR_BITS
#define NLIMBS DECAF_255_LIMBS
#define API_NS(_id) decaf_255_##_id
#define API_NS2(_pref,_id) _pref##_decaf_255_##_id
#define scalar_t decaf_255_scalar_t
#define point_t decaf_255_point_t
#define precomputed_s decaf_255_precomputed_s
#define SER_BYTES DECAF_255_SER_BYTES
#define IMAGINE_TWIST 1
#define P_MOD_8 5
#define COFACTOR 8

static const int EDWARDS_D = -121665;

static const scalar_t sc_p = {{{
    SC_LIMB(0x5812631a5cf5d3ed),
    SC_LIMB(0x14def9dea2f79cd6),
    SC_LIMB(0),
    SC_LIMB(0x1000000000000000)
}}};

/* sqrt(9) = 3 from the curve spec.  Not exported, but used by pregen tool. */
const unsigned char base_point_ser_for_pregen[SER_BYTES] = {
    3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

const gf SQRT_ONE_MINUS_D = {FIELD_LITERAL(
    0x6db8831bbddec,
    0x38d7b56c9c165,
    0x016b221394bdc,
    0x7540f7816214a,
    0x0a0d85b4032b1
)};