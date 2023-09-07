#include <gb/gb.h>
#include <gb/hardware.h>
#include <stdint.h>
#include <stdio.h>
#include "gen1.h"

#define PARTY_SIZE 6
#define POKE_SIZE 44
#define NAME_LEN 11
#define SELP_LEN 8
#define POKE_LEN POKE_SIZE * PARTY_SIZE
#define ORIG_LEN NAME_LEN * PARTY_SIZE
#define NICK_LEN NAME_LEN * PARTY_SIZE
#define FULL_LEN NAME_LEN + SELP_LEN + (POKE_SIZE * PARTY_SIZE) + (NAME_LEN * PARTY_SIZE) + (NAME_LEN * PARTY_SIZE)

#define SER_REG_DIR (*(uint8_t *)0xFF01)
#define SER_OPT_REG_DIR (*(uint8_t *)0xFF02)

enum connection_state_t connection_state = NOT_CONNECTED;
enum trade_state_t trade_state = INIT;
uint32_t emu_var = 0x12345678;
uint8_t INPUT_BLOCK[418];
uint8_t DATA_BLOCK[418];
int trade_pokemon = -1;
unsigned char name[11] = {
    pokechar_B, 
    pokechar_r, 
    pokechar_e, 
    pokechar_a, 
    pokechar_d, 
    pokechar_B, 
    pokechar_o, 
    pokechar_r, 
    pokechar_e, 
    pokechar_d, 
    pokechar_STOP_BYTE 
};
unsigned char nicknames[11] = {
    // Pokemon Nickname
    pokechar_M, 
    pokechar_E, 
    pokechar_W, 
    pokechar_STOP_BYTE, 
    pokechar_NULL_BYTE, 
    pokechar_NULL_BYTE, 
    pokechar_NULL_BYTE, 
    pokechar_NULL_BYTE, 
    pokechar_NULL_BYTE, 
    pokechar_NULL_BYTE, 
    pokechar_NULL_BYTE, 
};

typedef struct TraderPacket {
    // Name must not exceed 10 characters + 1 STOP_BYTE
    // Any leftover space after STOP_BYTE must be filled with NULL_BYTE
    unsigned char name[11];
    struct SelectedPokemon selected_pokemon;
    struct PartyMember pokemon[6];
    unsigned char original_trainer_names[6][11];
    unsigned char pokemon_nicknames[6][11];
} TraderPacket;

void party_member_to_bytes(struct PartyMember *pPartyMember, uint8_t *out) {
    uint8_t res[44] = {
        pPartyMember->pokemon,
        (uint8_t) (pPartyMember->current_hp >> 8),
        (uint8_t) (pPartyMember->current_hp & 0x00FF),
        pPartyMember->level,
        pPartyMember->status,
        pPartyMember->type1,
        pPartyMember->type2,
        pPartyMember->catch_rate_or_held_item,
        pPartyMember->move1,
        pPartyMember->move2,
        pPartyMember->move3,
        pPartyMember->move4,
        (uint8_t) (pPartyMember->original_trainer_id >> 8),
        (uint8_t) (pPartyMember->original_trainer_id & 0x00FF),
        (uint8_t) (pPartyMember->experience & 0x000000FF),
        (uint8_t) ((pPartyMember->experience & 0x0000FF00) >> 8),
        (uint8_t) ((pPartyMember->experience & 0x00FF0000) >> 16),
        (uint8_t) (pPartyMember->HP_ev >> 8),
        (uint8_t) (pPartyMember->HP_ev & 0x00FF),
        (uint8_t) (pPartyMember->attack_ev >> 8),
        (uint8_t) (pPartyMember->attack_ev & 0x00FF),
        (uint8_t) (pPartyMember->defense_ev >> 8),
        (uint8_t) (pPartyMember->defense_ev & 0x00FF),
        (uint8_t) (pPartyMember->speed_ev >> 8),
        (uint8_t) (pPartyMember->speed_ev & 0x00FF),
        (uint8_t) (pPartyMember->special_ev >> 8),
        (uint8_t) (pPartyMember->special_ev & 0x00FF),
        (uint8_t) (((pPartyMember->attack_iv & 0xF) << 4) | (pPartyMember->defense_iv & 0xF)),
        (uint8_t) (((pPartyMember->speed_iv & 0xF) << 4) | (pPartyMember->special_iv & 0xF)),
        pPartyMember->move1_pp,
        pPartyMember->move2_pp,
        pPartyMember->move3_pp,
        pPartyMember->move4_pp,
        pPartyMember->level,
        (uint8_t) (pPartyMember->max_hp >> 8),
        (uint8_t) (pPartyMember->max_hp & 0x00FF),
        (uint8_t) (pPartyMember->attack >> 8),
        (uint8_t) (pPartyMember->attack & 0x00FF),
        (uint8_t) (pPartyMember->defense >> 8),
        (uint8_t) (pPartyMember->defense & 0x00FF),
        (uint8_t) (pPartyMember->speed >> 8),
        (uint8_t) (pPartyMember->speed & 0x00FF),
        (uint8_t) (pPartyMember->special >> 8),
        (uint8_t) (pPartyMember->special & 0x00FF),
    };
    for (size_t i = 0; i < 44; i++) {
        out[i] = res[i];
    }
}

