#ifndef GEN1_H_
#define GEN1_H_

#include <gb/gb.h>
#include <stdint.h>

#define PKMN_BLANK						0x00

#define ITEM_1_HIGHLIGHTED				0xD0
#define ITEM_2_HIGHLIGHTED				0xD1
#define ITEM_3_HIGHLIGHTED				0xD2
#define ITEM_1_SELECTED					0xD4
#define ITEM_2_SELECTED					0xD5
#define ITEM_3_SELECTED					0xD6

#define PKMN_MASTER						0x01
#define PKMN_SLAVE						0x02
#define PKMN_CONNECTED					0x60
// #define PKMN_CONNECTED					0x03
#define PKMN_WAIT						0x7F

#define PKMN_ACTION						0x60

#define PKMN_TRADE_CENTRE				ITEM_1_SELECTED
#define PKMN_COLOSSEUM					ITEM_2_SELECTED
#define PKMN_BREAK_LINK					ITEM_3_SELECTED

#define TRADE_CENTRE_WAIT				0xFD

#define pokechar_STOP_BYTE  0x50 
// Ends a string
#define pokechar_NULL_BYTE  0x00 
// Nothing, comes after the stop byte to fill in the rest

// ENG Characters
#define pokechar_SPACE  0x7F
#define pokechar_A  0x80
#define pokechar_B  0x81
#define pokechar_C  0x82
#define pokechar_D  0x83
#define pokechar_E  0x84
#define pokechar_F  0x85
#define pokechar_G  0x86
#define pokechar_H  0x87
#define pokechar_I  0x88
#define pokechar_J  0x89
#define pokechar_K  0x8A
#define pokechar_L  0x8B
#define pokechar_M  0x8C
#define pokechar_N  0x8D
#define pokechar_O  0x8E
#define pokechar_P  0x8F
#define pokechar_Q  0x90
#define pokechar_R  0x91
#define pokechar_S  0x92
#define pokechar_T  0x93
#define pokechar_U  0x94
#define pokechar_V  0x95
#define pokechar_W  0x96
#define pokechar_X  0x97
#define pokechar_Y  0x98
#define pokechar_Z  0x99
#define pokechar_OPEN_PARENTHESIS  0x9A
#define pokechar_CLOSE_PARENTHESIS  0x9B
#define pokechar_COLON  0x9C
#define pokechar_SEMICOLON  0x9D
#define pokechar_OPEN_BRACKET  0x9E
#define pokechar_CLOSE_BRACKET  0x9F
#define pokechar_a  0xA0
#define pokechar_b  0xA1
#define pokechar_c  0xA2
#define pokechar_d  0xA3
#define pokechar_e  0xA4
#define pokechar_f  0xA5
#define pokechar_g  0xA6
#define pokechar_h  0xA7
#define pokechar_i  0xA8
#define pokechar_j  0xA9
#define pokechar_k  0xAa
#define pokechar_l  0xAb
#define pokechar_m  0xAc
#define pokechar_n  0xAd
#define pokechar_o  0xAe
#define pokechar_p  0xAf
#define pokechar_q  0xB0
#define pokechar_r  0xB1
#define pokechar_s  0xB2
#define pokechar_t  0xB3
#define pokechar_u  0xB4
#define pokechar_v  0xB5
#define pokechar_w  0xB6
#define pokechar_x  0xB7
#define pokechar_y  0xB8
#define pokechar_z  0xB9
#define pokechar_e_accent  0xBA
#define pokechar_apostrophe_d  0xBB
#define pokechar_apostrophe_l  0xBC
#define pokechar_apostrophe_s  0xBD
#define pokechar_apostrophe_t  0xBE
#define pokechar_apostrophe_v  0xBF
#define pokechar_apostrophe  0xE0
#define pokechar_PK_character  0xE1
#define pokechar_MN_character  0xE2
#define pokechar_hyphen  0xE3
#define pokechar_apostrophe_r  0xE4
#define pokechar_apostrophe_m  0xE5
#define pokechar_question_mark  0xE6
#define pokechar_exclamation_mark  0xE7

// NOTE: `period` is never used in names. Instead use `decimal_point`
// . (used as punctuation)
#define pokechar_period  0xE8

