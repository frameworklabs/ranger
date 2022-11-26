/*
** This is generated code - do not touch!
*/

#include <string.h>

/*
** used C headers
*/

#include "env.h"

/*
** blech types
*/

#include "blech.h"

/*
** exports, user types and C wrappers
*/

#include "ranger.h"

/*
** direct C constants
*/

#define blc_ranger_UNDEF_RANGE (UNDEF_RANGE)
#define blc_ranger_DIALOG_BATTERY (DIALOG_BATTERY)
#define blc_ranger_DIALOG_BLE (DIALOG_BLE)
#define blc_ranger_DIALOG_USB (DIALOG_USB)
#define blc_ranger_DIALOG_BATTERY_BELOW_10 (DIALOG_BATTERY_BELOW_10)
#define blc_ranger_DIALOG_BATTERY_BELOW_20 (DIALOG_BATTERY_BELOW_20)
#define blc_ranger_DIALOG_BLE_DISCONNECTED (DIALOG_BLE_DISCONNECTED)
#define blc_ranger_DIALOG_BLE_CONNECTED (DIALOG_BLE_CONNECTED)
#define blc_ranger_DIALOG_BLE_ENABLED (DIALOG_BLE_ENABLED)
#define blc_ranger_DIALOG_USB_DISCONNECTED (DIALOG_USB_DISCONNECTED)
#define blc_ranger_DIALOG_USB_CONNECTED (DIALOG_USB_CONNECTED)
#define blc_ranger_SETTINGS_HELP (SETTINGS_HELP)
#define blc_ranger_SETTINGS_UNIT (SETTINGS_UNIT)
#define blc_ranger_SETTINGS_OFFSET (SETTINGS_OFFSET)
#define blc_ranger_SETTINGS_BLE (SETTINGS_BLE)
#define blc_ranger_SETTINGS_BRIGHTNESS (SETTINGS_BRIGHTNESS)
#define blc_ranger_MEASURE_UNIT_MM (MEASURE_UNIT_MM)
#define blc_ranger_MEASURE_UNIT_CM (MEASURE_UNIT_CM)
#define blc_ranger_MEASURE_UNIT_M (MEASURE_UNIT_M)
#define blc_ranger_ORIENTATION_HAT_LEFT (ORIENTATION_HAT_LEFT)
#define blc_ranger_ORIENTATION_HAT_RIGHT (ORIENTATION_HAT_RIGHT)

/*
** direct C functions
*/

/*
** parameters
*/

/*
** state
*/

struct blc_ranger_Main blc_blech_ctx;

/*
** activities and functions
*/

/**  Delays the current tail for the given ticks. A tick is assumed to be 1/10s. */
static blc_pc_t blc_ranger_Delay (struct blc_ranger_Delay *blc_blech_ctx,
                                  const blc_nat16 blc_ticks) {
    loopHead:
    if ( blc_blech_ctx->pc_1 == 2 ) {
        blc_blech_ctx->blc_Delay_i = blc_ticks;
        blc_blech_ctx->pc_1 = 4;
    }
    if ( blc_blech_ctx->pc_1 == 4 ) {
        blc_blech_ctx->pc_1 = 7; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_1 == 6 ) {
        if ( 1 ) {
            blc_blech_ctx->blc_Delay_i = (blc_blech_ctx->blc_Delay_i - 1);
            if ( !((blc_blech_ctx->blc_Delay_i == 0)) ) {
                blc_blech_ctx->pc_1 = 4;
                goto loopHead;
            } else if ( (blc_blech_ctx->blc_Delay_i == 0) ) {
                blc_blech_ctx->pc_1 = 8;
            }
        }
    }
    if ( blc_blech_ctx->pc_1 == 8 ) {
        blc_blech_ctx->pc_1 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_1);
    return blc_blech_ctx->pc_1 ;
}

/**  Delays for given ticks (1/10s per tick) or until woken from sleep. */
static blc_pc_t blc_ranger_DelayOrDidWakeup (struct blc_ranger_DelayOrDidWakeup *blc_blech_ctx,
                                             const blc_nat16 blc_ticks) {
    blc_bool blc_didWakeup = didWakeup;
    if ( blc_blech_ctx->pc_2 == 2 ) {
        /* The extern declaration is outside the Blech code */
        blc_blech_ctx->pc_2_blc_ranger_Delay.pc_1 = 2;
        blc_int32 blc_blech_aux_retcode_3;
        blc_blech_aux_retcode_3 = blc_ranger_Delay(&blc_blech_ctx->pc_2_blc_ranger_Delay,
                                                   blc_ticks);
        BLC_UNUSED(blc_blech_aux_retcode_3);
        blc_blech_ctx->pc_2 = 8;
    }
    if ( blc_blech_ctx->pc_2 == 4 ) {
        if ( blc_didWakeup ) {
            blc_blech_ctx->pc_2 = 12;
        } else if ( 1 ) {
            blc_blech_ctx->pc_2 = 6;
        }
    }
    if ( blc_blech_ctx->pc_2 == 6 ) {
        blc_int32 blc_blech_aux_retcode_3;
        blc_blech_aux_retcode_3 = blc_ranger_Delay(&blc_blech_ctx->pc_2_blc_ranger_Delay,
                                                   blc_ticks);
        if ( !((0 == blc_blech_aux_retcode_3)) ) {
            blc_blech_ctx->pc_2 = 8;
        } else if ( (0 == blc_blech_aux_retcode_3) ) {
            blc_blech_ctx->pc_2 = 10;
        }
    }
    if ( blc_blech_ctx->pc_2 == 8 ) {
        blc_blech_ctx->pc_2 = 5; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_2 == 10 ) {
        blc_blech_ctx->pc_2 = 12;
    }
    if ( blc_blech_ctx->pc_2 == 12 ) {
        blc_blech_ctx->pc_2 = 0; /* end */ /* abort subthreads and carry on */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_2);
    return blc_blech_ctx->pc_2 ;
}

static blc_nat8 blc_ranger_maxNat8 (const blc_nat8 blc_x[2]) {
    if ( (blc_x[1] <= blc_x[0]) ) {
        return blc_x[0];
    } else {
        return blc_x[1];
    }
}

static blc_bool blc_ranger_chargeChanged (const struct blc_ranger_BatteryInfo *const blc_lhs,
                                          const struct blc_ranger_BatteryInfo *const blc_rhs) {
    return (!(((*blc_lhs).stateOfCharge == (*blc_rhs).stateOfCharge))
    || !(((*blc_lhs).isCharging == (*blc_rhs).isCharging)));
}

static blc_bool blc_ranger_equalSettings (const struct blc_ranger_Settings *const blc_a,
                                          const struct blc_ranger_Settings *const blc_b) {
    return (((((*blc_a).measureFromBack == (*blc_b).measureFromBack)
    && ((*blc_a).brightness == (*blc_b).brightness)) && ((*blc_a).bleEnabled
    == (*blc_b).bleEnabled)) && ((*blc_a).measureUnit == (*blc_b).measureUnit));
}

/**  Observes settings and writes them to "disk" when changed. */
static blc_pc_t blc_ranger_SettingsPersister (struct blc_ranger_SettingsPersister *blc_blech_ctx,
                                              const struct blc_ranger_Settings *const blc_settings) {
    loopHead:
    if ( blc_blech_ctx->pc_6 == 2 ) {
        memset((&blc_blech_ctx->blc_SettingsPersister_prevSettings),
               0,
               sizeof(struct blc_ranger_Settings));
        blc_blech_ctx->blc_SettingsPersister_prevSettings = (*blc_settings);
        blc_blech_ctx->pc_6 = 4;
    }
    if ( blc_blech_ctx->pc_6 == 4 ) {
        blc_blech_ctx->pc_6 = 7; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_6 == 6 ) {
        if ( !(blc_ranger_equalSettings(blc_settings,
                                        (&blc_blech_ctx->blc_SettingsPersister_prevSettings))) ) {
            blc_ranger_storeSettings(blc_settings);
            blc_blech_ctx->blc_SettingsPersister_prevSettings = (*blc_settings);
            if ( 1 ) {
                blc_blech_ctx->pc_6 = 4;
                goto loopHead;
            } else if ( 0 ) {
                blc_blech_ctx->pc_6 = 8;
            }
        }
    }
    if ( blc_blech_ctx->pc_6 == 8 ) {
        blc_blech_ctx->pc_6 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_6);
    return blc_blech_ctx->pc_6 ;
}

static blc_bool blc_ranger_anyButtonPressed (const struct blc_ranger_ButtonStates *const blc_buttonStates) {
    return ((*blc_buttonStates).aPressed || (*blc_buttonStates).bPressed);
}

/**  Recognizes single, double and long presses of the main button. */
/**  Pressing the secondary button is like double-pressing the main button. */
static blc_pc_t blc_ranger_PressRecognizer (struct blc_ranger_PressRecognizer *blc_blech_ctx,
                                            const struct blc_ranger_ButtonStates *const blc_buttonStates,
                                            blc_nat8 *blc_retvar) {
    if ( blc_blech_ctx->pc_8 == 2 ) {
        blc_blech_ctx->pc_8 = 5; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_8 == 4 ) {
        if ( blc_ranger_anyButtonPressed(blc_buttonStates) ) {
            if ( !((*blc_buttonStates).bPressed) ) {
                blc_blech_ctx->pc_8 = 6;
            } else if ( (*blc_buttonStates).bPressed ) {
                blc_blech_ctx->pc_8 = 8;
            }
        }
    }
    if ( blc_blech_ctx->pc_8 == 6 ) {
        
        blc_blech_ctx->pc_8 = 10;
    }
    if ( blc_blech_ctx->pc_8 == 8 ) {
        (*blc_retvar) = 3;
        blc_blech_ctx->pc_8 = 0;
        blc_blech_ctx->pc_9 = 0;
        blc_blech_ctx->pc_10 = 0;
    }
    if ( blc_blech_ctx->pc_8 == 10 ) {
        blc_blech_ctx->blc_PressRecognizer_wasReleased = 0;
        blc_blech_ctx->blc_PressRecognizer_wasDouble = 0;
        blc_blech_ctx->pc_9 = 24;
        blc_blech_ctx->pc_10 = 12;
        blc_blech_ctx->pc_8 = 28;
    }
    if ( blc_blech_ctx->pc_10 == 12 ) {
        blc_blech_ctx->pc_10 = 15; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_10 == 14 ) {
        if ( (*blc_buttonStates).aReleased ) {
            blc_blech_ctx->blc_PressRecognizer_wasReleased = 1;
            blc_blech_ctx->pc_10 = 17; /* proceed from surface to depth */
        }
    }
    if ( blc_blech_ctx->pc_10 == 16 ) {
        if ( (*blc_buttonStates).aPressed ) {
            blc_blech_ctx->blc_PressRecognizer_wasDouble = 1;
            blc_blech_ctx->pc_10 = 0; /* term */
        }
    }
    if ( blc_blech_ctx->pc_8 == 18 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_8 = 28;
        }
    }
    if ( blc_blech_ctx->pc_9 == 20 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_5;
            blc_blech_aux_retcode_5 = blc_ranger_Delay(&blc_blech_ctx->pc_9_blc_ranger_Delay,
                                                       3);
            if ( !((0 == blc_blech_aux_retcode_5)) ) {
                blc_blech_ctx->pc_9 = 26;
            } else if ( (0 == blc_blech_aux_retcode_5) ) {
                blc_blech_ctx->pc_9 = 22;
            }
        }
    }
    if ( blc_blech_ctx->pc_9 == 22 ) {
        blc_blech_ctx->pc_9 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_9 == 24 ) {
        blc_blech_ctx->pc_9_blc_ranger_Delay.pc_1 = 2;
        blc_int32 blc_blech_aux_retcode_5;
        blc_blech_aux_retcode_5 = blc_ranger_Delay(&blc_blech_ctx->pc_9_blc_ranger_Delay,
                                                   3);
        BLC_UNUSED(blc_blech_aux_retcode_5);
        blc_blech_ctx->pc_9 = 26;
    }
    if ( blc_blech_ctx->pc_9 == 26 ) {
        blc_blech_ctx->pc_9 = 21; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_8 == 28 ) {
        blc_bool blc_blech_aux_termVar_4;
        if ( blc_blech_ctx->pc_9 == 0 || blc_blech_ctx->pc_10 == 0 ) {
            blc_blech_ctx->pc_9 = 0;
            blc_blech_ctx->pc_10 = 0;
            blc_blech_aux_termVar_4 = 1;
        } else {
            blc_blech_aux_termVar_4 = 0;
        }
        if ( blc_blech_aux_termVar_4 ) {
            blc_blech_ctx->pc_8 = 30;
        } else if ( !(blc_blech_aux_termVar_4) ) {
            blc_blech_ctx->pc_8 = 42;
        }
    }
    if ( blc_blech_ctx->pc_8 == 30 ) {
        if ( !(blc_blech_ctx->blc_PressRecognizer_wasDouble) ) {
            blc_blech_ctx->pc_8 = 32;
        } else if ( blc_blech_ctx->blc_PressRecognizer_wasDouble ) {
            blc_blech_ctx->pc_8 = 38;
        }
    }
    if ( blc_blech_ctx->pc_8 == 32 ) {
        if ( !(blc_blech_ctx->blc_PressRecognizer_wasReleased) ) {
            blc_blech_ctx->pc_8 = 34;
        } else if ( blc_blech_ctx->blc_PressRecognizer_wasReleased ) {
            blc_blech_ctx->pc_8 = 36;
        }
    }
    if ( blc_blech_ctx->pc_8 == 34 ) {
        (*blc_retvar) = 2;
        blc_blech_ctx->pc_8 = 0;
        blc_blech_ctx->pc_9 = 0;
        blc_blech_ctx->pc_10 = 0;
    }
    if ( blc_blech_ctx->pc_8 == 36 ) {
        (*blc_retvar) = 1;
        blc_blech_ctx->pc_8 = 0;
        blc_blech_ctx->pc_9 = 0;
        blc_blech_ctx->pc_10 = 0;
    }
    if ( blc_blech_ctx->pc_8 == 38 ) {
        (*blc_retvar) = 3;
        blc_blech_ctx->pc_8 = 0;
        blc_blech_ctx->pc_9 = 0;
        blc_blech_ctx->pc_10 = 0;
    }
    if ( blc_blech_ctx->pc_8 == 40 ) {
        blc_blech_ctx->pc_8 = 0;
        blc_blech_ctx->pc_9 = 0;
        blc_blech_ctx->pc_10 = 0; /* end */
    }
    if ( blc_blech_ctx->pc_8 == 42 ) {
        blc_blech_ctx->pc_8 = 19; /* proceed from surface to depth */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_8);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_9);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_10);
    return blc_blech_ctx->pc_8 ;
}

static blc_bool blc_ranger_isShortOrDoublePress (const blc_nat8 blc_press) {
    return ((blc_press == 1) || (blc_press == 3));
}

/**  Dims level from its current value down to the minimum at a specific duration per step. */
static blc_pc_t blc_ranger_DimDown (struct blc_ranger_DimDown *blc_blech_ctx,
                                    const blc_nat8 blc_stepDur,
                                    blc_nat8 *blc_level) {
    loopHead:
    if ( blc_blech_ctx->pc_12 == 2 ) {
        (*blc_level) = ((*blc_level) - 1);
        blc_blech_ctx->pc_12_blc_ranger_Delay.pc_1 = 2;
        blc_int32 blc_blech_aux_retcode_6;
        blc_blech_aux_retcode_6 = blc_ranger_Delay(&blc_blech_ctx->pc_12_blc_ranger_Delay,
                                                   blc_stepDur);
        BLC_UNUSED(blc_blech_aux_retcode_6);
        blc_blech_ctx->pc_12 = 6;
    }
    if ( blc_blech_ctx->pc_12 == 4 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_6;
            blc_blech_aux_retcode_6 = blc_ranger_Delay(&blc_blech_ctx->pc_12_blc_ranger_Delay,
                                                       blc_stepDur);
            if ( !((0 == blc_blech_aux_retcode_6)) ) {
                blc_blech_ctx->pc_12 = 6;
            } else if ( (0 == blc_blech_aux_retcode_6) ) {
                blc_blech_ctx->pc_12 = 8;
            }
        }
    }
    if ( blc_blech_ctx->pc_12 == 6 ) {
        blc_blech_ctx->pc_12 = 5; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_12 == 8 ) {
        if ( !(((*blc_level) == 7)) ) {
            blc_blech_ctx->pc_12 = 2;
            goto loopHead;
        } else if ( ((*blc_level) == 7) ) {
            blc_blech_ctx->pc_12 = 10;
        }
    }
    if ( blc_blech_ctx->pc_12 == 10 ) {
        blc_blech_ctx->pc_12 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_12);
    return blc_blech_ctx->pc_12 ;
}

