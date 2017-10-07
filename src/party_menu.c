#include "global.h"
#include "party_menu.h"
#include "battle.h"
#include "battle_interface.h"
#include "battle_party_menu.h"
#include "data2.h"
#include "decompress.h"
#include "event_data.h"
#include "evolution_scene.h"
#include "item.h"
#include "item_use.h"
#include "item_menu.h"
#include "items.h"
#include "mail_data.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "palette.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "pokemon_item_effect.h"
#include "pokemon_menu.h"
#include "pokemon_summary_screen.h"
#include "rom_8077ABC.h"
#include "rom_8094928.h"
#include "songs.h"
#include "sound.h"
#include "species.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "util.h"

struct Unk201C000
{
    /*0x00*/ struct Pokemon *pokemon;
    /*0x04*/ u8 unk4;
    /*0x05*/ u8 unk5;
    /*0x06*/ u16 unk6;
    /*0x08*/ u16 unk8;
    /*0x0A*/ u8 pad_0A[2];
    /*0x0C*/ s32 unkC;
    /*0x10*/ TaskFunc unk10;
    /*0x14*/ TaskFunc unk14;
};

struct Unk201F000
{
    u8 filler0[0xE00];
    u8 unkE00[3];  // not sure if this is an array or struct, or how big it is
};

struct UnknownStruct5
{
    u8 unk0;
    u8 unk1;
    u16 *unk4;
};

struct Coords8
{
    u8 x;
    u8 y;
};

struct PartyMenuWindowCoords
{
    u8 left;
    u8 top;
    u8 right;
    u8 bottom;
};

struct UnknownPokemonStruct2
{
    /*0x00*/ u16 species;
    /*0x02*/ u16 heldItem;
    /*0x04*/ u8 nickname[11];
    /*0x0F*/ u8 level;
    /*0x10*/ u16 hp;
    /*0x12*/ u16 maxhp;
    /*0x14*/ u32 status;
    /*0x18*/ u32 personality;
    /*0x1C*/ u8 gender;
    /*0x1D*/ u8 language;
};

struct PartyMenuFunctionsStruct
{
    /*0x0*/TaskFunc func1;
    /*0x4*/TaskFunc func2;
    /*0x8*/u8 unk8;
};

#define ewram1C000 (*(struct Unk201C000 *)(ewram + 0x1C000))
#define ewram1F000 (*(struct Unk201F000 *)(ewram + 0x1F000))

extern u16 gBattleTypeFlags;

extern u8 gUnknown_0202E8F4;
extern u8 gUnknown_0202E8F6;
extern u16 gUnknown_0202E8F8;
extern u8 gUnknown_0202E8FA;
extern u8 gLastFieldPokeMenuOpened;
extern u8 gPlayerPartyCount;
extern s32 gBattleMoveDamage;
extern u16 gMoveToLearn;

extern struct PartyMenuFunctionsStruct const gUnknown_08376C74[];
extern u8 gUnknown_083769D8[];
extern u8 gUnknown_08376A25[];
extern u8 gUnknown_08376A5E[];
extern u16 gUnknown_08E9A300[];
extern const u16 gUnknown_08376CD4[];
extern const u16 gUnknown_08376CEC[];
extern u16 *const gUnknown_08376918[2][PARTY_SIZE];
extern struct Coords8 const gUnknown_08376738[12][6];
extern struct Coords8 const gUnknown_08376678[12][6];
extern struct PartyMenuWindowCoords const gUnknown_08376948[2][6];
extern struct PartyMenuWindowCoords const gUnknown_08376978[2][6];
extern struct Coords8 const gUnknown_083768B8[3][8];
extern u8 *const gUnknown_08376624[];
extern const u8 gUnknown_083769C0[];
//extern const u16 gUnknown_083769A8[][6];
//extern const u8 gUnknown_083769A8[][12];
extern u16 *const gUnknown_08376858[][6];
extern const u8 gUnknown_083769A8[];
extern const u8 gUnknown_08376D1C[NUM_STATS];
extern const u16 gUnknown_08376504[];
extern const struct SpriteSheet gUnknown_083765DC;
extern const struct SpritePalette gUnknown_083765E4;
extern void (*const gUnknown_08376B54[])(u8);
extern const u8 *const gUnknown_08376D04[NUM_STATS];
extern const struct UnknownStruct5 gUnknown_08376BB4[][6];
extern u8 gUnknown_02039460[];
extern u8 gTileBuffer[];
extern const struct SpriteTemplate gSpriteTemplate_837660C[];
extern struct Window gUnknown_03004210;

extern const u8 gPartyMenuMisc_Gfx[];
extern const u8 gPartyMenuMisc_Tilemap[];
extern const u8 gPartyMenuMisc_Pal[];
extern const u8 gFontDefaultPalette[];
extern const u8 gPartyMenuHpBar_Gfx[];
extern const u8 gPartyMenuOrderText_Gfx[];
extern const u8 gStatusGfx_Icons[];
extern const u8 gStatusPal_Icons[];

static void nullsub_12(u8 monIndex, struct Pokemon *pokemon);
static void TryPrintPartyMenuMonNickname(u8 monIndex, struct Pokemon *pokemon);
static void PartyMenuTryPrintHP(u8 monIndex, struct Pokemon *pokemon);
static void sub_806D05C(u8 taskId);
static void sub_806D15C(u8 taskId);
static void sub_806D198(u8 taskId);
static void sub_806E884(u8 taskId);
static void sub_8070D90(u8 taskId);
static void sub_806D5B8(u8 taskId);
static void sub_806D014(u8 taskId);
static void sub_806D118(u8 taskId);
static void sub_806B460(void);
static void sub_806B548(void);
static void sub_806BA94(s16 a, u16 b, u8 c, u8 d);
static void sub_806B9A4(s16 a, u16 b, u8 c);
static void sub_806CA18(u8 taskId, u8 b);
static void sub_806C310(u8 spriteId, u8 menuIndex, s8 directionPressed);
static void sub_806C1E4(u8 spriteId, u8 menuIndex, s8 directionPressed);
static void sub_806C490(u8 spriteId, u8 menuIndex, s8 directionPressed);
static void UpdateMonIconFrame_806DA0C(struct Sprite *sprite);
static void UpdateMonIconFrame_806DA38(struct Sprite *sprite);
static void UpdateMonIconFrame_806DA44(u8 taskId, u8 monIndex, u8 c);
static u8 sub_806CA00(u8 taskId);
static void SpriteCB_sub_806D37C(struct Sprite *sprite);
static u8 GetMonIconSpriteId_maybe(u8 taskId, u8 monIndex);

#if ENGLISH
#define WINDOW_LEFT (3)
#define WINDOW_RIGHT (26)
#elif GERMAN
#define WINDOW_LEFT (0)
#define WINDOW_RIGHT (29)
#endif


#ifdef NONMATCHING
void sub_806AEDC(void)
{
    const struct UnknownStruct5 *var1;
    s32 i;

    AnimateSprites();
    BuildOamBuffer();

    var1 = gUnknown_08376BB4[gUnknown_0202E8FA];
    for (i = 0; i < 6; i++)
    {
        sub_800142C(var1[i].unk0 * 8, var1[i].unk1 * 8, var1[i].unk4, 0, (i << 5) | 0x200);
    }

    RunTasks();
    UpdatePaletteFade();
}
#else
__attribute__((naked))
void sub_806AEDC(void)
{
    asm(".syntax unified\n\
    push {r4-r6,lr}\n\
    sub sp, 0x4\n\
    bl AnimateSprites\n\
    bl BuildOamBuffer\n\
    ldr r0, _0806AF2C @ =gUnknown_0202E8FA\n\
    ldrb r1, [r0]\n\
    lsls r0, r1, 1\n\
    adds r0, r1\n\
    lsls r0, 4\n\
    ldr r1, _0806AF30 @ =gUnknown_08376BB4\n\
    adds r5, r0, r1\n\
    movs r6, 0\n\
_0806AEF8:\n\
    ldrb r0, [r5]\n\
    lsls r0, 3\n\
    ldrb r1, [r5, 0x1]\n\
    lsls r1, 3\n\
    ldr r2, [r5, 0x4]\n\
    lsls r3, r6, 5\n\
    movs r4, 0x80\n\
    lsls r4, 2\n\
    orrs r3, r4\n\
    str r3, [sp]\n\
    movs r3, 0\n\
    bl sub_800142C\n\
    adds r5, 0x8\n\
    adds r6, 0x1\n\
    cmp r6, 0x5\n\
    ble _0806AEF8\n\
    bl RunTasks\n\
    bl UpdatePaletteFade\n\
    add sp, 0x4\n\
    pop {r4-r6}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_0806AF2C: .4byte gUnknown_0202E8FA\n\
_0806AF30: .4byte gUnknown_08376BB4\n\
    .syntax divided\n");
}
#endif // NONMATCHING

void sub_806AF34(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    sub_806B548();
}

void sub_806AF4C(u8 a, u8 battleFlags, TaskFunc func, u8 d)
{
    if (battleFlags != 0xFF)
    {
        gBattleTypeFlags = battleFlags;
    }

    ewram1B000.unk258 = a;
    ewram1B000.taskFunc = func;
    ewram1B000.unk259 = d;
}

void sub_806AF8C(u8 a, u8 battleFlags, TaskFunc func, u8 d)
{
    sub_806AF4C(a, battleFlags, func, d);
    SetMainCallback2(sub_806B460);
}

void OpenPartyMenu(u8 a, u8 battleFlags)
{
    sub_806AF8C(a, battleFlags, gUnknown_08376C74[a].func1, gUnknown_08376C74[a].unk8);
}

__attribute__((naked))
bool8 sub_806AFD0(void)
{
    asm(".syntax unified\n\
    push {r4,r5,lr}\n\
    ldr r1, _0806AFF0 @ =0x0201b000\n\
    movs r2, 0x99\n\
    lsls r2, 2\n\
    adds r0, r1, r2\n\
    movs r2, 0\n\
    ldrsh r0, [r0, r2]\n\
    adds r4, r1, 0\n\
    cmp r0, 0x9\n\
    bls _0806AFE6\n\
    b _0806B11A\n\
_0806AFE6:\n\
    lsls r0, 2\n\
    ldr r1, _0806AFF4 @ =_0806AFF8\n\
    adds r0, r1\n\
    ldr r0, [r0]\n\
    mov pc, r0\n\
    .align 2, 0\n\
_0806AFF0: .4byte 0x0201b000\n\
_0806AFF4: .4byte _0806AFF8\n\
    .align 2, 0\n\
_0806AFF8:\n\
    .4byte _0806B020\n\
    .4byte _0806B060\n\
    .4byte _0806B066\n\
    .4byte _0806B07A\n\
    .4byte _0806B0A4\n\
    .4byte _0806B0AA\n\
    .4byte _0806B0BC\n\
    .4byte _0806B0C2\n\
    .4byte _0806B0D4\n\
    .4byte _0806B0EC\n\
_0806B020:\n\
    ldr r0, _0806B048 @ =0x00000266\n\
    adds r5, r4, r0\n\
    movs r1, 0\n\
    ldrsh r3, [r5, r1]\n\
    ldr r0, _0806B04C @ =gPlayerPartyCount\n\
    ldrb r0, [r0]\n\
    cmp r3, r0\n\
    bge _0806B054\n\
    movs r2, 0x98\n\
    lsls r2, 2\n\
    adds r0, r4, r2\n\
    ldrb r0, [r0]\n\
    ldrb r1, [r5]\n\
    movs r2, 0x64\n\
    muls r2, r3\n\
    ldr r3, _0806B050 @ =gPlayerParty\n\
    adds r2, r3\n\
    bl TryCreatePartyMenuMonIcon\n\
    b _0806B114\n\
    .align 2, 0\n\
_0806B048: .4byte 0x00000266\n\
_0806B04C: .4byte gPlayerPartyCount\n\
_0806B050: .4byte gPlayerParty\n\
_0806B054:\n\
    movs r0, 0\n\
    strh r0, [r5]\n\
    movs r0, 0x99\n\
    lsls r0, 2\n\
    adds r1, r4, r0\n\
    b _0806B0E0\n\
_0806B060:\n\
    bl LoadHeldItemIconGraphics\n\
    b _0806B0D8\n\
_0806B066:\n\
    movs r1, 0x98\n\
    lsls r1, 2\n\
    adds r0, r4, r1\n\
    ldrb r0, [r0]\n\
    bl CreateHeldItemIcons_806DC34\n\
    movs r2, 0x99\n\
    lsls r2, 2\n\
    adds r1, r4, r2\n\
    b _0806B0E0\n\
_0806B07A:\n\
    movs r1, 0x98\n\
    lsls r1, 2\n\
    adds r0, r4, r1\n\
    ldrb r0, [r0]\n\
    ldr r2, _0806B0A0 @ =0x00000266\n\
    adds r5, r4, r2\n\
    ldrb r1, [r5]\n\
    bl sub_806BD58\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _0806B114\n\
    movs r0, 0\n\
    strh r0, [r5]\n\
    movs r0, 0x99\n\
    lsls r0, 2\n\
    adds r1, r4, r0\n\
    b _0806B0E0\n\
    .align 2, 0\n\
_0806B0A0: .4byte 0x00000266\n\
_0806B0A4:\n\
    bl PartyMenuPrintMonsLevelOrStatus\n\
    b _0806B0D8\n\
_0806B0AA:\n\
    bl PrintPartyMenuMonNicknames\n\
    ldr r1, _0806B0B8 @ =0x0201b000\n\
    movs r0, 0x99\n\
    lsls r0, 2\n\
    adds r1, r0\n\
    b _0806B0E0\n\
    .align 2, 0\n\
_0806B0B8: .4byte 0x0201b000\n\
_0806B0BC:\n\
    bl PartyMenuTryPrintMonsHP\n\
    b _0806B0D8\n\
_0806B0C2:\n\
    bl nullsub_13\n\
    ldr r1, _0806B0D0 @ =0x0201b000\n\
    movs r0, 0x99\n\
    lsls r0, 2\n\
    adds r1, r0\n\
    b _0806B0E0\n\
    .align 2, 0\n\
_0806B0D0: .4byte 0x0201b000\n\
_0806B0D4:\n\
    bl PartyMenuDrawHPBars\n\
_0806B0D8:\n\
    ldr r1, _0806B0E8 @ =0x0201b000\n\
    movs r2, 0x99\n\
    lsls r2, 2\n\
    adds r1, r2\n\
_0806B0E0:\n\
    ldrh r0, [r1]\n\
    adds r0, 0x1\n\
    strh r0, [r1]\n\
    b _0806B11A\n\
    .align 2, 0\n\
_0806B0E8: .4byte 0x0201b000\n\
_0806B0EC:\n\
    ldr r0, _0806B110 @ =0x00000266\n\
    adds r5, r4, r0\n\
    ldrb r0, [r5]\n\
    bl sub_806B58C\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _0806B114\n\
    movs r1, 0\n\
    strh r1, [r5]\n\
    movs r2, 0x99\n\
    lsls r2, 2\n\
    adds r0, r4, r2\n\
    strh r1, [r0]\n\
    movs r0, 0x1\n\
    b _0806B11C\n\
    .align 2, 0\n\
_0806B110: .4byte 0x00000266\n\
_0806B114:\n\
    ldrh r0, [r5]\n\
    adds r0, 0x1\n\
    strh r0, [r5]\n\
_0806B11A:\n\
    movs r0, 0\n\
_0806B11C:\n\
    pop {r4,r5}\n\
    pop {r1}\n\
    bx r1\n\
    .syntax divided\n");
}

__attribute__((naked))
bool8 sub_806B124(void)
{
    asm(".syntax unified\n\
    push {r4-r7,lr}\n\
    mov r7, r8\n\
    push {r7}\n\
    sub sp, 0xC\n\
    ldr r0, _0806B144 @ =gMain\n\
    ldr r1, _0806B148 @ =0x0000043c\n\
    adds r0, r1\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x11\n\
    bls _0806B13A\n\
    b _0806B450\n\
_0806B13A:\n\
    lsls r0, 2\n\
    ldr r1, _0806B14C @ =_0806B150\n\
    adds r0, r1\n\
    ldr r0, [r0]\n\
    mov pc, r0\n\
    .align 2, 0\n\
_0806B144: .4byte gMain\n\
_0806B148: .4byte 0x0000043c\n\
_0806B14C: .4byte _0806B150\n\
    .align 2, 0\n\
_0806B150:\n\
    .4byte _0806B198\n\
    .4byte _0806B240\n\
    .4byte _0806B246\n\
    .4byte _0806B27C\n\
    .4byte _0806B282\n\
    .4byte _0806B2AC\n\
    .4byte _0806B2B2\n\
    .4byte _0806B2D0\n\
    .4byte _0806B2EC\n\
    .4byte _0806B318\n\
    .4byte _0806B344\n\
    .4byte _0806B37C\n\
    .4byte _0806B382\n\
    .4byte _0806B3C0\n\
    .4byte _0806B3CC\n\
    .4byte _0806B3E4\n\
    .4byte _0806B40C\n\
    .4byte _0806B440\n\
_0806B198:\n\
    movs r0, 0\n\
    bl SetVBlankCallback\n\
    movs r3, 0xC0\n\
    lsls r3, 19\n\
    movs r4, 0xC0\n\
    lsls r4, 9\n\
    add r2, sp, 0x8\n\
    mov r8, r2\n\
    add r2, sp, 0x4\n\
    movs r6, 0\n\
    ldr r1, _0806B22C @ =0x040000d4\n\
    movs r5, 0x80\n\
    lsls r5, 5\n\
    ldr r7, _0806B230 @ =0x81000800\n\
    movs r0, 0x81\n\
    lsls r0, 24\n\
    mov r12, r0\n\
_0806B1BC:\n\
    strh r6, [r2]\n\
    add r0, sp, 0x4\n\
    str r0, [r1]\n\
    str r3, [r1, 0x4]\n\
    str r7, [r1, 0x8]\n\
    ldr r0, [r1, 0x8]\n\
    adds r3, r5\n\
    subs r4, r5\n\
    cmp r4, r5\n\
    bhi _0806B1BC\n\
    strh r6, [r2]\n\
    add r2, sp, 0x4\n\
    str r2, [r1]\n\
    str r3, [r1, 0x4]\n\
    lsrs r0, r4, 1\n\
    mov r3, r12\n\
    orrs r0, r3\n\
    str r0, [r1, 0x8]\n\
    ldr r0, [r1, 0x8]\n\
    movs r0, 0xE0\n\
    lsls r0, 19\n\
    movs r3, 0x80\n\
    lsls r3, 3\n\
    movs r4, 0\n\
    str r4, [sp, 0x8]\n\
    ldr r2, _0806B22C @ =0x040000d4\n\
    mov r1, r8\n\
    str r1, [r2]\n\
    str r0, [r2, 0x4]\n\
    lsrs r0, r3, 2\n\
    movs r1, 0x85\n\
    lsls r1, 24\n\
    orrs r0, r1\n\
    str r0, [r2, 0x8]\n\
    ldr r0, [r2, 0x8]\n\
    movs r1, 0xA0\n\
    lsls r1, 19\n\
    add r0, sp, 0x4\n\
    strh r4, [r0]\n\
    str r0, [r2]\n\
    str r1, [r2, 0x4]\n\
    lsrs r3, 1\n\
    movs r0, 0x81\n\
    lsls r0, 24\n\
    orrs r3, r0\n\
    str r3, [r2, 0x8]\n\
    ldr r0, [r2, 0x8]\n\
    ldr r2, _0806B234 @ =gPaletteFade\n\
    ldrb r0, [r2, 0x8]\n\
    movs r1, 0x80\n\
    orrs r0, r1\n\
    strb r0, [r2, 0x8]\n\
    ldr r1, _0806B238 @ =gMain\n\
    ldr r2, _0806B23C @ =0x0000043c\n\
    adds r1, r2\n\
    b _0806B42C\n\
    .align 2, 0\n\
_0806B22C: .4byte 0x040000d4\n\
_0806B230: .4byte 0x81000800\n\
_0806B234: .4byte gPaletteFade\n\
_0806B238: .4byte gMain\n\
_0806B23C: .4byte 0x0000043c\n\
_0806B240:\n\
    bl remove_some_task\n\
    b _0806B426\n\
_0806B246:\n\
    bl sub_806B4A8\n\
    ldr r1, _0806B26C @ =0x0201b000\n\
    movs r2, 0x99\n\
    lsls r2, 2\n\
    adds r0, r1, r2\n\
    movs r2, 0\n\
    strh r2, [r0]\n\
    ldr r3, _0806B270 @ =0x00000266\n\
    adds r0, r1, r3\n\
    strh r2, [r0]\n\
    movs r0, 0x9A\n\
    lsls r0, 2\n\
    adds r1, r0\n\
    strh r2, [r1]\n\
    ldr r1, _0806B274 @ =gMain\n\
    ldr r2, _0806B278 @ =0x0000043c\n\
    adds r1, r2\n\
    b _0806B42C\n\
    .align 2, 0\n\
_0806B26C: .4byte 0x0201b000\n\
_0806B270: .4byte 0x00000266\n\
_0806B274: .4byte gMain\n\
_0806B278: .4byte 0x0000043c\n\
_0806B27C:\n\
    bl ResetSpriteData\n\
    b _0806B426\n\
_0806B282:\n\
    ldr r0, _0806B2A0 @ =0x0201b000\n\
    movs r1, 0x96\n\
    lsls r1, 2\n\
    adds r0, r1\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x1\n\
    beq _0806B298\n\
    cmp r0, 0x5\n\
    beq _0806B298\n\
    bl ResetTasks\n\
_0806B298:\n\
    ldr r1, _0806B2A4 @ =gMain\n\
    ldr r2, _0806B2A8 @ =0x0000043c\n\
    adds r1, r2\n\
    b _0806B42C\n\
    .align 2, 0\n\
_0806B2A0: .4byte 0x0201b000\n\
_0806B2A4: .4byte gMain\n\
_0806B2A8: .4byte 0x0000043c\n\
_0806B2AC:\n\
    bl FreeAllSpritePalettes\n\
    b _0806B426\n\
_0806B2B2:\n\
    ldr r4, _0806B2CC @ =0x0201b000\n\
    movs r1, 0x97\n\
    lsls r1, 2\n\
    adds r0, r4, r1\n\
    ldr r0, [r0]\n\
    movs r1, 0\n\
    bl CreateTask\n\
    movs r2, 0x98\n\
    lsls r2, 2\n\
    adds r1, r4, r2\n\
    strb r0, [r1]\n\
    b _0806B426\n\
    .align 2, 0\n\
_0806B2CC: .4byte 0x0201b000\n\
_0806B2D0:\n\
    ldr r0, _0806B2E0 @ =gWindowConfig_81E6C90\n\
    bl SetUpWindowConfig\n\
    ldr r1, _0806B2E4 @ =gMain\n\
    ldr r0, _0806B2E8 @ =0x0000043c\n\
    adds r1, r0\n\
    b _0806B42C\n\
    .align 2, 0\n\
_0806B2E0: .4byte gWindowConfig_81E6C90\n\
_0806B2E4: .4byte gMain\n\
_0806B2E8: .4byte 0x0000043c\n\
_0806B2EC:\n\
    ldr r4, _0806B308 @ =gUnknown_03004210\n\
    ldr r1, _0806B30C @ =gWindowConfig_81E6C90\n\
    adds r0, r4, 0\n\
    bl InitWindowFromConfig\n\
    adds r0, r4, 0\n\
    movs r1, 0x1\n\
    bl MultistepInitWindowTileData\n\
    ldr r1, _0806B310 @ =gMain\n\
    ldr r2, _0806B314 @ =0x0000043c\n\
    adds r1, r2\n\
    b _0806B42C\n\
    .align 2, 0\n\
_0806B308: .4byte gUnknown_03004210\n\
_0806B30C: .4byte gWindowConfig_81E6C90\n\
_0806B310: .4byte gMain\n\
_0806B314: .4byte 0x0000043c\n\
_0806B318:\n\
    bl MultistepLoadFont\n\
    cmp r0, 0\n\
    bne _0806B322\n\
    b _0806B450\n\
_0806B322:\n\
    ldr r0, _0806B338 @ =0x0201b000\n\
    movs r3, 0x99\n\
    lsls r3, 2\n\
    adds r0, r3\n\
    movs r1, 0x1\n\
    strh r1, [r0]\n\
    ldr r1, _0806B33C @ =gMain\n\
    ldr r0, _0806B340 @ =0x0000043c\n\
    adds r1, r0\n\
    b _0806B42C\n\
    .align 2, 0\n\
_0806B338: .4byte 0x0201b000\n\
_0806B33C: .4byte gMain\n\
_0806B340: .4byte 0x0000043c\n\
_0806B344:\n\
    ldr r0, _0806B368 @ =0x0201b000\n\
    movs r1, 0x99\n\
    lsls r1, 2\n\
    adds r4, r0, r1\n\
    ldrb r0, [r4]\n\
    bl LoadPartyMenuGraphics\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _0806B374\n\
    movs r0, 0\n\
    strh r0, [r4]\n\
    ldr r1, _0806B36C @ =gMain\n\
    ldr r2, _0806B370 @ =0x0000043c\n\
    adds r1, r2\n\
    b _0806B42C\n\
    .align 2, 0\n\
_0806B368: .4byte 0x0201b000\n\
_0806B36C: .4byte gMain\n\
_0806B370: .4byte 0x0000043c\n\
_0806B374:\n\
    ldrh r0, [r4]\n\
    adds r0, 0x1\n\
    strh r0, [r4]\n\
    b _0806B450\n\
_0806B37C:\n\
    bl sub_809D51C\n\
    b _0806B426\n\
_0806B382:\n\
    ldr r2, _0806B3B0 @ =gUnknown_08376C74\n\
    ldr r0, _0806B3B4 @ =0x0201b000\n\
    movs r1, 0x96\n\
    lsls r1, 2\n\
    adds r0, r1\n\
    ldrb r1, [r0]\n\
    lsls r0, r1, 1\n\
    adds r0, r1\n\
    lsls r0, 2\n\
    adds r2, 0x4\n\
    adds r0, r2\n\
    ldr r0, [r0]\n\
    bl _call_via_r0\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _0806B450\n\
    ldr r1, _0806B3B8 @ =gMain\n\
    ldr r2, _0806B3BC @ =0x0000043c\n\
    adds r1, r2\n\
    b _0806B42C\n\
    .align 2, 0\n\
_0806B3B0: .4byte gUnknown_08376C74\n\
_0806B3B4: .4byte 0x0201b000\n\
_0806B3B8: .4byte gMain\n\
_0806B3BC: .4byte 0x0000043c\n\
_0806B3C0:\n\
    ldr r0, _0806B3C8 @ =gWindowConfig_81E6CC8\n\
    bl MultistepInitMenuWindowBegin\n\
    b _0806B426\n\
    .align 2, 0\n\
_0806B3C8: .4byte gWindowConfig_81E6CC8\n\
_0806B3CC:\n\
    bl MultistepInitMenuWindowContinue\n\
    cmp r0, 0\n\
    beq _0806B450\n\
    ldr r1, _0806B3DC @ =gMain\n\
    ldr r0, _0806B3E0 @ =0x0000043c\n\
    adds r1, r0\n\
    b _0806B42C\n\
    .align 2, 0\n\
_0806B3DC: .4byte gMain\n\
_0806B3E0: .4byte 0x0000043c\n\
_0806B3E4:\n\
    ldr r0, _0806B3FC @ =0x0201b000\n\
    ldr r1, _0806B400 @ =0x00000259\n\
    adds r0, r1\n\
    ldrb r0, [r0]\n\
    movs r1, 0\n\
    bl sub_806D538\n\
    ldr r1, _0806B404 @ =gMain\n\
    ldr r2, _0806B408 @ =0x0000043c\n\
    adds r1, r2\n\
    b _0806B42C\n\
    .align 2, 0\n\
_0806B3FC: .4byte 0x0201b000\n\
_0806B400: .4byte 0x00000259\n\
_0806B404: .4byte gMain\n\
_0806B408: .4byte 0x0000043c\n\
_0806B40C:\n\
    movs r0, 0x1\n\
    negs r0, r0\n\
    movs r1, 0\n\
    str r1, [sp]\n\
    movs r2, 0x10\n\
    movs r3, 0\n\
    bl BeginNormalPaletteFade\n\
    ldr r2, _0806B434 @ =gPaletteFade\n\
    ldrb r1, [r2, 0x8]\n\
    movs r0, 0x7F\n\
    ands r0, r1\n\
    strb r0, [r2, 0x8]\n\
_0806B426:\n\
    ldr r1, _0806B438 @ =gMain\n\
    ldr r3, _0806B43C @ =0x0000043c\n\
    adds r1, r3\n\
_0806B42C:\n\
    ldrb r0, [r1]\n\
    adds r0, 0x1\n\
    strb r0, [r1]\n\
    b _0806B450\n\
    .align 2, 0\n\
_0806B434: .4byte gPaletteFade\n\
_0806B438: .4byte gMain\n\
_0806B43C: .4byte 0x0000043c\n\
_0806B440:\n\
    ldr r0, _0806B44C @ =sub_806AF34\n\
    bl SetVBlankCallback\n\
    movs r0, 0x1\n\
    b _0806B452\n\
    .align 2, 0\n\
_0806B44C: .4byte sub_806AF34\n\
_0806B450:\n\
    movs r0, 0\n\
_0806B452:\n\
    add sp, 0xC\n\
    pop {r3}\n\
    mov r8, r3\n\
    pop {r4-r7}\n\
    pop {r1}\n\
    bx r1\n\
    .syntax divided\n");
}