#define pokechar_hollow_play  0xEC 
// ▷
#define pokechar_solid_play  0xED 
// ▶
#define pokechar_solid_down  0xEE 
// ▼
#define pokechar_male_symbol  0xEF 
// ♂
#define pokechar_pokemon_dollar  0xF0
#define pokechar_multiply  0xF1 
// ×
#define pokechar_decimal_point  0xF2 
// . (used as a decimal point)
#define pokechar_slash_forward  0xF3 
// /
#define pokechar_comma  0xF4 
// ,
#define pokechar_female_symbol  0xF5 
// ♀
#define pokechar_zero  0xF6
#define pokechar_one  0xF7
#define pokechar_two  0xF8
#define pokechar_three  0xF9
#define pokechar_four  0xFA
#define pokechar_five  0xFB
#define pokechar_six  0xFC
#define pokechar_seven  0xFD
#define pokechar_eight  0xFE
#define pokechar_nine  0xFF
// Characters that weren't removed from JPN when translating to ENG
// Some seem bolded, some are symbols, others are katakana or hiragana letters
#define pokechar_JPN_A  0x60
#define pokechar_JPN_B  0x61
#define pokechar_JPN_C  0x62
#define pokechar_JPN_D  0x63
#define pokechar_JPN_E  0x64
#define pokechar_JPN_F  0x65
#define pokechar_JPN_G  0x66
#define pokechar_JPN_H  0x67
#define pokechar_JPN_I  0x68
#define pokechar_JPN_V  0x69
#define pokechar_JPN_S  0x6A
#define pokechar_JPN_L  0x6B
#define pokechar_JPN_M  0x6C
#define pokechar_JPN_colon  0x6D
#define pokechar_hiragana_i  0x6E 
// ぃ
#define pokechar_hiragana_u  0x6F 
// ぅ
#define pokechar_open_single_quote  0x70 
// ‘
#define pokechar_close_single_quote  0x71 
// ’
#define pokechar_open_double_quote  0x72 
// “
#define pokechar_close_double_quote  0x73 
// ”
#define pokechar_dot  0x74 
// ・
#define pokechar_ellipsis  0x75 
// ⋯
#define pokechar_hiragana_a  0x76 
// ぁ
#define pokechar_hiragana_e  0x77 
// ぇ
#define pokechar_hiragana_o  0x78 
// ぉ
#define pokechar_katakana_a  0xE9 
// ァ
#define pokechar_katakana_u  0xEA 
// ゥ
#define pokechar_katakana_e  0xEB 
// ェ

enum connection_state_t {
	TRADE_CENTRE,
	NOT_CONNECTED,
	CONNECTED,
	COLOSSEUM,
};

enum trade_state_t {
	INIT = 0x00,
	READY = 0x01,
	DETECTED = 0x02,
	DATA_TX = 0x03,
	DATA_TX_WAIT = 0x04,
	DATA_TX_WAIT_HOLD = 0x05,
	DATA_TX_START = 0x06,
	DATA_TX_RANDOM = 0x07,
    DATA_TX_PATCH = 0x08,
    TRADE_WAIT = 0x09,
    TRADE_DONE = 0x0A,
    DONE = 0x0B
};