/**  Creates a brightness level by dimming the brightness after some time. */
/**  Pressing any button while dimmed will put the level back to the desired max level. */
/**  Also returns a filtered button-state stream by dropping the button presses used to  */
/**  bring the brightness back to max. */
static blc_pc_t blc_ranger_Dimmer (struct blc_ranger_Dimmer *blc_blech_ctx,
                                   const blc_nat8 blc_maxLevel,
                                   struct blc_ranger_ButtonStates *blc_filteredButtonStates,
                                   blc_nat8 *blc_level) {
    struct blc_ranger_ButtonStates blc_buttonStates = buttonStates;
    loopHead:
    if ( blc_blech_ctx->pc_13 == 2 ) {
        /* The extern declaration is outside the Blech code */
        blc_blech_ctx->pc_13 = 4;
    }
    if ( blc_blech_ctx->pc_13 == 4 ) {
        blc_blech_ctx->blc_Dimmer_19_20_0_abortFinished = 0;
        blc_blech_ctx->pc_13 = 6;
    }
    if ( blc_blech_ctx->pc_13 == 6 ) {
        blc_blech_ctx->blc_Dimmer_19_20_0_abortFinished = 0;
        blc_blech_ctx->pc_14 = 24;
        blc_blech_ctx->pc_15 = 8;
        blc_blech_ctx->pc_13 = 28;
    }
    if ( blc_blech_ctx->pc_15 == 8 ) {
        (*blc_filteredButtonStates) = blc_buttonStates;
        (*blc_level) = blc_maxLevel;
        blc_blech_ctx->pc_15 = 11; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_15 == 10 ) {
        if ( blc_ranger_anyButtonPressed((&blc_buttonStates)) ) {
            blc_blech_ctx->pc_15 = 32;
        } else if ( 1 ) {
            blc_blech_ctx->pc_15 = 12;
        }
    }
    if ( blc_blech_ctx->pc_15 == 12 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_15 = 8;
            goto loopHead;
        } else if ( 0 ) {
            blc_blech_ctx->pc_15 = 14;
        }
    }
    if ( blc_blech_ctx->pc_15 == 14 ) {
        blc_blech_ctx->pc_15 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_13 == 16 ) {
        if ( blc_ranger_anyButtonPressed((&blc_buttonStates)) ) {
            blc_blech_ctx->pc_13 = 32;
        } else if ( 1 ) {
            blc_blech_ctx->pc_13 = 28;
        }
    }
    if ( blc_blech_ctx->pc_14 == 18 ) {
        if ( blc_ranger_anyButtonPressed((&blc_buttonStates)) ) {
            blc_blech_ctx->pc_14 = 32;
        } else if ( 1 ) {
            blc_blech_ctx->pc_14 = 20;
        }
    }
    if ( blc_blech_ctx->pc_14 == 20 ) {
        blc_int32 blc_blech_aux_retcode_8;
        blc_blech_aux_retcode_8 = blc_ranger_Delay(&blc_blech_ctx->pc_14_blc_ranger_Delay,
                                                   50);
        if ( !((0 == blc_blech_aux_retcode_8)) ) {
            blc_blech_ctx->pc_14 = 26;
        } else if ( (0 == blc_blech_aux_retcode_8) ) {
            blc_blech_ctx->pc_14 = 22;
        }
    }
    if ( blc_blech_ctx->pc_14 == 22 ) {
        blc_blech_ctx->pc_14 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_14 == 24 ) {
        blc_blech_ctx->pc_14_blc_ranger_Delay.pc_1 = 2;
        blc_int32 blc_blech_aux_retcode_8;
        blc_blech_aux_retcode_8 = blc_ranger_Delay(&blc_blech_ctx->pc_14_blc_ranger_Delay,
                                                   50);
        BLC_UNUSED(blc_blech_aux_retcode_8);
        blc_blech_ctx->pc_14 = 26;
    }
    if ( blc_blech_ctx->pc_14 == 26 ) {
        blc_blech_ctx->pc_14 = 19; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_13 == 28 ) {
        blc_bool blc_blech_aux_termVar_7;
        if ( blc_blech_ctx->pc_14 == 0 ) {
            blc_blech_ctx->pc_14 = 0;
            blc_blech_ctx->pc_15 = 0;
            blc_blech_aux_termVar_7 = 1;
        } else {
            blc_blech_aux_termVar_7 = 0;
        }
        if ( blc_blech_aux_termVar_7 ) {
            blc_blech_ctx->pc_13 = 30;
        } else if ( !(blc_blech_aux_termVar_7) ) {
            blc_blech_ctx->pc_13 = 60;
        }
    }
    if ( blc_blech_ctx->pc_13 == 30 ) {
        blc_blech_ctx->blc_Dimmer_19_20_0_abortFinished = 1;
        blc_blech_ctx->pc_13 = 32;
    }
    if ( blc_blech_ctx->pc_13 == 32 ) {
        blc_blech_ctx->pc_14 = 0;
        blc_blech_ctx->pc_15 = 0;
        if ( blc_blech_ctx->blc_Dimmer_19_20_0_abortFinished ) {
            blc_blech_ctx->pc_13 = 34;
        } else if ( !(blc_blech_ctx->blc_Dimmer_19_20_0_abortFinished) ) {
            blc_blech_ctx->pc_13 = 6;
            goto loopHead;
        } /* abort subthreads and carry on */
    }
    if ( blc_blech_ctx->pc_13 == 34 ) {
        if ( blc_ranger_anyButtonPressed((&blc_buttonStates)) ) {
            blc_blech_ctx->pc_13 = 36;
        } else if ( !(blc_ranger_anyButtonPressed((&blc_buttonStates))) ) {
            blc_blech_ctx->pc_13 = 44;
        }
    }
    if ( blc_blech_ctx->pc_13 == 36 ) {
        
        blc_blech_ctx->pc_13 = 40;
    }
    if ( blc_blech_ctx->pc_13 == 38 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_13 = 40;
        }
    }
    if ( blc_blech_ctx->pc_13 == 40 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_13 = 4;
            goto loopHead;
        } else if ( 0 ) {
            blc_blech_ctx->pc_13 = 42;
        }
    }
    if ( blc_blech_ctx->pc_13 == 42 ) {
        blc_blech_ctx->pc_13 = 0;
        blc_blech_ctx->pc_14 = 0;
        blc_blech_ctx->pc_15 = 0; /* end */
    }
    if ( blc_blech_ctx->pc_13 == 44 ) {
        struct blc_ranger_ButtonStates blc_blech_aux_tmpLiteral_74;
        memset(&blc_blech_aux_tmpLiteral_74,
               0,
               sizeof(struct blc_ranger_ButtonStates));
        (*blc_filteredButtonStates) = blc_blech_aux_tmpLiteral_74;
        blc_blech_ctx->pc_13_blc_ranger_DimDown.pc_12 = 2;
        blc_int32 blc_blech_aux_retcode_9;
        blc_blech_aux_retcode_9 = blc_ranger_DimDown(&blc_blech_ctx->pc_13_blc_ranger_DimDown,
                                                     4,
                                                     blc_level);
        BLC_UNUSED(blc_blech_aux_retcode_9);
        blc_blech_ctx->pc_13 = 50;
    }
    if ( blc_blech_ctx->pc_13 == 46 ) {
        if ( blc_ranger_anyButtonPressed((&blc_buttonStates)) ) {
            blc_blech_ctx->pc_13 = 58;
        } else if ( 1 ) {
            blc_blech_ctx->pc_13 = 48;
        }
    }
    if ( blc_blech_ctx->pc_13 == 48 ) {
        blc_int32 blc_blech_aux_retcode_9;
        blc_blech_aux_retcode_9 = blc_ranger_DimDown(&blc_blech_ctx->pc_13_blc_ranger_DimDown,
                                                     4,
                                                     blc_level);
        if ( (0 == blc_blech_aux_retcode_9) ) {
            blc_blech_ctx->pc_13 = 52;
        } else if ( !((0 == blc_blech_aux_retcode_9)) ) {
            blc_blech_ctx->pc_13 = 50;
        }
    }
    if ( blc_blech_ctx->pc_13 == 50 ) {
        blc_blech_ctx->pc_13 = 47; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_13 == 52 ) {
        blc_blech_ctx->pc_13 = 55; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_13 == 54 ) {
        if ( blc_ranger_anyButtonPressed((&blc_buttonStates)) ) {
            blc_blech_ctx->pc_13 = 58;
        } else if ( 0 ) {
            blc_blech_ctx->pc_13 = 56;
        }
    }
    if ( blc_blech_ctx->pc_13 == 56 ) {
        blc_blech_ctx->pc_13 = 58;
    }
    if ( blc_blech_ctx->pc_13 == 58 ) {
        (*blc_level) = blc_maxLevel;
        blc_blech_ctx->pc_13 = 39; /* proceed from surface to depth */
        /* abort subthreads and carry on */
    }
    if ( blc_blech_ctx->pc_13 == 60 ) {
        blc_blech_ctx->pc_13 = 17; /* proceed from surface to depth */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_13);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_14);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_15);
    return blc_blech_ctx->pc_13 ;
}

/**  Controls the resulting brightness of the LCD from 2 brightness requests by  */
/**  using the max brightness of both. */
static blc_pc_t blc_ranger_BrightnessController (struct blc_ranger_BrightnessController *blc_blech_ctx,
                                                 const blc_nat8 blc_levels[2],
                                                 blc_nat8 *blc_level) {
    loopHead:
    if ( blc_blech_ctx->pc_16 == 2 ) {
        blc_blech_ctx->blc_BrightnessController_prevLevel = (*blc_level);
        blc_blech_ctx->pc_16 = 4;
    }
    if ( blc_blech_ctx->pc_16 == 4 ) {
        (*blc_level) = blc_ranger_maxNat8(blc_levels);
        if ( ((*blc_level)
        == blc_blech_ctx->blc_BrightnessController_prevLevel) ) {
            blc_blech_ctx->pc_16 = 6;
        } else if ( !(((*blc_level)
        == blc_blech_ctx->blc_BrightnessController_prevLevel)) ) {
            blc_blech_ctx->pc_16 = 8;
        }
    }
    if ( blc_blech_ctx->pc_16 == 6 ) {
        
        blc_blech_ctx->pc_16 = 10;
    }
    if ( blc_blech_ctx->pc_16 == 8 ) {
        blc_ranger_setScreenDimming((*blc_level));
        blc_blech_ctx->blc_BrightnessController_prevLevel = (*blc_level);
        blc_blech_ctx->pc_16 = 10;
    }
    if ( blc_blech_ctx->pc_16 == 10 ) {
        blc_blech_ctx->pc_16 = 13; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_16 == 12 ) {
        if ( 1 ) {
            if ( 1 ) {
                blc_blech_ctx->pc_16 = 4;
                goto loopHead;
            } else if ( 0 ) {
                blc_blech_ctx->pc_16 = 14;
            }
        }
    }
    if ( blc_blech_ctx->pc_16 == 14 ) {
        blc_blech_ctx->pc_16 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_16);
    return blc_blech_ctx->pc_16 ;
}

/**  Reads the accelerometer data at 1Hz and determines the orientation to use. */
static blc_pc_t blc_ranger_RotationController (struct blc_ranger_RotationController *blc_blech_ctx,
                                               blc_nat8 *blc_orientation) {
    loopHead:
    if ( blc_blech_ctx->pc_17 == 2 ) {
        if ( !((-0.1 <= blc_ranger_readRotation())) ) {
            blc_blech_ctx->pc_17 = 4;
        } else if ( (-0.1 <= blc_ranger_readRotation()) ) {
            blc_blech_ctx->pc_17 = 6;
        }
    }
    if ( blc_blech_ctx->pc_17 == 4 ) {
        (*blc_orientation) = blc_ranger_ORIENTATION_HAT_RIGHT;
        blc_blech_ctx->pc_17 = 8;
    }
    if ( blc_blech_ctx->pc_17 == 6 ) {
        (*blc_orientation) = blc_ranger_ORIENTATION_HAT_LEFT;
        blc_blech_ctx->pc_17 = 8;
    }
    if ( blc_blech_ctx->pc_17 == 8 ) {
        blc_ranger_setOrientation((*blc_orientation));
        blc_blech_ctx->blc_RotationController_prevOrientation = (*blc_orientation);
        blc_blech_ctx->pc_17 = 10;
    }
    if ( blc_blech_ctx->pc_17 == 10 ) {
        blc_blech_ctx->pc_17_blc_ranger_DelayOrDidWakeup.pc_2 = 2;
        blc_int32 blc_blech_aux_retcode_10;
        blc_blech_aux_retcode_10 = blc_ranger_DelayOrDidWakeup(&blc_blech_ctx->pc_17_blc_ranger_DelayOrDidWakeup,
                                                               10);
        BLC_UNUSED(blc_blech_aux_retcode_10);
        blc_blech_ctx->pc_17 = 14;
    }
    if ( blc_blech_ctx->pc_17 == 12 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_10;
            blc_blech_aux_retcode_10 = blc_ranger_DelayOrDidWakeup(&blc_blech_ctx->pc_17_blc_ranger_DelayOrDidWakeup,
                                                                   10);
            if ( (0 == blc_blech_aux_retcode_10) ) {
                blc_blech_ctx->pc_17 = 16;
            } else if ( !((0 == blc_blech_aux_retcode_10)) ) {
                blc_blech_ctx->pc_17 = 14;
            }
        }
    }
    if ( blc_blech_ctx->pc_17 == 14 ) {
        blc_blech_ctx->pc_17 = 13; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_17 == 16 ) {
        blc_blech_ctx->blc_RotationController_34_rot = blc_ranger_readRotation();
        if ( !(((blc_blech_ctx->blc_RotationController_prevOrientation
        == blc_ranger_ORIENTATION_HAT_LEFT)
        && (blc_blech_ctx->blc_RotationController_34_rot < -0.2))) ) {
            blc_blech_ctx->pc_17 = 18;
        } else if ( ((blc_blech_ctx->blc_RotationController_prevOrientation
        == blc_ranger_ORIENTATION_HAT_LEFT)
        && (blc_blech_ctx->blc_RotationController_34_rot < -0.2)) ) {
            blc_blech_ctx->pc_17 = 24;
        }
    }
    if ( blc_blech_ctx->pc_17 == 18 ) {
        if ( !(((blc_blech_ctx->blc_RotationController_prevOrientation
        == blc_ranger_ORIENTATION_HAT_RIGHT) && (0.2
        < blc_blech_ctx->blc_RotationController_34_rot))) ) {
            blc_blech_ctx->pc_17 = 20;
        } else if ( ((blc_blech_ctx->blc_RotationController_prevOrientation
        == blc_ranger_ORIENTATION_HAT_RIGHT) && (0.2
        < blc_blech_ctx->blc_RotationController_34_rot)) ) {
            blc_blech_ctx->pc_17 = 22;
        }
    }
    if ( blc_blech_ctx->pc_17 == 20 ) {
        
        blc_blech_ctx->pc_17 = 26;
    }
    if ( blc_blech_ctx->pc_17 == 22 ) {
        (*blc_orientation) = blc_ranger_ORIENTATION_HAT_LEFT;
        blc_ranger_setOrientation((*blc_orientation));
        blc_blech_ctx->blc_RotationController_prevOrientation = (*blc_orientation);
        blc_blech_ctx->pc_17 = 26;
    }
    if ( blc_blech_ctx->pc_17 == 24 ) {
        (*blc_orientation) = blc_ranger_ORIENTATION_HAT_RIGHT;
        blc_ranger_setOrientation((*blc_orientation));
        blc_blech_ctx->blc_RotationController_prevOrientation = (*blc_orientation);
        blc_blech_ctx->pc_17 = 26;
    }
    if ( blc_blech_ctx->pc_17 == 26 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_17 = 10;
            goto loopHead;
        } else if ( 0 ) {
            blc_blech_ctx->pc_17 = 28;
        }
    }
    if ( blc_blech_ctx->pc_17 == 28 ) {
        blc_blech_ctx->pc_17 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_17);
    return blc_blech_ctx->pc_17 ;
}

static void blc_ranger_insertRequests (const struct blc_ranger_DialogRequest blc_requests[3],
                                       struct blc_ranger_DialogRequest blc_nexts[3]) {
    blc_nat8 blc_kind;
    blc_kind = 0;
    if ( (blc_kind < 3) ) {
        do {
            struct blc_ranger_DialogRequest blc_r;
            blc_r = blc_requests[blc_kind];
            if ( !((blc_r.kind == 0)) ) {
                blc_nat8 blc_indexForkind;
                blc_indexForkind = (blc_r.kind - 1);
                blc_nexts[blc_indexForkind] = blc_r;
            }
            blc_kind = (blc_kind + 1);
        } while ( (blc_kind < 3) );
    }
}

static blc_int8 blc_ranger_findNextRequest (const struct blc_ranger_DialogRequest blc_nexts[3]) {
    blc_nat8 blc_i;
    blc_i = 0;
    do {
        if ( !((blc_nexts[blc_i].kind == 0)) ) {
            return (blc_int8)blc_i;
        }
        blc_i = (blc_i + 1);
    } while ( !((blc_i == 3)) );
    return -1;
}

/**  Manages dialog requests by presenting them one after another. */
static blc_pc_t blc_ranger_DialogManager (struct blc_ranger_DialogManager *blc_blech_ctx,
                                          const struct blc_ranger_DialogRequest blc_requests[3],
                                          const blc_nat8 blc_maxLevel,
                                          blc_nat8 *blc_level) {
    blc_int8 blc_blech_prev_delIdx = blc_blech_ctx->blc_DialogManager_delIdx;
    struct blc_ranger_DialogRequest blc_blech_prev_curr = blc_blech_ctx->blc_DialogManager_48_49_curr;
    loopHead:
    if ( blc_blech_ctx->pc_20 == 2 ) {
        memset(blc_blech_ctx->blc_DialogManager_nexts,
               0,
               3 * sizeof(struct blc_ranger_DialogRequest));
        blc_blech_ctx->blc_DialogManager_delIdx = -1;
        blc_blech_prev_delIdx = blc_blech_ctx->blc_DialogManager_delIdx;
        blc_blech_ctx->pc_21 = 8;
        blc_blech_ctx->pc_22 = 4;
        blc_blech_ctx->pc_20 = 76;
    }
    if ( blc_blech_ctx->pc_22 == 4 ) {
        (*blc_level) = 7;
        blc_blech_ctx->pc_22 = 6;
    }
    if ( blc_blech_ctx->pc_22 == 6 ) {
        blc_blech_ctx->pc_22 = 18;
    }
    if ( blc_blech_ctx->pc_21 == 8 ) {
        if ( (blc_blech_prev_delIdx == -1) ) {
            blc_blech_ctx->pc_21 = 10;
        } else if ( !((blc_blech_prev_delIdx == -1)) ) {
            blc_blech_ctx->pc_21 = 12;
        }
    }
    if ( blc_blech_ctx->pc_21 == 10 ) {
        
        blc_blech_ctx->pc_21 = 14;
    }
    if ( blc_blech_ctx->pc_21 == 12 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_86;
        memset(&blc_blech_aux_tmpLiteral_86,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_ctx->blc_DialogManager_nexts[blc_blech_prev_delIdx] = blc_blech_aux_tmpLiteral_86;
        blc_blech_ctx->pc_21 = 14;
    }
    if ( blc_blech_ctx->pc_21 == 14 ) {
        blc_ranger_insertRequests(blc_requests,
                                  blc_blech_ctx->blc_DialogManager_nexts);
        blc_blech_ctx->pc_21 = 17; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_21 == 16 ) {
        if ( 1 ) {
            if ( 1 ) {
                blc_blech_ctx->pc_21 = 8;
                goto loopHead;
            } else if ( 0 ) {
                blc_blech_ctx->pc_21 = 72;
            }
        }
    }
    if ( blc_blech_ctx->pc_22 == 18 ) {
        blc_blech_ctx->blc_DialogManager_48_49_idx = blc_ranger_findNextRequest(blc_blech_ctx->blc_DialogManager_nexts);
        if ( !((blc_blech_ctx->blc_DialogManager_48_49_idx == -1)) ) {
            blc_blech_ctx->pc_22 = 20;
        } else if ( (blc_blech_ctx->blc_DialogManager_48_49_idx == -1) ) {
            blc_blech_ctx->pc_22 = 74;
        }
    }
    if ( blc_blech_ctx->pc_22 == 20 ) {
        
        blc_blech_ctx->pc_22 = 26;
    }
    if ( blc_blech_ctx->pc_22 == 22 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_22 = 24;
        }
    }
    if ( blc_blech_ctx->pc_22 == 24 ) {
        blc_blech_ctx->blc_DialogManager_48_49_idx = blc_ranger_findNextRequest(blc_blech_ctx->blc_DialogManager_nexts);
        if ( (blc_blech_ctx->blc_DialogManager_48_49_idx == -1) ) {
            blc_blech_ctx->pc_22 = 74;
            goto loopHead;
        } else if ( !((blc_blech_ctx->blc_DialogManager_48_49_idx == -1)) ) {
            blc_blech_ctx->pc_22 = 26;
        }
    }
    if ( blc_blech_ctx->pc_22 == 26 ) {
        memset((&blc_blech_ctx->blc_DialogManager_48_49_curr),
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_prev_curr = blc_blech_ctx->blc_DialogManager_48_49_curr;
        blc_blech_ctx->blc_DialogManager_48_49_51_1_abortFinished = 0;
        blc_blech_ctx->pc_22 = 28;
    }
    if ( blc_blech_ctx->pc_22 == 28 ) {
        blc_blech_ctx->blc_DialogManager_48_49_51_1_abortFinished = 0;
        blc_blech_ctx->pc_22 = 30;
    }
    if ( blc_blech_ctx->pc_22 == 30 ) {
        blc_blech_ctx->blc_DialogManager_48_49_curr = blc_blech_ctx->blc_DialogManager_nexts[blc_blech_ctx->blc_DialogManager_48_49_idx];
        blc_blech_ctx->blc_DialogManager_delIdx = blc_blech_ctx->blc_DialogManager_48_49_idx;
        blc_blech_ctx->pc_23 = 46;
        blc_blech_ctx->pc_24 = 32;
        blc_blech_ctx->pc_22 = 58;
    }
    if ( blc_blech_ctx->pc_24 == 32 ) {
        blc_blech_ctx->pc_24 = 35; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_24 == 34 ) {
        if ( (!((blc_blech_ctx->blc_DialogManager_nexts[blc_blech_ctx->blc_DialogManager_48_49_idx].kind
        == 0))
        && !((blc_blech_ctx->blc_DialogManager_nexts[blc_blech_ctx->blc_DialogManager_48_49_idx].info
        == blc_blech_prev_curr.info))) ) {
            blc_blech_ctx->pc_24 = 64;
        } else if ( 1 ) {
            blc_blech_ctx->pc_24 = 36;
        }
    }
    if ( blc_blech_ctx->pc_24 == 36 ) {
        blc_blech_ctx->blc_DialogManager_delIdx = -1;
        blc_blech_ctx->pc_24 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_22 == 38 ) {
        if ( (!((blc_blech_ctx->blc_DialogManager_nexts[blc_blech_ctx->blc_DialogManager_48_49_idx].kind
        == 0))
        && !((blc_blech_ctx->blc_DialogManager_nexts[blc_blech_ctx->blc_DialogManager_48_49_idx].info
        == blc_blech_prev_curr.info))) ) {
            blc_blech_ctx->pc_22 = 64;
        } else if ( 1 ) {
            blc_blech_ctx->pc_22 = 58;
        }
    }
    if ( blc_blech_ctx->pc_23 == 40 ) {
        if ( (!((blc_blech_ctx->blc_DialogManager_nexts[blc_blech_ctx->blc_DialogManager_48_49_idx].kind
        == 0))
        && !((blc_blech_ctx->blc_DialogManager_nexts[blc_blech_ctx->blc_DialogManager_48_49_idx].info
        == blc_blech_prev_curr.info))) ) {
            blc_blech_ctx->pc_23 = 64;
        } else if ( 1 ) {
            blc_blech_ctx->pc_23 = 42;
        }
    }
    if ( blc_blech_ctx->pc_23 == 42 ) {
        blc_int32 blc_blech_aux_retcode_14;
        blc_blech_aux_retcode_14 = blc_ranger_DimDown(&blc_blech_ctx->pc_23_blc_ranger_DimDown,
                                                      2,
                                                      blc_level);
        if ( (0 == blc_blech_aux_retcode_14) ) {
            blc_blech_ctx->pc_23 = 44;
        } else if ( !((0 == blc_blech_aux_retcode_14)) ) {
            blc_blech_ctx->pc_23 = 56;
        }
    }
    if ( blc_blech_ctx->pc_23 == 44 ) {
        blc_ranger_hideDialog();
        blc_blech_ctx->pc_23 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_23 == 46 ) {
        blc_ranger_displayDialog((&blc_blech_ctx->blc_DialogManager_48_49_curr));
        (*blc_level) = blc_maxLevel;
        blc_blech_ctx->pc_23_blc_ranger_Delay.pc_1 = 2;
        blc_int32 blc_blech_aux_retcode_13;
        blc_blech_aux_retcode_13 = blc_ranger_Delay(&blc_blech_ctx->pc_23_blc_ranger_Delay,
                                                    10);
        BLC_UNUSED(blc_blech_aux_retcode_13);
        blc_blech_ctx->pc_23 = 52;
    }
    if ( blc_blech_ctx->pc_23 == 48 ) {
        if ( (!((blc_blech_ctx->blc_DialogManager_nexts[blc_blech_ctx->blc_DialogManager_48_49_idx].kind
        == 0))
        && !((blc_blech_ctx->blc_DialogManager_nexts[blc_blech_ctx->blc_DialogManager_48_49_idx].info
        == blc_blech_prev_curr.info))) ) {
            blc_blech_ctx->pc_23 = 64;
        } else if ( 1 ) {
            blc_blech_ctx->pc_23 = 50;
        }
    }
    if ( blc_blech_ctx->pc_23 == 50 ) {
        blc_int32 blc_blech_aux_retcode_13;
        blc_blech_aux_retcode_13 = blc_ranger_Delay(&blc_blech_ctx->pc_23_blc_ranger_Delay,
                                                    10);
        if ( (0 == blc_blech_aux_retcode_13) ) {
            blc_blech_ctx->pc_23 = 54;
        } else if ( !((0 == blc_blech_aux_retcode_13)) ) {
            blc_blech_ctx->pc_23 = 52;
        }
    }
    if ( blc_blech_ctx->pc_23 == 52 ) {
        blc_blech_ctx->pc_23 = 49; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_23 == 54 ) {
        (*blc_level) = blc_maxLevel;
        blc_blech_ctx->pc_23_blc_ranger_DimDown.pc_12 = 2;
        blc_int32 blc_blech_aux_retcode_14;
        blc_blech_aux_retcode_14 = blc_ranger_DimDown(&blc_blech_ctx->pc_23_blc_ranger_DimDown,
                                                      2,
                                                      blc_level);
        BLC_UNUSED(blc_blech_aux_retcode_14);
        blc_blech_ctx->pc_23 = 56;
    }
    if ( blc_blech_ctx->pc_23 == 56 ) {
        blc_blech_ctx->pc_23 = 41; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_22 == 58 ) {
        blc_bool blc_blech_aux_termVar_12;
        if ( blc_blech_ctx->pc_23 == 0 && blc_blech_ctx->pc_24 == 0 ) {
            blc_blech_ctx->pc_23 = 0;
            blc_blech_ctx->pc_24 = 0;
            blc_blech_aux_termVar_12 = 1;
        } else {
            blc_blech_aux_termVar_12 = 0;
        }
        if ( blc_blech_aux_termVar_12 ) {
            blc_blech_ctx->pc_22 = 60;
        } else if ( !(blc_blech_aux_termVar_12) ) {
            blc_blech_ctx->pc_22 = 62;
        }
    }
    if ( blc_blech_ctx->pc_22 == 60 ) {
        blc_blech_ctx->blc_DialogManager_48_49_51_1_abortFinished = 1;
        blc_blech_ctx->pc_22 = 64;
    }
    if ( blc_blech_ctx->pc_22 == 62 ) {
        blc_blech_ctx->pc_22 = 39; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_22 == 64 ) {
        blc_blech_ctx->pc_23 = 0;
        blc_blech_ctx->pc_23 = 0;
        blc_blech_ctx->pc_24 = 0;
        if ( !(blc_blech_ctx->blc_DialogManager_48_49_51_1_abortFinished) ) {
            blc_blech_ctx->pc_22 = 28;
            goto loopHead;
        } else if ( blc_blech_ctx->blc_DialogManager_48_49_51_1_abortFinished ) {
            blc_blech_ctx->pc_22 = 66;
        } /* abort subthreads and carry on */
    }
    if ( blc_blech_ctx->pc_22 == 66 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_22 = 6;
            goto loopHead;
        } else if ( 0 ) {
            blc_blech_ctx->pc_22 = 68;
        }
    }
    if ( blc_blech_ctx->pc_22 == 68 ) {
        blc_blech_ctx->pc_22 = 0;
        blc_blech_ctx->pc_23 = 0;
        blc_blech_ctx->pc_24 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_20 == 70 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_20 = 76;
        }
    }
    if ( blc_blech_ctx->pc_21 == 72 ) {
        blc_blech_ctx->pc_21 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_22 == 74 ) {
        blc_blech_ctx->pc_22 = 23; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_20 == 76 ) {
        blc_bool blc_blech_aux_termVar_11;
        if ( blc_blech_ctx->pc_21 == 0 && blc_blech_ctx->pc_22 == 0 ) {
            blc_blech_ctx->pc_21 = 0;
            blc_blech_ctx->pc_22 = 0;
            blc_blech_ctx->pc_23 = 0;
            blc_blech_ctx->pc_24 = 0;
            blc_blech_aux_termVar_11 = 1;
        } else {
            blc_blech_aux_termVar_11 = 0;
        }
        if ( !(blc_blech_aux_termVar_11) ) {
            blc_blech_ctx->pc_20 = 78;
        } else if ( blc_blech_aux_termVar_11 ) {
            blc_blech_ctx->pc_20 = 80;
        }
    }
    if ( blc_blech_ctx->pc_20 == 78 ) {
        blc_blech_ctx->pc_20 = 71; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_20 == 80 ) {
        blc_blech_ctx->pc_20 = 0;
        blc_blech_ctx->pc_21 = 0;
        blc_blech_ctx->pc_22 = 0;
        blc_blech_ctx->pc_23 = 0;
        blc_blech_ctx->pc_24 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_20);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_21);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_22);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_23);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_24);
    return blc_blech_ctx->pc_20 ;
}