void sub_806B460(void)
{
    while (sub_806B124() != TRUE)
    {
        if (sub_80F9344() == TRUE)
        {
            return;
        }
    }

    if (ewram1B000.unk258 != 5)
    {
        sub_806BF74(ewram1B000.unk260, 0);
    }

    SetMainCallback2(sub_806AEDC);
}

void sub_806B4A8(void)
{
    SetHBlankCallback(NULL);
    REG_DISPCNT = 8000;
    REG_BG0CNT = 0x1E05;
    REG_BG1CNT = 0x703;
    REG_BG2CNT = 0xF08;
    REG_BG3CNT = 0x602;
    REG_BLDCNT = 0;
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;
    REG_BG1HOFS = 0;
    REG_BG1VOFS = 0;
    REG_BG2HOFS = 0;
    REG_BG2VOFS = 0;
    REG_BG3HOFS = 0;
    REG_BG3VOFS = 0;
    REG_BG3VOFS = -1;
}

bool8 IsLinkDoubleBattle()
{
    if ((gBattleTypeFlags & BATTLE_TYPE_LINK_DOUBLE) == BATTLE_TYPE_LINK_DOUBLE)
        return TRUE;
    else
        return FALSE;
}

#ifdef NONMATCHING
void sub_806B548(void)
{
    if (ewram1B000.unk261)
    {
        u32 src = (u32)&gBGTilemapBuffers[2];
        u32 dest = BG_VRAM + 0x3000;

        REG_DMA3SAD = src;
        REG_DMA3DAD = dest;
        REG_DMA3CNT = ((DMA_ENABLE) << 16) | 0x400;

        if (ewram1B000.unk261 == 2)
        {
            ewram1B000.unk261 = 0;
        }
    }
}
#else
__attribute__((naked))
void sub_806B548(void)
{
    asm(".syntax unified\n\
    push {r4,lr}\n\
    ldr r0, _0806B574 @ =0x0201b000\n\
    ldr r1, _0806B578 @ =0x00000261\n\
    adds r4, r0, r1\n\
    ldrb r3, [r4]\n\
    cmp r3, 0\n\
    beq _0806B56E\n\
    ldr r1, _0806B57C @ =gBGTilemapBuffers + 0x1000\n\
    ldr r2, _0806B580 @ =0x06003000\n\
    ldr r0, _0806B584 @ =0x040000d4\n\
    str r1, [r0]\n\
    str r2, [r0, 0x4]\n\
    ldr r1, _0806B588 @ =0x80000400\n\
    str r1, [r0, 0x8]\n\
    ldr r0, [r0, 0x8]\n\
    cmp r3, 0x2\n\
    bne _0806B56E\n\
    movs r0, 0\n\
    strb r0, [r4]\n\
_0806B56E:\n\
    pop {r4}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_0806B574: .4byte 0x0201b000\n\
_0806B578: .4byte 0x00000261\n\
_0806B57C: .4byte gBGTilemapBuffers + 0x1000\n\
_0806B580: .4byte 0x06003000\n\
_0806B584: .4byte 0x040000d4\n\
_0806B588: .4byte 0x80000400\n\
    .syntax divided\n");
}
#endif // NONMATCHING

__attribute__((naked))
u8 sub_806B58C(u8 a)
{
    asm(".syntax unified\n\
    push {r4,r5,lr}\n\
    lsls r0, 24\n\
    lsrs r5, r0, 24\n\
    bl IsDoubleBattle\n\
    lsls r0, 24\n\
    lsrs r2, r0, 24\n\
    cmp r2, 0\n\
    bne _0806B5A8\n\
    ldr r0, _0806B5A4 @ =gUnknown_0202E8FA\n\
    strb r2, [r0]\n\
    b _0806B5C8\n\
    .align 2, 0\n\
_0806B5A4: .4byte gUnknown_0202E8FA\n\
_0806B5A8:\n\
    bl IsLinkDoubleBattle\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _0806B5C0\n\
    ldr r1, _0806B5BC @ =gUnknown_0202E8FA\n\
    movs r0, 0x2\n\
    b _0806B5C4\n\
    .align 2, 0\n\
_0806B5BC: .4byte gUnknown_0202E8FA\n\
_0806B5C0:\n\
    ldr r1, _0806B5E4 @ =gUnknown_0202E8FA\n\
    movs r0, 0x1\n\
_0806B5C4:\n\
    strb r0, [r1]\n\
    adds r0, r1, 0\n\
_0806B5C8:\n\
    ldrb r0, [r0]\n\
    lsls r1, r0, 1\n\
    adds r1, r0\n\
    lsls r1, 2\n\
    ldr r0, _0806B5E8 @ =gUnknown_083769A8\n\
    adds r4, r1, r0\n\
    cmp r5, 0x8\n\
    bls _0806B5DA\n\
    b _0806B900\n\
_0806B5DA:\n\
    lsls r0, r5, 2\n\
    ldr r1, _0806B5EC @ =_0806B5F0\n\
    adds r0, r1\n\
    ldr r0, [r0]\n\
    mov pc, r0\n\
    .align 2, 0\n\
_0806B5E4: .4byte gUnknown_0202E8FA\n\
_0806B5E8: .4byte gUnknown_083769A8\n\
_0806B5EC: .4byte _0806B5F0\n\
    .align 2, 0\n\
_0806B5F0:\n\
    .4byte _0806B614\n\
    .4byte _0806B628\n\
    .4byte _0806B638\n\
    .4byte _0806B694\n\
    .4byte _0806B71A\n\
    .4byte _0806B7A2\n\
    .4byte _0806B832\n\
    .4byte _0806B8C6\n\
    .4byte _0806B8E8\n\
_0806B614:\n\
    ldr r0, _0806B624 @ =gBGTilemapBuffers + 0x1000\n\
    movs r2, 0x80\n\
    lsls r2, 4\n\
    movs r1, 0\n\
    bl memset\n\
    b _0806B900\n\
    .align 2, 0\n\
_0806B624: .4byte gBGTilemapBuffers + 0x1000\n\
_0806B628:\n\
    ldrb r0, [r4]\n\
    ldrb r1, [r4, 0x1]\n\
    movs r2, 0x3\n\
    bl sub_806B9A4\n\
    adds r0, r4, 0\n\
    movs r1, 0\n\
    b _0806B8A8\n\
_0806B638:\n\
    bl IsDoubleBattle\n\
    lsls r0, 24\n\
    cmp r0, 0\n\
    bne _0806B666\n\
    ldr r0, _0806B65C @ =gPlayerPartyCount\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x1\n\
    bls _0806B660\n\
    ldrb r0, [r4, 0x2]\n\
    ldrb r1, [r4, 0x3]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    adds r0, r4, 0x2\n\
    movs r1, 0x1\n\
    b _0806B8A8\n\
    .align 2, 0\n\
_0806B65C: .4byte gPlayerPartyCount\n\
_0806B660:\n\
    ldrb r0, [r4, 0x2]\n\
    ldrb r1, [r4, 0x3]\n\
    b _0806B8BC\n\
_0806B666:\n\
    bl IsLinkDoubleBattle\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _0806B684\n\
    ldrb r0, [r4, 0x2]\n\
    ldrb r1, [r4, 0x3]\n\
    movs r2, 0x4\n\
    bl sub_806B9A4\n\
    adds r0, r4, 0x2\n\
    movs r1, 0x1\n\
    movs r2, 0x4\n\
    b _0806B8AA\n\
_0806B684:\n\
    ldrb r0, [r4, 0x2]\n\
    ldrb r1, [r4, 0x3]\n\
    movs r2, 0x3\n\
    bl sub_806B9A4\n\
    adds r0, r4, 0x2\n\
    movs r1, 0x1\n\
    b _0806B8A8\n\
_0806B694:\n\
    bl IsDoubleBattle\n\
    lsls r0, 24\n\
    cmp r0, 0\n\
    bne _0806B6C2\n\
    ldr r0, _0806B6B8 @ =gPlayerPartyCount\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x2\n\
    bls _0806B6BC\n\
    ldrb r0, [r4, 0x4]\n\
    ldrb r1, [r4, 0x5]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    adds r0, r4, 0x4\n\
    movs r1, 0x2\n\
    b _0806B8A8\n\
    .align 2, 0\n\
_0806B6B8: .4byte gPlayerPartyCount\n\
_0806B6BC:\n\
    ldrb r0, [r4, 0x4]\n\
    ldrb r1, [r4, 0x5]\n\
    b _0806B8BC\n\
_0806B6C2:\n\
    bl IsLinkDoubleBattle\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _0806B6F6\n\
    ldr r0, _0806B6EC @ =gPlayerParty + 2 * 0x64\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    beq _0806B6F0\n\
    ldrb r0, [r4, 0x4]\n\
    ldrb r1, [r4, 0x5]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    adds r0, r4, 0x4\n\
    movs r1, 0x2\n\
    b _0806B8A8\n\
    .align 2, 0\n\
_0806B6EC: .4byte gPlayerParty + 2 * 0x64\n\
_0806B6F0:\n\
    ldrb r0, [r4, 0x4]\n\
    ldrb r1, [r4, 0x5]\n\
    b _0806B8BC\n\
_0806B6F6:\n\
    ldr r0, _0806B710 @ =gPlayerPartyCount\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x2\n\
    bls _0806B714\n\
    ldrb r0, [r4, 0x4]\n\
    ldrb r1, [r4, 0x5]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    adds r0, r4, 0x4\n\
    movs r1, 0x2\n\
    b _0806B8A8\n\
    .align 2, 0\n\
_0806B710: .4byte gPlayerPartyCount\n\
_0806B714:\n\
    ldrb r0, [r4, 0x4]\n\
    ldrb r1, [r4, 0x5]\n\
    b _0806B8BC\n\
_0806B71A:\n\
    bl IsDoubleBattle\n\
    lsls r0, 24\n\
    cmp r0, 0\n\
    bne _0806B74A\n\
    ldr r0, _0806B740 @ =gPlayerPartyCount\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x3\n\
    bls _0806B744\n\
    ldrb r0, [r4, 0x6]\n\
    ldrb r1, [r4, 0x7]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    adds r0, r4, 0x6\n\
    movs r1, 0x3\n\
    b _0806B8A8\n\
    .align 2, 0\n\
_0806B740: .4byte gPlayerPartyCount\n\
_0806B744:\n\
    ldrb r0, [r4, 0x6]\n\
    ldrb r1, [r4, 0x7]\n\
    b _0806B8BC\n\
_0806B74A:\n\
    bl IsLinkDoubleBattle\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _0806B77E\n\
    ldr r0, _0806B774 @ =gPlayerParty + 3 * 0x64\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    beq _0806B778\n\
    ldrb r0, [r4, 0x6]\n\
    ldrb r1, [r4, 0x7]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    adds r0, r4, 0x6\n\
    movs r1, 0x3\n\
    b _0806B8A8\n\
    .align 2, 0\n\
_0806B774: .4byte gPlayerParty + 3 * 0x64\n\
_0806B778:\n\
    ldrb r0, [r4, 0x6]\n\
    ldrb r1, [r4, 0x7]\n\
    b _0806B8BC\n\
_0806B77E:\n\
    ldr r0, _0806B798 @ =gPlayerPartyCount\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x3\n\
    bls _0806B79C\n\
    ldrb r0, [r4, 0x6]\n\
    ldrb r1, [r4, 0x7]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    adds r0, r4, 0x6\n\
    movs r1, 0x3\n\
    b _0806B8A8\n\
    .align 2, 0\n\
_0806B798: .4byte gPlayerPartyCount\n\
_0806B79C:\n\
    ldrb r0, [r4, 0x6]\n\
    ldrb r1, [r4, 0x7]\n\
    b _0806B8BC\n\
_0806B7A2:\n\
    bl IsDoubleBattle\n\
    lsls r0, 24\n\
    cmp r0, 0\n\
    bne _0806B7D2\n\
    ldr r0, _0806B7C8 @ =gPlayerPartyCount\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x4\n\
    bls _0806B7CC\n\
    ldrb r0, [r4, 0x8]\n\
    ldrb r1, [r4, 0x9]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    adds r0, r4, 0\n\
    adds r0, 0x8\n\
    movs r1, 0x4\n\
    b _0806B8A8\n\
    .align 2, 0\n\
_0806B7C8: .4byte gPlayerPartyCount\n\
_0806B7CC:\n\
    ldrb r0, [r4, 0x8]\n\
    ldrb r1, [r4, 0x9]\n\
    b _0806B8BC\n\
_0806B7D2:\n\
    bl IsLinkDoubleBattle\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _0806B80A\n\
    ldr r0, _0806B800 @ =gPlayerParty + 4 * 0x64\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    beq _0806B804\n\
    ldrb r0, [r4, 0x8]\n\
    ldrb r1, [r4, 0x9]\n\
    movs r2, 0\n\
    movs r3, 0x4\n\
    bl sub_806BA94\n\
    adds r0, r4, 0\n\
    adds r0, 0x8\n\
    movs r1, 0x4\n\
    movs r2, 0x4\n\
    b _0806B8AA\n\
    .align 2, 0\n\
_0806B800: .4byte gPlayerParty + 4 * 0x64\n\
_0806B804:\n\
    ldrb r0, [r4, 0x8]\n\
    ldrb r1, [r4, 0x9]\n\
    b _0806B884\n\
_0806B80A:\n\
    ldr r0, _0806B828 @ =gPlayerPartyCount\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x4\n\
    bls _0806B82C\n\
    ldrb r0, [r4, 0x8]\n\
    ldrb r1, [r4, 0x9]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    adds r0, r4, 0\n\
    adds r0, 0x8\n\
    movs r1, 0x4\n\
    b _0806B8A8\n\
    .align 2, 0\n\
_0806B828: .4byte gPlayerPartyCount\n\
_0806B82C:\n\
    ldrb r0, [r4, 0x8]\n\
    ldrb r1, [r4, 0x9]\n\
    b _0806B8BC\n\
_0806B832:\n\
    bl IsDoubleBattle\n\
    lsls r0, 24\n\
    cmp r0, 0\n\
    bne _0806B84C\n\
    ldr r0, _0806B848 @ =gPlayerPartyCount\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x5\n\
    bhi _0806B896\n\
    b _0806B8B8\n\
    .align 2, 0\n\
_0806B848: .4byte gPlayerPartyCount\n\
_0806B84C:\n\
    bl IsLinkDoubleBattle\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bne _0806B88E\n\
    ldr r0, _0806B87C @ =gPlayerParty + 5 * 0x64\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    beq _0806B880\n\
    ldrb r0, [r4, 0xA]\n\
    ldrb r1, [r4, 0xB]\n\
    movs r2, 0\n\
    movs r3, 0x4\n\
    bl sub_806BA94\n\
    adds r0, r4, 0\n\
    adds r0, 0xA\n\
    movs r1, 0x5\n\
    movs r2, 0x4\n\
    b _0806B8AA\n\
    .align 2, 0\n\
_0806B87C: .4byte gPlayerParty + 5 * 0x64\n\
_0806B880:\n\
    ldrb r0, [r4, 0xA]\n\
    ldrb r1, [r4, 0xB]\n\
_0806B884:\n\
    movs r2, 0x1\n\
    movs r3, 0x4\n\
    bl sub_806BA94\n\
    b _0806B900\n\
_0806B88E:\n\
    ldr r0, _0806B8B4 @ =gPlayerPartyCount\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x5\n\
    bls _0806B8B8\n\
_0806B896:\n\
    ldrb r0, [r4, 0xA]\n\
    ldrb r1, [r4, 0xB]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    adds r0, r4, 0\n\
    adds r0, 0xA\n\
    movs r1, 0x5\n\
_0806B8A8:\n\
    movs r2, 0x3\n\
_0806B8AA:\n\
    movs r3, 0\n\
    bl sub_806BF24\n\
    b _0806B900\n\
    .align 2, 0\n\
_0806B8B4: .4byte gPlayerPartyCount\n\
_0806B8B8:\n\
    ldrb r0, [r4, 0xA]\n\
    ldrb r1, [r4, 0xB]\n\
_0806B8BC:\n\
    movs r2, 0x1\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    b _0806B900\n\
_0806B8C6:\n\
    ldr r0, _0806B8E4 @ =0x0201b000\n\
    movs r1, 0x96\n\
    lsls r1, 2\n\
    adds r0, r1\n\
    ldrb r0, [r0]\n\
    cmp r0, 0x4\n\
    bne _0806B8DA\n\
    movs r0, 0x1\n\
    bl sub_806BB9C\n\
_0806B8DA:\n\
    movs r0, 0x1\n\
    bl sub_806BBEC\n\
    b _0806B900\n\
    .align 2, 0\n\
_0806B8E4: .4byte 0x0201b000\n\
_0806B8E8:\n\
    ldr r0, _0806B8F8 @ =0x0201b000\n\
    ldr r1, _0806B8FC @ =0x00000261\n\
    adds r0, r1\n\
    movs r1, 0x2\n\
    strb r1, [r0]\n\
    movs r0, 0x1\n\
    b _0806B902\n\
    .align 2, 0\n\
_0806B8F8: .4byte 0x0201b000\n\
_0806B8FC: .4byte 0x00000261\n\
_0806B900:\n\
    movs r0, 0\n\
_0806B902:\n\
    pop {r4,r5}\n\
    pop {r1}\n\
    bx r1\n\
    .syntax divided\n");
}

