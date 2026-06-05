#include <3ds.h>
#include <citro2d.h>
#include "sonnybun.h"
int main(void) {
    romfsInit();
    gfxInitDefault(); gfxSet3D(true);
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE); C2D_Init(C2D_DEFAULT_MAX_OBJECTS); C2D_Prepare();
    C3D_RenderTarget* topL = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget* topR = C2D_CreateScreenTarget(GFX_TOP, GFX_RIGHT);
    C2D_SpriteSheet sheet = C2D_SpriteSheetLoad("romfs:/gfx/sonnybun.t3x");
    C2D_Sprite spr; C2D_SpriteFromSheet(&spr, sheet, 0); C2D_SpriteSetCenter(&spr, .5f, .5f);
    float x = 200.f, y = 120.f;
    while (aptMainLoop()) {
        hidScanInput();
        u32 h = hidKeysHeld(); if (h & KEY_START) break;
        float dx = 0, dy = 0;
        if (h & KEY_LEFT)  dx += 3.f; if (h & KEY_RIGHT) dx -= 3.f;
        if (h & KEY_UP)    dy += 3.f; if (h & KEY_DOWN)  dy -= 3.f;
        x += dx; y += dy;
        float sep = osGet3DSliderState() * 6.f;
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(topL, C2D_Color32(0, 0, 0, 0xFF)); C2D_SceneBegin(topL);
        C2D_SpriteSetPos(&spr, x - sep, y); C2D_DrawSprite(&spr);
        C2D_TargetClear(topR, C2D_Color32(0, 0, 0, 0xFF)); C2D_SceneBegin(topR);
        C2D_SpriteSetPos(&spr, x + sep, y); C2D_DrawSprite(&spr);
        C3D_FrameEnd(0);
    }
    C2D_SpriteSheetFree(sheet); C2D_Fini(); C3D_Fini(); romfsExit(); gfxExit();
}