/**  Observes the battery state of charge and issues a dialog request */
/**  when the charge drops below 20% and 10%. */
static blc_pc_t blc_ranger_BatteryDialog (struct blc_ranger_BatteryDialog *blc_blech_ctx,
                                          const struct blc_ranger_BatteryInfo *const blc_battery,
                                          struct blc_ranger_DialogRequest *blc_request) {
    loopHead:
    if ( blc_blech_ctx->pc_25 == 2 ) {
        blc_blech_ctx->blc_BatteryDialog_seenBelow20 = 0;
        blc_blech_ctx->blc_BatteryDialog_seenBelow10 = 0;
        blc_blech_ctx->pc_25 = 4;
    }
    if ( blc_blech_ctx->pc_25 == 4 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_95;
        memset(&blc_blech_aux_tmpLiteral_95,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        (*blc_request) = blc_blech_aux_tmpLiteral_95;
        if ( !(((*blc_battery).stateOfCharge <= 20)) ) {
            blc_blech_ctx->pc_25 = 6;
        } else if ( ((*blc_battery).stateOfCharge <= 20) ) {
            blc_blech_ctx->pc_25 = 8;
        }
    }
    if ( blc_blech_ctx->pc_25 == 6 ) {
        
        blc_blech_ctx->pc_25 = 14;
    }
    if ( blc_blech_ctx->pc_25 == 8 ) {
        if ( blc_blech_ctx->blc_BatteryDialog_seenBelow20 ) {
            blc_blech_ctx->pc_25 = 10;
        } else if ( !(blc_blech_ctx->blc_BatteryDialog_seenBelow20) ) {
            blc_blech_ctx->pc_25 = 12;
        }
    }
    if ( blc_blech_ctx->pc_25 == 10 ) {
        
        blc_blech_ctx->pc_25 = 14;
    }
    if ( blc_blech_ctx->pc_25 == 12 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_96;
        memset(&blc_blech_aux_tmpLiteral_96,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_aux_tmpLiteral_96.kind = blc_ranger_DIALOG_BATTERY;
        blc_blech_aux_tmpLiteral_96.info = blc_ranger_DIALOG_BATTERY_BELOW_20;
        (*blc_request) = blc_blech_aux_tmpLiteral_96;
        blc_blech_ctx->blc_BatteryDialog_seenBelow20 = 1;
        blc_blech_ctx->pc_25 = 14;
    }
    if ( blc_blech_ctx->pc_25 == 14 ) {
        if ( !(((*blc_battery).stateOfCharge <= 10)) ) {
            blc_blech_ctx->pc_25 = 16;
        } else if ( ((*blc_battery).stateOfCharge <= 10) ) {
            blc_blech_ctx->pc_25 = 18;
        }
    }
    if ( blc_blech_ctx->pc_25 == 16 ) {
        
        blc_blech_ctx->pc_25 = 24;
    }
    if ( blc_blech_ctx->pc_25 == 18 ) {
        if ( blc_blech_ctx->blc_BatteryDialog_seenBelow10 ) {
            blc_blech_ctx->pc_25 = 20;
        } else if ( !(blc_blech_ctx->blc_BatteryDialog_seenBelow10) ) {
            blc_blech_ctx->pc_25 = 22;
        }
    }
    if ( blc_blech_ctx->pc_25 == 20 ) {
        
        blc_blech_ctx->pc_25 = 24;
    }
    if ( blc_blech_ctx->pc_25 == 22 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_97;
        memset(&blc_blech_aux_tmpLiteral_97,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_aux_tmpLiteral_97.kind = blc_ranger_DIALOG_BATTERY;
        blc_blech_aux_tmpLiteral_97.info = blc_ranger_DIALOG_BATTERY_BELOW_10;
        (*blc_request) = blc_blech_aux_tmpLiteral_97;
        blc_blech_ctx->blc_BatteryDialog_seenBelow10 = 1;
        blc_blech_ctx->pc_25 = 24;
    }
    if ( blc_blech_ctx->pc_25 == 24 ) {
        if ( !((13 < (*blc_battery).stateOfCharge)) ) {
            blc_blech_ctx->pc_25 = 26;
        } else if ( (13 < (*blc_battery).stateOfCharge) ) {
            blc_blech_ctx->pc_25 = 28;
        }
    }
    if ( blc_blech_ctx->pc_25 == 26 ) {
        
        blc_blech_ctx->pc_25 = 30;
    }
    if ( blc_blech_ctx->pc_25 == 28 ) {
        blc_blech_ctx->blc_BatteryDialog_seenBelow10 = 0;
        blc_blech_ctx->pc_25 = 30;
    }
    if ( blc_blech_ctx->pc_25 == 30 ) {
        if ( !((23 < (*blc_battery).stateOfCharge)) ) {
            blc_blech_ctx->pc_25 = 32;
        } else if ( (23 < (*blc_battery).stateOfCharge) ) {
            blc_blech_ctx->pc_25 = 34;
        }
    }
    if ( blc_blech_ctx->pc_25 == 32 ) {
        
        blc_blech_ctx->pc_25 = 36;
    }
    if ( blc_blech_ctx->pc_25 == 34 ) {
        blc_blech_ctx->blc_BatteryDialog_seenBelow20 = 0;
        blc_blech_ctx->pc_25 = 36;
    }
    if ( blc_blech_ctx->pc_25 == 36 ) {
        blc_blech_ctx->pc_25 = 39; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_25 == 38 ) {
        if ( 1 ) {
            if ( 1 ) {
                blc_blech_ctx->pc_25 = 4;
                goto loopHead;
            } else if ( 0 ) {
                blc_blech_ctx->pc_25 = 40;
            }
        }
    }
    if ( blc_blech_ctx->pc_25 == 40 ) {
        blc_blech_ctx->pc_25 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_25);
    return blc_blech_ctx->pc_25 ;
}

/**  Observes if BLE gets enabled or connected and requests a dialog if so. */
static blc_pc_t blc_ranger_BLEDialog (struct blc_ranger_BLEDialog *blc_blech_ctx,
                                      const blc_bool blc_bleEnabled,
                                      struct blc_ranger_DialogRequest *blc_request) {
    blc_bool blc_bleConnected = bleConnected;
    loopHead:
    if ( blc_blech_ctx->pc_26 == 2 ) {
        blc_blech_ctx->blc_BLEDialog_prevBLEEnabled = blc_bleEnabled;
        memset((&blc_blech_ctx->blc_BLEDialog_enabledRequest),
               0,
               sizeof(struct blc_ranger_DialogRequest));
        /* The extern declaration is outside the Blech code */
        blc_blech_ctx->blc_BLEDialog_prevBLEConnected = blc_bleConnected;
        memset((&blc_blech_ctx->blc_BLEDialog_connectedRequest),
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_ctx->pc_27 = 14;
        blc_blech_ctx->pc_28 = 6;
        blc_blech_ctx->pc_29 = 4;
        blc_blech_ctx->pc_26 = 52;
    }
    if ( blc_blech_ctx->pc_29 == 4 ) {
        blc_blech_ctx->pc_29 = 12;
    }
    if ( blc_blech_ctx->pc_28 == 6 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_98;
        memset(&blc_blech_aux_tmpLiteral_98,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_ctx->blc_BLEDialog_enabledRequest = blc_blech_aux_tmpLiteral_98;
        blc_blech_ctx->pc_28 = 9; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_28 == 8 ) {
        if ( (blc_bleEnabled
        && !(blc_blech_ctx->blc_BLEDialog_prevBLEEnabled)) ) {
            blc_blech_ctx->blc_BLEDialog_prevBLEEnabled = 1;
            struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_99;
            memset(&blc_blech_aux_tmpLiteral_99,
                   0,
                   sizeof(struct blc_ranger_DialogRequest));
            blc_blech_aux_tmpLiteral_99.kind = blc_ranger_DIALOG_BLE;
            blc_blech_aux_tmpLiteral_99.info = blc_ranger_DIALOG_BLE_ENABLED;
            blc_blech_ctx->blc_BLEDialog_enabledRequest = blc_blech_aux_tmpLiteral_99;
            blc_blech_ctx->pc_28 = 11; /* proceed from surface to depth */
        }
    }
    if ( blc_blech_ctx->pc_28 == 10 ) {
        if ( 1 ) {
            if ( 1 ) {
                blc_blech_ctx->pc_28 = 6;
                goto loopHead;
            } else if ( 0 ) {
                blc_blech_ctx->pc_28 = 44;
            }
        }
    }
    if ( blc_blech_ctx->pc_29 == 12 ) {
        if ( (blc_blech_ctx->blc_BLEDialog_enabledRequest.kind == 0) ) {
            blc_blech_ctx->pc_29 = 28;
        } else if ( !((blc_blech_ctx->blc_BLEDialog_enabledRequest.kind
        == 0)) ) {
            blc_blech_ctx->pc_29 = 34;
        }
    }
    if ( blc_blech_ctx->pc_27 == 14 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_100;
        memset(&blc_blech_aux_tmpLiteral_100,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_ctx->blc_BLEDialog_connectedRequest = blc_blech_aux_tmpLiteral_100;
        if ( !((blc_bleConnected
        == blc_blech_ctx->blc_BLEDialog_prevBLEConnected)) ) {
            blc_blech_ctx->pc_27 = 16;
        } else if ( (blc_bleConnected
        == blc_blech_ctx->blc_BLEDialog_prevBLEConnected) ) {
            blc_blech_ctx->pc_27 = 50;
        }
    }
    if ( blc_blech_ctx->pc_27 == 16 ) {
        
        blc_blech_ctx->pc_27 = 20;
    }
    if ( blc_blech_ctx->pc_27 == 18 ) {
        if ( !((blc_bleConnected
        == blc_blech_ctx->blc_BLEDialog_prevBLEConnected)) ) {
            blc_blech_ctx->pc_27 = 20;
        }
    }
    if ( blc_blech_ctx->pc_27 == 20 ) {
        blc_blech_ctx->blc_BLEDialog_prevBLEConnected = blc_bleConnected;
        if ( !(blc_bleConnected) ) {
            blc_blech_ctx->pc_27 = 22;
        } else if ( blc_bleConnected ) {
            blc_blech_ctx->pc_27 = 26;
        }
    }
    if ( blc_blech_ctx->pc_27 == 22 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_101;
        memset(&blc_blech_aux_tmpLiteral_101,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_aux_tmpLiteral_101.kind = blc_ranger_DIALOG_BLE;
        blc_blech_aux_tmpLiteral_101.info = blc_ranger_DIALOG_BLE_DISCONNECTED;
        blc_blech_ctx->blc_BLEDialog_connectedRequest = blc_blech_aux_tmpLiteral_101;
        blc_blech_ctx->pc_27 = 48;
    }
    if ( blc_blech_ctx->pc_27 == 24 ) {
        if ( 1 ) {
            if ( 1 ) {
                blc_blech_ctx->pc_27 = 14;
                goto loopHead;
            } else if ( 0 ) {
                blc_blech_ctx->pc_27 = 46;
            }
        }
    }
    if ( blc_blech_ctx->pc_27 == 26 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_102;
        memset(&blc_blech_aux_tmpLiteral_102,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_aux_tmpLiteral_102.kind = blc_ranger_DIALOG_BLE;
        blc_blech_aux_tmpLiteral_102.info = blc_ranger_DIALOG_BLE_CONNECTED;
        blc_blech_ctx->blc_BLEDialog_connectedRequest = blc_blech_aux_tmpLiteral_102;
        blc_blech_ctx->pc_27 = 48;
    }
    if ( blc_blech_ctx->pc_29 == 28 ) {
        if ( (blc_blech_ctx->blc_BLEDialog_connectedRequest.kind == 0) ) {
            blc_blech_ctx->pc_29 = 30;
        } else if ( !((blc_blech_ctx->blc_BLEDialog_connectedRequest.kind
        == 0)) ) {
            blc_blech_ctx->pc_29 = 32;
        }
    }
    if ( blc_blech_ctx->pc_29 == 30 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_103;
        memset(&blc_blech_aux_tmpLiteral_103,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        (*blc_request) = blc_blech_aux_tmpLiteral_103;
        blc_blech_ctx->pc_29 = 36;
    }
    if ( blc_blech_ctx->pc_29 == 32 ) {
        (*blc_request) = blc_blech_ctx->blc_BLEDialog_connectedRequest;
        blc_blech_ctx->pc_29 = 36;
    }
    if ( blc_blech_ctx->pc_29 == 34 ) {
        (*blc_request) = blc_blech_ctx->blc_BLEDialog_enabledRequest;
        blc_blech_ctx->pc_29 = 36;
    }
    if ( blc_blech_ctx->pc_29 == 36 ) {
        blc_blech_ctx->pc_29 = 39; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_29 == 38 ) {
        if ( 1 ) {
            if ( 1 ) {
                blc_blech_ctx->pc_29 = 4;
                goto loopHead;
            } else if ( 0 ) {
                blc_blech_ctx->pc_29 = 40;
            }
        }
    }
    if ( blc_blech_ctx->pc_29 == 40 ) {
        blc_blech_ctx->pc_29 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_26 == 42 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_26 = 52;
        }
    }
    if ( blc_blech_ctx->pc_28 == 44 ) {
        blc_blech_ctx->pc_28 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_27 == 46 ) {
        blc_blech_ctx->pc_27 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_27 == 48 ) {
        blc_blech_ctx->pc_27 = 25; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_27 == 50 ) {
        blc_blech_ctx->pc_27 = 19; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_26 == 52 ) {
        blc_bool blc_blech_aux_termVar_15;
        if ( blc_blech_ctx->pc_27 == 0 && blc_blech_ctx->pc_28 == 0 && blc_blech_ctx->pc_29 == 0 ) {
            blc_blech_ctx->pc_27 = 0;
            blc_blech_ctx->pc_28 = 0;
            blc_blech_ctx->pc_29 = 0;
            blc_blech_aux_termVar_15 = 1;
        } else {
            blc_blech_aux_termVar_15 = 0;
        }
        if ( !(blc_blech_aux_termVar_15) ) {
            blc_blech_ctx->pc_26 = 54;
        } else if ( blc_blech_aux_termVar_15 ) {
            blc_blech_ctx->pc_26 = 56;
        }
    }
    if ( blc_blech_ctx->pc_26 == 54 ) {
        blc_blech_ctx->pc_26 = 43; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_26 == 56 ) {
        blc_blech_ctx->pc_26 = 0;
        blc_blech_ctx->pc_27 = 0;
        blc_blech_ctx->pc_28 = 0;
        blc_blech_ctx->pc_29 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_26);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_27);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_28);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_29);
    return blc_blech_ctx->pc_26 ;
}

/**  This activity will request a dialog if it detects USB being plugged or unplugged. */
static blc_pc_t blc_ranger_USBDialog (struct blc_ranger_USBDialog *blc_blech_ctx,
                                      const struct blc_ranger_BatteryInfo *const blc_battery,
                                      struct blc_ranger_DialogRequest *blc_request) {
    loopHead:
    if ( blc_blech_ctx->pc_30 == 2 ) {
        blc_blech_ctx->blc_USBDialog_prevIsCharging = (*blc_battery).isCharging;
        blc_blech_ctx->pc_30 = 4;
    }
    if ( blc_blech_ctx->pc_30 == 4 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_104;
        memset(&blc_blech_aux_tmpLiteral_104,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        (*blc_request) = blc_blech_aux_tmpLiteral_104;
        if ( !(((*blc_battery).isCharging
        == blc_blech_ctx->blc_USBDialog_prevIsCharging)) ) {
            blc_blech_ctx->pc_30 = 6;
        } else if ( ((*blc_battery).isCharging
        == blc_blech_ctx->blc_USBDialog_prevIsCharging) ) {
            blc_blech_ctx->pc_30 = 22;
        }
    }
    if ( blc_blech_ctx->pc_30 == 6 ) {
        
        blc_blech_ctx->pc_30 = 10;
    }
    if ( blc_blech_ctx->pc_30 == 8 ) {
        if ( !(((*blc_battery).isCharging
        == blc_blech_ctx->blc_USBDialog_prevIsCharging)) ) {
            blc_blech_ctx->pc_30 = 10;
        }
    }
    if ( blc_blech_ctx->pc_30 == 10 ) {
        blc_blech_ctx->blc_USBDialog_prevIsCharging = (*blc_battery).isCharging;
        if ( !((*blc_battery).isCharging) ) {
            blc_blech_ctx->pc_30 = 12;
        } else if ( (*blc_battery).isCharging ) {
            blc_blech_ctx->pc_30 = 14;
        }
    }
    if ( blc_blech_ctx->pc_30 == 12 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_105;
        memset(&blc_blech_aux_tmpLiteral_105,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_aux_tmpLiteral_105.kind = blc_ranger_DIALOG_USB;
        blc_blech_aux_tmpLiteral_105.info = blc_ranger_DIALOG_USB_DISCONNECTED;
        (*blc_request) = blc_blech_aux_tmpLiteral_105;
        blc_blech_ctx->pc_30 = 16;
    }
    if ( blc_blech_ctx->pc_30 == 14 ) {
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_106;
        memset(&blc_blech_aux_tmpLiteral_106,
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_aux_tmpLiteral_106.kind = blc_ranger_DIALOG_USB;
        blc_blech_aux_tmpLiteral_106.info = blc_ranger_DIALOG_USB_CONNECTED;
        (*blc_request) = blc_blech_aux_tmpLiteral_106;
        blc_blech_ctx->pc_30 = 16;
    }
    if ( blc_blech_ctx->pc_30 == 16 ) {
        blc_blech_ctx->pc_30 = 19; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_30 == 18 ) {
        if ( 1 ) {
            if ( 1 ) {
                blc_blech_ctx->pc_30 = 4;
                goto loopHead;
            } else if ( 0 ) {
                blc_blech_ctx->pc_30 = 20;
            }
        }
    }
    if ( blc_blech_ctx->pc_30 == 20 ) {
        blc_blech_ctx->pc_30 = 0; /* end */
    }
    if ( blc_blech_ctx->pc_30 == 22 ) {
        blc_blech_ctx->pc_30 = 9; /* proceed from surface to depth */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_30);
    return blc_blech_ctx->pc_30 ;
}

/**  The splash screen displayed after setup. */
static blc_pc_t blc_ranger_WelcomeScreen (struct blc_ranger_WelcomeScreen *blc_blech_ctx) {
    if ( blc_blech_ctx->pc_31 == 2 ) {
        blc_ranger_displayWelcomeScreen();
        blc_blech_ctx->pc_31_blc_ranger_Delay.pc_1 = 2;
        blc_int32 blc_blech_aux_retcode_16;
        blc_blech_aux_retcode_16 = blc_ranger_Delay(&blc_blech_ctx->pc_31_blc_ranger_Delay,
                                                    20);
        BLC_UNUSED(blc_blech_aux_retcode_16);
        blc_blech_ctx->pc_31 = 6;
    }
    if ( blc_blech_ctx->pc_31 == 4 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_16;
            blc_blech_aux_retcode_16 = blc_ranger_Delay(&blc_blech_ctx->pc_31_blc_ranger_Delay,
                                                        20);
            if ( !((0 == blc_blech_aux_retcode_16)) ) {
                blc_blech_ctx->pc_31 = 6;
            } else if ( (0 == blc_blech_aux_retcode_16) ) {
                blc_blech_ctx->pc_31 = 8;
            }
        }
    }
    if ( blc_blech_ctx->pc_31 == 6 ) {
        blc_blech_ctx->pc_31 = 5; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_31 == 8 ) {
        blc_blech_ctx->pc_31 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_31);
    return blc_blech_ctx->pc_31 ;
}

/**  A screen consisting of several text pages explaining the software. */
static blc_pc_t blc_ranger_HelpSettingsScreen (struct blc_ranger_HelpSettingsScreen *blc_blech_ctx,
                                               const struct blc_ranger_ButtonStates *const blc_buttonStates) {
    loopHead:
    if ( blc_blech_ctx->pc_32 == 2 ) {
        blc_blech_ctx->blc_HelpSettingsScreen_page = 0;
        blc_blech_ctx->pc_32 = 4;
    }
    if ( blc_blech_ctx->pc_32 == 4 ) {
        blc_blech_ctx->blc_HelpSettingsScreen_87_hasNextPage = blc_ranger_displayHelpSettingsScreen(blc_blech_ctx->blc_HelpSettingsScreen_page);
        blc_blech_ctx->blc_HelpSettingsScreen_87_press = 0;
        blc_blech_ctx->pc_32_blc_ranger_PressRecognizer.pc_8 = 2;
        blc_blech_ctx->pc_32_blc_ranger_PressRecognizer.pc_9 = 0;
        blc_blech_ctx->pc_32_blc_ranger_PressRecognizer.pc_10 = 0;
        blc_int32 blc_blech_aux_retcode_17;
        blc_blech_aux_retcode_17 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_32_blc_ranger_PressRecognizer,
                                                              blc_buttonStates,
                                                              (&blc_blech_ctx->blc_HelpSettingsScreen_87_press));
        BLC_UNUSED(blc_blech_aux_retcode_17);
        blc_blech_ctx->pc_32 = 8;
    }
    if ( blc_blech_ctx->pc_32 == 6 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_17;
            blc_blech_aux_retcode_17 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_32_blc_ranger_PressRecognizer,
                                                                  blc_buttonStates,
                                                                  (&blc_blech_ctx->blc_HelpSettingsScreen_87_press));
            if ( (0 == blc_blech_aux_retcode_17) ) {
                blc_blech_ctx->pc_32 = 10;
            } else if ( !((0 == blc_blech_aux_retcode_17)) ) {
                blc_blech_ctx->pc_32 = 8;
            }
        }
    }
    if ( blc_blech_ctx->pc_32 == 8 ) {
        blc_blech_ctx->pc_32 = 7; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_32 == 10 ) {
        if ( !((blc_blech_ctx->blc_HelpSettingsScreen_87_press == 1)) ) {
            blc_blech_ctx->pc_32 = 12;
        } else if ( (blc_blech_ctx->blc_HelpSettingsScreen_87_press == 1) ) {
            blc_blech_ctx->pc_32 = 18;
        }
    }
    if ( blc_blech_ctx->pc_32 == 12 ) {
        if ( !((blc_blech_ctx->blc_HelpSettingsScreen_87_press == 3)) ) {
            blc_blech_ctx->pc_32 = 14;
        } else if ( (blc_blech_ctx->blc_HelpSettingsScreen_87_press == 3) ) {
            blc_blech_ctx->pc_32 = 16;
        }
    }
    if ( blc_blech_ctx->pc_32 == 14 ) {
        
        blc_blech_ctx->pc_32 = 24;
    }
    if ( blc_blech_ctx->pc_32 == 16 ) {
        blc_blech_ctx->blc_HelpSettingsScreen_page = 0;
        blc_blech_ctx->pc_32 = 24;
    }
    if ( blc_blech_ctx->pc_32 == 18 ) {
        if ( !(blc_blech_ctx->blc_HelpSettingsScreen_87_hasNextPage) ) {
            blc_blech_ctx->pc_32 = 20;
        } else if ( blc_blech_ctx->blc_HelpSettingsScreen_87_hasNextPage ) {
            blc_blech_ctx->pc_32 = 22;
        }
    }
    if ( blc_blech_ctx->pc_32 == 20 ) {
        blc_blech_ctx->blc_HelpSettingsScreen_page = 0;
        blc_blech_ctx->pc_32 = 24;
    }
    if ( blc_blech_ctx->pc_32 == 22 ) {
        blc_blech_ctx->blc_HelpSettingsScreen_page = (blc_blech_ctx->blc_HelpSettingsScreen_page
        + 1);
        blc_blech_ctx->pc_32 = 24;
    }
    if ( blc_blech_ctx->pc_32 == 24 ) {
        if ( !((blc_blech_ctx->blc_HelpSettingsScreen_87_press == 2)) ) {
            blc_blech_ctx->pc_32 = 4;
            goto loopHead;
        } else if ( (blc_blech_ctx->blc_HelpSettingsScreen_87_press == 2) ) {
            blc_blech_ctx->pc_32 = 26;
        }
    }
    if ( blc_blech_ctx->pc_32 == 26 ) {
        blc_blech_ctx->pc_32 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_32);
    return blc_blech_ctx->pc_32 ;
}

/**  Screen allowing user to chose the measure unit. */
static blc_pc_t blc_ranger_UnitSettingsScreen (struct blc_ranger_UnitSettingsScreen *blc_blech_ctx,
                                               const struct blc_ranger_ButtonStates *const blc_buttonStates,
                                               blc_nat8 *blc_selectedUnit) {
    loopHead:
    if ( blc_blech_ctx->pc_33 == 2 ) {
        blc_blech_ctx->blc_UnitSettingsScreen_displayedUnit = (*blc_selectedUnit);
        blc_blech_ctx->pc_33 = 4;
    }
    if ( blc_blech_ctx->pc_33 == 4 ) {
        blc_ranger_displayUnitSettingsScreen(blc_blech_ctx->blc_UnitSettingsScreen_displayedUnit,
                                             (*blc_selectedUnit));
        blc_blech_ctx->blc_UnitSettingsScreen_93_press = 0;
        blc_blech_ctx->pc_33_blc_ranger_PressRecognizer.pc_8 = 2;
        blc_blech_ctx->pc_33_blc_ranger_PressRecognizer.pc_9 = 0;
        blc_blech_ctx->pc_33_blc_ranger_PressRecognizer.pc_10 = 0;
        blc_int32 blc_blech_aux_retcode_18;
        blc_blech_aux_retcode_18 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_33_blc_ranger_PressRecognizer,
                                                              blc_buttonStates,
                                                              (&blc_blech_ctx->blc_UnitSettingsScreen_93_press));
        BLC_UNUSED(blc_blech_aux_retcode_18);
        blc_blech_ctx->pc_33 = 8;
    }
    if ( blc_blech_ctx->pc_33 == 6 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_18;
            blc_blech_aux_retcode_18 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_33_blc_ranger_PressRecognizer,
                                                                  blc_buttonStates,
                                                                  (&blc_blech_ctx->blc_UnitSettingsScreen_93_press));
            if ( (0 == blc_blech_aux_retcode_18) ) {
                blc_blech_ctx->pc_33 = 10;
            } else if ( !((0 == blc_blech_aux_retcode_18)) ) {
                blc_blech_ctx->pc_33 = 8;
            }
        }
    }
    if ( blc_blech_ctx->pc_33 == 8 ) {
        blc_blech_ctx->pc_33 = 7; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_33 == 10 ) {
        if ( !((blc_blech_ctx->blc_UnitSettingsScreen_93_press == 1)) ) {
            blc_blech_ctx->pc_33 = 12;
        } else if ( (blc_blech_ctx->blc_UnitSettingsScreen_93_press == 1) ) {
            blc_blech_ctx->pc_33 = 18;
        }
    }
    if ( blc_blech_ctx->pc_33 == 12 ) {
        if ( !((blc_blech_ctx->blc_UnitSettingsScreen_93_press == 3)) ) {
            blc_blech_ctx->pc_33 = 14;
        } else if ( (blc_blech_ctx->blc_UnitSettingsScreen_93_press == 3) ) {
            blc_blech_ctx->pc_33 = 16;
        }
    }
    if ( blc_blech_ctx->pc_33 == 14 ) {
        
        blc_blech_ctx->pc_33 = 20;
    }
    if ( blc_blech_ctx->pc_33 == 16 ) {
        (*blc_selectedUnit) = blc_blech_ctx->blc_UnitSettingsScreen_displayedUnit;
        blc_blech_ctx->pc_33 = 20;
    }
    if ( blc_blech_ctx->pc_33 == 18 ) {
        blc_blech_ctx->blc_UnitSettingsScreen_displayedUnit = ((blc_blech_ctx->blc_UnitSettingsScreen_displayedUnit
        + 1) % 3);
        blc_blech_ctx->pc_33 = 20;
    }
    if ( blc_blech_ctx->pc_33 == 20 ) {
        if ( !((blc_blech_ctx->blc_UnitSettingsScreen_93_press == 2)) ) {
            blc_blech_ctx->pc_33 = 4;
            goto loopHead;
        } else if ( (blc_blech_ctx->blc_UnitSettingsScreen_93_press == 2) ) {
            blc_blech_ctx->pc_33 = 22;
        }
    }
    if ( blc_blech_ctx->pc_33 == 22 ) {
        blc_blech_ctx->pc_33 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_33);
    return blc_blech_ctx->pc_33 ;
}

/**  Screen allowing user to toggle between measurment from hat or bottom of stick. */
static blc_pc_t blc_ranger_OffsetSettingsScreen (struct blc_ranger_OffsetSettingsScreen *blc_blech_ctx,
                                                 const struct blc_ranger_ButtonStates *const blc_buttonStates,
                                                 blc_bool *blc_measureFromBack) {
    loopHead:
    if ( blc_blech_ctx->pc_34 == 2 ) {
        blc_ranger_displayOffsetSettingsScreen((*blc_measureFromBack));
        blc_blech_ctx->blc_OffsetSettingsScreen_97_press = 0;
        blc_blech_ctx->pc_34_blc_ranger_PressRecognizer.pc_8 = 2;
        blc_blech_ctx->pc_34_blc_ranger_PressRecognizer.pc_9 = 0;
        blc_blech_ctx->pc_34_blc_ranger_PressRecognizer.pc_10 = 0;
        blc_int32 blc_blech_aux_retcode_19;
        blc_blech_aux_retcode_19 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_34_blc_ranger_PressRecognizer,
                                                              blc_buttonStates,
                                                              (&blc_blech_ctx->blc_OffsetSettingsScreen_97_press));
        BLC_UNUSED(blc_blech_aux_retcode_19);
        blc_blech_ctx->pc_34 = 6;
    }
    if ( blc_blech_ctx->pc_34 == 4 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_19;
            blc_blech_aux_retcode_19 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_34_blc_ranger_PressRecognizer,
                                                                  blc_buttonStates,
                                                                  (&blc_blech_ctx->blc_OffsetSettingsScreen_97_press));
            if ( (0 == blc_blech_aux_retcode_19) ) {
                blc_blech_ctx->pc_34 = 8;
            } else if ( !((0 == blc_blech_aux_retcode_19)) ) {
                blc_blech_ctx->pc_34 = 6;
            }
        }
    }
    if ( blc_blech_ctx->pc_34 == 6 ) {
        blc_blech_ctx->pc_34 = 5; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_34 == 8 ) {
        if ( !(blc_ranger_isShortOrDoublePress(blc_blech_ctx->blc_OffsetSettingsScreen_97_press)) ) {
            blc_blech_ctx->pc_34 = 10;
        } else if ( blc_ranger_isShortOrDoublePress(blc_blech_ctx->blc_OffsetSettingsScreen_97_press) ) {
            blc_blech_ctx->pc_34 = 12;
        }
    }
    if ( blc_blech_ctx->pc_34 == 10 ) {
        
        blc_blech_ctx->pc_34 = 14;
    }
    if ( blc_blech_ctx->pc_34 == 12 ) {
        (*blc_measureFromBack) = !((*blc_measureFromBack));
        blc_blech_ctx->pc_34 = 14;
    }
    if ( blc_blech_ctx->pc_34 == 14 ) {
        if ( !((blc_blech_ctx->blc_OffsetSettingsScreen_97_press == 2)) ) {
            blc_blech_ctx->pc_34 = 2;
            goto loopHead;
        } else if ( (blc_blech_ctx->blc_OffsetSettingsScreen_97_press == 2) ) {
            blc_blech_ctx->pc_34 = 16;
        }
    }
    if ( blc_blech_ctx->pc_34 == 16 ) {
        blc_blech_ctx->pc_34 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_34);
    return blc_blech_ctx->pc_34 ;
}