#ifdef NONMATCHING
void sub_806B908(void)
{
    memset(&gBGTilemapBuffers[2], 0, 0x800);
    gUnknown_0202E8FA = 3;
    sub_806B9A4(gUnknown_083769C0[12], gUnknown_083769C0[13], 3);

    if (GetMonData(&gPlayerParty[1], MON_DATA_SPECIES))
        sub_806BA94(gUnknown_083769C0[16], gUnknown_083769C0[17], 0, 3);
    else
        sub_806BA94(gUnknown_083769C0[16], gUnknown_083769C0[17], 1, 3);

    if (GetMonData(&gPlayerParty[2], MON_DATA_SPECIES))
        sub_806BA94(gUnknown_083769C0[18], gUnknown_083769C0[19], 0, 3);
    else
        sub_806BA94(gUnknown_083769C0[18], gUnknown_083769C0[19], 1, 3);

    ewram1B000.unk261 = 2;
}
#else
__attribute__((naked))
void sub_806B908(void)
{
    asm(".syntax unified\n\
    push {r4,r5,lr}\n\
    ldr r0, _0806B948 @ =gBGTilemapBuffers + 0x1000\n\
    movs r2, 0x80\n\
    lsls r2, 4\n\
    movs r1, 0\n\
    bl memset\n\
    ldr r1, _0806B94C @ =gUnknown_0202E8FA\n\
    movs r0, 0x3\n\
    strb r0, [r1]\n\
    ldr r0, _0806B950 @ =gUnknown_083769A8\n\
    adds r4, r0, 0\n\
    adds r4, 0x24\n\
    ldr r5, _0806B954 @ =gPlayerParty + 1 * 0x64\n\
    ldrb r0, [r4]\n\
    ldrb r1, [r4, 0x1]\n\
    movs r2, 0x3\n\
    bl sub_806B9A4\n\
    adds r0, r5, 0\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    beq _0806B958\n\
    ldrb r0, [r4, 0x4]\n\
    ldrb r1, [r4, 0x5]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    b _0806B964\n\
    .align 2, 0\n\
_0806B948: .4byte gBGTilemapBuffers + 0x1000\n\
_0806B94C: .4byte gUnknown_0202E8FA\n\
_0806B950: .4byte gUnknown_083769A8\n\
_0806B954: .4byte gPlayerParty + 1 * 0x64\n\
_0806B958:\n\
    ldrb r0, [r4, 0x4]\n\
    ldrb r1, [r4, 0x5]\n\
    movs r2, 0x1\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
_0806B964:\n\
    adds r0, r5, 0\n\
    adds r0, 0x64\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    beq _0806B980\n\
    ldrb r0, [r4, 0x6]\n\
    ldrb r1, [r4, 0x7]\n\
    movs r2, 0\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
    b _0806B98C\n\
_0806B980:\n\
    ldrb r0, [r4, 0x6]\n\
    ldrb r1, [r4, 0x7]\n\
    movs r2, 0x1\n\
    movs r3, 0x3\n\
    bl sub_806BA94\n\
_0806B98C:\n\
    ldr r0, _0806B99C @ =0x0201b000\n\
    ldr r1, _0806B9A0 @ =0x00000261\n\
    adds r0, r1\n\
    movs r1, 0x2\n\
    strb r1, [r0]\n\
    pop {r4,r5}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_0806B99C: .4byte 0x0201b000\n\
_0806B9A0: .4byte 0x00000261\n\
    .syntax divided\n");
}
#endif // NONMATCHING

void sub_806B9A4(s16 a, u16 b, u8 c)
{
    u8 i;
    u16 var1 = b * 32;

    for (i = 0; i <= 6; i++)
    {
        u8 j = 0;

        if (a <= 0x1F)
        {
            for (; j <= 10 && a + j <= 0x1F; j++)
            {
                if (a + j >= 0)
                {
                    gBGTilemapBuffers[2][var1 + (i * 32) + (a + j)] = (c << 12) | gUnknown_083769D8[i * 11 + j];
                }
            }
        }
    }
}

void sub_806BA34(s16 a, u16 b)
{
    u8 i;
    u16 var1 = b * 32;

    for (i = 0; i <= 6; i++)
    {
        u8 j = 0;

        if (a <= 0x1F)
        {
            for (; j <= 10 && a + j <= 0x1F; j++)
            {
                if (a + j >= 0)
                {
                    gBGTilemapBuffers[2][var1 + (i * 32) + (a + j)] = 0;
                }
            }
        }
    }
}

void sub_806BA94(s16 a, u16 b, u8 c, u8 d)
{
    u8 i;
    u8 *arr;
    u16 var1;

    arr = gUnknown_08376A5E;
    if (c == 0)
    {
        arr = gUnknown_08376A25;
    }

    var1 = b * 32;


    for (i = 0; i < 3; i++)
    {
        u8 j = 0;

        if (a <= 0x1F)
        {
            while (j <= 0x12 && a + j <= 0x1F)
            {
                if (a + j >= 0)
                {
                    gBGTilemapBuffers[2][var1 + (i * 32) + (a + j)] = (d << 12) | arr[i * 19 + j];
                }

                j++;
            }
        }
    }
}

void sub_806BB3C(s16 a, u16 b)
{
    u8 i;
    u16 var1 = (b * 32);

    for (i = 0; i < 3; i++)
    {
        u8 j = 0;

        if (a <= 0x1F)
        {
            for (; j <= 0x12 && a + j <= 0x1F; j++)
            {
                if (a + j >= 0)
                {
                    gBGTilemapBuffers[2][var1 + (i * 32) + (a + j)] = 0;
                }                
            }
        }
    }
}

void sub_806BB9C(u8 a)
{
    u8 i;
    u16 *vramPtr;
    const u16 arr[12];

    memcpy(&arr, gUnknown_08376CD4, 12 * 2);

    vramPtr = (u16 *)(BG_VRAM + 0x3C30);
    for (i = 0; i < PARTY_SIZE; i++)
    {
        vramPtr[i] = arr[i] + (a << 12);
        vramPtr[i + 0x20] = arr[i + PARTY_SIZE] + (a << 12);
    }
}

void sub_806BBEC(u8 a)
{
    u8 i;
    u16 *vramPtr;
    const u16 arr[12];

    memcpy(&arr, gUnknown_08376CEC, 12 * 2);

    vramPtr = (u16 *)(BG_VRAM + 0x3CB0);
    for (i = 0; i < PARTY_SIZE; i++)
    {
        vramPtr[i] = arr[i] + (a << 12);
        vramPtr[i + 0x20] = arr[i + PARTY_SIZE] + (a << 12);
    }
}

#ifdef NONMATCHING
// The original THUMB is preserving r8 for seemingly no reason. Unsure how to match.
void sub_806BC3C(u8 monIndex, u8 b)
{
    u16 *vramPtr = gUnknown_08376918[IsDoubleBattle()][monIndex];
    u8 i;
    u16 var1;

    for (i = 0, var1 = (b / 7) * 32; i <= PARTY_SIZE; i++)
    {
        u32 offset = i + var1;
        vramPtr[i] = gUnknown_08E9A300[offset] + 0x10C;
        vramPtr[i + 0x20] = gUnknown_08E9A300[offset + 0x20] + 0x10C;
    }
}
#else
__attribute__((naked))
void sub_806BC3C(u8 monIndex, u8 b)
{
    asm(".syntax unified\n\
    push {r4-r7,lr}\n\
    mov r7, r8\n\
    push {r7}\n\
    adds r4, r0, 0\n\
    adds r5, r1, 0\n\
    lsls r4, 24\n\
    lsrs r4, 24\n\
    lsls r5, 24\n\
    lsrs r5, 24\n\
    ldr r6, _0806BCB0 @ =gUnknown_08376918\n\
    bl IsDoubleBattle\n\
    lsls r4, 2\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    lsls r1, r0, 1\n\
    adds r1, r0\n\
    lsls r1, 3\n\
    adds r4, r1\n\
    adds r4, r6\n\
    ldr r7, [r4]\n\
    movs r6, 0\n\
    adds r0, r5, 0\n\
    movs r1, 0x7\n\
    bl __udivsi3\n\
    lsls r0, 24\n\
    lsrs r4, r0, 19\n\
    ldr r5, _0806BCB4 @ =gUnknown_08E9A300\n\
    movs r0, 0x86\n\
    lsls r0, 1\n\
    adds r3, r0, 0\n\
_0806BC7C:\n\
    adds r1, r6, r4\n\
    lsls r2, r6, 1\n\
    adds r2, r7\n\
    lsls r0, r1, 1\n\
    adds r0, r5\n\
    ldrh r0, [r0]\n\
    adds r0, r3, r0\n\
    strh r0, [r2]\n\
    adds r2, 0x40\n\
    adds r1, 0x20\n\
    lsls r1, 1\n\
    adds r1, r5\n\
    ldrh r1, [r1]\n\
    adds r0, r3, r1\n\
    strh r0, [r2]\n\
    adds r0, r6, 0x1\n\
    lsls r0, 24\n\
    lsrs r6, r0, 24\n\
    cmp r6, 0x6\n\
    bls _0806BC7C\n\
    pop {r3}\n\
    mov r8, r3\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_0806BCB0: .4byte gUnknown_08376918\n\
_0806BCB4: .4byte gUnknown_08E9A300\n\
    .syntax divided\n");
}
#endif // NONMATCHING

void unref_sub_806BCB8(u8 a)
{
    u8 i;

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        sub_806BC3C(i, a);
    }
}

void sub_806BCE8()
{
    u8 i;

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        if (!GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
        {
            u8 gender = GetMonGender(&gPlayerParty[i]);
            switch (gender)
            {
            case MON_MALE:
                sub_806BC3C(i, 0x54);
                break;
            case MON_FEMALE:
                sub_806BC3C(i, 0x62);
                break;
            default:
                sub_806BC3C(i, 0x46);
                break;
            }
        }
        else
        {
            sub_806BC3C(i, 0x46);
        }
    }    
}

u8 sub_806BD58(u8 taskId, u8 b)
{
    u8 spriteId = CreateInvisibleSpriteWithCallback(SpriteCallbackDummy);
    sub_806CA18(taskId, spriteId);
    return 1;
}

#ifdef NONMATCHING
u16 sub_806BD80(u8 taskId)
{
    s8 menuDirectionPressed = 0x0;

    switch (gMain.newAndRepeatedKeys)
    {
    case DPAD_UP:
        menuDirectionPressed = 0xFF;
        break;
    case DPAD_DOWN:
        menuDirectionPressed = 0x1;
        break;
    case DPAD_LEFT:
        menuDirectionPressed = 0xFE;
        break;
    case DPAD_RIGHT:
        menuDirectionPressed = 0x2;
        break;
    }

    if (menuDirectionPressed == 0)
    {
        u8 var1 = sub_80F92BC();
        switch (var1)
        {
        case 1:
            menuDirectionPressed = 0xFF;
            break;
        case 2:
            menuDirectionPressed = 0x1;
            break;
        }

        if (menuDirectionPressed == 0)
        {
            if ((gMain.newKeys & A_BUTTON) && gSprites[sub_806CA00(taskId)].data0 == 7)
            {
                // Selected "CANCEL"
                return B_BUTTON;
            }
            else
            {
                return gMain.newKeys & (A_BUTTON | B_BUTTON);
            }
        }
    }

    sub_806BF74(taskId, menuDirectionPressed);
    return gMain.newAndRepeatedKeys;
}
#else
__attribute__((naked))
u16 sub_806BD80(u8 taskId)
{
    asm(".syntax unified\n\
    push {r4,r5,lr}\n\
    lsls r0, 24\n\
    lsrs r5, r0, 24\n\
    movs r4, 0\n\
    ldr r0, _0806BD9C @ =gMain\n\
    ldrh r0, [r0, 0x30]\n\
    cmp r0, 0x20\n\
    beq _0806BDB2\n\
    cmp r0, 0x20\n\
    bgt _0806BDA0\n\
    cmp r0, 0x10\n\
    beq _0806BDB6\n\
    b _0806BDB8\n\
    .align 2, 0\n\
_0806BD9C: .4byte gMain\n\
_0806BDA0:\n\
    cmp r0, 0x40\n\
    beq _0806BDAA\n\
    cmp r0, 0x80\n\
    beq _0806BDAE\n\
    b _0806BDB8\n\
_0806BDAA:\n\
    movs r4, 0xFF\n\
    b _0806BDB8\n\
_0806BDAE:\n\
    movs r4, 0x1\n\
    b _0806BDB8\n\
_0806BDB2:\n\
    movs r4, 0xFE\n\
    b _0806BDB8\n\
_0806BDB6:\n\
    movs r4, 0x2\n\
_0806BDB8:\n\
    lsls r0, r4, 24\n\
    cmp r0, 0\n\
    bne _0806BDDC\n\
    bl sub_80F92BC\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    beq _0806BDD0\n\
    cmp r0, 0x2\n\
    beq _0806BDD4\n\
    b _0806BDD6\n\
_0806BDD0:\n\
    movs r4, 0xFF\n\
    b _0806BDD6\n\
_0806BDD4:\n\
    movs r4, 0x1\n\
_0806BDD6:\n\
    lsls r0, r4, 24\n\
    cmp r0, 0\n\
    beq _0806BDF0\n\
_0806BDDC:\n\
    asrs r1, r0, 24\n\
    adds r0, r5, 0\n\
    bl sub_806BF74\n\
    ldr r0, _0806BDEC @ =gMain\n\
    ldrh r0, [r0, 0x30]\n\
    b _0806BE2C\n\
    .align 2, 0\n\
_0806BDEC: .4byte gMain\n\
_0806BDF0:\n\
    ldr r0, _0806BE1C @ =gMain\n\
    ldrh r1, [r0, 0x2E]\n\
    movs r0, 0x1\n\
    ands r0, r1\n\
    cmp r0, 0\n\
    beq _0806BE24\n\
    ldr r4, _0806BE20 @ =gSprites\n\
    adds r0, r5, 0\n\
    bl sub_806CA00\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    lsls r1, r0, 4\n\
    adds r1, r0\n\
    lsls r1, 2\n\
    adds r1, r4\n\
    movs r2, 0x2E\n\
    ldrsh r0, [r1, r2]\n\
    cmp r0, 0x7\n\
    bne _0806BE24\n\
    movs r0, 0x2\n\
    b _0806BE2C\n\
    .align 2, 0\n\
_0806BE1C: .4byte gMain\n\
_0806BE20: .4byte gSprites\n\
_0806BE24:\n\
    ldr r0, _0806BE34 @ =gMain\n\
    ldrh r1, [r0, 0x2E]\n\
    movs r0, 0x3\n\
    ands r0, r1\n\
_0806BE2C:\n\
    pop {r4,r5}\n\
    pop {r1}\n\
    bx r1\n\
    .align 2, 0\n\
_0806BE34: .4byte gMain\n\
    .syntax divided\n");
}
#endif // NONMATCHING

u16 sub_806BE38(u8 taskId)
{
    u8 menuDirectionPressed = 0x0;

    switch (gMain.newAndRepeatedKeys)
    {
    case DPAD_UP:
        menuDirectionPressed = 0xFF;
        break;
    case DPAD_DOWN:
        menuDirectionPressed = 0x1;
        break;
    case DPAD_LEFT:
        menuDirectionPressed = 0xFE;
        break;
    case DPAD_RIGHT:
        menuDirectionPressed = 0x2;
        break;   
    }

    if (menuDirectionPressed == 0)
    {
        u8 var1 = sub_80F92BC();
        switch (var1)
        {
        case 1:
            menuDirectionPressed = 0xFF;
            break;
        case 2:
            menuDirectionPressed = 0x1;
            break;
        }
    }

    if (gMain.newKeys & START_BUTTON)
    {
        sub_806C890(taskId);
        return START_BUTTON;
    }
    else
    {
        s8 signedMenuDirection = menuDirectionPressed;
        if (signedMenuDirection)
        {
            sub_806C658(taskId, signedMenuDirection);
            return gMain.newAndRepeatedKeys;
        }
        else
        {
            if (gMain.newKeys & A_BUTTON)
            {
                if (gSprites[sub_806CA00(taskId)].data0 == 7)
                {
                    return B_BUTTON;
                }
            }
        }
    }

    return gMain.newKeys & (A_BUTTON | B_BUTTON);
}

void task_pc_turn_off(const u8 *a, u8 b)
{
    if (a[0])
        sub_806BA94(a[0], a[1], 0, b);
    else
        sub_806B9A4(a[0], a[1], b);
}

void sub_806BF24(const u8 *a, u8 monIndex, u8 c, u8 d)
{
    if (GetMonData(&gPlayerParty[monIndex], MON_DATA_SPECIES) && GetMonData(&gPlayerParty[monIndex], MON_DATA_HP) == 0)
        c = PARTY_SIZE - 1;

    if (d == 1)
        c += 4;

    task_pc_turn_off(a, c);
}

void sub_806BF74(u8 taskId, s8 directionPressed)
{
    bool8 isLinkDoubleBattle;
    u8 spriteId = sub_806CA00(taskId);
    u8 menuIndex = gSprites[spriteId].data0;

    UpdateMonIconFrame_806DA44(taskId, menuIndex, 0);
    
    isLinkDoubleBattle = IsLinkDoubleBattle();
    if (isLinkDoubleBattle == 1)
    {
        if (menuIndex == 0 || menuIndex == 2 || menuIndex == 3)
            sub_806BF24(&gUnknown_083769C0[menuIndex * 2], menuIndex, 3, 0);
        if (menuIndex == 1 || menuIndex == 4 || menuIndex == 5)
            sub_806BF24(&gUnknown_083769C0[menuIndex * 2], menuIndex, 4, 0);
        if (menuIndex == 7)
            sub_806BBEC(1);

        sub_806C490(spriteId, menuIndex, directionPressed);

        if (gSprites[spriteId].data0 == 0 || gSprites[spriteId].data0 == 2 || gSprites[spriteId].data0 == 3)
            sub_806BF24(&gUnknown_083769C0[gSprites[spriteId].data0 * 2], gSprites[spriteId].data0, 3, 1);
        if (gSprites[spriteId].data0 == 1 || gSprites[spriteId].data0 == 4 || gSprites[spriteId].data0 == 5)
                sub_806BF24(&gUnknown_083769C0[gSprites[spriteId].data0 * 2], gSprites[spriteId].data0, 4, 1);
        if (gSprites[spriteId].data0 == 7)
            sub_806BBEC(2);

        ewram1B000.unk261 = 2;

        gSprites[spriteId].pos1.x = gUnknown_083768B8[2][gSprites[spriteId].data0].x;
        gSprites[spriteId].pos1.y = gUnknown_083768B8[2][gSprites[spriteId].data0].y;
    }
    else
    {
        u8 isDoubleBattle = IsDoubleBattle();

        if (menuIndex <= PARTY_SIZE - 1)
        {
            sub_806BF24(&gUnknown_083769A8[isDoubleBattle * 12 + menuIndex * 2], menuIndex, 3, 0);
        }
        else
        {
            sub_806BBEC(1);
        }

        if (!isDoubleBattle)
        {
            sub_806C1E4(spriteId, menuIndex, directionPressed);
        }
        else
        {
            sub_806C310(spriteId, menuIndex, directionPressed);
        }

        if (gSprites[spriteId].data0 <= PARTY_SIZE - 1)
        {
            sub_806BF24(&gUnknown_083769A8[isDoubleBattle * 12 + gSprites[spriteId].data0 * 2], gSprites[spriteId].data0, 3, 1);
        }
        else
        {
            sub_806BBEC(2);
        }

        ewram1B000.unk261 = 2;

        gSprites[spriteId].pos1.x = gUnknown_083768B8[isDoubleBattle][gSprites[spriteId].data0].x;
        gSprites[spriteId].pos1.y = gUnknown_083768B8[isDoubleBattle][gSprites[spriteId].data0].y;
    }

    UpdateMonIconFrame_806DA44(taskId, gSprites[spriteId].data0, 1);

    if (menuIndex != gSprites[spriteId].data0)
    {
        PlaySE(5);
    }
}

void sub_806C1E4(u8 spriteId, u8 menuIndex, s8 directionPressed)
{
    u8 var1;
    s8 menuMovement = directionPressed + 2;

    switch (menuMovement)
    {
    case 2:
        gSprites[spriteId].data1 = 0;
        break;
    case 1:
        if (menuIndex == 0) {
            gSprites[spriteId].data0 = 7;
        } else if (menuIndex == 7) {
            gSprites[spriteId].data0 = gPlayerPartyCount - 1;
        } else {
            s8 diff = directionPressed;
            gSprites[spriteId].data0 += diff;
        }

        gSprites[spriteId].data1 = 0;
        break;
    case 3:
        if (menuIndex == gPlayerPartyCount - 1) {
            gSprites[spriteId].data0 = 7;
        } else if (menuIndex == 7) {
            gSprites[spriteId].data0 = 0;
        } else {
            s8 diff = directionPressed;
            gSprites[spriteId].data0 += diff;
        }

        gSprites[spriteId].data1 = 0;
        break;
    case 4:
        if (gPlayerPartyCount > 1 && menuIndex == 0)
        {
            if (gSprites[spriteId].data1 == 0)
                gSprites[spriteId].data1 = 1;

            gSprites[spriteId].data0 = gSprites[spriteId].data1;
        }
        break;
    case 0:
        var1 = menuIndex - 1;
        if (var1 <= 4) {
            gSprites[spriteId].data0 = 0;
            gSprites[spriteId].data1 = menuIndex;
        }
        break;
    }
}

void sub_806C310(u8 spriteId, u8 menuIndex, s8 directionPressed)
{
    u8 var3;
    s8 menuMovement = directionPressed + 2;

    switch(menuMovement)
    {
    case 2:
        gSprites[spriteId].data1 = 0;
        break;
    case 3:
        if (menuIndex == 7) {
            gSprites[spriteId].data0 = 0;
        } else if (menuIndex == gPlayerPartyCount - 1) {
            gSprites[spriteId].data0 = 7;
        } else {
            s8 diff = directionPressed;
            gSprites[spriteId].data0 += diff;
        }

        gSprites[spriteId].data1 = 0;
        break;
    case 1:
        if (menuIndex == 0) {
            gSprites[spriteId].data0 = 7;
        } else if (menuIndex == 7) {
            gSprites[spriteId].data0 = gPlayerPartyCount - 1;
        } else {
            s8 diff = directionPressed;
            gSprites[spriteId].data0 += diff;
        }

        gSprites[spriteId].data1 = 0;
        break;
    case 4:
        if (menuIndex == 0) {
            if (gPlayerPartyCount > 2) {
                u16 var1 = gSprites[spriteId].data1 - 2;
                if (var1 > 1)
                    gSprites[spriteId].data0 = 2;
                else
                    gSprites[spriteId].data0 = gSprites[spriteId].data1;
            }
        }
        else if (menuIndex == 1) {
            if (gPlayerPartyCount > 4) {
                u16 var1 = gSprites[spriteId].data1 - 4;
                if (var1 <= 1)
                    gSprites[spriteId].data0 = gSprites[spriteId].data1;
                else
                    gSprites[spriteId].data0 = 4;
            }
        }
        break;
    case 0:
        var3 = menuIndex - 2;
        if (var3 <= 1) {
            gSprites[spriteId].data0 = 0;
            gSprites[spriteId].data1 = menuIndex;
        } else {
            u8 var2 = menuIndex - 4;
            if (var2 <= 1) {
                gSprites[spriteId].data0 = 1;
                gSprites[spriteId].data1 = menuIndex;
            }
        }
        break;
    }
}