enum gen_one_dex_t {
    NULL_POKEMON = 0xFF,
    RHYDON = 0x01,
    KANGASKHAN = 0x02,
    NIDORAN_MALE = 0x03,
    CLEFAIRY = 0x04,
    SPEAROW = 0x05,
    VOLTORB = 0x06,
    NIDOKING = 0x07,
    SLOWBRO = 0x08,
    IVYSAUR = 0x09,
    EXEGGUTOR = 0x0A,
    LICKITUNG = 0x0B,
    EXEGGCUTE = 0x0C,
    GRIMER = 0x0D,
    GENGAR = 0x0E,
    NIDORAN_FEMALE = 0x0F,
    NIDOQUEEN = 0x10,
    CUBONE = 0x11,
    RHYHORN = 0x12,
    LAPRAS = 0x13,
    ARCANINE = 0x14,
    MEW = 0x15,
    GYARADOS = 0x16,
    SHELLDER = 0x17,
    TENTACOOL = 0x18,
    GASTLY = 0x19,
    SCYTHER = 0x1A,
    STARYU = 0x1B,
    BLASTOISE = 0x1C,
    PINSIR = 0x1D,
    TANGELA = 0x1E,
    GROWLITHE = 0x21,
    ONIX = 0x22,
    FEAROW = 0x23,
    PIDGEY = 0x24,
    SLOWPOKE = 0x25,
    KADABRA = 0x26,
    GRAVELER = 0x27,
    CHANSEY = 0x28,
    MACHOKE = 0x29,
    MR_MIME = 0x2A,
    HITMONLEE = 0x2B,
    HITMONCHAN = 0x2C,
    ARBOK = 0x2D,
    PARASECT = 0x2E,
    PSYDUCK = 0x2F,
    DROWZEE = 0x30,
    GOLEM = 0x31,
    MAGMAR = 0x33,
    ELECTABUZZ = 0x35,
    MAGNETON = 0x36,
    KOFFING = 0x37,
    MANKEY = 0x39,
    SEEL = 0x3A,
    DIGLETT = 0x3B,
    TAUROS = 0x3C,
    FARFETCH = 0x40,
    VENONAT = 0x41,
    DRAGONITE = 0x42,
    DODUO = 0x46,
    POLIWAG = 0x47,
    JYNX = 0x48,
    MOLTRES = 0x49,
    ARTICUNO = 0x4A,
    ZAPDOS = 0x4B,
    DITTO = 0x4C,
    MEOWTH = 0x4D,
    KRABBY = 0x4E,
    VULPIX = 0x52,
    NINETALES = 0x53,
    PIKACHU = 0x54,
    RAICHU = 0x55,
    DRATINI = 0x58,
    DRAGONAIR = 0x59,
    KABUTO = 0x5A,
    KABUTOPS = 0x5B,
    HORSEA = 0x5C,
    SEADRA = 0x5D,
    SANDSHREW = 0x60,
    SANDSLASH = 0x61,
    OMANYTE = 0x62,
    OMASTAR = 0x63,
    JIGGLYPUFF = 0x64,
    WIGGLYTUFF = 0x65,
    EEVEE = 0x66,
    FLAREON = 0x67,
    JOLTEON = 0x68,
    VAPOREON = 0x69,
    MACHOP = 0x6A,
    ZUBAT = 0x6B,
    EKANS = 0x6C,
    PARAS = 0x6D,
    POLIWHIRL = 0x6E,
    POLIWRATH = 0x6F,
    WEEDLE = 0x70,
    KAKUNA = 0x71,
    BEEDRILL = 0x72,
    DODRIO = 0x74,
    PRIMEAPE = 0x75,
    DUGTRIO = 0x76,
    VENOMOTH = 0x77,
    DEWGONG = 0x78,
    CATERPIE = 0x7B,
    METAPOD = 0x7C,
    BUTTERFREE = 0x7D,
    MACHAMP = 0x7E,
    GOLDUCK = 0x80,
    HYPNO = 0x81,
    GOLBAT = 0x82,
    MEWTWO = 0x83,
    SNORLAX = 0x84,
    MAGIKARP = 0x85,
    MUK = 0x88,
    KINGLER = 0x8A,
    CLOYSTER = 0x8B,
    ELECTRODE = 0x8D,
    CLEFABLE = 0x8E,
    WEEZING = 0x8F,
    PERSIAN = 0x90,
    MAROWAK = 0x91,
    HAUNTER = 0x93,
    ABRA = 0x94,
    ALAKAZAM = 0x95,
    PIDGEOTTO = 0x96,
    PIDGEOT = 0x97,
    STARMIE = 0x98,
    BULBASAUR = 0x99,
    VENUSAUR = 0x9A,
    TENTACRUEL = 0x9B,
    GOLDEEN = 0x9D,
    SEAKING = 0x9E,
    PONYTA = 0xA3,
    RAPIDASH = 0xA4,
    RATTATA = 0xA5,
    RATICATE = 0xA6,
    NIDORINO = 0xA7,
    NIDORINA = 0xA8,
    GEODUDE = 0xA9,
    PORYGON = 0xAA,
    AERODACTYL = 0xAB,
    MAGNEMITE = 0xAD,
    CHARMANDER = 0xB0,
    SQUIRTLE = 0xB1,
    CHARMELEON = 0xB2,
    WARTORTLE = 0xB3,
    CHARIZARD = 0xB4,
    ODDISH = 0xB9,
    GLOOM = 0xBA,
    VILEPLUME = 0xBB,
    BELLSPROUT = 0xBC,
    WEEPINBELL = 0xBD,
    VICTREEBEL = 0xBE,
};