/**  Screen to enable or disable bluetooth. */
static blc_pc_t blc_ranger_BLESettingsScreen (struct blc_ranger_BLESettingsScreen *blc_blech_ctx,
                                              const struct blc_ranger_ButtonStates *const blc_buttonStates,
                                              blc_bool *blc_bleEnabled) {
    loopHead:
    if ( blc_blech_ctx->pc_35 == 2 ) {
        blc_ranger_displayBLESettingsScreen((*blc_bleEnabled));
        blc_blech_ctx->blc_BLESettingsScreen_100_press = 0;
        blc_blech_ctx->pc_35_blc_ranger_PressRecognizer.pc_8 = 2;
        blc_blech_ctx->pc_35_blc_ranger_PressRecognizer.pc_9 = 0;
        blc_blech_ctx->pc_35_blc_ranger_PressRecognizer.pc_10 = 0;
        blc_int32 blc_blech_aux_retcode_20;
        blc_blech_aux_retcode_20 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_35_blc_ranger_PressRecognizer,
                                                              blc_buttonStates,
                                                              (&blc_blech_ctx->blc_BLESettingsScreen_100_press));
        BLC_UNUSED(blc_blech_aux_retcode_20);
        blc_blech_ctx->pc_35 = 6;
    }
    if ( blc_blech_ctx->pc_35 == 4 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_20;
            blc_blech_aux_retcode_20 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_35_blc_ranger_PressRecognizer,
                                                                  blc_buttonStates,
                                                                  (&blc_blech_ctx->blc_BLESettingsScreen_100_press));
            if ( (0 == blc_blech_aux_retcode_20) ) {
                blc_blech_ctx->pc_35 = 8;
            } else if ( !((0 == blc_blech_aux_retcode_20)) ) {
                blc_blech_ctx->pc_35 = 6;
            }
        }
    }
    if ( blc_blech_ctx->pc_35 == 6 ) {
        blc_blech_ctx->pc_35 = 5; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_35 == 8 ) {
        if ( !((blc_blech_ctx->blc_BLESettingsScreen_100_press == 3)) ) {
            blc_blech_ctx->pc_35 = 10;
        } else if ( (blc_blech_ctx->blc_BLESettingsScreen_100_press == 3) ) {
            blc_blech_ctx->pc_35 = 20;
        }
    }
    if ( blc_blech_ctx->pc_35 == 10 ) {
        
        blc_blech_ctx->pc_35 = 16;
    }
    if ( blc_blech_ctx->pc_35 == 12 ) {
        if ( 1 ) {
            blc_ranger_enableBLE();
            blc_blech_ctx->pc_35 = 16;
        }
    }
    if ( blc_blech_ctx->pc_35 == 14 ) {
        if ( 0 ) {
            blc_blech_ctx->pc_35 = 16;
        }
    }
    if ( blc_blech_ctx->pc_35 == 16 ) {
        if ( !((blc_blech_ctx->blc_BLESettingsScreen_100_press == 2)) ) {
            blc_blech_ctx->pc_35 = 2;
            goto loopHead;
        } else if ( (blc_blech_ctx->blc_BLESettingsScreen_100_press == 2) ) {
            blc_blech_ctx->pc_35 = 18;
        }
    }
    if ( blc_blech_ctx->pc_35 == 18 ) {
        blc_blech_ctx->pc_35 = 0; /* end */
    }
    if ( blc_blech_ctx->pc_35 == 20 ) {
        if ( !((*blc_bleEnabled)) ) {
            blc_blech_ctx->pc_35 = 22;
        } else if ( (*blc_bleEnabled) ) {
            blc_blech_ctx->pc_35 = 24;
        }
    }
    if ( blc_blech_ctx->pc_35 == 22 ) {
        (*blc_bleEnabled) = 1;
        blc_blech_ctx->pc_35 = 13; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_35 == 24 ) {
        (*blc_bleEnabled) = 0;
        blc_ranger_requestRestart();
        blc_blech_ctx->pc_35 = 15; /* proceed from surface to depth */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_35);
    return blc_blech_ctx->pc_35 ;
}