/*void sub_806C490(u8 spriteId, u8 menuIndex, s8 directionPressed)
{
    s8 menuMovement;
    s16 var1;
    u8 var2;

    menuMovement = directionPressed + 2;
    switch (menuMovement)
    {
    case 2:
        gSprites[spriteId].data1 = 0;
        break;
    case 3:
        if (menuIndex == 7) {
            gSprites[spriteId].data0 = 0;
        } else if (menuIndex == PARTY_SIZE - 1) {
            gSprites[spriteId].data0 = 7;
        } else {
            // Put if statment here
            while (menuIndex++ != PARTY_SIZE - 1) {
                if (GetMonData(&gPlayerParty[menuIndex], MON_DATA_SPECIES))
                {
                    gSprites[spriteId].data0 = menuIndex;
                    gSprites[spriteId].data1 = 0;
                    return;
                }
            }

            gSprites[spriteId].data0 = 7;
        }

        gSprites[spriteId].data1 = 0;
        break;
    case 1:
        while (menuIndex-- != 0) {
            if (GetMonData(gPlayerParty[menuIndex], MON_DATA_SPECIES))
            {
                gSprites[spriteId].data0 = menuIndex;
                gSprites[spriteId].data1 = 0;
                return;
            }
        }

        gSprites[spriteId].data0 = 7;
        gSprites[spriteId].data1 = 0;
        break;
    case 4:
        if (menuIndex == 0) {
            var1 = gSprites[spriteId].data1 - 2;
            if (var1 > 1) {
                if (GetMonData(&gPlayerParty[2], MON_DATA_SPECIES)) {
                    gSprites[spriteId].data0 = 2;
                } else if (GetMonData(&gPlayerParty[3], MON_DATA_SPECIES)) {
                    gSprites[spriteId].data0 = 3;
                }
            } else {
                gSprites[spriteId].data0 = 1;
            }
        } else if (menuIndex == 1) {
            var1 = gSprites[spriteId].data1 - 4;
            if (var1 <= 1) {
                gSprites[spriteId].data0 = var1;
            } else {
                if (GetMonData(&gPlayerParty[4], MON_DATA_SPECIES)) {
                    gSprites[spriteId].data0 = 4;
                } else if (GetMonData(&gPlayerParty[5], MON_DATA_SPECIES)) {
                    gSprites[spriteId].data0 = 5;
                }
            }
        }
        break;
    case 0:
        var2 = menuIndex - 2;
        if (var2 <= 1) {
            gSprites[spriteId].data0 = 0;
        } else {
            var2 = menuIndex - 4;
            if (var2 <= 1) {
                gSprites[spriteId].data0 = 1;
            }
        }

        gSprites[spriteId].data1 = menuIndex;
        break;
    }
}*/
__attribute__((naked))
void sub_806C490(u8 spriteId, u8 menuIndex, s8 directionPressed)
{
    asm(".syntax unified\n\
    push {r4-r6,lr}\n\
    lsls r0, 24\n\
    lsrs r5, r0, 24\n\
    lsls r1, 24\n\
    lsrs r4, r1, 24\n\
    lsls r2, 24\n\
    movs r0, 0x80\n\
    lsls r0, 18\n\
    adds r2, r0\n\
    asrs r0, r2, 24\n\
    cmp r0, 0x4\n\
    bls _0806C4AA\n\
    b _0806C64E\n\
_0806C4AA:\n\
    lsls r0, 2\n\
    ldr r1, _0806C4B4 @ =_0806C4B8\n\
    adds r0, r1\n\
    ldr r0, [r0]\n\
    mov pc, r0\n\
    .align 2, 0\n\
_0806C4B4: .4byte _0806C4B8\n\
    .align 2, 0\n\
_0806C4B8:\n\
    .4byte _0806C618\n\
    .4byte _0806C524\n\
    .4byte _0806C4CC\n\
    .4byte _0806C4E0\n\
    .4byte _0806C57C\n\
_0806C4CC:\n\
    ldr r0, _0806C4DC @ =gSprites\n\
    lsls r1, r5, 4\n\
    adds r1, r5\n\
    lsls r1, 2\n\
    adds r1, r0\n\
    movs r0, 0\n\
    strh r0, [r1, 0x30]\n\
    b _0806C64E\n\
    .align 2, 0\n\
_0806C4DC: .4byte gSprites\n\
_0806C4E0:\n\
    cmp r4, 0x7\n\
    bne _0806C4FC\n\
    ldr r2, _0806C4F8 @ =gSprites\n\
    lsls r3, r5, 4\n\
    adds r0, r3, r5\n\
    lsls r0, 2\n\
    adds r0, r2\n\
    movs r1, 0\n\
    strh r1, [r0, 0x2E]\n\
    adds r1, r2, 0\n\
    adds r6, r3, 0\n\
    b _0806C566\n\
    .align 2, 0\n\
_0806C4F8: .4byte gSprites\n\
_0806C4FC:\n\
    lsls r6, r5, 4\n\
    b _0806C518\n\
_0806C500:\n\
    adds r0, r4, 0x1\n\
    lsls r0, 24\n\
    lsrs r4, r0, 24\n\
    movs r0, 0x64\n\
    muls r0, r4\n\
    ldr r1, _0806C520 @ =gPlayerParty\n\
    adds r0, r1\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    bne _0806C528\n\
_0806C518:\n\
    cmp r4, 0x5\n\
    bne _0806C500\n\
    b _0806C558\n\
    .align 2, 0\n\
_0806C520: .4byte gPlayerParty\n\
_0806C524:\n\
    lsls r6, r5, 4\n\
    b _0806C554\n\
_0806C528:\n\
    ldr r1, _0806C534 @ =gSprites\n\
    adds r0, r6, r5\n\
    lsls r0, 2\n\
    adds r0, r1\n\
    strh r4, [r0, 0x2E]\n\
    b _0806C566\n\
    .align 2, 0\n\
_0806C534: .4byte gSprites\n\
_0806C538:\n\
    subs r0, r4, 0x1\n\
    lsls r0, 24\n\
    lsrs r4, r0, 24\n\
    cmp r4, 0x6\n\
    beq _0806C554\n\
    movs r0, 0x64\n\
    muls r0, r4\n\
    ldr r1, _0806C574 @ =gPlayerParty\n\
    adds r0, r1\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    bne _0806C528\n\
_0806C554:\n\
    cmp r4, 0\n\
    bne _0806C538\n\
_0806C558:\n\
    ldr r0, _0806C578 @ =gSprites\n\
    adds r1, r6, r5\n\
    lsls r1, 2\n\
    adds r1, r0\n\
    movs r2, 0x7\n\
    strh r2, [r1, 0x2E]\n\
    adds r1, r0, 0\n\
_0806C566:\n\
    adds r0, r6, r5\n\
    lsls r0, 2\n\
    adds r0, r1\n\
    movs r1, 0\n\
    strh r1, [r0, 0x30]\n\
    b _0806C64E\n\
    .align 2, 0\n\
_0806C574: .4byte gPlayerParty\n\
_0806C578: .4byte gSprites\n\
_0806C57C:\n\
    cmp r4, 0\n\
    bne _0806C5C8\n\
    ldr r0, _0806C5AC @ =gSprites\n\
    lsls r1, r5, 4\n\
    adds r1, r5\n\
    lsls r1, 2\n\
    adds r4, r1, r0\n\
    ldrh r1, [r4, 0x30]\n\
    subs r0, r1, 0x2\n\
    lsls r0, 16\n\
    lsrs r0, 16\n\
    cmp r0, 0x1\n\
    bls _0806C5E2\n\
    ldr r5, _0806C5B0 @ =gPlayerParty + 2 * 0x64\n\
    adds r0, r5, 0\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    beq _0806C5B4\n\
    movs r0, 0x2\n\
    strh r0, [r4, 0x2E]\n\
    b _0806C64E\n\
    .align 2, 0\n\
_0806C5AC: .4byte gSprites\n\
_0806C5B0: .4byte gPlayerParty + 2 * 0x64\n\
_0806C5B4:\n\
    adds r0, r5, 0\n\
    adds r0, 0x64\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    beq _0806C64E\n\
    movs r0, 0x3\n\
    strh r0, [r4, 0x2E]\n\
    b _0806C64E\n\
_0806C5C8:\n\
    cmp r4, 0x1\n\
    bne _0806C64E\n\
    ldr r0, _0806C5E8 @ =gSprites\n\
    lsls r1, r5, 4\n\
    adds r1, r5\n\
    lsls r1, 2\n\
    adds r4, r1, r0\n\
    ldrh r1, [r4, 0x30]\n\
    subs r0, r1, 0x4\n\
    lsls r0, 16\n\
    lsrs r0, 16\n\
    cmp r0, 0x1\n\
    bhi _0806C5EC\n\
_0806C5E2:\n\
    strh r1, [r4, 0x2E]\n\
    b _0806C64E\n\
    .align 2, 0\n\
_0806C5E8: .4byte gSprites\n\
_0806C5EC:\n\
    ldr r5, _0806C600 @ =gPlayerParty + 4 * 0x64\n\
    adds r0, r5, 0\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    beq _0806C604\n\
    movs r0, 0x4\n\
    strh r0, [r4, 0x2E]\n\
    b _0806C64E\n\
    .align 2, 0\n\
_0806C600: .4byte gPlayerParty + 4 * 0x64\n\
_0806C604:\n\
    adds r0, r5, 0\n\
    adds r0, 0x64\n\
    movs r1, 0xB\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    beq _0806C64E\n\
    movs r0, 0x5\n\
    strh r0, [r4, 0x2E]\n\
    b _0806C64E\n\
_0806C618:\n\
    subs r0, r4, 0x2\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bhi _0806C634\n\
    ldr r0, _0806C630 @ =gSprites\n\
    lsls r1, r5, 4\n\
    adds r1, r5\n\
    lsls r1, 2\n\
    adds r1, r0\n\
    movs r0, 0\n\
    b _0806C64A\n\
    .align 2, 0\n\
_0806C630: .4byte gSprites\n\
_0806C634:\n\
    subs r0, r4, 0x4\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    cmp r0, 0x1\n\
    bhi _0806C64E\n\
    ldr r0, _0806C654 @ =gSprites\n\
    lsls r1, r5, 4\n\
    adds r1, r5\n\
    lsls r1, 2\n\
    adds r1, r0\n\
    movs r0, 0x1\n\
_0806C64A:\n\
    strh r0, [r1, 0x2E]\n\
    strh r4, [r1, 0x30]\n\
_0806C64E:\n\
    pop {r4-r6}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_0806C654: .4byte gSprites\n\
    .syntax divided\n");
}


// directionPressed = -2 for left, 2 for right, 1 for down, -1 for up
void sub_806C658(u8 taskId, s8 directionPressed)
{
    u16 newMenuIndex;
    u8 newMenuIndex2;
    u8 newMenuIndex3;
    s8 menuMovement;
    u8 spriteId = sub_806CA00(taskId);
    u8 menuIndex = gSprites[spriteId].data0;

    UpdateMonIconFrame_806DA44(taskId, menuIndex, 0);

    if (menuIndex < PARTY_SIZE)
    {
        sub_806BF24(&gUnknown_083769A8[menuIndex * 2], menuIndex, 3, 0);
    }
    else if (menuIndex == PARTY_SIZE)
    {
        sub_806BB9C(1);
    }
    else
    {
        sub_806BBEC(1);
    }

    menuMovement = directionPressed + 2;

    switch (menuMovement)
    {
    case 2:
        gSprites[spriteId].data1 = 0;
        break;
    case 1:
        if (menuIndex == 0) {
            gSprites[spriteId].data0 = 7;
        } else if (menuIndex == PARTY_SIZE) {
            gSprites[spriteId].data0 = gPlayerPartyCount - 1;
        } else {
            gSprites[spriteId].data0 += directionPressed;
        }

        gSprites[spriteId].data1 = 0;
        break;
    case 3:
        if (menuIndex == gPlayerPartyCount - 1) {
            gSprites[spriteId].data0 = 6;
        } else if (menuIndex == 7) {
            gSprites[spriteId].data0 = 0;
        } else {
            gSprites[spriteId].data0 += directionPressed;
        }

        gSprites[spriteId].data1 = 0;
        break;
    case 4:
        if (gPlayerPartyCount > 1 && menuIndex == 0)
        {
            if (gSprites[spriteId].data1 == 0) {
                gSprites[spriteId].data1 = 1;
            }

            gSprites[spriteId].data0 = gSprites[spriteId].data1;
        }
        break;
    case 0:
        newMenuIndex3 = menuIndex - 1;
        if (newMenuIndex3 <= 4)
        {
            gSprites[spriteId].data0 = 0;
            gSprites[spriteId].data1 = menuIndex;
        }
        break;
    }
    
    gSprites[spriteId].pos1.x = gUnknown_083768B8[0][gSprites[spriteId].data0].x;
    gSprites[spriteId].pos1.y = gUnknown_083768B8[0][gSprites[spriteId].data0].y;


    newMenuIndex = gSprites[spriteId].data0;
    if (gSprites[spriteId].data0 <= PARTY_SIZE - 1)
    {
        sub_806BF24(&gUnknown_083769A8[gSprites[spriteId].data0 * 2], newMenuIndex, 3, 1);
    }
    else if (gSprites[spriteId].data0 == PARTY_SIZE)
    {
        sub_806BB9C(2);
    }
    else
    {
        sub_806BBEC(2);
    }

    ewram1B000.unk261 = 2;

    newMenuIndex2 = gSprites[spriteId].data0;
    UpdateMonIconFrame_806DA44(taskId, newMenuIndex2, 1);

    if (menuIndex != gSprites[spriteId].data0)
    {
        PlaySE(5);
    }
}

void sub_806C890(u8 taskId)
{
    u8 spriteId = sub_806CA00(taskId);

    u8 monIndex = gSprites[spriteId].data0;
    if (monIndex != 6)
    {
        UpdateMonIconFrame_806DA44(taskId, monIndex, 0);

        if (monIndex < PARTY_SIZE)
        {
            sub_806BF24(&gUnknown_083769A8[monIndex * 2], monIndex, 3, 0);
        }
        else
        {
            sub_806BBEC(1);
        }

        gSprites[spriteId].data1 = 0;
        gSprites[spriteId].data0 = 6;
        gSprites[spriteId].pos1.x = gUnknown_083768B8[0][6].x;
        gSprites[spriteId].pos1.y = gUnknown_083768B8[0][6].y;

        sub_806BB9C(2);

        ewram1B000.unk261 = 2;
        PlaySE(5);
    }
}

void sub_806C92C(u8 spriteId)
{
    u8 monIndex1 = gSprites[spriteId].data0;
    u8 monIndex2 = gSprites[spriteId].data1;

    if (!IsDoubleBattle())
    {
        if (monIndex1 < 1) {
            if (monIndex2 < 1) {
                monIndex2 = 1;
            }
        } else {
            if (monIndex2 >= 1) {
                monIndex2 = 0;
            }
        }
    } else {
        if (monIndex1 < 2) {
            if (monIndex2 < 2) {
                monIndex2 = 2;
            }
        } else {
            if (monIndex2 >= 2) {
                monIndex2 = 0;
            }
        }
    }

    gSprites[spriteId].data1 = monIndex2;
}

void sub_806C994(u8 taskId, u8 b)
{
    u8 spriteId = sub_806CA00(taskId);

    gSprites[spriteId].data0 = b;
    sub_806C92C(spriteId);
}

void sub_806C9C4(u8 taskId, u8 spriteId)
{
    u8 spriteId2 = sub_806CA00(taskId);

    gSprites[spriteId].pos1.x = gSprites[spriteId2].pos1.x;
    gSprites[spriteId].pos1.y = gSprites[spriteId2].pos1.y;
    gSprites[spriteId].data0 = gSprites[spriteId2].data0;
}

u8 sub_806CA00(u8 taskId)
{
    return gTasks[taskId].data[3] >> 8;
}

void sub_806CA18(u8 taskId, u8 b)
{
    u8 var1 = gTasks[taskId].data[3];
    gTasks[taskId].data[3] = var1 | (b << 8);
}

u8 sub_806CA38(u8 taskId)
{
    u8 spriteId = sub_806CA00(taskId);
    return gSprites[spriteId].data0;
}

void sub_806CA60(u8 taskId)
{
    gTasks[taskId].func = TaskDummy;
    ewram01000.unk0 = taskId;

    CreateTask(sub_806CB74, 0);
    ewram01000.unk1 = CreateInvisibleSpriteWithCallback(SpriteCallbackDummy);

    sub_806C9C4(taskId, ewram01000.unk1);
    ewram01000.unk2 = sub_806CA00(taskId);

    sub_806D538(ewram1B000_alt.unk272, 0);

    sub_806BF24(&gUnknown_083769A8[gSprites[ewram01000.unk1].data0 * 2], gSprites[ewram01000.unk1].data0, 6, 0);
    ewram1B000.unk261 = 2;
}

void sub_806CAFC(u8 a, s16 b)
{
    struct Sprite *sprite1 = &gSprites[ewram01000.unk1];
    struct Sprite *sprite2 = &gSprites[ewram01000.unk2];

    sub_806BF74(a, b);

    if (sprite1->data0 != sprite2->data0)
    {
        sub_806BF24(&gUnknown_083769A8[sprite1->data0 * 2], sprite1->data0, 6, 1);
    }
    else
    {
        sub_806BF24(&gUnknown_083769A8[sprite1->data0 * 2], sprite1->data0, 6, 0);
    }
}

void sub_806CB74(u8 taskId)
{
    switch (gMain.newAndRepeatedKeys)
    {
    case DPAD_UP:
        sub_806CAFC(ewram01000.unk0, -1);
        break;
    case DPAD_DOWN:
        sub_806CAFC(ewram01000.unk0, 1);
        break;
    case DPAD_LEFT:
        sub_806CAFC(ewram01000.unk0, -2);
        break;
    case DPAD_RIGHT:
        sub_806CAFC(ewram01000.unk0, 2);
        break;
    }

    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(5);
        gTasks[taskId].func = ewram01000.unkC;
        gTasks[taskId].func(taskId);
    }
    else if (gMain.newKeys == B_BUTTON)
    {
        PlaySE(5);
        sub_806CD44(taskId);
    }
}

void sub_806CC2C(u8 taskId)
{
    DestroySprite(&gSprites[ewram01000.unk1]);
    sub_806D538(0, 0);

    ewram1B000.unk261 = 2;
    SwitchTaskToFollowupFunc(ewram01000.unk0);
    DestroyTask(taskId);
}

void sub_806CC74(u8 taskId)
{
    sub_806BF24(&gUnknown_083769A8[gSprites[ewram01000.unk2].data0 * 2], gSprites[ewram01000.unk2].data0, 3, 1);
    sub_806BF24(&gUnknown_083769A8[gSprites[ewram01000.unk1].data0 * 2], gSprites[ewram01000.unk1].data0, 3, 0);
    sub_806CC2C(taskId);
}

void sub_806CCE4()
{
    u8 monIndex1 = gSprites[ewram01000.unk1].data0;
    u8 monIndex2 = gSprites[ewram01000.unk2].data0;

    if (monIndex1 <= 5)
    {
        sub_806BF24(&gUnknown_083769A8[monIndex1 * 2], monIndex1, 3, 0);
    }

    if (monIndex2 <= 5)
    {
        sub_806BF24(&gUnknown_083769A8[monIndex2 * 2], monIndex2, 3, 1);
    }
}

void sub_806CD44(u8 taskId)
{
    sub_806CCE4();
    sub_806CC2C(taskId);
}

void sub_806CD5C(u8 taskId)
{
    u8 monIndex1 = gSprites[ewram01000.unk1].data0;
    u8 monIndex2 = gSprites[ewram01000.unk2].data0;

    if (monIndex1 == monIndex2 || monIndex1 == 7 || monIndex2 == 7)
    {
        sub_806CD44(taskId);
    }
    else
    {
        u8 var1;

        sub_806D5B8(monIndex1);
        sub_806D5B8(monIndex2);

        if (monIndex1 > monIndex2)
        {
            ewram01000.unk5 = monIndex2;
            ewram01000.unk6 = monIndex1;
        }
        else
        {
            ewram01000.unk5 = monIndex1;
            ewram01000.unk6 = monIndex2;
        }

        ewram01000.unk3 = GetMonIconSpriteId_maybe(ewram01000.unk0, ewram01000.unk5);
        ewram01000.unk4 = GetMonIconSpriteId_maybe(ewram01000.unk0, ewram01000.unk6);

        var1 = ewram01000.unk5;
        if (!var1)
        {
            gSprites[ewram01000.unk3].data0 = -8;
            gSprites[ewram01000.unk3].data2 = -0xA8;
            ewram01000.unk8 = var1;
            ewram01000.unkA = 11;

            gTasks[taskId].func = sub_806D014;
            ewram1B000.unk261 = 1;
        }
        else
        {
            gSprites[ewram01000.unk3].data0 = 8;
            gSprites[ewram01000.unk3].data2 = 0xA8;
            ewram01000.unk8 = 11;
            ewram01000.unkA = 11;

            gTasks[taskId].func = sub_806D118;
            ewram1B000.unk261 = 1;
        }

        gSprites[ewram01000.unk3].callback = SpriteCB_sub_806D37C;

        gSprites[ewram01000.unk4].data0 = 8;
        gSprites[ewram01000.unk4].data2 = 0xA8;
        gSprites[ewram01000.unk4].callback = SpriteCB_sub_806D37C;

        gSprites[ewram01000.unk3].callback(&gSprites[ewram01000.unk3]);
        gSprites[ewram01000.unk4].callback(&gSprites[ewram01000.unk4]);
    }
}

void sub_806CEF8(s16 *x, s16 *y)
{
    s16 temp = *x;
    *x = *y;
    *y = temp;
}

#ifdef NONMATCHING
void sub_806CF04(void)
{
    sub_806CEF8(&gSprites[ewram01000.unk3].pos1.x, &gSprites[ewram01000.unk4].pos1.x);
    sub_806CEF8(&gSprites[ewram01000.unk3].pos1.y, &gSprites[ewram01000.unk4].pos1.y);
    sub_806CEF8(&gSprites[ewram01000.unk3].pos2.x, &gSprites[ewram01000.unk4].pos2.x);
    sub_806CEF8(&gSprites[ewram01000.unk3].data0, &gSprites[ewram01000.unk4].data0);

    gSprites[ewram01000.unk3].callback = SpriteCB_sub_806D37C;
    gSprites[ewram01000.unk4].callback = SpriteCB_sub_806D37C;
}
#else
__attribute__((naked))
void sub_806CF04(void)
{
    asm(".syntax unified\n\
    push {r4,r5,lr}\n\
    ldr r4, _0806CF94 @ =0x02001000\n\
    ldrb r1, [r4, 0x3]\n\
    lsls r0, r1, 4\n\
    adds r0, r1\n\
    lsls r0, 2\n\
    ldr r5, _0806CF98 @ =gSprites + 0x20\n\
    adds r0, r5\n\
    ldrb r2, [r4, 0x4]\n\
    lsls r1, r2, 4\n\
    adds r1, r2\n\
    lsls r1, 2\n\
    adds r1, r5\n\
    bl sub_806CEF8\n\
    ldrb r1, [r4, 0x3]\n\
    lsls r0, r1, 4\n\
    adds r0, r1\n\
    lsls r0, 2\n\
    adds r3, r5, 0x2\n\
    adds r0, r3\n\
    ldrb r2, [r4, 0x4]\n\
    lsls r1, r2, 4\n\
    adds r1, r2\n\
    lsls r1, 2\n\
    adds r1, r3\n\
    bl sub_806CEF8\n\
    ldrb r1, [r4, 0x3]\n\
    lsls r0, r1, 4\n\
    adds r0, r1\n\
    lsls r0, 2\n\
    adds r3, r5, 0x4\n\
    adds r0, r3\n\
    ldrb r2, [r4, 0x4]\n\
    lsls r1, r2, 4\n\
    adds r1, r2\n\
    lsls r1, 2\n\
    adds r1, r3\n\
    bl sub_806CEF8\n\
    ldrb r1, [r4, 0x3]\n\
    lsls r0, r1, 4\n\
    adds r0, r1\n\
    lsls r0, 2\n\
    adds r3, r5, 0\n\
    adds r3, 0xE\n\
    adds r0, r3\n\
    ldrb r2, [r4, 0x4]\n\
    lsls r1, r2, 4\n\
    adds r1, r2\n\
    lsls r1, 2\n\
    adds r1, r3\n\
    bl sub_806CEF8\n\
    ldrb r1, [r4, 0x3]\n\
    lsls r0, r1, 4\n\
    adds r0, r1\n\
    lsls r0, 2\n\
    subs r5, 0x4\n\
    adds r0, r5\n\
    ldr r2, _0806CF9C @ =SpriteCB_sub_806D37C\n\
    str r2, [r0]\n\
    ldrb r1, [r4, 0x4]\n\
    lsls r0, r1, 4\n\
    adds r0, r1\n\
    lsls r0, 2\n\
    adds r0, r5\n\
    str r2, [r0]\n\
    pop {r4,r5}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_0806CF94: .4byte 0x02001000\n\
_0806CF98: .4byte gSprites + 0x20\n\
_0806CF9C: .4byte SpriteCB_sub_806D37C\n\
    .syntax divided\n");
}
#endif // NONMATCHING

void sub_806CFA0(u8 taskId, u8 b)
{
    u8 var1 = ((ewram01000.unk6 - 1) * 3) + 1;

    sub_806BA34(ewram01000.unk8, 3);
    sub_806BB3C(ewram01000.unkA, var1);

    if (!b)
    {
        ewram01000.unk8--;
        ewram01000.unkA++;
    }
    else
    {
        ewram01000.unk8++;
        ewram01000.unkA--;
    }

    sub_806B9A4(ewram01000.unk8, 3, 10);
    sub_806BA94(ewram01000.unkA, var1, 0, 10);
}

void sub_806D014(u8 taskId)
{
    sub_806CFA0(taskId, 0);

    if (ewram01000.unk8 < -13 && ewram01000.unkA > 32)
    {
        sub_806CF04();
        gTasks[taskId].func = sub_806D05C;
    }
}

void sub_806D05C(u8 taskId)
{
    sub_806CFA0(taskId, 1);

    if (ewram01000.unk8 == 0 && ewram01000.unkA == 11)
    {
        gTasks[taskId].func = sub_806D198;
    }
}

void sub_806D098(u8 a, u8 b)
{
    u8 var1 = ((ewram01000.unk5 - 1) * 3) + 1;
    u8 var2 = ((ewram01000.unk6 - 1) * 3) + 1;

    sub_806BB3C(ewram01000.unk8, var1);
    sub_806BB3C(ewram01000.unkA, var2);

    if (!b)
    {
        ewram01000.unk8++;
        ewram01000.unkA++;
    }
    else
    {
        ewram01000.unk8--;
        ewram01000.unkA--;
    }

    sub_806BA94(ewram01000.unk8, var1, 0, 10);
    sub_806BA94(ewram01000.unkA, var2, 0, 10);
}

void sub_806D118(u8 taskId)
{
    sub_806D098(taskId, 0);

    if (ewram01000.unk8 > 32 && ewram01000.unkA > 32)
    {
        sub_806CF04();
        gTasks[taskId].func = sub_806D15C;
    }
}

void sub_806D15C(u8 taskId)
{
    sub_806D098(taskId, 1);

    if (ewram01000.unk8 == 11 && ewram01000.unkA == 11)
    {
        gTasks[taskId].func = sub_806D198;
    }
}

void sub_806D198(u8 taskId)
{
    u8 spriteId;

    SetMonIconSpriteId_maybe(ewram01000.unk0, ewram01000.unk5, ewram01000.unk4);
    SetMonIconSpriteId_maybe(ewram01000.unk0, ewram01000.unk6, ewram01000.unk3);

    gSprites[ewram01000.unk3].pos1.x = gUnknown_08376678[IsDoubleBattle()][ewram01000.unk6].x;
    gSprites[ewram01000.unk3].pos1.y = gUnknown_08376678[IsDoubleBattle()][ewram01000.unk6].y;
    gSprites[ewram01000.unk3].pos2.x = 0;
    gSprites[ewram01000.unk3].pos2.y = 0;
    gSprites[ewram01000.unk3].callback = UpdateMonIconFrame_806DA38;

    gSprites[ewram01000.unk4].pos1.x = gUnknown_08376678[IsDoubleBattle()][ewram01000.unk5].x;
    gSprites[ewram01000.unk4].pos1.y = gUnknown_08376678[IsDoubleBattle()][ewram01000.unk5].y;
    gSprites[ewram01000.unk4].pos2.x = 0;
    gSprites[ewram01000.unk4].pos2.y = 0;
    gSprites[ewram01000.unk4].callback = UpdateMonIconFrame_806DA38;

    spriteId = GetMonIconSpriteId_maybe(ewram01000.unk0, gSprites[ewram01000.unk2].data0);
    gSprites[spriteId].callback = UpdateMonIconFrame_806DA0C;

    SwapPokemon(&gPlayerParty[ewram01000.unk5], &gPlayerParty[ewram01000.unk6]);

    PartyMenuPrintMonLevelOrStatus(ewram01000.unk5, &gPlayerParty[ewram01000.unk5]);
    TryPrintPartyMenuMonNickname(ewram01000.unk5, &gPlayerParty[ewram01000.unk5]);
    PartyMenuTryPrintHP(ewram01000.unk5, &gPlayerParty[ewram01000.unk5]);
    nullsub_12(ewram01000.unk5, &gPlayerParty[ewram01000.unk5]);

    PartyMenuPrintMonLevelOrStatus(ewram01000.unk6, &gPlayerParty[ewram01000.unk6]);
    TryPrintPartyMenuMonNickname(ewram01000.unk6, &gPlayerParty[ewram01000.unk6]);
    PartyMenuTryPrintHP(ewram01000.unk6, &gPlayerParty[ewram01000.unk6]);
    nullsub_12(ewram01000.unk6, &gPlayerParty[ewram01000.unk6]);

    PartyMenuDrawHPBars();
    sub_806CC74(taskId);
}