enum poke_move_t {
    ABSORB = 0x47,
    ACID = 0x33,
    ACID_ARMOR = 0x97,
    AGILITY = 0x61,
    AMNESIA = 0x85,
    AURORA_BEAM = 0x3E,
    BARRAGE = 0x8C,
    BARRIER = 0x70,
    BIDE = 0x75,
    BIND = 0x14,
    BITE = 0x2C,
    BLIZZARD = 0x3B,
    BODY_SLAM = 0x22,
    BONE_CLUB = 0x7D,
    BONEMERANG = 0x9B,
    BUBBLE = 0x91,
    BUBBLEBEAM = 0x3D,
    CLAMP = 0x80,
    COMET_PUNCH = 0x04,
    CONFUSE_RAY = 0x6D,
    CONFUSION = 0x5D,
    CONSTRICT = 0x84,
    CONVERSION = 0xA0,
    COUNTER = 0x44,
    CRABHAMMER = 0x98,
    CUT = 0x0F,
    DEFENSE_CURL = 0x6F,
    DIG = 0x5B,
    DISABLE = 0x32,
    DIZZY_PUNCH = 0x92,
    DOUBLE_EDGE = 0x26,
    DOUBLE_KICK = 0x18,
    DOUBLE_SLAP = 0x03,
    DOUBLE_TEAM = 0x68,
    DRAGON_RAGE = 0x52,
    DREAM_EATER = 0x8A,
    DRILL_PECK = 0x41,
    EARTHQUAKE = 0x59,
    EGG_BOMB = 0x79,
    EMBER = 0x34,
    EXPLOSION = 0x99,
    FIRE_BLAST = 0x7E,
    FIRE_PUNCH = 0x07,
    FIRE_SPIN = 0x53,
    FISSURE = 0x5A,
    FLAMETHROWER = 0x35,
    FLASH = 0x94,
    FLY = 0x13,
    FOCUS_ENERGY = 0x74,
    FURY_ATTACK = 0x1F,
    FURY_SWIPES = 0x9A,
    GLARE = 0x89,
    GROWL = 0x2D,
    GROWTH = 0x4A,
    GUILLOTINE = 0x0C,
    GUST = 0x10,
    HARDEN = 0x6A,
    HAZE = 0x72,
    HEADBUTT = 0x1D,
    HI_JUMP_KICK = 0x88,
    HORN_ATTACK = 0x1E,
    HORN_DRILL = 0x20,
    HYDRO_PUMP = 0x38,
    HYPER_BEAM = 0x3F,
    HYPER_FANG = 0x9E,
    HYPNOSIS = 0x5F,
    ICE_BEAM = 0x3A,
    ICE_PUNCH = 0x08,
    JUMP_KICK = 0x1A,
    KARATE_CHOP = 0x02,
    KINESIS = 0x86,
    LEECH_LIFE = 0x8D,
    LEECH_SEED = 0x49,
    LEER = 0x2B,
    LICK = 0x7A,
    LIGHT_SCREEN = 0x71,
    LOVELY_KISS = 0x8E,
    LOW_KICK = 0x43,
    MEDITATE = 0x60,
    MEGA_DRAIN = 0x48,
    MEGA_KICK = 0x19,
    MEGA_PUNCH = 0x05,
    METRONOME = 0x76,
    MIMIC = 0x66,
    MINIMIZE = 0x6B,
    MIRROR_MOVE = 0x77,
    MIST = 0x36,
    NIGHT_SHADE = 0x65,
    PAYDAY = 0x06,
    PECK = 0x40,
    PETAL_DANCE = 0x50,
    PIN_MISSILE = 0x2A,
    POISON_GAS = 0x8B,
    POISON_STING = 0x28,
    POISON_POWDER = 0x4D,
    POUND = 0x01,
    PSYBEAM = 0x3C,
    PSYCHIC = 0x5E,
    PSYWAVE = 0x95,
    QUICK_ATTACK = 0x62,
    RAGE = 0x63,
    RAZOR_LEAF = 0x4B,
    RAZOR_WIND = 0x0D,
    RECOVER = 0x69,
    REFLECT = 0x73,
    REST = 0x9C,
    ROAR = 0x2E,
    ROCK_SLIDE = 0x9D,
    ROCK_THROW = 0x58,
    ROLLING_KICK = 0x1B,
    SAND_ATTACK = 0x1C,
    SCRATCH = 0x0A,
    SCREECH = 0x67,
    SEISMIC_TOSS = 0x45,
    SELFDESTRUCT = 0x78,
    SHARPEN = 0x9F,
    SING = 0x2F,
    SKULL_BASH = 0x82,
    SKY_ATTACK = 0x8F,
    SLAM = 0x15,
    SLASH = 0xA3,
    SLEEP_POWDER = 0x4F,
    SLUDGE = 0x7C,
    SMOG = 0x7B,
    SMOKESCREEN = 0x6C,
    SOFTBOILED = 0x87,
    SOLAR_BEAM = 0x4C,
    SONIC_BOOM = 0x31,
    SPIKE_CANNON = 0x83,
    SPLASH = 0x96,
    SPORE = 0x93,
    STOMP = 0x17,
    STRENGTH = 0x46,
    STRING_SHOT = 0x51,
    STRUGGLE = 0xA5,
    STUN_SPORE = 0x4E,
    SUBMISSION = 0x42,
    SUBSTITUTE = 0xA4,
    SUPER_FANG = 0xA2,
    SUPERSONIC = 0x30,
    SURF = 0x39,
    SWIFT = 0x81,
    SWORDS_DANCE = 0x0E,
    TACKLE = 0x21,
    TAIL_WHIP = 0x27,
    TAKE_DOWN = 0x24,
    TELEPORT = 0x64,
    THRASH = 0x25,
    THUNDER = 0x57,
    THUNDERBOLT = 0x55,
    THUNDER_PUNCH = 0x09,
    THUNDERSHOCK = 0x54,
    THUNDERWAVE = 0x56,
    TOXIC = 0x5C,
    TRANSFORM = 0x90,
    TRI_ATTACK = 0xA1,
    TWINEEDLE = 0x29,
    VICE_GRIP = 0x0B,
    VINE_WHIP = 0x16,
    WATER_GUN = 0x37,
    WATERFALL = 0x7F,
    WHIRLWIND = 0x12,
    WING_ATTACK = 0x11,
    WITHDRAW = 0x6E,
    WRAP = 0x23,
};