/**  This screen allows the user to select the brightness of the LCD. */
static blc_pc_t blc_ranger_BrightnessSettingsScreen (struct blc_ranger_BrightnessSettingsScreen *blc_blech_ctx,
                                                     const struct blc_ranger_ButtonStates *const blc_buttonStates,
                                                     blc_nat8 *blc_brightness) {
    loopHead:
    if ( blc_blech_ctx->pc_36 == 2 ) {
        blc_ranger_displayBrightnessSettingsScreen(((*blc_brightness) - 7));
        blc_blech_ctx->blc_BrightnessSettingsScreen_105_press = 0;
        blc_blech_ctx->pc_36_blc_ranger_PressRecognizer.pc_8 = 2;
        blc_blech_ctx->pc_36_blc_ranger_PressRecognizer.pc_9 = 0;
        blc_blech_ctx->pc_36_blc_ranger_PressRecognizer.pc_10 = 0;
        blc_int32 blc_blech_aux_retcode_21;
        blc_blech_aux_retcode_21 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_36_blc_ranger_PressRecognizer,
                                                              blc_buttonStates,
                                                              (&blc_blech_ctx->blc_BrightnessSettingsScreen_105_press));
        BLC_UNUSED(blc_blech_aux_retcode_21);
        blc_blech_ctx->pc_36 = 6;
    }
    if ( blc_blech_ctx->pc_36 == 4 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_21;
            blc_blech_aux_retcode_21 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_36_blc_ranger_PressRecognizer,
                                                                  blc_buttonStates,
                                                                  (&blc_blech_ctx->blc_BrightnessSettingsScreen_105_press));
            if ( (0 == blc_blech_aux_retcode_21) ) {
                blc_blech_ctx->pc_36 = 8;
            } else if ( !((0 == blc_blech_aux_retcode_21)) ) {
                blc_blech_ctx->pc_36 = 6;
            }
        }
    }
    if ( blc_blech_ctx->pc_36 == 6 ) {
        blc_blech_ctx->pc_36 = 5; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_36 == 8 ) {
        if ( !(blc_ranger_isShortOrDoublePress(blc_blech_ctx->blc_BrightnessSettingsScreen_105_press)) ) {
            blc_blech_ctx->pc_36 = 10;
        } else if ( blc_ranger_isShortOrDoublePress(blc_blech_ctx->blc_BrightnessSettingsScreen_105_press) ) {
            blc_blech_ctx->pc_36 = 12;
        }
    }
    if ( blc_blech_ctx->pc_36 == 10 ) {
        
        blc_blech_ctx->pc_36 = 18;
    }
    if ( blc_blech_ctx->pc_36 == 12 ) {
        (*blc_brightness) = ((*blc_brightness) - 1);
        if ( !(((*blc_brightness) < 8)) ) {
            blc_blech_ctx->pc_36 = 14;
        } else if ( ((*blc_brightness) < 8) ) {
            blc_blech_ctx->pc_36 = 16;
        }
    }
    if ( blc_blech_ctx->pc_36 == 14 ) {
        
        blc_blech_ctx->pc_36 = 18;
    }
    if ( blc_blech_ctx->pc_36 == 16 ) {
        (*blc_brightness) = 12;
        blc_blech_ctx->pc_36 = 18;
    }
    if ( blc_blech_ctx->pc_36 == 18 ) {
        if ( !((blc_blech_ctx->blc_BrightnessSettingsScreen_105_press == 2)) ) {
            blc_blech_ctx->pc_36 = 2;
            goto loopHead;
        } else if ( (blc_blech_ctx->blc_BrightnessSettingsScreen_105_press
        == 2) ) {
            blc_blech_ctx->pc_36 = 20;
        }
    }
    if ( blc_blech_ctx->pc_36 == 20 ) {
        blc_blech_ctx->pc_36 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_36);
    return blc_blech_ctx->pc_36 ;
}

/**  A screen showing the possible setting sub-screens. */
static blc_pc_t blc_ranger_SettingsScreen (struct blc_ranger_SettingsScreen *blc_blech_ctx,
                                           const struct blc_ranger_ButtonStates *const blc_buttonStates,
                                           struct blc_ranger_Settings *blc_settings) {
    loopHead:
    if ( blc_blech_ctx->pc_37 == 2 ) {
        blc_blech_ctx->blc_SettingsScreen_index = 0;
        blc_blech_ctx->pc_37 = 4;
    }
    if ( blc_blech_ctx->pc_37 == 4 ) {
        blc_ranger_displaySettingsScreen(blc_blech_ctx->blc_SettingsScreen_index);
        blc_blech_ctx->blc_SettingsScreen_110_press = 0;
        blc_blech_ctx->pc_37_blc_ranger_PressRecognizer.pc_8 = 2;
        blc_blech_ctx->pc_37_blc_ranger_PressRecognizer.pc_9 = 0;
        blc_blech_ctx->pc_37_blc_ranger_PressRecognizer.pc_10 = 0;
        blc_int32 blc_blech_aux_retcode_22;
        blc_blech_aux_retcode_22 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_37_blc_ranger_PressRecognizer,
                                                              blc_buttonStates,
                                                              (&blc_blech_ctx->blc_SettingsScreen_110_press));
        BLC_UNUSED(blc_blech_aux_retcode_22);
        blc_blech_ctx->pc_37 = 8;
    }
    if ( blc_blech_ctx->pc_37 == 6 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_22;
            blc_blech_aux_retcode_22 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_37_blc_ranger_PressRecognizer,
                                                                  blc_buttonStates,
                                                                  (&blc_blech_ctx->blc_SettingsScreen_110_press));
            if ( (0 == blc_blech_aux_retcode_22) ) {
                blc_blech_ctx->pc_37 = 10;
            } else if ( !((0 == blc_blech_aux_retcode_22)) ) {
                blc_blech_ctx->pc_37 = 8;
            }
        }
    }
    if ( blc_blech_ctx->pc_37 == 8 ) {
        blc_blech_ctx->pc_37 = 7; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_37 == 10 ) {
        if ( !((blc_blech_ctx->blc_SettingsScreen_110_press == 1)) ) {
            blc_blech_ctx->pc_37 = 12;
        } else if ( (blc_blech_ctx->blc_SettingsScreen_110_press == 1) ) {
            blc_blech_ctx->pc_37 = 76;
        }
    }
    if ( blc_blech_ctx->pc_37 == 12 ) {
        if ( !((blc_blech_ctx->blc_SettingsScreen_110_press == 3)) ) {
            blc_blech_ctx->pc_37 = 14;
        } else if ( (blc_blech_ctx->blc_SettingsScreen_110_press == 3) ) {
            blc_blech_ctx->pc_37 = 32;
        }
    }
    if ( blc_blech_ctx->pc_37 == 14 ) {
        
        blc_blech_ctx->pc_37 = 78;
    }
    if ( blc_blech_ctx->pc_39 == 16 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_39 = 26;
        }
    }
    if ( blc_blech_ctx->pc_38 == 18 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_28;
            blc_blech_aux_retcode_28 = blc_ranger_BrightnessSettingsScreen(&blc_blech_ctx->pc_38_blc_ranger_BrightnessSettingsScreen,
                                                                           blc_buttonStates,
                                                                           (&(*blc_settings).brightness));
            if ( (0 == blc_blech_aux_retcode_28) ) {
                blc_blech_ctx->pc_38 = 48;
            } else if ( !((0 == blc_blech_aux_retcode_28)) ) {
                blc_blech_ctx->pc_38 = 62;
            }
        }
    }
    if ( blc_blech_ctx->pc_38 == 20 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_27;
            blc_blech_aux_retcode_27 = blc_ranger_BLESettingsScreen(&blc_blech_ctx->pc_38_blc_ranger_BLESettingsScreen,
                                                                    blc_buttonStates,
                                                                    (&(*blc_settings).bleEnabled));
            if ( !((0 == blc_blech_aux_retcode_27)) ) {
                blc_blech_ctx->pc_38 = 64;
            } else if ( (0 == blc_blech_aux_retcode_27) ) {
                blc_blech_ctx->pc_38 = 48;
            }
        }
    }
    if ( blc_blech_ctx->pc_38 == 22 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_26;
            blc_blech_aux_retcode_26 = blc_ranger_OffsetSettingsScreen(&blc_blech_ctx->pc_38_blc_ranger_OffsetSettingsScreen,
                                                                       blc_buttonStates,
                                                                       (&(*blc_settings).measureFromBack));
            if ( (0 == blc_blech_aux_retcode_26) ) {
                blc_blech_ctx->pc_38 = 48;
            } else if ( !((0 == blc_blech_aux_retcode_26)) ) {
                blc_blech_ctx->pc_38 = 66;
            }
        }
    }
    if ( blc_blech_ctx->pc_38 == 24 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_25;
            blc_blech_aux_retcode_25 = blc_ranger_UnitSettingsScreen(&blc_blech_ctx->pc_38_blc_ranger_UnitSettingsScreen,
                                                                     blc_buttonStates,
                                                                     (&(*blc_settings).measureUnit));
            if ( !((0 == blc_blech_aux_retcode_25)) ) {
                blc_blech_ctx->pc_38 = 68;
            } else if ( (0 == blc_blech_aux_retcode_25) ) {
                blc_blech_ctx->pc_38 = 48;
            }
        }
    }
    if ( blc_blech_ctx->pc_39 == 26 ) {
        blc_int32 blc_blech_aux_retcode_29;
        blc_blech_aux_retcode_29 = blc_ranger_SettingsPersister(&blc_blech_ctx->pc_39_blc_ranger_SettingsPersister,
                                                                blc_settings);
        if ( !((0 == blc_blech_aux_retcode_29)) ) {
            blc_blech_ctx->pc_39 = 60;
        } else if ( (0 == blc_blech_aux_retcode_29) ) {
            blc_blech_ctx->pc_39 = 28;
        }
    }
    if ( blc_blech_ctx->pc_39 == 28 ) {
        blc_blech_ctx->pc_39 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_37 == 30 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_37 = 74;
        }
    }
    if ( blc_blech_ctx->pc_37 == 32 ) {
        blc_blech_ctx->pc_38 = 34;
        blc_blech_ctx->pc_39 = 58;
        blc_blech_ctx->pc_37 = 74;
    }
    if ( blc_blech_ctx->pc_38 == 34 ) {
        if ( !((blc_blech_ctx->blc_SettingsScreen_index
        == blc_ranger_SETTINGS_HELP)) ) {
            blc_blech_ctx->pc_38 = 36;
        } else if ( (blc_blech_ctx->blc_SettingsScreen_index
        == blc_ranger_SETTINGS_HELP) ) {
            blc_blech_ctx->pc_38 = 70;
        }
    }
    if ( blc_blech_ctx->pc_38 == 36 ) {
        if ( !((blc_blech_ctx->blc_SettingsScreen_index
        == blc_ranger_SETTINGS_UNIT)) ) {
            blc_blech_ctx->pc_38 = 38;
        } else if ( (blc_blech_ctx->blc_SettingsScreen_index
        == blc_ranger_SETTINGS_UNIT) ) {
            blc_blech_ctx->pc_38 = 56;
        }
    }
    if ( blc_blech_ctx->pc_38 == 38 ) {
        if ( !((blc_blech_ctx->blc_SettingsScreen_index
        == blc_ranger_SETTINGS_OFFSET)) ) {
            blc_blech_ctx->pc_38 = 40;
        } else if ( (blc_blech_ctx->blc_SettingsScreen_index
        == blc_ranger_SETTINGS_OFFSET) ) {
            blc_blech_ctx->pc_38 = 54;
        }
    }
    if ( blc_blech_ctx->pc_38 == 40 ) {
        if ( !((blc_blech_ctx->blc_SettingsScreen_index
        == blc_ranger_SETTINGS_BLE)) ) {
            blc_blech_ctx->pc_38 = 42;
        } else if ( (blc_blech_ctx->blc_SettingsScreen_index
        == blc_ranger_SETTINGS_BLE) ) {
            blc_blech_ctx->pc_38 = 52;
        }
    }
    if ( blc_blech_ctx->pc_38 == 42 ) {
        if ( !((blc_blech_ctx->blc_SettingsScreen_index
        == blc_ranger_SETTINGS_BRIGHTNESS)) ) {
            blc_blech_ctx->pc_38 = 44;
        } else if ( (blc_blech_ctx->blc_SettingsScreen_index
        == blc_ranger_SETTINGS_BRIGHTNESS) ) {
            blc_blech_ctx->pc_38 = 50;
        }
    }
    if ( blc_blech_ctx->pc_38 == 44 ) {
        
        blc_blech_ctx->pc_38 = 48;
    }
    if ( blc_blech_ctx->pc_38 == 46 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_24;
            blc_blech_aux_retcode_24 = blc_ranger_HelpSettingsScreen(&blc_blech_ctx->pc_38_blc_ranger_HelpSettingsScreen,
                                                                     blc_buttonStates);
            if ( (0 == blc_blech_aux_retcode_24) ) {
                blc_blech_ctx->pc_38 = 48;
            } else if ( !((0 == blc_blech_aux_retcode_24)) ) {
                blc_blech_ctx->pc_38 = 72;
            }
        }
    }
    if ( blc_blech_ctx->pc_38 == 48 ) {
        blc_blech_ctx->pc_38 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_38 == 50 ) {
        blc_blech_ctx->pc_38_blc_ranger_BrightnessSettingsScreen.pc_36 = 2;
        blc_int32 blc_blech_aux_retcode_28;
        blc_blech_aux_retcode_28 = blc_ranger_BrightnessSettingsScreen(&blc_blech_ctx->pc_38_blc_ranger_BrightnessSettingsScreen,
                                                                       blc_buttonStates,
                                                                       (&(*blc_settings).brightness));
        BLC_UNUSED(blc_blech_aux_retcode_28);
        blc_blech_ctx->pc_38 = 62;
    }
    if ( blc_blech_ctx->pc_38 == 52 ) {
        blc_blech_ctx->pc_38_blc_ranger_BLESettingsScreen.pc_35 = 2;
        blc_int32 blc_blech_aux_retcode_27;
        blc_blech_aux_retcode_27 = blc_ranger_BLESettingsScreen(&blc_blech_ctx->pc_38_blc_ranger_BLESettingsScreen,
                                                                blc_buttonStates,
                                                                (&(*blc_settings).bleEnabled));
        BLC_UNUSED(blc_blech_aux_retcode_27);
        blc_blech_ctx->pc_38 = 64;
    }
    if ( blc_blech_ctx->pc_38 == 54 ) {
        blc_blech_ctx->pc_38_blc_ranger_OffsetSettingsScreen.pc_34 = 2;
        blc_int32 blc_blech_aux_retcode_26;
        blc_blech_aux_retcode_26 = blc_ranger_OffsetSettingsScreen(&blc_blech_ctx->pc_38_blc_ranger_OffsetSettingsScreen,
                                                                   blc_buttonStates,
                                                                   (&(*blc_settings).measureFromBack));
        BLC_UNUSED(blc_blech_aux_retcode_26);
        blc_blech_ctx->pc_38 = 66;
    }
    if ( blc_blech_ctx->pc_38 == 56 ) {
        blc_blech_ctx->pc_38_blc_ranger_UnitSettingsScreen.pc_33 = 2;
        blc_int32 blc_blech_aux_retcode_25;
        blc_blech_aux_retcode_25 = blc_ranger_UnitSettingsScreen(&blc_blech_ctx->pc_38_blc_ranger_UnitSettingsScreen,
                                                                 blc_buttonStates,
                                                                 (&(*blc_settings).measureUnit));
        BLC_UNUSED(blc_blech_aux_retcode_25);
        blc_blech_ctx->pc_38 = 68;
    }
    if ( blc_blech_ctx->pc_39 == 58 ) {
        blc_blech_ctx->pc_39_blc_ranger_SettingsPersister.pc_6 = 2;
        blc_int32 blc_blech_aux_retcode_29;
        blc_blech_aux_retcode_29 = blc_ranger_SettingsPersister(&blc_blech_ctx->pc_39_blc_ranger_SettingsPersister,
                                                                blc_settings);
        BLC_UNUSED(blc_blech_aux_retcode_29);
        blc_blech_ctx->pc_39 = 60;
    }
    if ( blc_blech_ctx->pc_39 == 60 ) {
        blc_blech_ctx->pc_39 = 17; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_38 == 62 ) {
        blc_blech_ctx->pc_38 = 19; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_38 == 64 ) {
        blc_blech_ctx->pc_38 = 21; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_38 == 66 ) {
        blc_blech_ctx->pc_38 = 23; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_38 == 68 ) {
        blc_blech_ctx->pc_38 = 25; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_38 == 70 ) {
        blc_blech_ctx->pc_38_blc_ranger_HelpSettingsScreen.pc_32 = 2;
        blc_int32 blc_blech_aux_retcode_24;
        blc_blech_aux_retcode_24 = blc_ranger_HelpSettingsScreen(&blc_blech_ctx->pc_38_blc_ranger_HelpSettingsScreen,
                                                                 blc_buttonStates);
        BLC_UNUSED(blc_blech_aux_retcode_24);
        blc_blech_ctx->pc_38 = 72;
    }
    if ( blc_blech_ctx->pc_38 == 72 ) {
        blc_blech_ctx->pc_38 = 47; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_37 == 74 ) {
        blc_bool blc_blech_aux_termVar_23;
        if ( blc_blech_ctx->pc_38 == 0 ) {
            blc_blech_ctx->pc_38 = 0;
            blc_blech_ctx->pc_39 = 0;
            blc_blech_aux_termVar_23 = 1;
        } else {
            blc_blech_aux_termVar_23 = 0;
        }
        if ( !(blc_blech_aux_termVar_23) ) {
            blc_blech_ctx->pc_37 = 82;
        } else if ( blc_blech_aux_termVar_23 ) {
            blc_blech_ctx->pc_37 = 78;
        }
    }
    if ( blc_blech_ctx->pc_37 == 76 ) {
        blc_blech_ctx->blc_SettingsScreen_index = ((blc_blech_ctx->blc_SettingsScreen_index
        + 1) % 5);
        blc_blech_ctx->pc_37 = 78;
    }
    if ( blc_blech_ctx->pc_37 == 78 ) {
        if ( !((blc_blech_ctx->blc_SettingsScreen_110_press == 2)) ) {
            blc_blech_ctx->pc_37 = 4;
            goto loopHead;
        } else if ( (blc_blech_ctx->blc_SettingsScreen_110_press == 2) ) {
            blc_blech_ctx->pc_37 = 80;
        }
    }
    if ( blc_blech_ctx->pc_37 == 80 ) {
        blc_blech_ctx->pc_37 = 0;
        blc_blech_ctx->pc_38 = 0;
        blc_blech_ctx->pc_39 = 0; /* end */
    }
    if ( blc_blech_ctx->pc_37 == 82 ) {
        blc_blech_ctx->pc_37 = 31; /* proceed from surface to depth */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_37);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_38);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_39);
    return blc_blech_ctx->pc_37 ;
}