void SpriteCB_sub_806D37C(struct Sprite *sprite)
{
    UpdateMonIconFrame(sprite);

    if (sprite->pos2.x == sprite->data2)
    {
        sprite->data0 *= -1;
        sprite->data2 = 0;
        sprite->callback = UpdateMonIconFrame_806DA38;
    }
    else
    {
        sprite->pos2.x += sprite->data0;
    }
}

void sub_806D3B4(u8 taskId, u16 species1, u16 species2)
{
    const u8 *var1 = gUnknown_083769C0;

    sub_806BA34(var1[2] + gTasks[taskId].data[0], var1[3]);
    sub_806BB3C(var1[8] + gTasks[taskId].data[0], var1[9]);
    sub_806BB3C(var1[10] + gTasks[taskId].data[0], var1[11]);

    gTasks[taskId].data[0]--;

    sub_806B9A4(var1[2] + gTasks[taskId].data[0], var1[3], 4);

    if (species1)
    {
        sub_806BA94(var1[8] + gTasks[taskId].data[0], var1[9], 0, 4);
    }
    else
    {
        sub_806BA94(var1[8] + gTasks[taskId].data[0], var1[9], 1, 4);
    }

    if (species2)
    {
        sub_806BA94(var1[10] + gTasks[taskId].data[0], var1[11], 0, 4);
    }
    else
    {
        sub_806BA94(var1[10] + gTasks[taskId].data[0], var1[11], 1, 4);
    }
}

void sub_806D4AC(u8 taskId, u16 species, u8 c)
{
    if (species)
    {
        u8 monIndex = c + 3;
        u8 spriteId = GetMonIconSpriteId_maybe(taskId, monIndex);

        gSprites[spriteId].data0 = -8;
        gSprites[spriteId].data2 = gTasks[taskId].data[0] * -8;
        gSprites[spriteId].callback = SpriteCB_sub_806D37C;
    }
}

void sub_806D50C(u8 taskId, u8 monIndex)
{
    gSprites[GetMonIconSpriteId_maybe(taskId, monIndex)].pos1.x += 0xF0;
}

void sub_806D538(u8 textId, u8 b)
{
    if (textId != 0xFF)
    {
        switch (b)
        {
        case 0:
            MenuDrawTextWindow(0, 16, 23, 19);
            break;
        case 1:
            MenuDrawTextWindow(0, 16, 19, 19);
            break;
        case 2:
            MenuDrawTextWindow(0, 16, 22, 19);
            break;
        case 3:
            MenuDrawTextWindow(0, 16, 18, 19);
            break;
        }

        MenuPrint(gUnknown_08376624[textId], 1, 17);
    }
}

void sub_806D5A4(void)
{
    MenuZeroFillWindowRect(0, 16, 29, 19);
}

void sub_806D5B8(u8 monIndex)
{
    u32 var1;
    u8 left = gUnknown_08376948[IsDoubleBattle()][monIndex].left;
    u8 top = gUnknown_08376948[IsDoubleBattle()][monIndex].top;
    u8 right = gUnknown_08376948[IsDoubleBattle()][monIndex].right;
    u8 bottom = gUnknown_08376948[IsDoubleBattle()][monIndex].bottom;

    ZeroFillWindowRect(&gUnknown_03004210, left, top, right, bottom);

    var1 = 0;
    CpuFastSet(&var1, (void *)(OBJ_VRAM1 + monIndex * 0x400), 0x1000100);
}

void sub_806D668(u8 monIndex)
{
    u32 var1;
    u8 left = gUnknown_08376978[IsDoubleBattle()][monIndex].left;
    u8 top = gUnknown_08376978[IsDoubleBattle()][monIndex].top;
    u8 right = gUnknown_08376978[IsDoubleBattle()][monIndex].right;
    u8 bottom = gUnknown_08376978[IsDoubleBattle()][monIndex].bottom;

    ZeroFillWindowRect(&gUnknown_03004210, left, top, right, bottom);

    var1 = 0;
    CpuFastSet(&var1, (void *)(OBJ_VRAM1 + 0x300 + monIndex * 0x400), 0x1000040);
}

u8 LoadPartyMenuGraphics(u8 a)
{
    u16 palette = 0x7FFF;
    u8 retVal = 0;

    if (a < 2)
    {
        LZDecompressVram(gPartyMenuMisc_Gfx, (void *)BG_VRAM);
    }

    if (a == 2 || a == 0)
    {
        LZDecompressVram(gPartyMenuMisc_Tilemap, (void *)(BG_VRAM + 0x3800));
    }

    if (a == 3 || a == 0)
    {
        LoadCompressedPalette(gPartyMenuMisc_Pal, 0, 0x160);
    }

    if (a == 4 || a == 0)
    {
        LoadPalette(&palette, 0, 2);
        LoadPalette(gFontDefaultPalette, 0xF0, 0x20);
    }

    if (a == 5 || a == 0)
    {
        LZDecompressVram(gPartyMenuHpBar_Gfx, (void *)(BG_VRAM + 0x6000));
    }

    if (a == 6 || a == 0)
    {
        LZDecompressVram(gPartyMenuOrderText_Gfx, (void *)(BG_VRAM + 0x6180));
    }

    if (a == 7 || a == 0)
    {
        LZDecompressVram(gStatusGfx_Icons, (void *)(BG_VRAM + 0x7180));
    }

    if (a == 8 || a == 0)
    {
        LoadCompressedPalette(gStatusPal_Icons, 0xB0, 0x20);
        retVal = 1;
    }

    return retVal;
}

void SetMonIconAnimByHP(u8 spriteId, u16 currentHP, u16 maxHP)
{
    u8 hpBarLevel = GetHPBarLevel(currentHP, maxHP);
    u8 animNum = 0;

    if (currentHP != maxHP)
    {
        if (hpBarLevel == 3)
        {
            animNum = 1;
        }
        else if (hpBarLevel == 2)
        {
            animNum = 2;
        }
        else if (hpBarLevel == 1)
        {
            animNum = 3;
        }
        else
        {
            animNum = 4;
        }
    }

    sub_809D824(&gSprites[spriteId], animNum);
}

void SetMonIconAnim(u8 spriteId, struct Pokemon *pokemon)
{
    u16 currentHP = GetMonData(pokemon, MON_DATA_HP);
    u16 maxHP = GetMonData(pokemon, MON_DATA_MAX_HP);

    SetMonIconAnimByHP(spriteId, currentHP, maxHP);
}

void CreatePartyMenuMonIcon(u8 taskId, u8 monIndex, u8 c, struct Pokemon *pokemon)
{
    u8 x = gUnknown_08376678[c][monIndex].x;
    u8 y = gUnknown_08376678[c][monIndex].y;

    u16 species2 = GetMonData(pokemon, MON_DATA_SPECIES2);
    u32 personality = GetMonData(pokemon, MON_DATA_PERSONALITY);

    u8 spriteId = CreateMonIcon(species2, sub_809D62C, x, y, 5, personality);
    SetMonIconSpriteId_maybe(taskId, monIndex, spriteId);
    SetMonIconAnim(spriteId, pokemon);
}

void TryCreatePartyMenuMonIcon(u8 a, u8 monIndex, struct Pokemon *pokemon)
{
    if (GetMonData(pokemon, MON_DATA_SPECIES))
    {
        bool8 isLinkDoubleBattle = IsLinkDoubleBattle();
        if (isLinkDoubleBattle == TRUE)
        {
            CreatePartyMenuMonIcon(a, monIndex, 2, pokemon);
        }
        else
        {
            CreatePartyMenuMonIcon(a, monIndex, IsDoubleBattle(), pokemon);
        }
    }
}

void unref_sub_806D964(u8 a)
{
    u8 i;
    for (i = 0; i < gPlayerPartyCount; i++)
    {
        TryCreatePartyMenuMonIcon(a, i, &gPlayerParty[i]);
    }
}

void CreateMonIcon_806D99C(u8 taskId, u8 monIndex, u8 c, struct UnknownPokemonStruct2 *d)
{
    u8 x = gUnknown_08376678[c][monIndex].x;
    u8 y = gUnknown_08376678[c][monIndex].y;

    u8 spriteId = CreateMonIcon(d->species, sub_809D62C, x, y, 5, d->personality);
    SetMonIconSpriteId_maybe(taskId, monIndex, spriteId);
    SetMonIconAnimByHP(spriteId, d->hp, d->maxhp);
}

void UpdateMonIconFrame_806DA0C(struct Sprite *sprite)
{
    u8 var1;

    var1 = UpdateMonIconFrame(sprite);
    if (var1)
    {
        if (var1 & 1)
        {
            sprite->pos2.y = -3;
        }
        else
        {
            sprite->pos2.y = 1;
        }
    }
}

void UpdateMonIconFrame_806DA38(struct Sprite *sprite)
{
    UpdateMonIconFrame(sprite);
}

void UpdateMonIconFrame_806DA44(u8 taskId, u8 monIndex, u8 c)
{
    u8 spriteId;

    if (monIndex < PARTY_SIZE)
    {
        spriteId = GetMonIconSpriteId_maybe(taskId, monIndex);
        gSprites[spriteId].pos2.y = 0;
        gSprites[spriteId].data0 = 0;

        if (!c)
        {
            gSprites[spriteId].callback = UpdateMonIconFrame_806DA38;
        }
        else
        {
            gSprites[spriteId].callback = UpdateMonIconFrame_806DA0C;
        }
    }
}

void LoadHeldItemIconGraphics(void)
{
    LoadSpriteSheet(&gUnknown_083765DC);
    LoadSpritePalette(&gUnknown_083765E4);
}

void SpriteCB_HeldItemIcon(struct Sprite *sprite)
{

    u8 data7 = sprite->data7;
    if (gSprites[data7].invisible)
    {
        sprite->invisible = 1;
    }
    else
    {
        sprite->invisible = 0;
        sprite->pos1.x = gSprites[data7].pos1.x + gSprites[data7].pos2.x;
        sprite->pos1.y = gSprites[data7].pos1.y + gSprites[data7].pos2.y;
    }
}

void CreateHeldItemIcon(u8 a, u8 b)
{
    u8 subPriority;
    u8 spriteId;

    subPriority = gSprites[a].subpriority;
    spriteId = CreateSprite(gSpriteTemplate_837660C, 0xFA, 0xAA, subPriority - 1);

    gSprites[spriteId].pos2.x = 4;
    gSprites[spriteId].pos2.y = 10;
    gSprites[spriteId].callback = SpriteCB_HeldItemIcon;
    gSprites[spriteId].data7 = a;

    StartSpriteAnim(&gSprites[spriteId], b);
    gSprites[spriteId].callback(&gSprites[spriteId]);
}

void CreateHeldItemIcons(u8 *a, u8 *b, u8 c)
{
    u16 i;
    u16 heldItem;

    switch (c)
    {
    case 0:
        i = 0;
        while (i < a[0])
        {
            heldItem = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
            if (heldItem)
            {
                CreateHeldItemIcon(b[i], ItemIsMail(heldItem));
            }

            i++;
        }
        break;
    case 1:
        i = 0;
        while (i < a[1])
        {
            heldItem = GetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM);
            if (heldItem)
            {
                CreateHeldItemIcon(b[i + 6], ItemIsMail(heldItem));
            }

            i++;
        }
        break;
    }
}

void CreateHeldItemIcons_806DC34(u8 taskId)
{
    u8 i;
    u8 monIconSpriteId;
    u8 heldItemSpriteId;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES))
        {
            monIconSpriteId = GetMonIconSpriteId_maybe(taskId, i);
            heldItemSpriteId = CreateSprite(gSpriteTemplate_837660C, 0xFA, 0xAA, 4);

            gSprites[heldItemSpriteId].pos2.x = 4;
            gSprites[heldItemSpriteId].pos2.y = 10;
            gSprites[heldItemSpriteId].data7 = monIconSpriteId;
            gSprites[monIconSpriteId].data7 = heldItemSpriteId;

            SetHeldItemIconVisibility(taskId, i);
            gSprites[heldItemSpriteId].callback(&gSprites[heldItemSpriteId]);
        }
    }
}

#ifdef NONMATCHING
void CreateHeldItemIcon_806DCD4(int taskId, u8 monIndex, int item)
{
    u8 monIconSpriteId;
    u8 heldItemSpriteId;

    monIconSpriteId = GetMonIconSpriteId_maybe(taskId, monIndex);
    heldItemSpriteId = CreateSprite(gSpriteTemplate_837660C, 0xFA, 0xAA, 4);

    gSprites[heldItemSpriteId].pos2.x = 4;
    gSprites[heldItemSpriteId].pos2.y = 10;
    gSprites[heldItemSpriteId].data7 = monIconSpriteId;
    gSprites[monIconSpriteId].data7 = heldItemSpriteId;

    if (!item)
    {
        gSprites[heldItemSpriteId].invisible = 1;
    }
    else
    {
        if (ItemIsMail(item))
        {
            StartSpriteAnim(&gSprites[heldItemSpriteId], 1);
        }
        else
        {
            StartSpriteAnim(&gSprites[heldItemSpriteId], 0);
        }

        gSprites[heldItemSpriteId].invisible = 0;
    }

    gSprites[heldItemSpriteId].callback(&gSprites[heldItemSpriteId]);
}
#else
__attribute__((naked))
void CreateHeldItemIcon_806DCD4(u8 a, u8 monIndex)
{
    asm(".syntax unified\n\
    push {r4-r7,lr}\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    lsls r1, 24\n\
    lsrs r1, 24\n\
    lsls r2, 16\n\
    lsrs r7, r2, 16\n\
    bl GetMonIconSpriteId_maybe\n\
    adds r4, r0, 0\n\
    lsls r4, 24\n\
    lsrs r4, 24\n\
    ldr r0, _0806DD2C @ =gSpriteTemplate_837660C\n\
    movs r1, 0xFA\n\
    movs r2, 0xAA\n\
    movs r3, 0x4\n\
    bl CreateSprite\n\
    lsls r0, 24\n\
    lsrs r6, r0, 24\n\
    ldr r1, _0806DD30 @ =gSprites\n\
    lsls r0, r6, 4\n\
    adds r0, r6\n\
    lsls r0, 2\n\
    adds r5, r0, r1\n\
    movs r0, 0x4\n\
    strh r0, [r5, 0x24]\n\
    movs r0, 0xA\n\
    strh r0, [r5, 0x26]\n\
    strh r4, [r5, 0x3C]\n\
    lsls r0, r4, 4\n\
    adds r0, r4\n\
    lsls r0, 2\n\
    adds r0, r1\n\
    strh r6, [r0, 0x3C]\n\
    cmp r7, 0\n\
    bne _0806DD34\n\
    adds r0, r5, 0\n\
    adds r0, 0x3E\n\
    ldrb r1, [r0]\n\
    movs r2, 0x4\n\
    orrs r1, r2\n\
    strb r1, [r0]\n\
    b _0806DD5C\n\
    .align 2, 0\n\
_0806DD2C: .4byte gSpriteTemplate_837660C\n\
_0806DD30: .4byte gSprites\n\
_0806DD34:\n\
    adds r0, r7, 0\n\
    bl ItemIsMail\n\
    lsls r0, 24\n\
    cmp r0, 0\n\
    beq _0806DD46\n\
    adds r0, r5, 0\n\
    movs r1, 0x1\n\
    b _0806DD4A\n\
_0806DD46:\n\
    adds r0, r5, 0\n\
    movs r1, 0\n\
_0806DD4A:\n\
    bl StartSpriteAnim\n\
    adds r2, r5, 0\n\
    adds r2, 0x3E\n\
    ldrb r1, [r2]\n\
    movs r0, 0x5\n\
    negs r0, r0\n\
    ands r0, r1\n\
    strb r0, [r2]\n\
_0806DD5C:\n\
    ldr r2, _0806DD78 @ =gSprites\n\
    lsls r0, r6, 4\n\
    adds r0, r6\n\
    lsls r0, 2\n\
    adds r1, r2, 0\n\
    adds r1, 0x1C\n\
    adds r1, r0, r1\n\
    adds r0, r2\n\
    ldr r1, [r1]\n\
    bl _call_via_r1\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_0806DD78: .4byte gSprites\n\
    .syntax divided\n");
}
#endif // NONMATCHING

void SpriteCB_UpdateHeldItemIconPosition(struct Sprite *sprite)
{
    u8 spriteId = sprite->data7;

    sprite->pos1.x = gSprites[spriteId].pos1.x + gSprites[spriteId].pos2.x;
    sprite->pos1.y = gSprites[spriteId].pos1.y;
}

u8 GetMonIconSpriteId_maybe(u8 taskId, u8 monIndex)
{
    switch (monIndex)
    {
        case 1:
            return gTasks[taskId].data[0]; 
            break;
        case 2:
            return gTasks[taskId].data[1] >> 8;
            break;
        case 3:
            return gTasks[taskId].data[1];
            break;
        case 4:
            return gTasks[taskId].data[2] >> 8;
            break;
        case 5:
            return gTasks[taskId].data[2];
            break;
        case 0:
        default:
            return gTasks[taskId].data[0] >> 8;
            break;
    }
}

void SetMonIconSpriteId_maybe(u8 taskId, u8 monIndex, u8 spriteId)
{
    switch (monIndex)
    {
        case 0:
            gTasks[taskId].data[0] = (u8)gTasks[taskId].data[0] | (spriteId << 8);
            break;
        case 1:
            gTasks[taskId].data[0] = (gTasks[taskId].data[0] & -0x100) | spriteId;
            break;
        case 2:
            gTasks[taskId].data[1] = (u8)gTasks[taskId].data[1] | (spriteId << 8);
            break;
        case 3:
            gTasks[taskId].data[1] = (gTasks[taskId].data[1] & -0x100) | spriteId;
            break;
        case 4:
            gTasks[taskId].data[2] = (u8)gTasks[taskId].data[2] | (spriteId << 8);
            break;
        case 5:
            gTasks[taskId].data[2] = (gTasks[taskId].data[2] & -0x100) | spriteId;
            break;
    }
}

u16 GetHeldItemIconSpriteIdByMon_maybe(u8 taskId, u8 monIndex)
{
    u8 spriteId = GetMonIconSpriteId_maybe(taskId, monIndex);
    u8 retVal = gSprites[spriteId].data7;
    return retVal;
}

#ifdef NONMATCHING
void SetHeldItemIconVisibility(u8 taskId, u8 monIndex)
{
    u8 spriteId;
    u16 heldItem;

    spriteId = GetHeldItemIconSpriteIdByMon_maybe(taskId, monIndex);
    if (!GetMonData(&gPlayerParty[monIndex], MON_DATA_HELD_ITEM))
    {
        gSprites[spriteId].invisible = 1;
    }
    else
    {
        struct Sprite *sprite;

        heldItem = GetMonData(&gPlayerParty[monIndex], MON_DATA_HELD_ITEM);
        sprite = &gSprites[spriteId];
        if (ItemIsMail(heldItem))
        {
            StartSpriteAnim(sprite, 1);
        }
        else
        {
            StartSpriteAnim(sprite, 0);
        }

        sprite->invisible = 0;
    }
}
#else
__attribute__((naked))
void SetHeldItemIconVisibility(u8 a, u8 monIndex)
{
    asm(".syntax unified\n\
    push {r4-r6,lr}\n\
    adds r4, r1, 0\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    lsls r4, 24\n\
    lsrs r4, 24\n\
    adds r1, r4, 0\n\
    bl GetHeldItemIconSpriteIdByMon_maybe\n\
    lsls r0, 24\n\
    lsrs r5, r0, 24\n\
    adds r6, r5, 0\n\
    movs r0, 0x64\n\
    adds r1, r4, 0\n\
    muls r1, r0\n\
    ldr r0, _0806DFA4 @ =gPlayerParty\n\
    adds r4, r1, r0\n\
    adds r0, r4, 0\n\
    movs r1, 0xC\n\
    bl GetMonData\n\
    cmp r0, 0\n\
    bne _0806DFAC\n\
    ldr r1, _0806DFA8 @ =gSprites\n\
    lsls r0, r5, 4\n\
    adds r0, r5\n\
    lsls r0, 2\n\
    adds r0, r1\n\
    adds r0, 0x3E\n\
    ldrb r1, [r0]\n\
    movs r2, 0x4\n\
    orrs r1, r2\n\
    strb r1, [r0]\n\
    b _0806DFF6\n\
    .align 2, 0\n\
_0806DFA4: .4byte gPlayerParty\n\
_0806DFA8: .4byte gSprites\n\
_0806DFAC:\n\
    adds r0, r4, 0\n\
    movs r1, 0xC\n\
    bl GetMonData\n\
    lsls r0, 16\n\
    lsrs r0, 16\n\
    bl ItemIsMail\n\
    lsls r0, 24\n\
    cmp r0, 0\n\
    beq _0806DFD8\n\
    lsls r4, r5, 4\n\
    adds r4, r5\n\
    lsls r4, 2\n\
    ldr r0, _0806DFD4 @ =gSprites\n\
    adds r4, r0\n\
    adds r0, r4, 0\n\
    movs r1, 0x1\n\
    b _0806DFE6\n\
    .align 2, 0\n\
_0806DFD4: .4byte gSprites\n\
_0806DFD8:\n\
    lsls r4, r6, 4\n\
    adds r4, r6\n\
    lsls r4, 2\n\
    ldr r0, _0806DFFC @ =gSprites\n\
    adds r4, r0\n\
    adds r0, r4, 0\n\
    movs r1, 0\n\
_0806DFE6:\n\
    bl StartSpriteAnim\n\
    adds r4, 0x3E\n\
    ldrb r1, [r4]\n\
    movs r0, 0x5\n\
    negs r0, r0\n\
    ands r0, r1\n\
    strb r0, [r4]\n\
_0806DFF6:\n\
    pop {r4-r6}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_0806DFFC: .4byte gSprites\n\
    .syntax divided\n");
}
#endif // NONMATCHING

void PartyMenuDoPrintMonNickname(u8 monIndex, int b, const u8 *nameBuffer)
{
    u32 var1 = 0;
    CpuFastSet(&var1, gTileBuffer, 0x1000100);
    sub_8004E3C((struct WindowConfig *)&gWindowConfig_81E6CAC, gTileBuffer, nameBuffer);
    CpuFastSet(gTileBuffer, (void *)(OBJ_VRAM1 + (monIndex * 0x400)), 128);
}

void PrintPartyMenuMonNickname(u8 monIndex, u8 b, struct Pokemon *pokemon)
{
    u8 nameBuffer[12];
    GetMonNickname(pokemon, nameBuffer);
    PartyMenuDoPrintMonNickname(monIndex, b, nameBuffer);
}

void TryPrintPartyMenuMonNickname(u8 monIndex, struct Pokemon *pokemon)
{
    if (GetMonData(pokemon, MON_DATA_SPECIES))
    {
        bool8 isLinkDoubleBattle = IsLinkDoubleBattle();
        if (isLinkDoubleBattle == TRUE)
        {
            PrintPartyMenuMonNickname(monIndex, 2, pokemon);
        }
        else
        {
            PrintPartyMenuMonNickname(monIndex, IsDoubleBattle(), pokemon);
        }
    }
}

void PrintPartyMenuMonNicknames(void)
{
    u8 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        TryPrintPartyMenuMonNickname(i, &gPlayerParty[i]);
    }
}

u8 *GetMonNickname(struct Pokemon *pokemon, u8 *stringBuffer)
{
    GetMonData(pokemon, MON_DATA_NICKNAME, stringBuffer);
    return StringGetEnd10(stringBuffer);
}

void PartyMenuPutStatusTilemap(u8 monIndex, u8 b, u8 status)
{
    u8 i;
    u8 x = gUnknown_08376738[b][monIndex].x - 1;
    u8 y = gUnknown_08376738[b][monIndex].y + 1;
    u16 *vramPtr = (u16*)(VRAM + 0xF000) + (x + y * 32);
    u8 var1 = status * 4;

    for (i = 0; i < 4; i++)
    {
        vramPtr[i] = (0x18C + var1 + i) | -0x5000;
    }
}