enum status_condition_t {
    NONE = 0x00,
    ASLEEP = 0x04,
    BURNED = 0x10,
    FROZEN = 0x20,
    PARALYZED = 0x40,
    POISONED = 0x08,
};

enum poke_type_t {
    NORMAL = 0x00,
    FIGHTING = 0x01,
    FLYING = 0x02,
    POISON = 0x03,
    GROUND = 0x04,
    ROCK = 0x05,
    BUG = 0x07,
    GHOST = 0x08,
    FIRE = 0x14,
    WATER = 0x15,
    GRASS = 0x16,
    ELECTRIC = 0x17,
    PSYCHIC_TYPE = 0x18,
    ICE = 0x19,
    DRAGON = 0x1A,
};

typedef struct SelectedPokemon {
    // Number of pokemon in the trainer's party
    uint8_t number;
    enum gen_one_dex_t pokemon[6];
} SelectedPokemon;


// Luckily it follows the save file structure closely enough
// https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_data_structure_(Generation_I)
typedef struct PartyMember {
    enum gen_one_dex_t pokemon;
    uint16_t current_hp;
    uint16_t max_hp;
    uint8_t level;
    enum status_condition_t status;
    enum poke_type_t type1;
    enum poke_type_t type2; // If only one type, copy the first
    uint8_t catch_rate_or_held_item; // R/G/B/Y (catch rate), G/S/C (held item), and Stadium (held item) use this byte differently
    enum poke_move_t move1;
    enum poke_move_t move2;
    enum poke_move_t move3;
    enum poke_move_t move4;
    uint16_t original_trainer_id; // In decimal, these are the funny numbers

    // -   Experience is complicated. You must look up the Pokemon you are trying to trade
    //      in the following table and apply the experience points that match the level.
    //      EXP LVL Table for gen 1: https://pwo-wiki.info/index.php/Generation_I_Experience_Charts
    //      That source was the best I could find for Gen 1. If you find another, submit a PR or open an issue and I'll fix it
    // -   Experience is a 24bit number, we will be dropping the MSB to acheive that
    uint32_t experience;

    // Effort Values
    // These are very specific to the Pokemon and who they battled in the past or what vitamins they were fed
    // Luckily, these get recalculated when you level them up, or when you put them in a box and then put them back in your party
    // For this example, I will take the max value and scale it to the level (65535 * 0.40) = 26214
    uint16_t HP_ev;
    uint16_t attack_ev;
    uint16_t defense_ev;
    uint16_t speed_ev;
    uint16_t special_ev;

    // IVs are a 4 bit number, so the max value is 15 (0-15 = 0b0000-0b1111 = 0x0-0xF)
    // These have been broken out for legibility, but will be condensed to only 2 bytes
    uint8_t attack_iv;
    uint8_t defense_iv;
    uint8_t speed_iv;
    uint8_t special_iv;

    uint8_t move1_pp;
    uint8_t move2_pp;
    uint8_t move3_pp;
    uint8_t move4_pp;

    uint16_t attack;
    uint16_t defense;
    uint16_t speed;
    uint16_t special;
} PartyMember;

#endif /* GEN1_H_ */