/**  Displays the home-screen and on button press the setting sub-screens. */
/**  While showing the home-screen or sub-screens the LCD will dim down after some time */
/**  to preserve battery. */
static blc_pc_t blc_ranger_HomeScreen (struct blc_ranger_HomeScreen *blc_blech_ctx,
                                       const struct blc_ranger_BatteryInfo *const blc_battery,
                                       blc_nat8 *blc_level,
                                       struct blc_ranger_Settings *blc_settings) {
    blc_bool blc_bleConnected = bleConnected;
    blc_nat8 blc_blech_prev_brightness = blc_blech_ctx->blc_HomeScreen_brightness;
    loopHead:
    if ( blc_blech_ctx->pc_40 == 2 ) {
        /* The extern declaration is outside the Blech code */
        blc_blech_ctx->blc_HomeScreen_prevBLEConnected = blc_bleConnected;
        memset((&blc_blech_ctx->blc_HomeScreen_prevBattery),
               0,
               sizeof(struct blc_ranger_BatteryInfo));
        blc_blech_ctx->blc_HomeScreen_prevBattery = (*blc_battery);
        memset((&blc_blech_ctx->blc_HomeScreen_buttonStates),
               0,
               sizeof(struct blc_ranger_ButtonStates));
        blc_blech_ctx->blc_HomeScreen_brightness = (*blc_settings).brightness;
        blc_blech_prev_brightness = blc_blech_ctx->blc_HomeScreen_brightness;
        blc_blech_ctx->pc_41 = 22;
        blc_blech_ctx->pc_44 = 20;
        blc_blech_ctx->pc_45 = 4;
        blc_blech_ctx->pc_40 = 62;
    }
    if ( blc_blech_ctx->pc_45 == 4 ) {
        blc_blech_ctx->pc_45 = 40;
    }
    if ( blc_blech_ctx->pc_43 == 6 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_43 = 10;
        }
    }
    if ( blc_blech_ctx->pc_44 == 8 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_34;
            blc_blech_aux_retcode_34 = blc_ranger_Dimmer(&blc_blech_ctx->pc_44_blc_ranger_Dimmer,
                                                         blc_blech_prev_brightness,
                                                         (&blc_blech_ctx->blc_HomeScreen_buttonStates),
                                                         blc_level);
            if ( !((0 == blc_blech_aux_retcode_34)) ) {
                blc_blech_ctx->pc_44 = 56;
            } else if ( (0 == blc_blech_aux_retcode_34) ) {
                blc_blech_ctx->pc_44 = 48;
            }
        }
    }
    if ( blc_blech_ctx->pc_43 == 10 ) {
        blc_int32 blc_blech_aux_retcode_32;
        blc_blech_aux_retcode_32 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_43_blc_ranger_PressRecognizer,
                                                              (&blc_blech_ctx->blc_HomeScreen_buttonStates),
                                                              (&blc_blech_ctx->blc_HomeScreen_122_123_pressType));
        if ( !((0 == blc_blech_aux_retcode_32)) ) {
            blc_blech_ctx->pc_43 = 26;
        } else if ( (0 == blc_blech_aux_retcode_32) ) {
            blc_blech_ctx->pc_43 = 12;
        }
    }
    if ( blc_blech_ctx->pc_43 == 12 ) {
        blc_blech_ctx->pc_43 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_41 == 14 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_41 = 30;
        }
    }
    if ( blc_blech_ctx->pc_42 == 16 ) {
        if ( (!((blc_bleConnected
        == blc_blech_ctx->blc_HomeScreen_prevBLEConnected))
        || blc_ranger_chargeChanged(blc_battery,
                                    (&blc_blech_ctx->blc_HomeScreen_prevBattery))) ) {
            blc_blech_ctx->blc_HomeScreen_prevBLEConnected = blc_bleConnected;
            blc_blech_ctx->blc_HomeScreen_prevBattery = (*blc_battery);
            if ( 1 ) {
                blc_blech_ctx->pc_42 = 28;
                goto loopHead;
            } else if ( 0 ) {
                blc_blech_ctx->pc_42 = 18;
            }
        }
    }
    if ( blc_blech_ctx->pc_42 == 18 ) {
        blc_blech_ctx->pc_42 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_44 == 20 ) {
        blc_blech_ctx->pc_44_blc_ranger_Dimmer.pc_13 = 2;
        blc_blech_ctx->pc_44_blc_ranger_Dimmer.pc_14 = 0;
        blc_blech_ctx->pc_44_blc_ranger_Dimmer.pc_15 = 0;
        blc_int32 blc_blech_aux_retcode_34;
        blc_blech_aux_retcode_34 = blc_ranger_Dimmer(&blc_blech_ctx->pc_44_blc_ranger_Dimmer,
                                                     blc_blech_prev_brightness,
                                                     (&blc_blech_ctx->blc_HomeScreen_buttonStates),
                                                     blc_level);
        BLC_UNUSED(blc_blech_aux_retcode_34);
        blc_blech_ctx->pc_44 = 56;
    }
    if ( blc_blech_ctx->pc_41 == 22 ) {
        blc_blech_ctx->blc_HomeScreen_122_123_pressType = 0;
        blc_blech_ctx->pc_42 = 28;
        blc_blech_ctx->pc_43 = 24;
        blc_blech_ctx->pc_41 = 30;
    }
    if ( blc_blech_ctx->pc_43 == 24 ) {
        blc_blech_ctx->pc_43_blc_ranger_PressRecognizer.pc_8 = 2;
        blc_blech_ctx->pc_43_blc_ranger_PressRecognizer.pc_9 = 0;
        blc_blech_ctx->pc_43_blc_ranger_PressRecognizer.pc_10 = 0;
        blc_int32 blc_blech_aux_retcode_32;
        blc_blech_aux_retcode_32 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_43_blc_ranger_PressRecognizer,
                                                              (&blc_blech_ctx->blc_HomeScreen_buttonStates),
                                                              (&blc_blech_ctx->blc_HomeScreen_122_123_pressType));
        BLC_UNUSED(blc_blech_aux_retcode_32);
        blc_blech_ctx->pc_43 = 26;
    }
    if ( blc_blech_ctx->pc_43 == 26 ) {
        blc_blech_ctx->pc_43 = 7; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_42 == 28 ) {
        blc_ranger_displayHomeScreen(blc_battery, (*blc_settings).bleEnabled);
        blc_blech_ctx->pc_42 = 17; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_41 == 30 ) {
        blc_bool blc_blech_aux_termVar_31;
        if ( blc_blech_ctx->pc_43 == 0 ) {
            blc_blech_ctx->pc_42 = 0;
            blc_blech_ctx->pc_43 = 0;
            blc_blech_aux_termVar_31 = 1;
        } else {
            blc_blech_aux_termVar_31 = 0;
        }
        if ( blc_blech_aux_termVar_31 ) {
            blc_blech_ctx->pc_41 = 32;
        } else if ( !(blc_blech_aux_termVar_31) ) {
            blc_blech_ctx->pc_41 = 60;
        }
    }
    if ( blc_blech_ctx->pc_41 == 32 ) {
        if ( !((blc_blech_ctx->blc_HomeScreen_122_123_pressType == 3)) ) {
            blc_blech_ctx->pc_41 = 50;
        } else if ( (blc_blech_ctx->blc_HomeScreen_122_123_pressType == 3) ) {
            blc_blech_ctx->pc_41 = 34;
        }
    }
    if ( blc_blech_ctx->pc_41 == 34 ) {
        blc_blech_ctx->pc_41_blc_ranger_SettingsScreen.pc_37 = 2;
        blc_blech_ctx->pc_41_blc_ranger_SettingsScreen.pc_38 = 0;
        blc_blech_ctx->pc_41_blc_ranger_SettingsScreen.pc_39 = 0;
        blc_int32 blc_blech_aux_retcode_33;
        blc_blech_aux_retcode_33 = blc_ranger_SettingsScreen(&blc_blech_ctx->pc_41_blc_ranger_SettingsScreen,
                                                             (&blc_blech_ctx->blc_HomeScreen_buttonStates),
                                                             blc_settings);
        BLC_UNUSED(blc_blech_aux_retcode_33);
        blc_blech_ctx->pc_41 = 58;
    }
    if ( blc_blech_ctx->pc_41 == 36 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_41 = 38;
        }
    }
    if ( blc_blech_ctx->pc_41 == 38 ) {
        blc_int32 blc_blech_aux_retcode_33;
        blc_blech_aux_retcode_33 = blc_ranger_SettingsScreen(&blc_blech_ctx->pc_41_blc_ranger_SettingsScreen,
                                                             (&blc_blech_ctx->blc_HomeScreen_buttonStates),
                                                             blc_settings);
        if ( (0 == blc_blech_aux_retcode_33) ) {
            blc_blech_ctx->pc_41 = 52;
        } else if ( !((0 == blc_blech_aux_retcode_33)) ) {
            blc_blech_ctx->pc_41 = 58;
        }
    }
    if ( blc_blech_ctx->pc_45 == 40 ) {
        blc_blech_ctx->blc_HomeScreen_brightness = (*blc_settings).brightness;
        blc_blech_ctx->pc_45 = 43; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_45 == 42 ) {
        if ( 1 ) {
            if ( 1 ) {
                blc_blech_ctx->pc_45 = 4;
                goto loopHead;
            } else if ( 0 ) {
                blc_blech_ctx->pc_45 = 44;
            }
        }
    }
    if ( blc_blech_ctx->pc_45 == 44 ) {
        blc_blech_ctx->pc_45 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_40 == 46 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_40 = 62;
        }
    }
    if ( blc_blech_ctx->pc_44 == 48 ) {
        blc_blech_ctx->pc_44 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_41 == 50 ) {
        
        blc_blech_ctx->pc_41 = 52;
    }
    if ( blc_blech_ctx->pc_41 == 52 ) {
        if ( !((blc_blech_ctx->blc_HomeScreen_122_123_pressType == 1)) ) {
            blc_blech_ctx->pc_41 = 22;
            goto loopHead;
        } else if ( (blc_blech_ctx->blc_HomeScreen_122_123_pressType == 1) ) {
            blc_blech_ctx->pc_41 = 54;
        }
    }
    if ( blc_blech_ctx->pc_41 == 54 ) {
        blc_blech_ctx->pc_41 = 0;
        blc_blech_ctx->pc_42 = 0;
        blc_blech_ctx->pc_43 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_44 == 56 ) {
        blc_blech_ctx->pc_44 = 9; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_41 == 58 ) {
        blc_blech_ctx->pc_41 = 37; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_41 == 60 ) {
        blc_blech_ctx->pc_41 = 15; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_40 == 62 ) {
        blc_bool blc_blech_aux_termVar_30;
        if ( blc_blech_ctx->pc_41 == 0 ) {
            blc_blech_ctx->pc_41 = 0;
            blc_blech_ctx->pc_42 = 0;
            blc_blech_ctx->pc_43 = 0;
            blc_blech_ctx->pc_44 = 0;
            blc_blech_ctx->pc_45 = 0;
            blc_blech_aux_termVar_30 = 1;
        } else {
            blc_blech_aux_termVar_30 = 0;
        }
        if ( !(blc_blech_aux_termVar_30) ) {
            blc_blech_ctx->pc_40 = 64;
        } else if ( blc_blech_aux_termVar_30 ) {
            blc_blech_ctx->pc_40 = 66;
        }
    }
    if ( blc_blech_ctx->pc_40 == 64 ) {
        blc_blech_ctx->pc_40 = 47; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_40 == 66 ) {
        blc_blech_ctx->pc_40 = 0;
        blc_blech_ctx->pc_41 = 0;
        blc_blech_ctx->pc_42 = 0;
        blc_blech_ctx->pc_43 = 0;
        blc_blech_ctx->pc_44 = 0;
        blc_blech_ctx->pc_45 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_40);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_41);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_42);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_43);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_44);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_45);
    return blc_blech_ctx->pc_40 ;
}

/**  The screen to show while doing measurement. */
static blc_pc_t blc_ranger_RangingScreen (struct blc_ranger_RangingScreen *blc_blech_ctx,
                                          const blc_nat16 blc_range,
                                          const struct blc_ranger_BatteryInfo *const blc_battery,
                                          const blc_nat8 blc_orientation,
                                          const struct blc_ranger_Settings *const blc_settings) {
    struct blc_ranger_ButtonStates blc_buttonStates = buttonStates;
    loopHead:
    if ( blc_blech_ctx->pc_46 == 2 ) {
        /* The extern declaration is outside the Blech code */
        blc_blech_ctx->pc_47 = 14;
        blc_blech_ctx->pc_48 = 4;
        blc_blech_ctx->pc_46 = 16;
    }
    if ( blc_blech_ctx->pc_48 == 4 ) {
        blc_blech_ctx->pc_48 = 7; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_48 == 6 ) {
        if ( blc_buttonStates.aPressed ) {
            blc_blech_ctx->pc_48 = 0; /* term */
        }
    }
    if ( blc_blech_ctx->pc_46 == 8 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_46 = 16;
        }
    }
    if ( blc_blech_ctx->pc_47 == 10 ) {
        if ( 1 ) {
            if ( 1 ) {
                blc_blech_ctx->pc_47 = 14;
                goto loopHead;
            } else if ( 0 ) {
                blc_blech_ctx->pc_47 = 12;
            }
        }
    }
    if ( blc_blech_ctx->pc_47 == 12 ) {
        blc_blech_ctx->pc_47 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_47 == 14 ) {
        blc_ranger_displayRangingScreen(blc_range,
                                        blc_battery,
                                        blc_orientation,
                                        blc_settings);
        blc_blech_ctx->pc_47 = 11; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_46 == 16 ) {
        blc_bool blc_blech_aux_termVar_35;
        if ( blc_blech_ctx->pc_48 == 0 ) {
            blc_blech_ctx->pc_47 = 0;
            blc_blech_ctx->pc_48 = 0;
            blc_blech_aux_termVar_35 = 1;
        } else {
            blc_blech_aux_termVar_35 = 0;
        }
        if ( !(blc_blech_aux_termVar_35) ) {
            blc_blech_ctx->pc_46 = 18;
        } else if ( blc_blech_aux_termVar_35 ) {
            blc_blech_ctx->pc_46 = 20;
        }
    }
    if ( blc_blech_ctx->pc_46 == 18 ) {
        blc_blech_ctx->pc_46 = 9; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_46 == 20 ) {
        blc_blech_ctx->pc_46 = 0;
        blc_blech_ctx->pc_47 = 0;
        blc_blech_ctx->pc_48 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_46);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_47);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_48);
    return blc_blech_ctx->pc_46 ;
}

/**  Displays any setup error and allows to restart via button press. */
static blc_pc_t blc_ranger_ErrorScreen (struct blc_ranger_ErrorScreen *blc_blech_ctx,
                                        const blc_nat8 blc_err) {
    struct blc_ranger_ButtonStates blc_buttonStates = buttonStates;
    if ( blc_blech_ctx->pc_49 == 2 ) {
        blc_ranger_displayErrorScreen(blc_err);
        /* The extern declaration is outside the Blech code */
        blc_blech_ctx->pc_49_blc_ranger_PressRecognizer.pc_8 = 2;
        blc_blech_ctx->pc_49_blc_ranger_PressRecognizer.pc_9 = 0;
        blc_blech_ctx->pc_49_blc_ranger_PressRecognizer.pc_10 = 0;
        blc_int32 blc_blech_aux_retcode_36;
        blc_nat8 blc_blech_aux_receiverVar_159;
        blc_blech_aux_retcode_36 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_49_blc_ranger_PressRecognizer,
                                                              (&blc_buttonStates),
                                                              (&blc_blech_aux_receiverVar_159));
        BLC_UNUSED(blc_blech_aux_retcode_36);
        blc_blech_ctx->pc_49 = 6;
    }
    if ( blc_blech_ctx->pc_49 == 4 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_36;
            blc_nat8 blc_blech_aux_receiverVar_161;
            blc_blech_aux_retcode_36 = blc_ranger_PressRecognizer(&blc_blech_ctx->pc_49_blc_ranger_PressRecognizer,
                                                                  (&blc_buttonStates),
                                                                  (&blc_blech_aux_receiverVar_161));
            if ( (0 == blc_blech_aux_retcode_36) ) {
                blc_blech_ctx->pc_49 = 8;
            } else if ( !((0 == blc_blech_aux_retcode_36)) ) {
                blc_blech_ctx->pc_49 = 6;
            }
        }
    }
    if ( blc_blech_ctx->pc_49 == 6 ) {
        blc_blech_ctx->pc_49 = 5; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_49 == 8 ) {
        blc_ranger_requestRestart();
        blc_blech_ctx->pc_49 = 11; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_49 == 10 ) {
        if ( 0 ) {
            blc_blech_ctx->pc_49 = 0; /* end */
        }
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_49);
    return blc_blech_ctx->pc_49 ;
}