static void PartyMenuClearLevelStatusTilemap(u8 monIndex)
{
    bool8 isLinkDoubleBattle;
    u8 b;
    u8 x;
    u8 y;
    u16 *vramPtr;
    u8 i;

    isLinkDoubleBattle = IsLinkDoubleBattle();
    if (isLinkDoubleBattle == TRUE)
    {
        b = 2;
    }
    else
    {
        b = IsDoubleBattle();
    }

    x = gUnknown_08376738[b][monIndex].x - 1;
    y = gUnknown_08376738[b][monIndex].y + 1;

    vramPtr = (u16*)(VRAM + 0xF000) + (x + y * 32);
    for (i = 0; i < 4; i++)
    {
        vramPtr[i] = 0;
    }
}

static void PartyMenuWriteTilemap(u8 a, u8 x, u8 y)
{
    u16 *vramPtr = (u16*)(VRAM + 0xF000) + (x + y * 32);
    *vramPtr = a + 0x10C;
}

void PartyMenuDoPrintLevel(u8 monIndex, u8 b, u8 level)
{
    u8 *stringVar;
    u32 var1;
    u8 x = gUnknown_08376738[b][monIndex].x;
    u8 y = gUnknown_08376738[b][monIndex].y;

    PartyMenuWriteTilemap(0x40, x - 1, y + 1);

    stringVar = gStringVar1;
    stringVar[0] = 0xFC;
    stringVar[1] = 0x12;
    stringVar[2] = 0x8;

    ConvertIntToDecimalString(&stringVar[3], level);

    var1 = 0;
    CpuFastSet(&var1, gUnknown_02039460, 0x1000020);
    sub_8004E3C((struct WindowConfig *)&gWindowConfig_81E6CAC, gUnknown_02039460 - 0x100 /*gTileBuffer*/, gStringVar1);
    CpuFastSet(gUnknown_02039460, (void *)(OBJ_VRAM1 + 0x200 + (monIndex * 0x400)), 32);
}

void PartyMenuPrintLevel(u8 monIndex, u8 b, struct Pokemon *pokemon)
{
    u16 level = GetMonData(pokemon, MON_DATA_LEVEL);
    PartyMenuDoPrintLevel(monIndex, b, level);
}

void PartyMenuPrintMonLevelOrStatus(u8 monIndex, struct Pokemon *pokemon)
{
    if (GetMonData(pokemon, MON_DATA_SPECIES) && !GetMonData(pokemon, MON_DATA_IS_EGG))
    {
        u8 statusAndPkrs;
        bool8 isLinkDoubleBattle;
        u8 b;

        statusAndPkrs = GetMonStatusAndPokerus(pokemon);

        isLinkDoubleBattle = IsLinkDoubleBattle();
        if (isLinkDoubleBattle == TRUE)
        {
            b = 2;
        }
        else
        {
            b = IsDoubleBattle();
        }

        if (statusAndPkrs != 0 && statusAndPkrs != 6)
        {
            PartyMenuPutStatusTilemap(monIndex, b, statusAndPkrs - 1);
        }
        else
        {
            PartyMenuPrintLevel(monIndex, b, pokemon);
        }

        PartyMenuPrintGenderIcon(monIndex, b, pokemon);
    }
}

void PartyMenuPrintMonsLevelOrStatus()
{
    u8 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        PartyMenuPrintMonLevelOrStatus(i, &gPlayerParty[i]);
    }
}

void PartyMenuDoPrintGenderIcon(u16 species, u8 gender, u8 c, u8 monIndex, u8 *nickname)
{
    if (!ShouldHideGenderIcon(species, nickname))
    {
        u8 x = gUnknown_08376738[c][monIndex].x + 3;
        u8 y = gUnknown_08376738[c][monIndex].y + 1;

        switch (gender)
        {
            case MON_MALE:
                PartyMenuWriteTilemap(0x42, x, y);
                break;
            case MON_FEMALE:
                PartyMenuWriteTilemap(0x44, x, y);
                break;
        }
    }
}

void PartyMenuPrintGenderIcon(u8 monIndex, u8 b, struct Pokemon *pokemon)
{
    u16 species2;
    u8 gender;

    GetMonNickname(pokemon, gStringVar1);
    species2 = GetMonData(pokemon, MON_DATA_SPECIES2);
    gender = GetMonGender(pokemon);
    PartyMenuDoPrintGenderIcon(species2, gender, b, monIndex, gStringVar1);
}

void PartyMenuDoPrintHP(u8 monIndex, u8 b, u16 currentHP, u16 maxHP)
{
    u32 *var;
    register u8 *stringVar1 asm("r2") = gStringVar1;
    register u8 *textPtr asm("r2") = sub_8072C14(stringVar1, currentHP, 15, 1);
    textPtr[0] = CHAR_SLASH;

    sub_8072C14(++textPtr, maxHP, 35, 1);
    var = 0;

    CpuFastSet(&var, gUnknown_02039460, 0x1000040);
    sub_8004E3C((struct WindowConfig *)&gWindowConfig_81E6CAC, gUnknown_02039460 - 0x100 /*gTileBuffer*/, gStringVar1);
    CpuFastSet(gUnknown_02039460, (void *)(OBJ_VRAM1 + 0x300 + (monIndex * 0x400)), 64);
}

void PartyMenuPrintHP(u8 monIndex, u8 b, struct Pokemon *pokemon)
{
    u16 currentHP;
    u16 maxHP;

    currentHP = GetMonData(pokemon, MON_DATA_HP);
    maxHP = GetMonData(pokemon, MON_DATA_MAX_HP);

    PartyMenuDoPrintHP(monIndex, b, currentHP, maxHP);
}

void PartyMenuTryPrintHP(u8 monIndex, struct Pokemon *pokemon)
{
    if (GetMonData(pokemon, MON_DATA_SPECIES) && !GetMonData(pokemon, MON_DATA_IS_EGG))
    {
        bool8 isLinkDoubleBattle = IsLinkDoubleBattle();
        if (isLinkDoubleBattle == TRUE)
        {
            PartyMenuPrintHP(monIndex, 2, pokemon);
        }
        else
        {
            PartyMenuPrintHP(monIndex, IsDoubleBattle(), pokemon);
        }
    }
}

void PartyMenuTryPrintMonsHP(void)
{
    u8 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        PartyMenuTryPrintHP(i, &gPlayerParty[i]);
    }
}

void unref_sub_806E564(void) { }
void unref_sub_806E568(void) { }
void nullsub_12(u8 monIndex, struct Pokemon *pokemon) { }
void nullsub_13(void) { }

void PartyMenuDoDrawHPBar(u8 monIndex, u8 b, u16 currentHP, u16 maxHP)
{
    u8 hpBarLevel;
    u16 *vramPtr;
    int var = -32768;
    struct BattleInterfaceStruct1 battleInterface;
    battleInterface.unk0 = maxHP;
    battleInterface.unk4 = currentHP;
    battleInterface.unk8 = 0;

    hpBarLevel = GetHPBarLevel(currentHP, maxHP);
    if (hpBarLevel > 2)
    {
        battleInterface.unkC_0 = 4;
    }
    if (hpBarLevel == 2)
    {
        battleInterface.unkC_0 = 5;
    }
    if (hpBarLevel < 2)
    {
        battleInterface.unkC_0 = 6;
    }

    battleInterface.unk10 = 0x100;

    vramPtr = gUnknown_08376858[b][monIndex];
    sub_80460C8(&battleInterface, &var, vramPtr, 0);

    vramPtr -= 2;

    vramPtr[0] = 0x3109;
    vramPtr[1] = 0x310A;
    vramPtr[8] = 0x310B;
}

void PartyMenuDrawHPBar(u8 monIndex, u8 b, struct Pokemon *pokemon)
{
    u16 currentHP = GetMonData(pokemon, MON_DATA_HP);
    u16 maxHP = GetMonData(pokemon, MON_DATA_MAX_HP);

    PartyMenuDoDrawHPBar(monIndex, b, currentHP, maxHP);
}

void PartyMenuTryDrawHPBar(u8 monIndex, struct Pokemon *pokemon)
{
    if (GetMonData(pokemon, MON_DATA_SPECIES) && !GetMonData(pokemon, MON_DATA_IS_EGG))
    {
        bool8 isDoubleBattle = IsLinkDoubleBattle();
        if (isDoubleBattle == TRUE)
        {
            PartyMenuDrawHPBar(monIndex, 2, pokemon);
        }
        else
        {
            PartyMenuDrawHPBar(monIndex, IsDoubleBattle(), pokemon);
        }
    }
}

void PartyMenuDrawHPBars(void)
{
    u8 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        PartyMenuTryDrawHPBar(i, &gPlayerParty[i]);
    }
}

void SwapPokemon(struct Pokemon *a, struct Pokemon *b)
{
    struct Pokemon temp = *a;
    *a = *b;
    *b = temp;
}

void SetPartyPopupMenuOffsets(u8 menuIndex, u8 *left, u8 *top, const struct PartyPopupMenu *menu)
{
    u8 bottomOffset = (2 * menu[menuIndex].numChoices) + 2;
    u8 rightOffset = menu[menuIndex].width + 1;

    *left = 30 - rightOffset;
    *top = 20 - bottomOffset;
}

void ShowPartyPopupMenu(u8 menuIndex, const struct PartyPopupMenu *menu, const struct MenuAction2 *menuActions, u8 cursorPos)
{
    u8 left;
    u8 top;

    SetPartyPopupMenuOffsets(menuIndex, &left, &top, menu);
    sub_8089C50(left, top, menu[menuIndex].width, menu[menuIndex].numChoices, menuActions, menu[menuIndex].items);

    InitMenu(0, left + 1, top + 1, menu[menuIndex].numChoices, cursorPos, menu[menuIndex].width - 1);
}

void ClosePartyPopupMenu(u8 index, const struct PartyPopupMenu *menu)
{
    u8 left;
    u8 top;

    SetPartyPopupMenuOffsets(index, &left, &top, menu);

    MenuZeroFillWindowRect(left, top, left + menu[index].width, menu[index].numChoices * 2 + top + 1);
    HandleDestroyMenuCursors();
}

TaskFunc PartyMenuGetPopupMenuFunc(u8 menuIndex, const struct PartyPopupMenu *menus, const struct MenuAction2 *menuActions, u8 itemIndex)
{
    u8 action = menus[menuIndex].items[itemIndex];
    return menuActions[action].func;
}

u8 sub_806E834(const u8 *message, u8 arg1)
{
    u8 taskId;

    gUnknown_0202E8F6 = 1;

    MenuDrawTextWindow(WINDOW_LEFT, 14, WINDOW_RIGHT, 19);
    MenuPrintMessage(message, WINDOW_LEFT + 1, 15);

    taskId = CreateTask(sub_806E884, 1);
    gTasks[taskId].data[0] = arg1;

    return taskId;
}

static void sub_806E884(u8 taskId)
{
    if (MenuUpdateWindowText())
    {
        gUnknown_0202E8F6 = 0;
        if (gTasks[taskId].data[0] == 0)
            MenuZeroFillWindowRect(WINDOW_LEFT, 14, WINDOW_RIGHT, 19);
        DestroyTask(taskId);
    }
}

void sub_806E8D0(u8 taskId, u16 b, TaskFunc c)
{
    ewram1C000.unk10 = c;
    ewram1C000.unk4 = taskId;
    ewram1C000.unk5 = sub_806CA38(taskId);
    ewram1C000.unk6 = b;
    ewram1C000.pokemon = &gPlayerParty[ewram1C000.unk5];
}

bool8 PartyMenuUpdateMonHeldItem(struct Pokemon *pkmn, u16 item)
{
    u8 itemData[2];

    if (ItemIsMail(item) == TRUE)
    {
        if (GiveMailToMon(pkmn, item) == 0xFF)
            return TRUE;
        gUnknown_0202E8F4 = 2;
    }
    else
    {
        gUnknown_0202E8F4 = 1;
    }

    itemData[0] = item;
    itemData[1] = item >> 8;
    SetMonData(pkmn, MON_DATA_HELD_ITEM, itemData);
    return FALSE;
}

void PartyMenuTryGiveMonHeldItem(u8 taskId, u16 newItem, TaskFunc c)
{
    u16 currentItem;

    gTasks[taskId].func = TaskDummy;
    sub_806E8D0(taskId, newItem, c);
    currentItem = GetMonData(ewram1C000.pokemon, MON_DATA_HELD_ITEM);
    gUnknown_0202E8F4 = 0;
    gUnknown_0202E8F8 = 0;
    if (currentItem != 0)
    {
        if (ItemIsMail(currentItem) == TRUE)
        {
            sub_806E834(gOtherText_MailMustBeRemoved, 1);
            CreateTask(party_menu_link_mon_held_item_object, 5);
        }
        else
        {
            GetMonNickname(ewram1C000.pokemon, gStringVar1);
            CopyItemName(currentItem, gStringVar2);
            StringExpandPlaceholders(gStringVar4, gOtherText_AlreadyHolding);
            sub_806E834(gStringVar4, 1);
            CreateTask(Task_ConfirmGiveHeldItem, 5);
            if (ItemIsMail(newItem) == TRUE)
                gUnknown_0202E8F8 = currentItem;
        }
    }
    else
    {
        PartyMenuUpdateMonHeldItem(ewram1C000.pokemon, newItem);
        RemoveBagItem(newItem, 1);
        if (ItemIsMail(newItem))
        {
            gTasks[taskId].func = c;
        }
        else
        {
            DisplayGiveHeldItemMessage(ewram1C000.unk5, newItem, 1);
            CreateTask(party_menu_link_mon_held_item_object, 5);
        }
    }
}

void party_menu_link_mon_held_item_object(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        SetHeldItemIconVisibility(ewram1C000.unk4, ewram1C000.unk5);
        gTasks[ewram1C000.unk4].func = ewram1C000.unk10;
        DestroyTask(taskId);
    }
}

void PartyMenuTryGiveMonHeldItem_806EACC(u8 taskId)
{
    s8 selection = ProcessMenuInputNoWrap_();

    if (selection == 0)
    {
        u16 currentItem;

        MenuZeroFillWindowRect(23, 8, 29, 13);
        currentItem = GetMonData(ewram1C000.pokemon, MON_DATA_HELD_ITEM);
        RemoveBagItem(ewram1C000.unk6, 1);
        if (AddBagItem(currentItem, 1) == TRUE)
        {
            PartyMenuUpdateMonHeldItem(ewram1C000.pokemon, ewram1C000.unk6);
            if (ItemIsMail(ewram1C000.unk6))
            {
                DisplayTakeHeldItemMessage(ewram1C000.unk5, currentItem, 1);
            }
            else
            {
                CopyItemName(ewram1C000.unk6, gStringVar1);
                StringExpandPlaceholders(gStringVar4, gOtherText_TakenAndReplaced);
                sub_806E834(gStringVar4, 1);
            }
        }
        else
        {
            sub_806E834(gOtherText_BagFullCannotRemoveItem, 0);
            AddBagItem(ewram1C000.unk6, 1);
        }
    }
    else
    {
        if (selection != 1 && selection != -1)
            return;
        if (selection == -1)
            PlaySE(SE_SELECT);
        MenuZeroFillWindowRect(23, 8, 29, 13);
    }
    gTasks[taskId].func = party_menu_link_mon_held_item_object;
}

void Task_ConfirmGiveHeldItem(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        DisplayYesNoMenu(23, 8, 1);
        gTasks[taskId].func = PartyMenuTryGiveMonHeldItem_806EACC;
    }
}

void DisplayGiveHeldItemMessage(u8 a, u16 b, u8 c)
{
    GetMonNickname(&gPlayerParty[a], gStringVar1);
    CopyItemName(b, gStringVar2);
    StringExpandPlaceholders(gStringVar4, gOtherText_WasGivenToHold);
    sub_806E834(gStringVar4, c);
}


// Not sure about this one for now.
/*
void PartyMenuTryGiveMonMail(u8 taskId, TaskFunc func)
{
    u16 currentItem;
    struct MailStruct *r4;

    gTasks[taskId].func = TaskDummy;
    sub_806E8D0(taskId, 0, func);
    currentItem = GetMonData(ewram1C000.pokemon, MON_DATA_HELD_ITEM);
    gUnknown_0202E8F4 = 0;
    r4 = &gSaveBlock1.mail[ewram1F000.unkE00[0] + ewram1F000.unkE00[2]];
    if (currentItem != 0)
    {
        sub_806E834(gOtherText_PokeHoldingItemCantMail, 1);
        CreateTask(party_menu_link_mon_held_item_object, 5);
    }
    else
    {
        GiveMailToMon2(ewram1C000.pokemon, r4);
        ClearMailStruct(r4);
        sub_806E834(gOtherText_MailTransferredMailbox, 1);
        CreateTask(party_menu_link_mon_held_item_object, 5);
    }
}
*/
__attribute__((naked))
void PartyMenuTryGiveMonMail(u8 taskId, TaskFunc func)
{
    asm(".syntax unified\n\
    push {r4,r5,lr}\n\
    adds r2, r1, 0\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    ldr r3, _0806ECA0 @ =gTasks\n\
    lsls r1, r0, 2\n\
    adds r1, r0\n\
    lsls r1, 3\n\
    adds r1, r3\n\
    ldr r3, _0806ECA4 @ =TaskDummy\n\
    str r3, [r1]\n\
    movs r1, 0\n\
    bl sub_806E8D0\n\
    ldr r5, _0806ECA8 @ =0x0201c000\n\
    ldr r0, [r5]\n\
    movs r1, 0xC\n\
    bl GetMonData\n\
    lsls r0, 16\n\
    ldr r2, _0806ECAC @ =gUnknown_0202E8F4\n\
    movs r1, 0\n\
    strb r1, [r2]\n\
    movs r1, 0xF8\n\
    lsls r1, 6\n\
    adds r2, r5, r1\n\
    ldrb r1, [r2]\n\
    adds r1, 0x6\n\
    ldrb r2, [r2, 0x2]\n\
    adds r1, r2\n\
    lsls r2, r1, 3\n\
    adds r2, r1\n\
    lsls r2, 2\n\
    ldr r1, _0806ECB0 @ =gSaveBlock1 + 0x2B4C\n\
    adds r4, r2, r1\n\
    cmp r0, 0\n\
    beq _0806ECBC\n\
    ldr r0, _0806ECB4 @ =gOtherText_PokeHoldingItemCantMail\n\
    movs r1, 0x1\n\
    bl sub_806E834\n\
    ldr r0, _0806ECB8 @ =party_menu_link_mon_held_item_object\n\
    movs r1, 0x5\n\
    bl CreateTask\n\
    b _0806ECDA\n\
    .align 2, 0\n\
_0806ECA0: .4byte gTasks\n\
_0806ECA4: .4byte TaskDummy\n\
_0806ECA8: .4byte 0x0201c000\n\
_0806ECAC: .4byte gUnknown_0202E8F4\n\
_0806ECB0: .4byte gSaveBlock1 + 0x2B4C\n\
_0806ECB4: .4byte gOtherText_PokeHoldingItemCantMail\n\
_0806ECB8: .4byte party_menu_link_mon_held_item_object\n\
_0806ECBC:\n\
    ldr r0, [r5]\n\
    adds r1, r4, 0\n\
    bl GiveMailToMon2\n\
    adds r0, r4, 0\n\
    bl ClearMailStruct\n\
    ldr r0, _0806ECE0 @ =gOtherText_MailTransferredMailbox\n\
    movs r1, 0x1\n\
    bl sub_806E834\n\
    ldr r0, _0806ECE4 @ =party_menu_link_mon_held_item_object\n\
    movs r1, 0x5\n\
    bl CreateTask\n\
_0806ECDA:\n\
    pop {r4,r5}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_0806ECE0: .4byte gOtherText_MailTransferredMailbox\n\
_0806ECE4: .4byte party_menu_link_mon_held_item_object\n\
    .syntax divided\n");
}

void PartyMenuTryGiveMonHeldItem_806ECE8(u8 taskId, TaskFunc func)
{
    u16 currentItem;

    gTasks[taskId].func = TaskDummy;
    sub_806E8D0(taskId, 0, func);
    currentItem = GetMonData(ewram1C000.pokemon, MON_DATA_HELD_ITEM);
    if (currentItem == 0)
    {
        StringExpandPlaceholders(gStringVar4, gOtherText_NotHoldingAnything);
        sub_806E834(gStringVar4, 0);
        CreateTask(party_menu_link_mon_held_item_object, 5);
    }
    else
    {
        u8 itemData[2];

        itemData[0] = 0;
        itemData[1] = 0;
        if (AddBagItem(currentItem, 1) == TRUE)
        {
            if (ItemIsMail(currentItem) == TRUE)
                TakeMailFromMon(ewram1C000.pokemon);
            DisplayTakeHeldItemMessage(ewram1C000.unk5, currentItem, 0);
            SetMonData(ewram1C000.pokemon, MON_DATA_HELD_ITEM, itemData);
        }
        else
        {
            sub_806E834(gOtherText_BagFullCannotRemoveItem, 0);
        }
        CreateTask(party_menu_link_mon_held_item_object, 5);
    }
}

void DisplayTakeHeldItemMessage(u8 a, u16 b, u8 c)
{
    GetMonNickname(&gPlayerParty[a], gStringVar1);
    CopyItemName(b, gStringVar2);
    StringExpandPlaceholders(gStringVar4, gOtherText_ReceivedTheThingFrom);
    sub_806E834(gStringVar4, c);
}

void DoTakeMail(u8 taskId, TaskFunc func)
{
    gTasks[taskId].func = TaskDummy;
    sub_806E8D0(taskId, 0, func);
    ewram1C000.unk6 = GetMonData(ewram1C000.pokemon, MON_DATA_HELD_ITEM);
    sub_806E834(gOtherText_SendRemovedMailPrompt, 1);
    CreateTask(Task_ConfirmTakeHeldMail, 5);
}

void Task_LoseMailMessage(u8 taskId)
{
    s8 selection = ProcessMenuInputNoWrap_();

    if (selection == 0)
    {
        if (AddBagItem(ewram1C000.unk6, 1) == TRUE)
        {
            TakeMailFromMon(ewram1C000.pokemon);
            sub_806E834(gOtherText_MailTaken, 0);
        }
        else
        {
            sub_806E834(gOtherText_BagFullCannotRemoveItem, 0);
        }
        MenuZeroFillWindowRect(23, 8, 29, 13);
        gTasks[taskId].func = party_menu_link_mon_held_item_object;
    }
    else
    {
        if (selection != 1 && selection != -1)
            return;
        if (selection == -1)
            PlaySE(SE_SELECT);
        MenuZeroFillWindowRect(23, 8, 29, 13);
        MenuZeroFillWindowRect(0, 14, 29, 19);
        gTasks[taskId].func = party_menu_link_mon_held_item_object;
    }
}

void Task_ConfirmLoseMailMessage(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        DisplayYesNoMenu(23, 8, 1);
        gTasks[taskId].func = Task_LoseMailMessage;
    }
}

void Task_TakeHeldMail(u8 taskId)
{
    s8 selection = ProcessMenuInputNoWrap_();

    if (selection == 0)
    {
        MenuZeroFillWindowRect(23, 8, 29, 13);
        if (TakeMailFromMon2(ewram1C000.pokemon) != 0xFF)
            sub_806E834(gOtherText_MailWasSent, 0);
        else
            sub_806E834(gOtherText_MailboxIsFull, 0);
        gTasks[taskId].func = party_menu_link_mon_held_item_object;
    }
    else
    {
        if (selection != 1 && selection != -1)
            return;
        if (selection == -1)
            PlaySE(SE_SELECT);
        MenuZeroFillWindowRect(23, 8, 29, 13);
        sub_806E834(gOtherText_MailRemovedMessageLost, 1);
        gTasks[taskId].func = Task_ConfirmLoseMailMessage;
    }
}

void Task_ConfirmTakeHeldMail(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        DisplayYesNoMenu(23, 8, 1);
        gTasks[taskId].func = Task_TakeHeldMail;
    }
}

u16 ItemIdToBattleMoveId(u16 item)
{
    u16 moveId = item - 289;

    return gUnknown_08376504[moveId];
}

bool8 pokemon_has_move(struct Pokemon *pkmn, u16 move)
{
    u8 i;

    for (i = 0; i < 4; i++)
    {
        if (GetMonData(pkmn, MON_DATA_MOVE1 + i) == move)
            return TRUE;
    }
    return FALSE;
}

void TeachMonTMMove(u8 taskId, u16 move, TaskFunc func)
{
    PlaySE(SE_SELECT);
    gTasks[taskId].func = TaskDummy;
    sub_806E8D0(taskId, move, func);
    CreateTask(Task_TeamMonTMMove, 5);
}