void selected_pokemon_to_bytes(struct SelectedPokemon *pSelectedPokemon, uint8_t *out) {
    uint8_t res[8] = {
        pSelectedPokemon->number,
        pSelectedPokemon->pokemon[0],
        pSelectedPokemon->pokemon[1],
        pSelectedPokemon->pokemon[2],
        pSelectedPokemon->pokemon[3],
        pSelectedPokemon->pokemon[4],
        pSelectedPokemon->pokemon[5],
        0xFF,
    };
    for (size_t i = 0; i < 8; i++) {
        out[i] = res[i];
    }
}

void trader_packet_to_bytes(struct TraderPacket *pTraderPacket, uint8_t *out) {
    uint8_t name_bytes[NAME_LEN];
    uint8_t selected_pokemon_bytes[SELP_LEN];
    uint8_t pokemon_bytes[POKE_LEN];
    uint8_t original_trainer_names_bytes[ORIG_LEN];
    uint8_t pokemon_nicknames_bytes[NICK_LEN];

    // Serialize the data
    for (size_t i = 0; i < NAME_LEN; i++) {
        name_bytes[i] = (uint8_t) pTraderPacket->name[i];
    }

    // Calculate the selected_pokemon and pokemon w/ stats and such
    for (size_t i = 0; i < PARTY_SIZE; i++) {
        uint8_t poke[POKE_SIZE];
        party_member_to_bytes(&pTraderPacket->pokemon[i], poke);

        // Selected Pokemon Data (for listing and ordering without stats)
        // if (poke[0] != 0x00) {
        //     pTraderPacket->selected_pokemon.number++;
        //     pTraderPacket->selected_pokemon.pokemon[i] = poke[0];
        // }
        
        // Full Party Data (all stats and such)
        for (size_t j = 0; j < POKE_SIZE; j++) {
            pokemon_bytes[(i * POKE_SIZE) + j] = (uint8_t) poke[j];
        }
    }
    selected_pokemon_to_bytes(&pTraderPacket->selected_pokemon, selected_pokemon_bytes);
    

    for (size_t i = 0; i < PARTY_SIZE; i++) {
        for (size_t j = 0; j < NAME_LEN; j++) {
            original_trainer_names_bytes[(i * NAME_LEN) + j] = (uint8_t) pTraderPacket->original_trainer_names[i][j];
        }
    }

    for (size_t i = 0; i < PARTY_SIZE; i++) {
        for (size_t j = 0; j < NAME_LEN; j++) {
            pokemon_nicknames_bytes[(i * NAME_LEN) + j] = (uint8_t) pTraderPacket->pokemon_nicknames[i][j];
        }
    }

    // Flatten the data
    uint8_t res[FULL_LEN + 3];

    for (size_t i = 0; i < NAME_LEN; i++) {
        res[i] = name_bytes[i];
    }
    for (size_t i = 0; i < SELP_LEN; i++) {
        res[i + NAME_LEN] = selected_pokemon_bytes[i];
    }
    for (size_t i = 0; i < POKE_LEN; i++) {
        res[i + NAME_LEN + SELP_LEN] = pokemon_bytes[i];
    }
    for (size_t i = 0; i < ORIG_LEN; i++) {
        res[i + NAME_LEN + SELP_LEN + POKE_LEN] = original_trainer_names_bytes[i];
    }
    for (size_t i = 0; i < NICK_LEN; i++) {
        res[i + NAME_LEN + SELP_LEN + POKE_LEN + ORIG_LEN] = pokemon_nicknames_bytes[i];
    }
    res[FULL_LEN] = 0x00;
    res[FULL_LEN + 1] = 0x00;
    res[FULL_LEN + 2] = 0x00;
    // Write the bytes to *out
    for (size_t i = 0; i < (FULL_LEN + 3); i++) {
        out[i] = res[i];
    }
}