/**  Manages the user input via buttons and the output via the LCD. */
static blc_pc_t blc_ranger_UI (struct blc_ranger_UI *blc_blech_ctx,
                               const blc_nat8 blc_setupErr,
                               const blc_nat16 blc_range,
                               const struct blc_ranger_BatteryInfo *const blc_battery,
                               blc_bool *blc_rangingRequest,
                               blc_nat8 *blc_brightness,
                               struct blc_ranger_Settings *blc_settings) {
    loopHead:
    if ( blc_blech_ctx->pc_50 == 2 ) {
        blc_blech_ctx->blc_UI_screenBrightness = (*blc_settings).brightness;
        blc_blech_ctx->blc_UI_dialogBrightness = (*blc_settings).brightness;
        memset((&blc_blech_ctx->blc_UI_bleDialogRequest),
               0,
               sizeof(struct blc_ranger_DialogRequest));
        memset((&blc_blech_ctx->blc_UI_usbDialogRequest),
               0,
               sizeof(struct blc_ranger_DialogRequest));
        memset((&blc_blech_ctx->blc_UI_batteryDialogRequest),
               0,
               sizeof(struct blc_ranger_DialogRequest));
        blc_blech_ctx->blc_UI_orientation = 0;
        blc_blech_ctx->pc_51 = 78;
        blc_blech_ctx->pc_52 = 62;
        blc_blech_ctx->pc_53 = 60;
        blc_blech_ctx->pc_54 = 58;
        blc_blech_ctx->pc_55 = 64;
        blc_blech_ctx->pc_56 = 66;
        blc_blech_ctx->pc_57 = 4;
        blc_blech_ctx->pc_50 = 94;
    }
    if ( blc_blech_ctx->pc_57 == 4 ) {
        blc_blech_ctx->pc_57_blc_ranger_RotationController.pc_17 = 2;
        blc_int32 blc_blech_aux_retcode_47;
        blc_blech_aux_retcode_47 = blc_ranger_RotationController(&blc_blech_ctx->pc_57_blc_ranger_RotationController,
                                                                 (&blc_blech_ctx->blc_UI_orientation));
        BLC_UNUSED(blc_blech_aux_retcode_47);
        blc_blech_ctx->pc_57 = 8;
    }
    if ( blc_blech_ctx->pc_57 == 6 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_47;
            blc_blech_aux_retcode_47 = blc_ranger_RotationController(&blc_blech_ctx->pc_57_blc_ranger_RotationController,
                                                                     (&blc_blech_ctx->blc_UI_orientation));
            if ( !((0 == blc_blech_aux_retcode_47)) ) {
                blc_blech_ctx->pc_57 = 8;
            } else if ( (0 == blc_blech_aux_retcode_47) ) {
                blc_blech_ctx->pc_57 = 10;
            }
        }
    }
    if ( blc_blech_ctx->pc_57 == 8 ) {
        blc_blech_ctx->pc_57 = 7; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_57 == 10 ) {
        blc_blech_ctx->pc_57 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_50 == 12 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_50 = 94;
        }
    }
    if ( blc_blech_ctx->pc_56 == 14 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_56 = 42;
        }
    }
    if ( blc_blech_ctx->pc_55 == 16 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_55 = 40;
        }
    }
    if ( blc_blech_ctx->pc_54 == 18 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_44;
            blc_blech_aux_retcode_44 = blc_ranger_BatteryDialog(&blc_blech_ctx->pc_54_blc_ranger_BatteryDialog,
                                                                blc_battery,
                                                                (&blc_blech_ctx->blc_UI_batteryDialogRequest));
            if ( !((0 == blc_blech_aux_retcode_44)) ) {
                blc_blech_ctx->pc_54 = 72;
            } else if ( (0 == blc_blech_aux_retcode_44) ) {
                blc_blech_ctx->pc_54 = 48;
            }
        }
    }
    if ( blc_blech_ctx->pc_53 == 20 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_43;
            blc_blech_aux_retcode_43 = blc_ranger_USBDialog(&blc_blech_ctx->pc_53_blc_ranger_USBDialog,
                                                            blc_battery,
                                                            (&blc_blech_ctx->blc_UI_usbDialogRequest));
            if ( !((0 == blc_blech_aux_retcode_43)) ) {
                blc_blech_ctx->pc_53 = 74;
            } else if ( (0 == blc_blech_aux_retcode_43) ) {
                blc_blech_ctx->pc_53 = 50;
            }
        }
    }
    if ( blc_blech_ctx->pc_52 == 22 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_52 = 38;
        }
    }
    if ( blc_blech_ctx->pc_51 == 24 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_38;
            blc_blech_aux_retcode_38 = blc_ranger_WelcomeScreen(&blc_blech_ctx->pc_51_blc_ranger_WelcomeScreen);
            if ( (0 == blc_blech_aux_retcode_38) ) {
                blc_blech_ctx->pc_51 = 26;
            } else if ( !((0 == blc_blech_aux_retcode_38)) ) {
                blc_blech_ctx->pc_51 = 80;
            }
        }
    }
    if ( blc_blech_ctx->pc_51 == 26 ) {
        if ( (blc_setupErr == 0) ) {
            blc_blech_ctx->pc_51 = 28;
        } else if ( !((blc_setupErr == 0)) ) {
            blc_blech_ctx->pc_51 = 90;
        }
    }
    if ( blc_blech_ctx->pc_51 == 28 ) {
        blc_blech_ctx->pc_51_blc_ranger_HomeScreen.pc_40 = 2;
        blc_blech_ctx->pc_51_blc_ranger_HomeScreen.pc_41 = 0;
        blc_blech_ctx->pc_51_blc_ranger_HomeScreen.pc_42 = 0;
        blc_blech_ctx->pc_51_blc_ranger_HomeScreen.pc_43 = 0;
        blc_blech_ctx->pc_51_blc_ranger_HomeScreen.pc_44 = 0;
        blc_blech_ctx->pc_51_blc_ranger_HomeScreen.pc_45 = 0;
        blc_int32 blc_blech_aux_retcode_40;
        blc_blech_aux_retcode_40 = blc_ranger_HomeScreen(&blc_blech_ctx->pc_51_blc_ranger_HomeScreen,
                                                         blc_battery,
                                                         (&blc_blech_ctx->blc_UI_screenBrightness),
                                                         blc_settings);
        BLC_UNUSED(blc_blech_aux_retcode_40);
        blc_blech_ctx->pc_51 = 82;
    }
    if ( blc_blech_ctx->pc_51 == 30 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_40;
            blc_blech_aux_retcode_40 = blc_ranger_HomeScreen(&blc_blech_ctx->pc_51_blc_ranger_HomeScreen,
                                                             blc_battery,
                                                             (&blc_blech_ctx->blc_UI_screenBrightness),
                                                             blc_settings);
            if ( (0 == blc_blech_aux_retcode_40) ) {
                blc_blech_ctx->pc_51 = 84;
            } else if ( !((0 == blc_blech_aux_retcode_40)) ) {
                blc_blech_ctx->pc_51 = 82;
            }
        }
    }
    if ( blc_blech_ctx->pc_51 == 32 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_51 = 34;
        }
    }
    if ( blc_blech_ctx->pc_51 == 34 ) {
        blc_int32 blc_blech_aux_retcode_41;
        blc_blech_aux_retcode_41 = blc_ranger_RangingScreen(&blc_blech_ctx->pc_51_blc_ranger_RangingScreen,
                                                            blc_range,
                                                            blc_battery,
                                                            blc_blech_ctx->blc_UI_orientation,
                                                            blc_settings);
        if ( (0 == blc_blech_aux_retcode_41) ) {
            blc_blech_ctx->pc_51 = 36;
        } else if ( !((0 == blc_blech_aux_retcode_41)) ) {
            blc_blech_ctx->pc_51 = 88;
        }
    }
    if ( blc_blech_ctx->pc_51 == 36 ) {
        (*blc_rangingRequest) = 0;
        if ( 0 ) {
            blc_blech_ctx->pc_51 = 56;
        } else if ( 1 ) {
            blc_blech_ctx->pc_51 = 28;
            goto loopHead;
        }
    }
    if ( blc_blech_ctx->pc_52 == 38 ) {
        blc_int32 blc_blech_aux_retcode_42;
        blc_blech_aux_retcode_42 = blc_ranger_BLEDialog(&blc_blech_ctx->pc_52_blc_ranger_BLEDialog,
                                                        (*blc_settings).bleEnabled,
                                                        (&blc_blech_ctx->blc_UI_bleDialogRequest));
        if ( !((0 == blc_blech_aux_retcode_42)) ) {
            blc_blech_ctx->pc_52 = 76;
        } else if ( (0 == blc_blech_aux_retcode_42) ) {
            blc_blech_ctx->pc_52 = 52;
        }
    }
    if ( blc_blech_ctx->pc_55 == 40 ) {
        blc_int32 blc_blech_aux_retcode_45;
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_172[3];
        memset(blc_blech_aux_tmpLiteral_172,
               0,
               3 * sizeof(struct blc_ranger_DialogRequest));
        blc_blech_aux_tmpLiteral_172[0] = blc_blech_ctx->blc_UI_bleDialogRequest;
        blc_blech_aux_tmpLiteral_172[1] = blc_blech_ctx->blc_UI_usbDialogRequest;
        blc_blech_aux_tmpLiteral_172[2] = blc_blech_ctx->blc_UI_batteryDialogRequest;
        blc_blech_aux_retcode_45 = blc_ranger_DialogManager(&blc_blech_ctx->pc_55_blc_ranger_DialogManager,
                                                            blc_blech_aux_tmpLiteral_172,
                                                            (*blc_settings).brightness,
                                                            (&blc_blech_ctx->blc_UI_dialogBrightness));
        if ( !((0 == blc_blech_aux_retcode_45)) ) {
            blc_blech_ctx->pc_55 = 70;
        } else if ( (0 == blc_blech_aux_retcode_45) ) {
            blc_blech_ctx->pc_55 = 46;
        }
    }
    if ( blc_blech_ctx->pc_56 == 42 ) {
        blc_int32 blc_blech_aux_retcode_46;
        blc_nat8 blc_blech_aux_tmpLiteral_174[2];
        memset(blc_blech_aux_tmpLiteral_174, 0, 2 * sizeof(blc_nat8));
        blc_blech_aux_tmpLiteral_174[0] = blc_blech_ctx->blc_UI_screenBrightness;
        blc_blech_aux_tmpLiteral_174[1] = blc_blech_ctx->blc_UI_dialogBrightness;
        blc_blech_aux_retcode_46 = blc_ranger_BrightnessController(&blc_blech_ctx->pc_56_blc_ranger_BrightnessController,
                                                                   blc_blech_aux_tmpLiteral_174,
                                                                   blc_brightness);
        if ( !((0 == blc_blech_aux_retcode_46)) ) {
            blc_blech_ctx->pc_56 = 68;
        } else if ( (0 == blc_blech_aux_retcode_46) ) {
            blc_blech_ctx->pc_56 = 44;
        }
    }
    if ( blc_blech_ctx->pc_56 == 44 ) {
        blc_blech_ctx->pc_56 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_55 == 46 ) {
        blc_blech_ctx->pc_55 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_54 == 48 ) {
        blc_blech_ctx->pc_54 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_53 == 50 ) {
        blc_blech_ctx->pc_53 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_52 == 52 ) {
        blc_blech_ctx->pc_52 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_51 == 54 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_39;
            blc_blech_aux_retcode_39 = blc_ranger_ErrorScreen(&blc_blech_ctx->pc_51_blc_ranger_ErrorScreen,
                                                              blc_setupErr);
            if ( (0 == blc_blech_aux_retcode_39) ) {
                blc_blech_ctx->pc_51 = 56;
            } else if ( !((0 == blc_blech_aux_retcode_39)) ) {
                blc_blech_ctx->pc_51 = 92;
            }
        }
    }
    if ( blc_blech_ctx->pc_51 == 56 ) {
        blc_blech_ctx->pc_51 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_54 == 58 ) {
        blc_blech_ctx->pc_54_blc_ranger_BatteryDialog.pc_25 = 2;
        blc_int32 blc_blech_aux_retcode_44;
        blc_blech_aux_retcode_44 = blc_ranger_BatteryDialog(&blc_blech_ctx->pc_54_blc_ranger_BatteryDialog,
                                                            blc_battery,
                                                            (&blc_blech_ctx->blc_UI_batteryDialogRequest));
        BLC_UNUSED(blc_blech_aux_retcode_44);
        blc_blech_ctx->pc_54 = 72;
    }
    if ( blc_blech_ctx->pc_53 == 60 ) {
        blc_blech_ctx->pc_53_blc_ranger_USBDialog.pc_30 = 2;
        blc_int32 blc_blech_aux_retcode_43;
        blc_blech_aux_retcode_43 = blc_ranger_USBDialog(&blc_blech_ctx->pc_53_blc_ranger_USBDialog,
                                                        blc_battery,
                                                        (&blc_blech_ctx->blc_UI_usbDialogRequest));
        BLC_UNUSED(blc_blech_aux_retcode_43);
        blc_blech_ctx->pc_53 = 74;
    }
    if ( blc_blech_ctx->pc_52 == 62 ) {
        blc_blech_ctx->pc_52_blc_ranger_BLEDialog.pc_26 = 2;
        blc_blech_ctx->pc_52_blc_ranger_BLEDialog.pc_27 = 0;
        blc_blech_ctx->pc_52_blc_ranger_BLEDialog.pc_28 = 0;
        blc_blech_ctx->pc_52_blc_ranger_BLEDialog.pc_29 = 0;
        blc_int32 blc_blech_aux_retcode_42;
        blc_blech_aux_retcode_42 = blc_ranger_BLEDialog(&blc_blech_ctx->pc_52_blc_ranger_BLEDialog,
                                                        (*blc_settings).bleEnabled,
                                                        (&blc_blech_ctx->blc_UI_bleDialogRequest));
        BLC_UNUSED(blc_blech_aux_retcode_42);
        blc_blech_ctx->pc_52 = 76;
    }
    if ( blc_blech_ctx->pc_55 == 64 ) {
        blc_blech_ctx->pc_55_blc_ranger_DialogManager.pc_20 = 2;
        blc_blech_ctx->pc_55_blc_ranger_DialogManager.pc_21 = 0;
        blc_blech_ctx->pc_55_blc_ranger_DialogManager.pc_22 = 0;
        blc_blech_ctx->pc_55_blc_ranger_DialogManager.pc_23 = 0;
        blc_blech_ctx->pc_55_blc_ranger_DialogManager.pc_24 = 0;
        blc_int32 blc_blech_aux_retcode_45;
        struct blc_ranger_DialogRequest blc_blech_aux_tmpLiteral_179[3];
        memset(blc_blech_aux_tmpLiteral_179,
               0,
               3 * sizeof(struct blc_ranger_DialogRequest));
        blc_blech_aux_tmpLiteral_179[0] = blc_blech_ctx->blc_UI_bleDialogRequest;
        blc_blech_aux_tmpLiteral_179[1] = blc_blech_ctx->blc_UI_usbDialogRequest;
        blc_blech_aux_tmpLiteral_179[2] = blc_blech_ctx->blc_UI_batteryDialogRequest;
        blc_blech_aux_retcode_45 = blc_ranger_DialogManager(&blc_blech_ctx->pc_55_blc_ranger_DialogManager,
                                                            blc_blech_aux_tmpLiteral_179,
                                                            (*blc_settings).brightness,
                                                            (&blc_blech_ctx->blc_UI_dialogBrightness));
        BLC_UNUSED(blc_blech_aux_retcode_45);
        blc_blech_ctx->pc_55 = 70;
    }
    if ( blc_blech_ctx->pc_56 == 66 ) {
        blc_blech_ctx->pc_56_blc_ranger_BrightnessController.pc_16 = 2;
        blc_int32 blc_blech_aux_retcode_46;
        blc_nat8 blc_blech_aux_tmpLiteral_181[2];
        memset(blc_blech_aux_tmpLiteral_181, 0, 2 * sizeof(blc_nat8));
        blc_blech_aux_tmpLiteral_181[0] = blc_blech_ctx->blc_UI_screenBrightness;
        blc_blech_aux_tmpLiteral_181[1] = blc_blech_ctx->blc_UI_dialogBrightness;
        blc_blech_aux_retcode_46 = blc_ranger_BrightnessController(&blc_blech_ctx->pc_56_blc_ranger_BrightnessController,
                                                                   blc_blech_aux_tmpLiteral_181,
                                                                   blc_brightness);
        BLC_UNUSED(blc_blech_aux_retcode_46);
        blc_blech_ctx->pc_56 = 68;
    }
    if ( blc_blech_ctx->pc_56 == 68 ) {
        blc_blech_ctx->pc_56 = 15; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_55 == 70 ) {
        blc_blech_ctx->pc_55 = 17; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_54 == 72 ) {
        blc_blech_ctx->pc_54 = 19; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_53 == 74 ) {
        blc_blech_ctx->pc_53 = 21; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_52 == 76 ) {
        blc_blech_ctx->pc_52 = 23; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_51 == 78 ) {
        blc_blech_ctx->pc_51_blc_ranger_WelcomeScreen.pc_31 = 2;
        blc_int32 blc_blech_aux_retcode_38;
        blc_blech_aux_retcode_38 = blc_ranger_WelcomeScreen(&blc_blech_ctx->pc_51_blc_ranger_WelcomeScreen);
        BLC_UNUSED(blc_blech_aux_retcode_38);
        blc_blech_ctx->pc_51 = 80;
    }
    if ( blc_blech_ctx->pc_51 == 80 ) {
        blc_blech_ctx->pc_51 = 25; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_51 == 82 ) {
        blc_blech_ctx->pc_51 = 31; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_51 == 84 ) {
        (*blc_rangingRequest) = 1;
        blc_blech_ctx->pc_51 = 86;
    }
    if ( blc_blech_ctx->pc_51 == 86 ) {
        blc_blech_ctx->pc_51_blc_ranger_RangingScreen.pc_46 = 2;
        blc_blech_ctx->pc_51_blc_ranger_RangingScreen.pc_47 = 0;
        blc_blech_ctx->pc_51_blc_ranger_RangingScreen.pc_48 = 0;
        blc_int32 blc_blech_aux_retcode_41;
        blc_blech_aux_retcode_41 = blc_ranger_RangingScreen(&blc_blech_ctx->pc_51_blc_ranger_RangingScreen,
                                                            blc_range,
                                                            blc_battery,
                                                            blc_blech_ctx->blc_UI_orientation,
                                                            blc_settings);
        BLC_UNUSED(blc_blech_aux_retcode_41);
        blc_blech_ctx->pc_51 = 88;
    }
    if ( blc_blech_ctx->pc_51 == 88 ) {
        blc_blech_ctx->pc_51 = 33; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_51 == 90 ) {
        blc_blech_ctx->pc_51_blc_ranger_ErrorScreen.pc_49 = 2;
        blc_int32 blc_blech_aux_retcode_39;
        blc_blech_aux_retcode_39 = blc_ranger_ErrorScreen(&blc_blech_ctx->pc_51_blc_ranger_ErrorScreen,
                                                          blc_setupErr);
        BLC_UNUSED(blc_blech_aux_retcode_39);
        blc_blech_ctx->pc_51 = 92;
    }
    if ( blc_blech_ctx->pc_51 == 92 ) {
        blc_blech_ctx->pc_51 = 55; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_50 == 94 ) {
        blc_bool blc_blech_aux_termVar_37;
        if ( blc_blech_ctx->pc_51 == 0 && blc_blech_ctx->pc_52 == 0 && blc_blech_ctx->pc_53 == 0 && blc_blech_ctx->pc_54 == 0 && blc_blech_ctx->pc_55 == 0 && blc_blech_ctx->pc_56 == 0 && blc_blech_ctx->pc_57 == 0 ) {
            blc_blech_ctx->pc_51 = 0;
            blc_blech_ctx->pc_52 = 0;
            blc_blech_ctx->pc_53 = 0;
            blc_blech_ctx->pc_54 = 0;
            blc_blech_ctx->pc_55 = 0;
            blc_blech_ctx->pc_56 = 0;
            blc_blech_ctx->pc_57 = 0;
            blc_blech_aux_termVar_37 = 1;
        } else {
            blc_blech_aux_termVar_37 = 0;
        }
        if ( !(blc_blech_aux_termVar_37) ) {
            blc_blech_ctx->pc_50 = 96;
        } else if ( blc_blech_aux_termVar_37 ) {
            blc_blech_ctx->pc_50 = 98;
        }
    }
    if ( blc_blech_ctx->pc_50 == 96 ) {
        blc_blech_ctx->pc_50 = 13; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_50 == 98 ) {
        blc_blech_ctx->pc_50 = 0;
        blc_blech_ctx->pc_51 = 0;
        blc_blech_ctx->pc_52 = 0;
        blc_blech_ctx->pc_53 = 0;
        blc_blech_ctx->pc_54 = 0;
        blc_blech_ctx->pc_55 = 0;
        blc_blech_ctx->pc_56 = 0;
        blc_blech_ctx->pc_57 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_50);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_51);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_52);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_53);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_54);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_55);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_56);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_57);
    return blc_blech_ctx->pc_50 ;
}

/**  Measures the range either from top or back of the stick if requested. */
static blc_pc_t blc_ranger_RangeSensor (struct blc_ranger_RangeSensor *blc_blech_ctx,
                                        const blc_bool blc_rangingRequested,
                                        const blc_bool blc_measureFromBack,
                                        blc_nat16 *blc_range) {
    loopHead:
    if ( blc_blech_ctx->pc_58 == 2 ) {
        if ( blc_rangingRequested ) {
            blc_blech_ctx->pc_58 = 4;
        } else if ( !(blc_rangingRequested) ) {
            blc_blech_ctx->pc_58 = 24;
        }
    }
    if ( blc_blech_ctx->pc_58 == 4 ) {
        
        blc_blech_ctx->pc_58 = 8;
    }
    if ( blc_blech_ctx->pc_58 == 6 ) {
        if ( blc_rangingRequested ) {
            blc_blech_ctx->pc_58 = 8;
        }
    }
    if ( blc_blech_ctx->pc_58 == 8 ) {
        blc_ranger_startRanging();
        blc_blech_ctx->pc_58 = 10;
    }
    if ( blc_blech_ctx->pc_58 == 10 ) {
        (*blc_range) = blc_ranger_measure();
        if ( !(blc_measureFromBack) ) {
            blc_blech_ctx->pc_58 = 12;
        } else if ( blc_measureFromBack ) {
            blc_blech_ctx->pc_58 = 14;
        }
    }
    if ( blc_blech_ctx->pc_58 == 12 ) {
        
        blc_blech_ctx->pc_58 = 16;
    }
    if ( blc_blech_ctx->pc_58 == 14 ) {
        (*blc_range) = ((*blc_range) + 62);
        blc_blech_ctx->pc_58 = 16;
    }
    if ( blc_blech_ctx->pc_58 == 16 ) {
        blc_blech_ctx->pc_58 = 19; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_58 == 18 ) {
        if ( 1 ) {
            if ( !(blc_rangingRequested) ) {
                blc_blech_ctx->pc_58 = 20;
            } else if ( blc_rangingRequested ) {
                blc_blech_ctx->pc_58 = 10;
                goto loopHead;
            }
        }
    }
    if ( blc_blech_ctx->pc_58 == 20 ) {
        blc_ranger_stopRanging();
        if ( 1 ) {
            blc_blech_ctx->pc_58 = 2;
            goto loopHead;
        } else if ( 0 ) {
            blc_blech_ctx->pc_58 = 22;
        }
    }
    if ( blc_blech_ctx->pc_58 == 22 ) {
        blc_blech_ctx->pc_58 = 0; /* end */
    }
    if ( blc_blech_ctx->pc_58 == 24 ) {
        blc_blech_ctx->pc_58 = 7; /* proceed from surface to depth */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_58);
    return blc_blech_ctx->pc_58 ;
}

/**  Publishes range and battery values via Bluetooth LE if connected. */
static blc_pc_t blc_ranger_BluetoothPublisher (struct blc_ranger_BluetoothPublisher *blc_blech_ctx,
                                               const blc_nat16 blc_range,
                                               const struct blc_ranger_BatteryInfo *const blc_battery) {
    blc_bool blc_bleConnected = bleConnected;
    loopHead:
    if ( blc_blech_ctx->pc_59 == 2 ) {
        /* The extern declaration is outside the Blech code */
        blc_blech_ctx->pc_59 = 4;
    }
    if ( blc_blech_ctx->pc_59 == 4 ) {
        if ( blc_bleConnected ) {
            blc_blech_ctx->pc_59 = 6;
        } else if ( !(blc_bleConnected) ) {
            blc_blech_ctx->pc_59 = 32;
        }
    }
    if ( blc_blech_ctx->pc_59 == 6 ) {
        
        blc_blech_ctx->pc_59 = 10;
    }
    if ( blc_blech_ctx->pc_59 == 8 ) {
        if ( blc_bleConnected ) {
            blc_blech_ctx->pc_59 = 10;
        }
    }
    if ( blc_blech_ctx->pc_59 == 10 ) {
        blc_blech_ctx->blc_BluetoothPublisher_151_prevRange = blc_ranger_UNDEF_RANGE;
        memset((&blc_blech_ctx->blc_BluetoothPublisher_151_prevBattery),
               0,
               sizeof(struct blc_ranger_BatteryInfo));
        blc_blech_ctx->pc_59 = 12;
    }
    if ( blc_blech_ctx->pc_59 == 12 ) {
        if ( (blc_range
        == blc_blech_ctx->blc_BluetoothPublisher_151_prevRange) ) {
            blc_blech_ctx->pc_59 = 14;
        } else if ( !((blc_range
        == blc_blech_ctx->blc_BluetoothPublisher_151_prevRange)) ) {
            blc_blech_ctx->pc_59 = 16;
        }
    }
    if ( blc_blech_ctx->pc_59 == 14 ) {
        
        blc_blech_ctx->pc_59 = 18;
    }
    if ( blc_blech_ctx->pc_59 == 16 ) {
        blc_ranger_publishRange(blc_range);
        blc_blech_ctx->blc_BluetoothPublisher_151_prevRange = blc_range;
        blc_blech_ctx->pc_59 = 18;
    }
    if ( blc_blech_ctx->pc_59 == 18 ) {
        if ( !(blc_ranger_chargeChanged(blc_battery,
                                        (&blc_blech_ctx->blc_BluetoothPublisher_151_prevBattery))) ) {
            blc_blech_ctx->pc_59 = 20;
        } else if ( blc_ranger_chargeChanged(blc_battery,
                                             (&blc_blech_ctx->blc_BluetoothPublisher_151_prevBattery)) ) {
            blc_blech_ctx->pc_59 = 22;
        }
    }
    if ( blc_blech_ctx->pc_59 == 20 ) {
        
        blc_blech_ctx->pc_59 = 24;
    }
    if ( blc_blech_ctx->pc_59 == 22 ) {
        blc_ranger_publishBattery(blc_battery);
        blc_blech_ctx->blc_BluetoothPublisher_151_prevBattery = (*blc_battery);
        blc_blech_ctx->pc_59 = 24;
    }
    if ( blc_blech_ctx->pc_59 == 24 ) {
        blc_blech_ctx->pc_59 = 27; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_59 == 26 ) {
        if ( 1 ) {
            if ( blc_bleConnected ) {
                blc_blech_ctx->pc_59 = 12;
                goto loopHead;
            } else if ( !(blc_bleConnected) ) {
                blc_blech_ctx->pc_59 = 28;
            }
        }
    }
    if ( blc_blech_ctx->pc_59 == 28 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_59 = 4;
            goto loopHead;
        } else if ( 0 ) {
            blc_blech_ctx->pc_59 = 30;
        }
    }
    if ( blc_blech_ctx->pc_59 == 30 ) {
        blc_blech_ctx->pc_59 = 0; /* end */
    }
    if ( blc_blech_ctx->pc_59 == 32 ) {
        blc_blech_ctx->pc_59 = 9; /* proceed from surface to depth */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_59);
    return blc_blech_ctx->pc_59 ;
}