void Task_TeamMonTMMove(u8 taskId)
{
    GetMonNickname(ewram1C000.pokemon, gStringVar1);
    ewram1C000.unk8 = ItemIdToBattleMoveId(ewram1C000.unk6);
    StringCopy(gStringVar2, gMoveNames[ewram1C000.unk8]);
    ewram1B000.unk282 = 0;
    if (pokemon_has_move(ewram1C000.pokemon, ewram1C000.unk8))
    {
        StringExpandPlaceholders(gStringVar4, gOtherText_AlreadyKnows);
        sub_806E834(gStringVar4, 1);
        gTasks[taskId].func = party_menu_link_mon_held_item_object;
    }
    else
    {
        if (!CanMonLearnTMHM(ewram1C000.pokemon, ewram1C000.unk6 - 33))
        {
            StringExpandPlaceholders(gStringVar4, gOtherText_NotCompatible);
            sub_806E834(gStringVar4, 1);
            gTasks[taskId].func = party_menu_link_mon_held_item_object;
        }
        else
        {
            if (GiveMoveToMon(ewram1C000.pokemon, ewram1C000.unk8) != 0xFFFF)
            {
                Task_TeamMonTMMove2(taskId);
            }
            else
            {
                StringExpandPlaceholders(gStringVar4, gOtherText_WantsToLearn);
                sub_806E834(gStringVar4, 1);
                gTasks[taskId].func = sub_806F358;
            }
        }
    }
}

void Task_TeamMonTMMove2(u8 taskId)
{
    StringCopy(gStringVar2, gMoveNames[ewram1C000.unk8]);
    StringExpandPlaceholders(gStringVar4, gOtherText_LearnedMove);
    sub_806E834(gStringVar4, 1);
    AdjustFriendship(ewram1C000.pokemon, 4);
    if (ewram1B000.unk282 == 0 && ewram1C000.unk6 <= 0x152)
        RemoveBagItem(ewram1C000.unk6, 1);
    gTasks[taskId].func = Task_TeamMonTMMove3;
}

void Task_TeamMonTMMove3(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        PlayFanfare(BGM_FANFA1);
        gTasks[taskId].func = Task_TeamMonTMMove4;
    }
}

void Task_TeamMonTMMove4(u8 taskId)
{
    if (IsFanfareTaskInactive())
    {
        if ((gMain.newKeys & A_BUTTON) || (gMain.newKeys & B_BUTTON))
        {
            SetHeldItemIconVisibility(ewram1C000.unk4, ewram1C000.unk5);
            if (ewram1B000.unk282 == 1)
            {
                TeachMonMoveInPartyMenu(taskId);
            }
            else
            {
                gTasks[ewram1C000.unk4].func = ewram1C000.unk10;
                DestroyTask(taskId);
            }
        }
    }
}

void sub_806F2FC(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        SetHeldItemIconVisibility(ewram1C000.unk4, ewram1C000.unk5);
        if (ewram1B000.unk282 == 1)
        {
            TeachMonMoveInPartyMenu(taskId);
        }
        else
        {
            gTasks[ewram1C000.unk4].func = ewram1C000.unk10;
            DestroyTask(taskId);
        }
    }
}

void sub_806F358(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        DisplayYesNoMenu(23, 8, 1);
        gTasks[taskId].func = sub_806F390;
    }
}

void sub_806F390(u8 taskId)
{
    s8 selection = ProcessMenuInputNoWrap_();

    if (selection == 0)
    {
        MenuZeroFillWindowRect(23, 8, 29, 13);
        sub_806E834(gOtherText_WhichMoveToForget2, 1);
        gTasks[taskId].func = sub_806F44C;
    }
    else
    {
        if (selection != 1 && selection != -1)
            return;
        if (selection == -1)
            PlaySE(SE_SELECT);
        StopTryingToTeachMove_806F614(taskId);
    }
}

void sub_806F3FC(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        sub_809D9F0(gPlayerParty, ewram1C000.unk5, gPlayerPartyCount - 1, sub_808B564, ewram1C000.unk8);
        DestroyTask(taskId);
    }
}

void sub_806F44C(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
        gTasks[taskId].func = sub_806F3FC;
    }
}

void TaughtMove(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        u8 moveIndex;
        u16 r4;

        gTasks[taskId].func = TaskDummy;
        sub_806E8D0(taskId, gScriptItemId, sub_808B508);
        moveIndex = sub_809FA30();
        r4 = GetMonData(ewram1C000.pokemon, MON_DATA_MOVE1 + moveIndex);
        GetMonNickname(ewram1C000.pokemon, gStringVar1);
        StringCopy(gStringVar2, gMoveNames[r4]);
        StringExpandPlaceholders(gStringVar4, gOtherText_ForgetMove123_2);
        sub_806E834(gStringVar4, 1);
        CreateTask(TMMoveUpdateMoveSlot, 5);
    }
}

void TMMoveUpdateMoveSlot(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        RemoveMonPPBonus(ewram1C000.pokemon, sub_809FA30());
        SetMonMoveSlot(ewram1C000.pokemon, ewram1C000.unk8, sub_809FA30());
        Task_TeamMonTMMove2(taskId);
    }
}

void StopTryingToTeachMove_806F588(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = TaskDummy;
        sub_806E8D0(taskId, gScriptItemId, sub_808B508);
        StringCopy(gStringVar2, gMoveNames[ewram1C000.unk8]);
        StringExpandPlaceholders(gStringVar4, gOtherText_StopTryingTo);
        sub_806E834(gStringVar4, 1);
        CreateTask(StopTryingToTeachMove_806F67C, 5);
    }
}

void StopTryingToTeachMove_806F614(u8 taskId)
{
    MenuZeroFillWindowRect(23, 8, 29, 13);
    StringCopy(gStringVar2, gMoveNames[ewram1C000.unk8]);
    StringExpandPlaceholders(gStringVar4, gOtherText_StopTryingTo);
    sub_806E834(gStringVar4, 1);
    gTasks[taskId].func = StopTryingToTeachMove_806F67C;
}

void StopTryingToTeachMove_806F67C(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        DisplayYesNoMenu(23, 8, 1);
        gTasks[taskId].func = StopTryingToTeachMove_806F6B4;
    }
}

void StopTryingToTeachMove_806F6B4(u8 taskId)
{
    s8 selection = ProcessMenuInputNoWrap_();

    if (selection == 0)
    {
        MenuZeroFillWindowRect(23, 8, 29, 13);
        GetMonNickname(ewram1C000.pokemon, gStringVar1);
        StringCopy(gStringVar2, gMoveNames[ewram1C000.unk8]);
        StringExpandPlaceholders(gStringVar4, gOtherText_DidNotLearnMove2);
        sub_806E834(gStringVar4, 1);
        gTasks[taskId].func = sub_806F2FC;
    }
    else
    {
        if (selection != 1 && selection != -1)
            return;
        if (selection == -1)
            PlaySE(SE_SELECT);
        MenuZeroFillWindowRect(23, 8, 29, 13);
        GetMonNickname(ewram1C000.pokemon, gStringVar1);
        StringCopy(gStringVar2, gMoveNames[ewram1C000.unk8]);
        StringExpandPlaceholders(gStringVar4, gOtherText_WantsToLearn);
        sub_806E834(gStringVar4, 1);
        gTasks[taskId].func = sub_806F358;
    }
}

bool8 IsHMMove(u16 move)
{
    u8 i;

    for (i = 0; i < 8; i++)
    {
        if (gUnknown_08376504[50 + i] == move)
            return TRUE;
    }
    return FALSE;
}

s16 sub_806F7E8(u8 taskId, struct BattleInterfaceStruct1 *b, s8 c)
{
    s16 *taskData;
    u8 hpBarLevel;
    void *vramPtr;

    taskData = gTasks[taskId].data;

    b->unk0 = taskData[10];
    b->unk4 = taskData[11];
    b->unk8 = taskData[12] * c;
    b->unk10 = 0x100;
    hpBarLevel = GetHPBarLevel(ewram1B000.unk282, b->unk0);
    if (hpBarLevel > 2)
        b->unkC_0 = 4;
    if (hpBarLevel == 2)
        b->unkC_0 = 5;
    if (hpBarLevel < 2)
        b->unkC_0 = 6;
    vramPtr = gUnknown_08376858[IsDoubleBattle()][ewram1C000.unk5];
    return sub_80460C8(b, &ewram1C000.unkC, vramPtr, 0);
}

void sub_806F8AC(u8 taskId)
{
    struct BattleInterfaceStruct1 sp0;
    u16 sp14;

    ewram1B000.unk282 = sub_806F7E8(taskId, &sp0, -1);
    if (ewram1B000.unk282 == -1)
    {
        ewram1C000.unkC = 0;
        if (-sp0.unk8 + sp0.unk4 > sp0.unk0)
            sp14 = sp0.unk0 - sp0.unk4;
        else
            sp14 = -sp0.unk8;
        gBattleMoveDamage = -sp14;
        GetMonNickname(ewram1C000.pokemon, gStringVar1);
        ConvertIntToDecimalStringN(gStringVar2, sp14, 0, 3);
        if (gTasks[taskId].data[14] == 0)
            StringExpandPlaceholders(gStringVar4, gOtherText_HPRestoredBy);
        else
            StringExpandPlaceholders(gStringVar4, gOtherText_RegainedHealth);
        SetMonIconAnim(GetMonIconSpriteId_maybe(ewram1C000.unk4, ewram1C000.unk5), ewram1C000.pokemon);
        task_pc_turn_off(&gUnknown_083769A8[IsDoubleBattle() * 12 + ewram1C000.unk5 * 2], 7);
        ewram1B000.unk261 = 2;
        sub_806E834(gStringVar4, 1);
        sp14 += sp0.unk4;
        SetMonData(ewram1C000.pokemon, MON_DATA_HP, (u8 *)&sp14);
        RemoveBagItem(ewram1C000.unk6, 1);
        sub_8032638();
        gTasks[taskId].func = sub_806FB44;
    }
    else
    {
        PartyMenuDoPrintHP(ewram1C000.unk5, IsDoubleBattle(), ewram1B000.unk282, sp0.unk0);
    }
}

void sub_806FA18(u8 taskId)
{
    struct BattleInterfaceStruct1 sp0;

    ewram1B000.unk282 = sub_806F7E8(taskId, &sp0, 1);
    if (ewram1B000.unk282 == -1)
    {
        PlaySE(SE_KAIFUKU);
        ewram1C000.unkC = 0;
        gTasks[taskId].data[11] -= gTasks[taskId].data[12];
        SetMonData(ewram1C000.pokemon, MON_DATA_HP, (u8 *)&gTasks[taskId].data[11]);
        SetMonIconAnim(GetMonIconSpriteId_maybe(ewram1C000.unk4, ewram01000.unk1), ewram1C000.pokemon);
        ewram1C000.unk5 = gSprites[ewram01000.unk2].data0;
        ewram1C000.pokemon = &gPlayerParty[ewram1C000.unk5];
        gTasks[taskId].data[10] = GetMonData(ewram1C000.pokemon, MON_DATA_MAX_HP);
        gTasks[taskId].data[11] = GetMonData(ewram1C000.pokemon, MON_DATA_HP);
        ewram1C000.unkC = -32768;
        ewram1C000.unk14 = ewram1C000.unk10;
        gTasks[taskId].func = sub_806F8AC;
        ewram1B000.unk282 = gTasks[taskId].data[11];
    }
    else
    {
        PartyMenuDoPrintHP(ewram1C000.unk5, IsDoubleBattle(), ewram1B000.unk282, sp0.unk0);
    }
}

void sub_806FB0C(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        gTasks[ewram1C000.unk4].func = ewram1C000.unk10;
        DestroyTask(taskId);
    }
}

void sub_806FB44(u8 taskId)
{
    if (gUnknown_0202E8F6 == 0)
    {
        gTasks[ewram1C000.unk4].func = ewram1C000.unk14;
        DestroyTask(taskId);
    }
}

bool8 IsHPRecoveryItem(u16 item)
{
    const u8 *itemEffect;

    if (item == ITEM_ENIGMA_BERRY)
        itemEffect = gSaveBlock1.enigmaBerry.itemEffect;
    else
        itemEffect = gItemEffectTable[item - ITEM_POTION];

    if (itemEffect[4] & 4)
        return TRUE;
    else
        return FALSE;
}

void PartyMenuUpdateLevelOrStatus(struct Pokemon *pkmn, u8 b)
{
    PartyMenuClearLevelStatusTilemap(b);
    PartyMenuPrintMonLevelOrStatus(b, pkmn);
}

void GetMedicineItemEffectMessage(u16 item)
{
    switch (GetItemEffectType(item))
    {
        case 3:
            StringExpandPlaceholders(gStringVar4, gOtherText_CuredPoisoning);
            break;
        case 4:
            StringExpandPlaceholders(gStringVar4, gOtherText_WokeUp);
            break;
        case 5:
            StringExpandPlaceholders(gStringVar4, gOtherText_BurnHealed);
            break;
        case 6:
            StringExpandPlaceholders(gStringVar4, gOtherText_ThawedOut);
            break;
        case 7:
            StringExpandPlaceholders(gStringVar4, gOtherText_CuredParalysis);
            break;
        case 8:
            StringExpandPlaceholders(gStringVar4, gOtherText_SnapConfusion);
            break;
        case 9:
            StringExpandPlaceholders(gStringVar4, gOtherText_GotOverLove);
            break;
        case 11:
            StringExpandPlaceholders(gStringVar4, gOtherText_BecameHealthy);
            break;
        case 13:
            StringCopy(gStringVar2, gOtherText_Hp2);
            StringExpandPlaceholders(gStringVar4, gOtherText_WasRaised);
            break;
        case 12:
            StringCopy(gStringVar2, gOtherText_Attack);
            StringExpandPlaceholders(gStringVar4, gOtherText_WasRaised);
            break;
        case 17:
            StringCopy(gStringVar2, gOtherText_Defense);
            StringExpandPlaceholders(gStringVar4, gOtherText_WasRaised);
            break;
        case 16:
            StringCopy(gStringVar2, gOtherText_Speed);
            StringExpandPlaceholders(gStringVar4, gOtherText_WasRaised);
            break;
        case 14:
            StringCopy(gStringVar2, gOtherText_SpAtk2);
            StringExpandPlaceholders(gStringVar4, gOtherText_WasRaised);
            break;
        case 15:
            StringCopy(gStringVar2, gOtherText_SpDef2);
            StringExpandPlaceholders(gStringVar4, gOtherText_WasRaised);
            break;
        case 19:
        case 20:
            StringExpandPlaceholders(gStringVar4, gOtherText_PPIncreased);
            break;
        case 21:
            StringExpandPlaceholders(gStringVar4, gOtherText_PPRestored);
            break;
        default:
            StringExpandPlaceholders(gStringVar4, gOtherText_WontHaveAnyEffect);
            break;
    }
}

bool8 IsMedicineIneffective(struct Pokemon *pkmn, u16 item)
{
    if (GetItemEffectType(item) == 13
     && GetMonData(pkmn, MON_DATA_SPECIES) == SPECIES_SHEDINJA)
        return TRUE;
    else
        return FALSE;
}

bool8 ExecuteTableBasedItemEffect__(u8 a, u16 b, u8 c)
{
    if (gMain.inBattle)
        return ExecuteTableBasedItemEffect_(&gPlayerParty[a], b, sub_8094C20(a), c);
    else
        return ExecuteTableBasedItemEffect_(&gPlayerParty[a], b, a, c);
}

void UseMedicine(u8 taskId, u16 item, TaskFunc func)
{
    u8 r7;
    bool8 r9 = FALSE;
    bool8 r0;

    gTasks[taskId].func = TaskDummy;
    r7 = CreateTask(TaskDummy, 5);
    sub_806E8D0(taskId, item, func);
    if (!IsMedicineIneffective(ewram1C000.pokemon, item))
    {
        r9 = IsHPRecoveryItem(item);
        if (r9 == TRUE)
        {
            gTasks[r7].data[10] = GetMonData(ewram1C000.pokemon, MON_DATA_MAX_HP);
            gTasks[r7].data[11] = GetMonData(ewram1C000.pokemon, MON_DATA_HP);
            if (gTasks[r7].data[10] == gTasks[r7].data[11])
            {
                r9 = FALSE;
                gTasks[r7].data[10] = 0;
                gTasks[r7].data[11] = 0;
            }
        }
        r0 = ExecuteTableBasedItemEffect__(ewram1C000.unk5, item, 0);
    }
    else
    {
        r0 = TRUE;
    }

    if (r0)
    {
        gUnknown_0202E8F4 = 0;
        PlaySE(SE_SELECT);
        sub_806E834(gOtherText_WontHaveAnyEffect, 1);
        gTasks[r7].func = sub_806FB0C;
    }
    else
    {
        u8 statusAndPkrs;

        gUnknown_0202E8F4 = 1;
        if (!IsBlueYellowRedFlute(item))
            PlaySE(SE_KAIFUKU);
        else
            PlaySE(SE_BIDORO);
        statusAndPkrs = GetMonStatusAndPokerus(ewram1C000.pokemon);
        if (statusAndPkrs == 6 || statusAndPkrs == 0)
            PartyMenuUpdateLevelOrStatus(ewram1C000.pokemon, ewram1C000.unk5);
        if (r9 == TRUE)
        {
            gTasks[r7].data[12] = GetMonData(ewram1C000.pokemon, MON_DATA_HP) - gTasks[r7].data[11];
            ewram1C000.unkC = -32768;
            if (gTasks[r7].data[11] == 0)
                gTasks[r7].data[14] = 1;
            else
                gTasks[r7].data[14] = 0;
            ewram1C000.unk14 = ewram1C000.unk10;
            gTasks[r7].func = sub_806F8AC;
            ewram1B000.unk282 = gTasks[r7].data[11];
        }
        else
        {
            GetMonNickname(ewram1C000.pokemon, gStringVar1);
            if (!IsBlueYellowRedFlute(item))
                RemoveBagItem(item, 1);
            GetMedicineItemEffectMessage(item);
            TryPrintPartyMenuMonNickname(ewram1C000.unk5, ewram1C000.pokemon);
            sub_806E834(gStringVar4, 1);
            gTasks[r7].func = sub_806FB0C;
        }
    }
}

bool8 IsBlueYellowRedFlute(u16 item)
{
    if (item == 0x27
     || item == 0x29
     || item == 0x28)
        return TRUE;
    else
        return FALSE;
}

void sub_8070048(u8 taskId, u16 item, TaskFunc func)
{
    ewram1C000.unk10 = func;
    ewram1C000.unk4 = taskId;
    ewram1C000.unk6 = item;
    ewram1C000.unk5 = 0;
    ewram1C000.unk14 = sub_80701DC;
    ewram1B000.unk27E = 0;
    ewram1B000.unk280 = 0;
    sub_8070088(taskId);
}

void sub_8070088(u8 taskId)
{
    u8 taskId2;

    gTasks[taskId].func = TaskDummy;
    if (GetMonData(&gPlayerParty[ewram1C000.unk5], MON_DATA_SPECIES) == 0)
    {
        gTasks[taskId].func = sub_80701DC;
    }
    else
    {
        s16 *taskData;

        taskId2 = CreateTask(TaskDummy, 5);
        taskData = gTasks[taskId2].data;
        ewram1C000.pokemon = &gPlayerParty[ewram1C000.unk5];
        taskData[10] = GetMonData(ewram1C000.pokemon, MON_DATA_MAX_HP);
        taskData[11] = GetMonData(ewram1C000.pokemon, MON_DATA_HP);
        if (ExecuteTableBasedItemEffect__(ewram1C000.unk5, ewram1C000.unk6, 0))
        {
            DestroyTask(taskId2);
            gTasks[taskId].func = sub_80701DC;
        }
        else
        {
            gUnknown_0202E8F4 = 1;
            MenuZeroFillWindowRect(WINDOW_LEFT, 14, WINDOW_RIGHT, 19);
            PlaySE(SE_KAIFUKU);
            PartyMenuUpdateLevelOrStatus(ewram1C000.pokemon, ewram1C000.unk5);
            task_pc_turn_off(&gUnknown_083769A8[IsDoubleBattle() * 12 + ewram1C000.unk5 * 2], 9);
            ewram1B000.unk261 = 2;
            taskData[12] = GetMonData(ewram1C000.pokemon, MON_DATA_HP) - taskData[11];
            taskData[14] = 1;
            ewram1B000.unk27E = 1;
            ewram1B000.unk280 = 1;
            ewram1B000.unk282 = taskData[11];
            ewram1C000.unkC = -32768;
            gTasks[taskId2].func = sub_806F8AC;
        }
    }
}

void sub_80701DC(u8 taskId)
{
    if (ewram1B000.unk27E == 1)
    {
        AddBagItem(ewram1C000.unk6, 1);
        if (GetMonData(&gPlayerParty[ewram1C000.unk5], MON_DATA_SPECIES) != 0)
        {
            task_pc_turn_off(&gUnknown_083769A8[IsDoubleBattle() * 12 + ewram1C000.unk5 * 2], 3);
            ewram1B000.unk261 = 2;
        }
        ewram1B000.unk27E = 0;
    }
    ewram1C000.unk5++;
    if (ewram1C000.unk5 == 6)
    {
        gUnknown_0202E8F4 = 0;
        if (ewram1B000.unk280 == 0)
        {
            gTasks[taskId].func = TaskDummy;
            sub_806E834(gOtherText_WontHaveAnyEffect, 1);
            CreateTask(sub_806FB0C, 8);
        }
        else
        {
            RemoveBagItem(ewram1C000.unk6, 1);
            gTasks[taskId].func = ewram1C000.unk10;
        }
        gLastFieldPokeMenuOpened = 0;
    }
    else
    {
        sub_8070088(taskId);
    }
}

void CreateItemUseMoveMenu(u8 partyMonIndex)
{
    u8 r6;
    u8 i;

    r6 = 0;
    MenuDrawTextWindow(19, 10, 29, 19);
    for (i = 0; i < 4; i++)
    {
        u16 move = GetMonData(&gPlayerParty[partyMonIndex], MON_DATA_MOVE1 + i);

        MenuPrint(gMoveNames[move], 20, i * 2 + 11);
        if (move != 0)
            r6++;
    }
    InitMenu(0, 20, 11, r6, 0, 9);
}