uint8_t handle_byte(uint8_t in, size_t *counter) {
    uint8_t out[1];
    
    switch (connection_state)
    {
        case NOT_CONNECTED:
    //        printf("Not connected...\n");
            if(in == PKMN_MASTER) {
                out[0] = PKMN_SLAVE;
        //        printf("We are slave\n");
            }
            else if(in == PKMN_BLANK) {
                out[0] = PKMN_BLANK;
        //        printf("Pokemon Blank\n");
            }
            else if(in == PKMN_CONNECTED) {
                out[0] = PKMN_CONNECTED;
                connection_state = CONNECTED;
        //        printf("We are connected!\n");
            } else if (in == PKMN_TRADE_CENTRE) {
                connection_state = CONNECTED;
                connection_state = TRADE_CENTRE;
                out[0] = PKMN_TRADE_CENTRE;
            }
            break;

        case CONNECTED:
            //printf("Connected...\n");
            if(in == PKMN_CONNECTED) {
                out[0] = PKMN_CONNECTED;
        //        printf("Confirmed connected.\n");
            }
            else if(in == PKMN_TRADE_CENTRE) {
                connection_state = TRADE_CENTRE;
        //        printf("Trade Center\n");
            }
            else if(in == PKMN_COLOSSEUM) {
                connection_state = COLOSSEUM;
        //        printf("COLOSSEUM\n");
            }
            else if(in == PKMN_BREAK_LINK || in == PKMN_MASTER) {
                connection_state = NOT_CONNECTED;
                out[0] = PKMN_BREAK_LINK;
        //        printf(in == PKMN_MASTER ? "PKMN_MASTER\n" : "PKMN_BREAK_LINK\n");
            } else {
                out[0] = in;
        //        printf("echoing back after connected: %x\n", in);
            }
            break;

        case TRADE_CENTRE:
    //        printf("Trade Center...\n");
            if(trade_state == INIT && in == 0x00) {
                trade_state = READY;
                out[0] = 0x00;
        //        printf("Init, now ready\n");
            } else if(trade_state == READY && in == 0xFD) {
                trade_state = FIRST_DETECTED_WAIT;
                out[0] = 0xFD;
        //        printf("Ready, begin waiting\n");
            } else if(trade_state == FIRST_DETECTED_WAIT && in != 0xFD) {
                // random data of slave is ignored.
                out[0] = in;
                trade_state = DATA_TX_RANDOM;
        //        printf("Detected, start random data\n");
            } else if(trade_state == DATA_TX_RANDOM && in == 0xFD) {
                trade_state = DATA_TX_WAIT;
                out[0] = 0xFD;
                (*counter) = 0;
        //        printf("Random data sent, wait\n");
            } else if (trade_state == DATA_TX_WAIT && in == 0xFD) {
                out[0] = 0x00;
            } else if(trade_state == DATA_TX_WAIT && in != 0xFD) {
                (*counter) = 0;
                // send first byte
                out[0] = DATA_BLOCK[(*counter)];
                INPUT_BLOCK[(*counter)] = in;
                trade_state = DATA_TX;
                (*counter)++;
        //        printf("Sending data (not 0xFD)\n");
            } else if(trade_state == DATA_TX) {
                out[0] = DATA_BLOCK[(*counter)];
                INPUT_BLOCK[(*counter)] = in;
                (*counter)++;
                if((*counter) == 418) {
                    trade_state = DATA_TX_PATCH;
                }
        //        printf("Sending data\n");
            } else if(trade_state == DATA_TX_PATCH && in == 0xFD) {
                (*counter) = 0;
                out[0] = 0xFD;
        //        printf("Send patch\n");
            } else if(trade_state == DATA_TX_PATCH && in != 0xFD) {
                out[0] = in;
                (*counter)++;
                if((*counter) == 197) {
                    trade_state = TRADE_WAIT;
                }
                (*counter) = 0;
        //        printf("Send patch trade wait\n");
            } else if(trade_state == TRADE_WAIT && (in & 0x60) == 0x60) {
                if (in == 0x6f) {
                    trade_state = READY;
                    out[0] = 0x6f;
            //        printf("Master ready\n");
                } else {
                    out[0] = 0x60; // first pokemon
                    trade_pokemon = in - 0x60;
            //        printf("Master first pokemon\n");
                }
            } else if(trade_state == TRADE_WAIT && in == 0x00) {
                out[0] = 0;
                trade_state = TRADE_DONE;
        //        printf("Sent the Gameboy:\n");
        //        printf("Gameboy Sent:\n");
        //        printf("Trade done\n");
            } else if(trade_state == TRADE_DONE && (in & 0x60) == 0x60) {
                out[0] = in;
                if (in  == 0x61) {
                    trade_pokemon = -1;
                    trade_state = TRADE_WAIT;
            //        printf("Trade done, wait\n");
                } else {
                    trade_state = DONE;
            //        printf("Trade done, mark done\n");
                }
            } else if(trade_state == DONE && in == 0x00) {
                out[0] = 0;
                trade_state = INIT;
        //        printf("Done, reinit\n");
            } else {
                out[0] = in;
        //        printf("Echo back\n");
            }
            break;
        
        default:
            out[0] = in;
    //        printf("Echo back 2\n");
            break;
    }

    return out[0];
}