/**  Senses the battery every second. */
static blc_pc_t blc_ranger_BatterySensor (struct blc_ranger_BatterySensor *blc_blech_ctx,
                                          struct blc_ranger_BatteryInfo *blc_batteryInfo) {
    loopHead:
    if ( blc_blech_ctx->pc_60 == 2 ) {
        struct blc_ranger_BatteryInfo blc_blech_aux_receiverVar_193;
        blc_ranger_readBatteryInfo((&blc_blech_aux_receiverVar_193));
        (*blc_batteryInfo) = blc_blech_aux_receiverVar_193;
        blc_blech_ctx->pc_60_blc_ranger_DelayOrDidWakeup.pc_2 = 2;
        blc_int32 blc_blech_aux_retcode_48;
        blc_blech_aux_retcode_48 = blc_ranger_DelayOrDidWakeup(&blc_blech_ctx->pc_60_blc_ranger_DelayOrDidWakeup,
                                                               10);
        BLC_UNUSED(blc_blech_aux_retcode_48);
        blc_blech_ctx->pc_60 = 6;
    }
    if ( blc_blech_ctx->pc_60 == 4 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_48;
            blc_blech_aux_retcode_48 = blc_ranger_DelayOrDidWakeup(&blc_blech_ctx->pc_60_blc_ranger_DelayOrDidWakeup,
                                                                   10);
            if ( !((0 == blc_blech_aux_retcode_48)) ) {
                blc_blech_ctx->pc_60 = 6;
            } else if ( (0 == blc_blech_aux_retcode_48) ) {
                blc_blech_ctx->pc_60 = 8;
            }
        }
    }
    if ( blc_blech_ctx->pc_60 == 6 ) {
        blc_blech_ctx->pc_60 = 5; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_60 == 8 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_60 = 2;
            goto loopHead;
        } else if ( 0 ) {
            blc_blech_ctx->pc_60 = 10;
        }
    }
    if ( blc_blech_ctx->pc_60 == 10 ) {
        blc_blech_ctx->pc_60 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_60);
    return blc_blech_ctx->pc_60 ;
}

/**  Tries to preserve battery by enterying sleep mode if possible. */
static blc_pc_t blc_ranger_PowerManager (struct blc_ranger_PowerManager *blc_blech_ctx,
                                         const struct blc_ranger_BatteryInfo *const blc_battery,
                                         const blc_nat8 blc_level,
                                         const blc_bool blc_bleEnabled) {
    blc_bool blc_bleConnected = bleConnected;
    blc_bool blc_didWakeup = didWakeup;
    loopHead:
    if ( blc_blech_ctx->pc_61 == 2 ) {
        blc_blech_ctx->pc_61 = 5; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_61 == 4 ) {
        if ( (blc_level == 7) ) {
            blc_blech_ctx->pc_61_blc_ranger_Delay.pc_1 = 2;
            blc_int32 blc_blech_aux_retcode_49;
            blc_blech_aux_retcode_49 = blc_ranger_Delay(&blc_blech_ctx->pc_61_blc_ranger_Delay,
                                                        10);
            BLC_UNUSED(blc_blech_aux_retcode_49);
            blc_blech_ctx->pc_61 = 10;
        }
    }
    if ( blc_blech_ctx->pc_61 == 6 ) {
        if ( !((blc_level == 7)) ) {
            blc_blech_ctx->pc_61 = 44;
        } else if ( 1 ) {
            blc_blech_ctx->pc_61 = 8;
        }
    }
    if ( blc_blech_ctx->pc_61 == 8 ) {
        blc_int32 blc_blech_aux_retcode_49;
        blc_blech_aux_retcode_49 = blc_ranger_Delay(&blc_blech_ctx->pc_61_blc_ranger_Delay,
                                                    10);
        if ( (0 == blc_blech_aux_retcode_49) ) {
            blc_blech_ctx->pc_61 = 12;
        } else if ( !((0 == blc_blech_aux_retcode_49)) ) {
            blc_blech_ctx->pc_61 = 10;
        }
    }
    if ( blc_blech_ctx->pc_61 == 10 ) {
        blc_blech_ctx->pc_61 = 7; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_61 == 12 ) {
        blc_ranger_activateDisplay(0);
        /* The extern declaration is outside the Blech code */
        if ( !(blc_bleConnected) ) {
            blc_blech_ctx->pc_61 = 14;
        } else if ( blc_bleConnected ) {
            blc_blech_ctx->pc_61 = 42;
        }
    }
    if ( blc_blech_ctx->pc_61 == 14 ) {
        /* The extern declaration is outside the Blech code */
        blc_blech_ctx->blc_PowerManager_160_161_163_164_2_abortFinished = 0;
        blc_blech_ctx->pc_61 = 16;
    }
    if ( blc_blech_ctx->pc_61 == 16 ) {
        blc_blech_ctx->blc_PowerManager_160_161_163_164_2_abortFinished = 0;
        blc_blech_ctx->pc_61_blc_ranger_Delay.pc_1 = 2;
        blc_int32 blc_blech_aux_retcode_50;
        blc_blech_aux_retcode_50 = blc_ranger_Delay(&blc_blech_ctx->pc_61_blc_ranger_Delay,
                                                    10);
        BLC_UNUSED(blc_blech_aux_retcode_50);
        blc_blech_ctx->pc_61 = 22;
    }
    if ( blc_blech_ctx->pc_61 == 18 ) {
        if ( !((blc_level == 7)) ) {
            blc_blech_ctx->pc_61 = 44;
        } else if ( blc_didWakeup ) {
            blc_blech_ctx->pc_61 = 36;
        } else if ( 1 ) {
            blc_blech_ctx->pc_61 = 20;
        }
    }
    if ( blc_blech_ctx->pc_61 == 20 ) {
        blc_int32 blc_blech_aux_retcode_50;
        blc_blech_aux_retcode_50 = blc_ranger_Delay(&blc_blech_ctx->pc_61_blc_ranger_Delay,
                                                    10);
        if ( (0 == blc_blech_aux_retcode_50) ) {
            blc_blech_ctx->pc_61 = 24;
        } else if ( !((0 == blc_blech_aux_retcode_50)) ) {
            blc_blech_ctx->pc_61 = 22;
        }
    }
    if ( blc_blech_ctx->pc_61 == 22 ) {
        blc_blech_ctx->pc_61 = 19; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_61 == 24 ) {
        if ( !(blc_bleEnabled) ) {
            blc_blech_ctx->pc_61 = 26;
        } else if ( blc_bleEnabled ) {
            blc_blech_ctx->pc_61 = 28;
        }
    }
    if ( blc_blech_ctx->pc_61 == 26 ) {
        blc_ranger_enterSleep(600);
        blc_blech_ctx->pc_61 = 30;
    }
    if ( blc_blech_ctx->pc_61 == 28 ) {
        blc_ranger_enterSleep(100);
        blc_blech_ctx->pc_61 = 30;
    }
    if ( blc_blech_ctx->pc_61 == 30 ) {
        blc_blech_ctx->pc_61 = 33; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_61 == 32 ) {
        if ( !((blc_level == 7)) ) {
            blc_blech_ctx->pc_61 = 44;
        } else if ( blc_didWakeup ) {
            blc_blech_ctx->pc_61 = 36;
        } else if ( 0 ) {
            blc_blech_ctx->pc_61 = 34;
        }
    }
    if ( blc_blech_ctx->pc_61 == 34 ) {
        blc_blech_ctx->blc_PowerManager_160_161_163_164_2_abortFinished = 1;
        blc_blech_ctx->pc_61 = 36;
    }
    if ( blc_blech_ctx->pc_61 == 36 ) {
        if ( blc_blech_ctx->blc_PowerManager_160_161_163_164_2_abortFinished ) {
            blc_blech_ctx->pc_61 = 40;
        } else if ( !(blc_blech_ctx->blc_PowerManager_160_161_163_164_2_abortFinished) ) {
            blc_blech_ctx->pc_61 = 16;
            goto loopHead;
        } /* abort subthreads and carry on */
    }
    if ( blc_blech_ctx->pc_61 == 38 ) {
        if ( !((blc_level == 7)) ) {
            blc_blech_ctx->pc_61 = 44;
        } else if ( 0 ) {
            blc_blech_ctx->pc_61 = 40;
        }
    }
    if ( blc_blech_ctx->pc_61 == 40 ) {
        blc_blech_ctx->pc_61 = 44;
    }
    if ( blc_blech_ctx->pc_61 == 42 ) {
        blc_blech_ctx->pc_61 = 39; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_61 == 44 ) {
        blc_ranger_activateDisplay(1);
        if ( 1 ) {
            blc_blech_ctx->pc_61 = 2;
            goto loopHead;
        } else if ( 0 ) {
            blc_blech_ctx->pc_61 = 46;
        } /* abort subthreads and carry on */
    }
    if ( blc_blech_ctx->pc_61 == 46 ) {
        blc_blech_ctx->pc_61 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_61);
    return blc_blech_ctx->pc_61 ;
}

/**  The top-level of the system composed of connected subsystems. */
static blc_pc_t blc_ranger_Main (struct blc_ranger_Main *blc_blech_ctx,
                                 const blc_nat8 blc_setupErr) {
    blc_bool blc_bleConnected = bleConnected;
    blc_bool blc_blech_prev_rangingRequest = blc_blech_ctx->blc_Main_rangingRequest;
    struct blc_ranger_Settings blc_blech_prev_settings = blc_blech_ctx->blc_Main_settings;
    if ( blc_blech_ctx->pc_62 == 2 ) {
        blc_blech_ctx->blc_Main_range = 0;
        memset((&blc_blech_ctx->blc_Main_battery),
               0,
               sizeof(struct blc_ranger_BatteryInfo));
        blc_blech_ctx->blc_Main_rangingRequest = 0;
        blc_blech_prev_rangingRequest = blc_blech_ctx->blc_Main_rangingRequest;
        /* The extern declaration is outside the Blech code */
        blc_blech_ctx->blc_Main_brightness = 0;
        memset((&blc_blech_ctx->blc_Main_settings),
               0,
               sizeof(struct blc_ranger_Settings));
        struct blc_ranger_Settings blc_blech_aux_receiverVar_204;
        blc_ranger_loadSettings((&blc_blech_aux_receiverVar_204));
        blc_blech_ctx->blc_Main_settings = blc_blech_aux_receiverVar_204;
        blc_blech_prev_settings = blc_blech_ctx->blc_Main_settings;
        blc_blech_ctx->pc_63 = 6;
        blc_blech_ctx->pc_64 = 4;
        blc_blech_ctx->pc_65 = 8;
        blc_blech_ctx->pc_66 = 42;
        blc_blech_ctx->pc_67 = 10;
        blc_blech_ctx->pc_62 = 52;
    }
    if ( blc_blech_ctx->pc_64 == 4 ) {
        blc_blech_ctx->pc_64_blc_ranger_BatterySensor.pc_60 = 2;
        blc_int32 blc_blech_aux_retcode_53;
        blc_blech_aux_retcode_53 = blc_ranger_BatterySensor(&blc_blech_ctx->pc_64_blc_ranger_BatterySensor,
                                                            (&blc_blech_ctx->blc_Main_battery));
        BLC_UNUSED(blc_blech_aux_retcode_53);
        blc_blech_ctx->pc_64 = 48;
    }
    if ( blc_blech_ctx->pc_63 == 6 ) {
        blc_blech_ctx->pc_63_blc_ranger_RangeSensor.pc_58 = 2;
        blc_int32 blc_blech_aux_retcode_52;
        blc_blech_aux_retcode_52 = blc_ranger_RangeSensor(&blc_blech_ctx->pc_63_blc_ranger_RangeSensor,
                                                          (blc_blech_prev_rangingRequest
                                                          || blc_bleConnected),
                                                          blc_blech_prev_settings.measureFromBack,
                                                          (&blc_blech_ctx->blc_Main_range));
        BLC_UNUSED(blc_blech_aux_retcode_52);
        blc_blech_ctx->pc_63 = 50;
    }
    if ( blc_blech_ctx->pc_65 == 8 ) {
        blc_blech_ctx->pc_65_blc_ranger_UI.pc_50 = 2;
        blc_blech_ctx->pc_65_blc_ranger_UI.pc_51 = 0;
        blc_blech_ctx->pc_65_blc_ranger_UI.pc_52 = 0;
        blc_blech_ctx->pc_65_blc_ranger_UI.pc_53 = 0;
        blc_blech_ctx->pc_65_blc_ranger_UI.pc_54 = 0;
        blc_blech_ctx->pc_65_blc_ranger_UI.pc_55 = 0;
        blc_blech_ctx->pc_65_blc_ranger_UI.pc_56 = 0;
        blc_blech_ctx->pc_65_blc_ranger_UI.pc_57 = 0;
        blc_int32 blc_blech_aux_retcode_54;
        blc_blech_aux_retcode_54 = blc_ranger_UI(&blc_blech_ctx->pc_65_blc_ranger_UI,
                                                 blc_setupErr,
                                                 blc_blech_ctx->blc_Main_range,
                                                 (&blc_blech_ctx->blc_Main_battery),
                                                 (&blc_blech_ctx->blc_Main_rangingRequest),
                                                 (&blc_blech_ctx->blc_Main_brightness),
                                                 (&blc_blech_ctx->blc_Main_settings));
        BLC_UNUSED(blc_blech_aux_retcode_54);
        blc_blech_ctx->pc_65 = 46;
    }
    if ( blc_blech_ctx->pc_67 == 10 ) {
        blc_blech_ctx->pc_67_blc_ranger_PowerManager.pc_61 = 2;
        blc_int32 blc_blech_aux_retcode_56;
        blc_blech_aux_retcode_56 = blc_ranger_PowerManager(&blc_blech_ctx->pc_67_blc_ranger_PowerManager,
                                                           (&blc_blech_ctx->blc_Main_battery),
                                                           blc_blech_ctx->blc_Main_brightness,
                                                           blc_blech_ctx->blc_Main_settings.bleEnabled);
        BLC_UNUSED(blc_blech_aux_retcode_56);
        blc_blech_ctx->pc_67 = 24;
    }
    if ( blc_blech_ctx->pc_67 == 12 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_67 = 22;
        }
    }
    if ( blc_blech_ctx->pc_65 == 14 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_65 = 20;
        }
    }
    if ( blc_blech_ctx->pc_64 == 16 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_53;
            blc_blech_aux_retcode_53 = blc_ranger_BatterySensor(&blc_blech_ctx->pc_64_blc_ranger_BatterySensor,
                                                                (&blc_blech_ctx->blc_Main_battery));
            if ( !((0 == blc_blech_aux_retcode_53)) ) {
                blc_blech_ctx->pc_64 = 48;
            } else if ( (0 == blc_blech_aux_retcode_53) ) {
                blc_blech_ctx->pc_64 = 38;
            }
        }
    }
    if ( blc_blech_ctx->pc_63 == 18 ) {
        if ( 1 ) {
            blc_int32 blc_blech_aux_retcode_52;
            blc_blech_aux_retcode_52 = blc_ranger_RangeSensor(&blc_blech_ctx->pc_63_blc_ranger_RangeSensor,
                                                              (blc_blech_prev_rangingRequest
                                                              || blc_bleConnected),
                                                              blc_blech_prev_settings.measureFromBack,
                                                              (&blc_blech_ctx->blc_Main_range));
            if ( !((0 == blc_blech_aux_retcode_52)) ) {
                blc_blech_ctx->pc_63 = 50;
            } else if ( (0 == blc_blech_aux_retcode_52) ) {
                blc_blech_ctx->pc_63 = 40;
            }
        }
    }
    if ( blc_blech_ctx->pc_65 == 20 ) {
        blc_int32 blc_blech_aux_retcode_54;
        blc_blech_aux_retcode_54 = blc_ranger_UI(&blc_blech_ctx->pc_65_blc_ranger_UI,
                                                 blc_setupErr,
                                                 blc_blech_ctx->blc_Main_range,
                                                 (&blc_blech_ctx->blc_Main_battery),
                                                 (&blc_blech_ctx->blc_Main_rangingRequest),
                                                 (&blc_blech_ctx->blc_Main_brightness),
                                                 (&blc_blech_ctx->blc_Main_settings));
        if ( !((0 == blc_blech_aux_retcode_54)) ) {
            blc_blech_ctx->pc_65 = 46;
        } else if ( (0 == blc_blech_aux_retcode_54) ) {
            blc_blech_ctx->pc_65 = 36;
        }
    }
    if ( blc_blech_ctx->pc_67 == 22 ) {
        blc_int32 blc_blech_aux_retcode_56;
        blc_blech_aux_retcode_56 = blc_ranger_PowerManager(&blc_blech_ctx->pc_67_blc_ranger_PowerManager,
                                                           (&blc_blech_ctx->blc_Main_battery),
                                                           blc_blech_ctx->blc_Main_brightness,
                                                           blc_blech_ctx->blc_Main_settings.bleEnabled);
        if ( !((0 == blc_blech_aux_retcode_56)) ) {
            blc_blech_ctx->pc_67 = 24;
        } else if ( (0 == blc_blech_aux_retcode_56) ) {
            blc_blech_ctx->pc_67 = 26;
        }
    }
    if ( blc_blech_ctx->pc_67 == 24 ) {
        blc_blech_ctx->pc_67 = 13; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_67 == 26 ) {
        blc_blech_ctx->pc_67 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_62 == 28 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_62 = 52;
        }
    }
    if ( blc_blech_ctx->pc_66 == 30 ) {
        if ( 1 ) {
            blc_blech_ctx->pc_66 = 32;
        }
    }
    if ( blc_blech_ctx->pc_66 == 32 ) {
        blc_int32 blc_blech_aux_retcode_55;
        blc_blech_aux_retcode_55 = blc_ranger_BluetoothPublisher(&blc_blech_ctx->pc_66_blc_ranger_BluetoothPublisher,
                                                                 blc_blech_ctx->blc_Main_range,
                                                                 (&blc_blech_ctx->blc_Main_battery));
        if ( !((0 == blc_blech_aux_retcode_55)) ) {
            blc_blech_ctx->pc_66 = 44;
        } else if ( (0 == blc_blech_aux_retcode_55) ) {
            blc_blech_ctx->pc_66 = 34;
        }
    }
    if ( blc_blech_ctx->pc_66 == 34 ) {
        blc_blech_ctx->pc_66 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_65 == 36 ) {
        blc_blech_ctx->pc_65 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_64 == 38 ) {
        blc_blech_ctx->pc_64 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_63 == 40 ) {
        blc_blech_ctx->pc_63 = 0; /* term */
    }
    if ( blc_blech_ctx->pc_66 == 42 ) {
        blc_blech_ctx->pc_66_blc_ranger_BluetoothPublisher.pc_59 = 2;
        blc_int32 blc_blech_aux_retcode_55;
        blc_blech_aux_retcode_55 = blc_ranger_BluetoothPublisher(&blc_blech_ctx->pc_66_blc_ranger_BluetoothPublisher,
                                                                 blc_blech_ctx->blc_Main_range,
                                                                 (&blc_blech_ctx->blc_Main_battery));
        BLC_UNUSED(blc_blech_aux_retcode_55);
        blc_blech_ctx->pc_66 = 44;
    }
    if ( blc_blech_ctx->pc_66 == 44 ) {
        blc_blech_ctx->pc_66 = 31; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_65 == 46 ) {
        blc_blech_ctx->pc_65 = 15; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_64 == 48 ) {
        blc_blech_ctx->pc_64 = 17; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_63 == 50 ) {
        blc_blech_ctx->pc_63 = 19; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_62 == 52 ) {
        blc_bool blc_blech_aux_termVar_51;
        if ( blc_blech_ctx->pc_63 == 0 && blc_blech_ctx->pc_64 == 0 && blc_blech_ctx->pc_65 == 0 && blc_blech_ctx->pc_66 == 0 && blc_blech_ctx->pc_67 == 0 ) {
            blc_blech_ctx->pc_63 = 0;
            blc_blech_ctx->pc_64 = 0;
            blc_blech_ctx->pc_65 = 0;
            blc_blech_ctx->pc_66 = 0;
            blc_blech_ctx->pc_67 = 0;
            blc_blech_aux_termVar_51 = 1;
        } else {
            blc_blech_aux_termVar_51 = 0;
        }
        if ( !(blc_blech_aux_termVar_51) ) {
            blc_blech_ctx->pc_62 = 54;
        } else if ( blc_blech_aux_termVar_51 ) {
            blc_blech_ctx->pc_62 = 56;
        }
    }
    if ( blc_blech_ctx->pc_62 == 54 ) {
        blc_blech_ctx->pc_62 = 29; /* proceed from surface to depth */
    }
    if ( blc_blech_ctx->pc_62 == 56 ) {
        blc_blech_ctx->pc_62 = 0;
        blc_blech_ctx->pc_63 = 0;
        blc_blech_ctx->pc_64 = 0;
        blc_blech_ctx->pc_65 = 0;
        blc_blech_ctx->pc_66 = 0;
        blc_blech_ctx->pc_67 = 0; /* end */
    }
    
    
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_62);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_63);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_64);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_65);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_66);
    BLC_SWITCH_TO_NEXTSTEP(blc_blech_ctx->pc_67);
    return blc_blech_ctx->pc_62 ;
}

/*
** blech program
*/

void blc_blech_ranger_tick (const blc_nat8 blc_setupErr) {
    blc_ranger_Main(&blc_blech_ctx, blc_setupErr);
}

void blc_blech_ranger_init (void) {
    blc_blech_ctx.pc_62 = 2;
}