void Task_HandleItemUseMoveMenuInput(u8 taskId)
{
    if (gMain.newKeys & DPAD_UP)
    {
        PlaySE(SE_SELECT);
        MoveMenuCursor(-1);
    }
    else if (gMain.newKeys & DPAD_DOWN)
    {
        PlaySE(SE_SELECT);
        MoveMenuCursor(1);
    }
    else if (gMain.newKeys & A_BUTTON)
    {
        gUnknown_08376B54[0](taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        gUnknown_08376B54[1](taskId);
    }
}

void DoPPRecoveryItemEffect(u8 taskId, u16 b, TaskFunc c)
{
    const u8 *itemEffect;
    u8 taskId2;

    if (b == ITEM_ENIGMA_BERRY)
        itemEffect = gSaveBlock1.enigmaBerry.itemEffect;
    else
        itemEffect = gItemEffectTable[b - ITEM_POTION];
    gTasks[taskId].func = TaskDummy;
    taskId2 = CreateTask(TaskDummy, 5);
    sub_806E8D0(taskId, b, c);
    if (!(itemEffect[4] & 0x10))
    {
        gTasks[taskId2].data[11] = 0;
        DoRecoverPP(taskId2);
    }
    else
    {
        PlaySE(SE_SELECT);
        sub_806D538(10, 3);
        CreateItemUseMoveMenu(ewram1C000.unk5);
        gTasks[taskId2].func = Task_HandleItemUseMoveMenuInput;
        gMain.newKeys = 0;
    }
}

void ItemUseMoveMenu_HandleMoveSelection(u8 taskId)
{
    HandleDestroyMenuCursors();
    MenuZeroFillWindowRect(19, 10, 29, 19);
    sub_806D5A4();
    gTasks[taskId].data[11] = GetMenuCursorPos();
    DoRecoverPP(taskId);
}

void ItemUseMoveMenu_HandleCancel(u8 taskId)
{
    HandleDestroyMenuCursors();
    MenuZeroFillWindowRect(19, 10, 29, 19);
    if (gMain.inBattle)
        gTasks[ewram1C000.unk4].func = SetUpBattlePokemonMenu;
    else
        gTasks[ewram1C000.unk4].func = sub_808B0C0;
    sub_806D538(3, 0);
    DestroyTask(taskId);
}

void DoRecoverPP(u8 taskId)
{
    u16 r5 = 0;

    if (ExecuteTableBasedItemEffect__(ewram1C000.unk5, ewram1C000.unk6, gTasks[taskId].data[11]))
    {
        gUnknown_0202E8F4 = r5;
        PlaySE(SE_SELECT);
        sub_806E834(gOtherText_WontHaveAnyEffect, 1);
    }
    else
    {
        gUnknown_0202E8F4 = 1;
        PlaySE(SE_KAIFUKU);
        RemoveBagItem(ewram1C000.unk6, 1);
        r5 = GetMonData(ewram1C000.pokemon, MON_DATA_MOVE1 + gTasks[taskId].data[11]);
        StringCopy(gStringVar1, gMoveNames[r5]);
        GetMedicineItemEffectMessage(ewram1C000.unk6);
        sub_806E834(gStringVar4, 1);
    }
    gTasks[taskId].func = sub_806FB0C;
}

void DoPPUpItemEffect(u8 taskId, u16 b, TaskFunc c)
{
    gTasks[taskId].func = TaskDummy;
    sub_806E8D0(taskId, b, c);
    PlaySE(SE_SELECT);
    sub_806D538(11, 3);
    CreateItemUseMoveMenu(ewram1C000.unk5);
    CreateTask(Task_HandleItemUseMoveMenuInput, 5);
    gMain.newKeys = 0;
}

void DoRareCandyItemEffect(u8 taskId, u16 b, TaskFunc c)
{
    u8 i;
    bool8 r0;

    gTasks[taskId].func = TaskDummy;
    sub_806E8D0(taskId, b, c);

    if (GetMonData(ewram1C000.pokemon, MON_DATA_LEVEL) != 100)
    {
        for (i = 0; i < 6; i++)
            ewram1B000.statGrowths[i] = GetMonData(ewram1C000.pokemon, gUnknown_08376D1C[i]);
        r0 = ExecuteTableBasedItemEffect__(ewram1C000.unk5, b, 0);
    }
    else
        r0 = TRUE;

    if (r0)
    {
        gUnknown_0202E8F4 = 0;
        PlaySE(SE_SELECT);
        sub_806E834(gOtherText_WontHaveAnyEffect, 1);
        CreateTask(sub_806FB0C, 5);
    }
    else
    {
        u8 level;

        gUnknown_0202E8F4 = 1;
        PlayFanfareByFanfareNum(0);
        RedrawPokemonInfoInMenu(ewram1C000.unk5, ewram1C000.pokemon);
        RemoveBagItem(b, 1);
        GetMonNickname(ewram1C000.pokemon, gStringVar1);
        level = GetMonData(ewram1C000.pokemon, MON_DATA_LEVEL);
        ConvertIntToDecimalStringN(gStringVar2, level, 0, 3);
        StringExpandPlaceholders(gStringVar4, gOtherText_ElevatedTo);
        sub_806E834(gStringVar4, 1);
        CreateTask(Task_RareCandy1, 5);
    }
}

void Task_RareCandy1(u8 taskId)
{
    if (WaitFanfare(0) && gUnknown_0202E8F6 == 0)
    {
        if ((gMain.newKeys & A_BUTTON) || (gMain.newKeys & B_BUTTON))
        {
            PlaySE(SE_SELECT);
            PrintStatGrowthsInLevelUpWindow(taskId);
            gTasks[taskId].func = Task_RareCandy2;
        }
    }
}

void Task_RareCandy2(u8 taskId)
{
    if ((gMain.newKeys & A_BUTTON) || (gMain.newKeys & B_BUTTON))
    {
        PlaySE(SE_SELECT);
        PrintNewStatsInLevelUpWindow(taskId);
        gTasks[taskId].func = Task_RareCandy3;
    }
}

#if ENGLISH
void PrintStatGrowthsInLevelUpWindow(u8 taskId)
{
    u8 i;

    MenuDrawTextWindow(11, 0, 29, 7);

    for (i = 0; i < NUM_STATS; i++)
    {
        u8 x;
        u8 y;
        u32 stat;

        stat = GetMonData(ewram1C000.pokemon, gUnknown_08376D1C[i]);

        ewram1B000.statGrowths[i + NUM_STATS] = stat;
        ewram1B000.statGrowths[i] = stat - ewram1B000.statGrowths[i];

        x = (i / 3) * 9 + 11;
        y = ((i % 3) << 1) + 1;

        MenuPrint_PixelCoords(gUnknown_08376D04[i], (x + 1) * 8, y * 8, 1);

        if (i == 2)
            MenuPrint_PixelCoords(gOtherText_TallPlusAndRightArrow, (x + 6) * 8 + 6, y * 8, 0);
        else
            MenuPrint_PixelCoords(gOtherText_TallPlusAndRightArrow, (x + 6) * 8 + 6, y * 8, 1);

        gStringVar1[0] = EXT_CTRL_CODE_BEGIN;
        gStringVar1[1] = 0x14;
        gStringVar1[2] = 0x06;

        ConvertIntToDecimalStringN(gStringVar1 + 3, ewram1B000.statGrowths[i], 1, 2);

        MenuPrint_PixelCoords(gStringVar1, (x + 6) * 8 + 12, y * 8, 0);
    }
}
#elif GERMAN
__attribute__((naked))
void PrintStatGrowthsInLevelUpWindow(u8 taskId) {
    asm(".syntax unified\n\
    push {r4-r7,lr}\n\
    mov r7, r10\n\
    mov r6, r9\n\
    mov r5, r8\n\
    push {r5-r7}\n\
    movs r0, 0xB\n\
    movs r1, 0\n\
    movs r2, 0x1D\n\
    movs r3, 0x7\n\
    bl MenuDrawTextWindow\n\
    movs r7, 0\n\
    ldr r0, _0807092C @ =gStringVar1\n\
    mov r10, r0\n\
    movs r1, 0xFC\n\
    mov r9, r1\n\
    movs r2, 0x13\n\
    mov r8, r2\n\
_0807086C:\n\
    ldr r1, _08070930 @ =0x0201c000\n\
    ldr r0, [r1]\n\
    ldr r1, _08070934 @ =gUnknown_08376D1C\n\
    adds r1, r7, r1\n\
    ldrb r1, [r1]\n\
    bl GetMonData\n\
    adds r1, r7, 0x6\n\
    lsls r1, 1\n\
    ldr r2, _08070938 @ =0x0201b264\n\
    adds r1, r2, r1\n\
    strh r0, [r1]\n\
    lsls r6, r7, 1\n\
    adds r6, r2, r6\n\
    ldrh r1, [r6]\n\
    subs r0, r1\n\
    strh r0, [r6]\n\
    adds r0, r7, 0\n\
    movs r1, 0x3\n\
    bl __udivsi3\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    lsls r4, r0, 3\n\
    adds r4, r0\n\
    adds r4, 0xB\n\
    lsls r4, 24\n\
    lsrs r4, 24\n\
    adds r0, r7, 0\n\
    movs r1, 0x3\n\
    bl __umodsi3\n\
    adds r5, r0, 0\n\
    lsls r5, 1\n\
    adds r5, 0x1\n\
    lsls r5, 24\n\
    lsrs r5, 24\n\
    ldr r1, _0807093C @ =gUnknown_08376D04\n\
    lsls r0, r7, 2\n\
    adds r0, r1\n\
    ldr r1, [r0]\n\
    mov r0, r10\n\
    bl StringCopy\n\
    adds r2, r0, 0\n\
    mov r0, r9\n\
    strb r0, [r2]\n\
    adds r2, 0x1\n\
    mov r1, r8\n\
    strb r1, [r2]\n\
    adds r2, 0x1\n\
    movs r0, 0x2E\n\
    strb r0, [r2]\n\
    adds r2, 0x1\n\
    adds r0, r2, 0\n\
    ldr r1, _08070940 @ =gOtherText_TallPlusAndRightArrow\n\
    bl StringCopy\n\
    adds r2, r0, 0\n\
    mov r0, r9\n\
    strb r0, [r2]\n\
    adds r2, 0x1\n\
    mov r1, r8\n\
    strb r1, [r2]\n\
    adds r2, 0x1\n\
    movs r0, 0x34\n\
    strb r0, [r2]\n\
    adds r2, 0x1\n\
    movs r0, 0\n\
    ldrsh r1, [r6, r0]\n\
    adds r0, r2, 0\n\
    movs r2, 0x1\n\
    movs r3, 0x2\n\
    bl ConvertIntToDecimalStringN\n\
    adds r4, 0x1\n\
    lsls r4, 24\n\
    lsrs r4, 24\n\
    mov r0, r10\n\
    adds r1, r4, 0\n\
    adds r2, r5, 0\n\
    bl MenuPrint\n\
    adds r0, r7, 0x1\n\
    lsls r0, 24\n\
    lsrs r7, r0, 24\n\
    cmp r7, 0x5\n\
    bls _0807086C\n\
    pop {r3-r5}\n\
    mov r8, r3\n\
    mov r9, r4\n\
    mov r10, r5\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0\n\
    .align 2, 0\n\
_0807092C: .4byte gStringVar1\n\
_08070930: .4byte 0x0201c000\n\
_08070934: .4byte gUnknown_08376D1C\n\
_08070938: .4byte 0x0201b264\n\
_0807093C: .4byte gUnknown_08376D04\n\
_08070940: .4byte gOtherText_TallPlusAndRightArrow\n\
    .syntax divided\n");
}
#endif

void PrintNewStatsInLevelUpWindow(u8 taskId)
{
    u8 i;

    for (i = 0; i < NUM_STATS; i++)
    {
        u8 x;
        u8 y;
        u32 stat;
        u32 newStatIndex;

        stat = GetMonData(ewram1C000.pokemon, gUnknown_08376D1C[i]);
        newStatIndex = i + 6;
        ewram1B000.statGrowths[newStatIndex] = stat;

        x = ((i / 3) * 9) + 11;
        y = ((i % 3) << 1) + 1;

        gStringVar1[0] = EXT_CTRL_CODE_BEGIN;
        gStringVar1[1] = 0x14;
        gStringVar1[2] = 0x06;

        ConvertIntToDecimalStringN(gStringVar1 + 3, ewram1B000.statGrowths[newStatIndex], 1, 3);
        MenuPrint_PixelCoords(gStringVar1, (x + 6) * 8 + 6, y * 8, 0);
    }
}

void RedrawPokemonInfoInMenu(u8 monIndex, struct Pokemon *pokemon)
{
    u8 statusAndPkrs;
    bool8 isDoubleBattle;
    u16 currentHP;
    u16 maxHP;
    u8 icon;

    statusAndPkrs = GetMonStatusAndPokerus(pokemon);
    if (statusAndPkrs == 0 || statusAndPkrs == 6)
    {
        PartyMenuUpdateLevelOrStatus(pokemon, monIndex);
    }

    isDoubleBattle = IsDoubleBattle();

    currentHP = GetMonData(pokemon, MON_DATA_HP);
    maxHP = GetMonData(pokemon, MON_DATA_MAX_HP);

    PartyMenuDoPrintHP(monIndex, isDoubleBattle, currentHP, maxHP);
    PartyMenuTryDrawHPBar(monIndex, pokemon);

    icon = GetMonIconSpriteId_maybe(ewram1C000.unk4, monIndex);
    SetMonIconAnim(icon, pokemon);

    task_pc_turn_off(&gUnknown_083769A8[IsDoubleBattle() * 12 + monIndex * 2], 7);
    ewram1B000.unk261 = 2;
}

void Task_RareCandy3(u8 taskId)
{
    if (WaitFanfare(0))
    {
        if ((gMain.newKeys & A_BUTTON) || (gMain.newKeys & B_BUTTON))
        {
            u16 learnedMove;
            u16 evolutionSpecies;

            MenuZeroFillWindowRect(WINDOW_LEFT + 8, 0, WINDOW_RIGHT + 3, 7);

            learnedMove = MonTryLearningNewMove(ewram1C000.pokemon, TRUE);
            ewram1B000.unk282 = 1;

            switch (learnedMove)
            {
                case 0:
                    // No move is learned.
                    evolutionSpecies = GetEvolutionTargetSpecies(ewram1C000.pokemon, 0, 0);
                    if (evolutionSpecies != 0)
                    {
                        gCB2_AfterEvolution = sub_80A53F8;
                        BeginEvolutionScene(ewram1C000.pokemon, evolutionSpecies, TRUE, ewram1C000.unk5);
                        DestroyTask(taskId);
                    }
                    else
                    {
                        sub_8070D90(taskId);
                    }
                    break;
                case 0xFFFF:
                    // Mon already knows 4 moves.
                    GetMonNickname(ewram1C000.pokemon, gStringVar1);
                    StringCopy(gStringVar2, gMoveNames[gMoveToLearn]);

                    StringExpandPlaceholders(gStringVar4, gOtherText_WantsToLearn);
                    sub_806E834(gStringVar4, 1);

                    ewram1C000.unk8 = gMoveToLearn;
                    gTasks[taskId].func = sub_806F358;
                    break;
                case 0xFFFE:
                    // Move was already known by the mon.
                    gTasks[taskId].func = TeachMonMoveInPartyMenu;
                    break;
                default:
                    // Mon automatically learned a move because it knew less than four moves.
                    GetMonNickname(ewram1C000.pokemon, gStringVar1);
                    StringCopy(gStringVar2, gMoveNames[learnedMove]);

                    StringExpandPlaceholders(gStringVar4, gOtherText_LearnedMove);
                    sub_806E834(gStringVar4, 1);

                    gTasks[taskId].func = Task_TeamMonTMMove3;
                    break;
            }
        }
    }
}

void TeachMonMoveInPartyMenu(u8 taskId)
{
    u16 learnedMove;
    u16 evolutionSpecies;

    learnedMove = MonTryLearningNewMove(ewram1C000.pokemon, FALSE);
    switch (learnedMove)
    {
        case 0:
            // No move is learned.
            evolutionSpecies = GetEvolutionTargetSpecies(ewram1C000.pokemon, 0, 0);
            if (evolutionSpecies != 0)
            {
                gCB2_AfterEvolution = sub_80A53F8;
                BeginEvolutionScene(ewram1C000.pokemon, evolutionSpecies, TRUE, ewram1C000.unk5);
                DestroyTask(taskId);
            }
            else
            {
                sub_8070D90(taskId);
            }
            break;
        case 0xFFFF:
            // Mon already knows 4 moves.
            GetMonNickname(ewram1C000.pokemon, gStringVar1);
            StringCopy(gStringVar2, gMoveNames[gMoveToLearn]);

            StringExpandPlaceholders(gStringVar4, gOtherText_WantsToLearn);
            sub_806E834(gStringVar4, 1);

            ewram1C000.unk8 = gMoveToLearn;
            gTasks[taskId].func = sub_806F358;
            break;
        case 0xFFFE:
            // Move was already known by the mon. Go on the the next move to be learned.
            TeachMonMoveInPartyMenu(taskId);
            break;
        default:
            // Mon automatically learned a move because it knew less than four moves.
            GetMonNickname(ewram1C000.pokemon, gStringVar1);
            StringCopy(gStringVar2, gMoveNames[learnedMove]);

            StringExpandPlaceholders(gStringVar4, gOtherText_LearnedMove);
            sub_806E834(gStringVar4, 1);

            gTasks[taskId].func = Task_TeamMonTMMove3;
            break;
    }
}

static void sub_8070D90(u8 taskId)
{
    gTasks[ewram1C000.unk4].func = ewram1C000.unk10;
    DestroyTask(taskId);
}

void DoEvolutionStoneItemEffect(u8 taskId, u16 evolutionStoneItem, TaskFunc c)
{
    PlaySE(SE_SELECT);

    gTasks[taskId].func = TaskDummy;
    sub_806E8D0(taskId, evolutionStoneItem, c);

    gCB2_AfterEvolution = sub_80A53F8;

    if (ExecuteTableBasedItemEffect__(ewram1C000.unk5, evolutionStoneItem, 0))
    {
        gUnknown_0202E8F4 = 0;
        sub_806E834(gOtherText_WontHaveAnyEffect, 1);

        CreateTask(sub_806FB0C, 5);
    }
    else
    {
        RemoveBagItem(evolutionStoneItem, 1);
    }
}

// u8 GetItemEffectType(u16 item)
// {
//     const u8 *itemEffect;
//     register u8 itemEffect0 asm("r1");
//     u8 mask;

//     // Read the item's effect properties.
//     if (item == ITEM_ENIGMA_BERRY)
//     {
//         itemEffect = gSaveBlock1.enigmaBerry.itemEffect;
//     }
//     else
//     {
//         itemEffect = gItemEffectTable[item - ITEM_POTION];
//     }

//     itemEffect0 = itemEffect[0];
//     mask = 0x3F;

//     if ((itemEffect0 & mask) || itemEffect[1] || itemEffect[2] || (itemEffect[3] & 0x80))
//     {
//         return 0;
//     }
//     else if (itemEffect0 & 0x40)
//     {
//         return 10;
//     }
//     else if (itemEffect[3] & 0x40)
//     {
//         return 1;
//     }
//     else if ((itemEffect[3] & mask) || (itemEffect0 >> 7))
//     {
//         if ((itemEffect[3] & mask) == 0x20)
//         {
//             return 4;
//         }
//         else if ((itemEffect[3] & mask) == 0x10)
//         {
//             return 3;
//         }
//         else if ((itemEffect[3] & mask) == 0x8)
//         {
//             return 5;
//         }
//         else if ((itemEffect[3] & mask) == 0x4)
//         {
//             return 6;
//         }
//         else if ((itemEffect[3] & mask) == 0x2)
//         {
//             return 7;
//         }
//         else if ((itemEffect[3] & mask) == 0x1)
//         {
//             return 8;
//         }
//         else if ((itemEffect0 >> 7) != 0 && (itemEffect[3] & mask) == 0)
//         {
//             return 9;
//         }
//         else
//         {
//             return 11;
//         }
//     }
//     else if (itemEffect[4] & 0x44)
//     {
//         return 2;
//     }
//     else if (itemEffect[4] & 0x2)
//     {
//         return 12;
//     }
//     else if (itemEffect[4] & 0x1)
//     {
//         return 13;
//     }
//     else if (itemEffect[5] & 0x8)
//     {
//         return 14;
//     }
//     else if (itemEffect[5] & 0x4)
//     {
//         return 15;
//     }
//     else if (itemEffect[5] & 0x2)
//     {
//         return 16;
//     }
//     else if (itemEffect[5] & 0x1)
//     {
//         return 17;
//     }
//     else if (itemEffect[4] & 0x80)
//     {
//         return 18;
//     }
//     else if (itemEffect[4] & 0x20)
//     {
//         return 19;
//     }
//     else if (itemEffect[5] & 0x10)
//     {
//         return 20;
//     }
//     else if (itemEffect[4] & 0x18)
//     {
//         return 21;
//     }
//     else
//     {
//         return 22;
//     }
// }
__attribute__((naked))
u8 GetItemEffectType(u16 item)
{
    asm(".syntax unified\n\
    push {r4,r5,lr}\n\
    lsls r0, 16\n\
    lsrs r0, 16\n\
    cmp r0, 0xAF\n\
    bne _08070E5C\n\
    ldr r4, _08070E58 @ =gSaveBlock1 + 0x3676\n\
    b _08070E66\n\
    .align 2, 0\n\
_08070E58: .4byte gSaveBlock1 + 0x3676\n\
_08070E5C:\n\
    ldr r1, _08070E8C @ =gItemEffectTable\n\
    subs r0, 0xD\n\
    lsls r0, 2\n\
    adds r0, r1\n\
    ldr r4, [r0]\n\
_08070E66:\n\
    ldrb r1, [r4]\n\
    movs r5, 0x3F\n\
    adds r0, r5, 0\n\
    ands r0, r1\n\
    cmp r0, 0\n\
    bne _08070E88\n\
    ldrb r0, [r4, 0x1]\n\
    cmp r0, 0\n\
    bne _08070E88\n\
    ldrb r0, [r4, 0x2]\n\
    cmp r0, 0\n\
    bne _08070E88\n\
    ldrb r3, [r4, 0x3]\n\
    movs r0, 0x80\n\
    ands r0, r3\n\
    cmp r0, 0\n\
    beq _08070E90\n\
_08070E88:\n\
    movs r0, 0\n\
    b _08070F8A\n\
    .align 2, 0\n\
_08070E8C: .4byte gItemEffectTable\n\
_08070E90:\n\
    movs r2, 0x40\n\
    adds r0, r2, 0\n\
    ands r0, r1\n\
    cmp r0, 0\n\
    beq _08070E9E\n\
    movs r0, 0xA\n\
    b _08070F8A\n\
_08070E9E:\n\
    adds r0, r2, 0\n\
    ands r0, r3\n\
    cmp r0, 0\n\
    beq _08070EAA\n\
    movs r0, 0x1\n\
    b _08070F8A\n\
_08070EAA:\n\
    adds r2, r5, 0\n\
    ands r2, r3\n\
    cmp r2, 0\n\
    bne _08070EB8\n\
    lsrs r0, r1, 7\n\
    cmp r0, 0\n\
    beq _08070EFA\n\
_08070EB8:\n\
    cmp r2, 0x20\n\
    bne _08070EC0\n\
    movs r0, 0x4\n\
    b _08070F8A\n\
_08070EC0:\n\
    cmp r2, 0x10\n\
    bne _08070EC8\n\
    movs r0, 0x3\n\
    b _08070F8A\n\
_08070EC8:\n\
    cmp r2, 0x8\n\
    bne _08070ED0\n\
    movs r0, 0x5\n\
    b _08070F8A\n\
_08070ED0:\n\
    cmp r2, 0x4\n\
    bne _08070ED8\n\
    movs r0, 0x6\n\
    b _08070F8A\n\
_08070ED8:\n\
    cmp r2, 0x2\n\
    bne _08070EE0\n\
    movs r0, 0x7\n\
    b _08070F8A\n\
_08070EE0:\n\
    cmp r2, 0x1\n\
    bne _08070EE8\n\
    movs r0, 0x8\n\
    b _08070F8A\n\
_08070EE8:\n\
    lsrs r0, r1, 7\n\
    cmp r0, 0\n\
    beq _08070EF6\n\
    cmp r2, 0\n\
    bne _08070EF6\n\
    movs r0, 0x9\n\
    b _08070F8A\n\
_08070EF6:\n\
    movs r0, 0xB\n\
    b _08070F8A\n\
_08070EFA:\n\
    ldrb r1, [r4, 0x4]\n\
    movs r0, 0x44\n\
    ands r0, r1\n\
    adds r2, r1, 0\n\
    cmp r0, 0\n\
    beq _08070F0A\n\
    movs r0, 0x2\n\
    b _08070F8A\n\
_08070F0A:\n\
    movs r5, 0x2\n\
    adds r0, r5, 0\n\
    ands r0, r2\n\
    cmp r0, 0\n\
    beq _08070F18\n\
    movs r0, 0xC\n\
    b _08070F8A\n\
_08070F18:\n\
    movs r3, 0x1\n\
    adds r0, r3, 0\n\
    ands r0, r2\n\
    cmp r0, 0\n\
    beq _08070F26\n\
    movs r0, 0xD\n\
    b _08070F8A\n\
_08070F26:\n\
    ldrb r1, [r4, 0x5]\n\
    movs r0, 0x8\n\
    ands r0, r1\n\
    cmp r0, 0\n\
    beq _08070F34\n\
    movs r0, 0xE\n\
    b _08070F8A\n\
_08070F34:\n\
    movs r0, 0x4\n\
    ands r0, r1\n\
    cmp r0, 0\n\
    beq _08070F40\n\
    movs r0, 0xF\n\
    b _08070F8A\n\
_08070F40:\n\
    adds r0, r5, 0\n\
    ands r0, r1\n\
    cmp r0, 0\n\
    beq _08070F4C\n\
    movs r0, 0x10\n\
    b _08070F8A\n\
_08070F4C:\n\
    adds r0, r3, 0\n\
    ands r0, r1\n\
    cmp r0, 0\n\
    beq _08070F58\n\
    movs r0, 0x11\n\
    b _08070F8A\n\
_08070F58:\n\
    movs r0, 0x80\n\
    ands r0, r2\n\
    cmp r0, 0\n\
    beq _08070F64\n\
    movs r0, 0x12\n\
    b _08070F8A\n\
_08070F64:\n\
    movs r0, 0x20\n\
    ands r0, r2\n\
    cmp r0, 0\n\
    beq _08070F70\n\
    movs r0, 0x13\n\
    b _08070F8A\n\
_08070F70:\n\
    movs r0, 0x10\n\
    ands r0, r1\n\
    cmp r0, 0\n\
    beq _08070F7C\n\
    movs r0, 0x14\n\
    b _08070F8A\n\
_08070F7C:\n\
    movs r0, 0x18\n\
    ands r0, r2\n\
    cmp r0, 0\n\
    bne _08070F88\n\
    movs r0, 0x16\n\
    b _08070F8A\n\
_08070F88:\n\
    movs r0, 0x15\n\
_08070F8A:\n\
    pop {r4,r5}\n\
    pop {r1}\n\
    bx r1\n\
    .syntax divided\n");
}

void unref_sub_8070F90(void)
{
    FlagSet(SYS_POKEDEX_GET);
    FlagSet(SYS_POKEMON_GET);
    FlagSet(SYS_POKENAV_GET);
}