void main(void)
{
    CRITICAL {
        add_SIO(nowait_int_handler);    // disable waiting VRAM state before return
    }
    set_interrupts(SIO_IFLAG);          // disable other interrupts. note: this disables sprite movement

    /**
     * Trader Packet Init
     */
    struct TraderPacket traderPacket;
    for (size_t i = 0; i < 11; i++) {
        traderPacket.name[i] = name[i];
    }

    struct SelectedPokemon *pSelectedPokemon = &traderPacket.selected_pokemon;
    pSelectedPokemon->number = 6;
    for (size_t i = 0; i < 6; i++) {
        pSelectedPokemon->pokemon[i] = MEW;
    }

    for (size_t i = 0; i < 6; i++) {
        struct PartyMember *pPartyMember = &traderPacket.pokemon[i];
        pPartyMember->pokemon = MEW;
        pPartyMember->current_hp = 100;
        pPartyMember->max_hp = 130;
        pPartyMember->level = 40;
        pPartyMember->status = NONE;
        pPartyMember->type1 = PSYCHIC_TYPE;
        pPartyMember->type2 = PSYCHIC_TYPE; // If only one type, copy the first
        pPartyMember->catch_rate_or_held_item = 0xFF; // R/G/B/Y (catch rate), G/S/C (held item), and Stadium (held item) use this byte differently
        pPartyMember->move1 = TELEPORT;
        pPartyMember->move2 = PSYWAVE;
        pPartyMember->move3 = PSYCHIC;
        pPartyMember->move4 = FLY;
        pPartyMember->original_trainer_id = 0xFFDE;//0xA455; // In decimal, these are the funny numbers

        // -   Experience is complicated. You must look up the Pokemon you are trying to trade
        //      in the following table and apply the experience points that match the level.
        //      EXP LVL Table for gen 1: https://pwo-wiki.info/index.php/Generation_I_Experience_Charts
        //      That source was the best I could find for Gen 1. If you find another, submit a PR or open an issue and I'll fix it
        // -   Experience is a 24bit number, we will be dropping the MSB to acheive that
        pPartyMember->experience = 190148;

        // Effort Values
        // These are very specific to the Pokemon and who they battled in the past or what vitamins they were fed
        // Luckily, these get recalculated when you level them up, or when you put them in a box and then put them back in your party
        // For this example, I will take the max value and scale it to the level (65535 * 0.40) = 26214
        pPartyMember->HP_ev = 26214;
        pPartyMember->attack_ev = 26214;
        pPartyMember->defense_ev = 26214;
        pPartyMember->speed_ev = 26214;
        pPartyMember->special_ev = 26214;

        // IVs are a 4 bit number, so the max value is 15 (0-15 = 0b0000-0b1111 = 0x0-0xF)
        // These have been broken out for legibility, but will be condensed to only 2 bytes
        pPartyMember->attack_iv = 0xF;
        pPartyMember->defense_iv = 0xF;
        pPartyMember->speed_iv = 0xF;
        pPartyMember->special_iv = 0xF;

        pPartyMember->move1_pp = 20;
        pPartyMember->move2_pp = 15;
        pPartyMember->move3_pp = 10;
        pPartyMember->move4_pp = 15;

        pPartyMember->attack = 100;
        pPartyMember->defense = 100;
        pPartyMember->speed = 100;
        pPartyMember->special = 100;
    }

    for (size_t i = 0; i < 6; i++) {
        for (size_t j = 0; j < 11; j++) {
            traderPacket.original_trainer_names[i][j] = name[j];
        }
    }
    for (size_t i = 0; i < 6; i++) {
        for (size_t j = 0; j < 11; j++) {
            traderPacket.pokemon_nicknames[i][j] = nicknames[j];
        }
    }
    
    trader_packet_to_bytes(&traderPacket, DATA_BLOCK);

    puts("Poke Distribution");
    puts("Copyright 2023");
    puts("BreadCodes");

    size_t trade_counter = 0;
    while(1) {

        receive_byte();
        while(_io_status == IO_RECEIVING);
        uint8_t in = _io_in; //SER_REG_DIR;
        
        _io_out = handle_byte(in, &trade_counter);

        // if (in == 0xD4) printf("%x %x\n", in, _io_out);

        while(_io_status == IO_SENDING);
        while((joypad() > 0)); // Pause output to read the screen
    }
}
