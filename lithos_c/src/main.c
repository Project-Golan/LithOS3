//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Program entry point.
//
//-----------------------------------------------------------------------------

#include "Lth.h"

#include <ACS_ZDoom.h>
#include <stdlib.h>

#define Test_Text


// Static Functions ----------------------------------------------------------|

[[__call("ScriptS"), __script("Enter")]]
static void main()
{
   Lth_Context *ctx = Lth_ContextNew(320, 200, 0x5000, 0x1000);

#if defined(Test_Text)

   char const *test =
    u8"<Graf> ɢ ᴜ ᴅ\n"
      "ASCII test\n"
      "!\"#$%&'()*+,-./0123456789:;<=>?@A\n"
      "BCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\n\n"
      "kanalang test\n"
      "ァサラルコ（エワイホロア♥ツレカク\n"
      "スノタヘチォメテケウョシヲーキマ\n"
      "ドニリヤゥソムフミンィェト、セ\n"
      "ュハユヒ。ャオモッヌ〜ヨ）ナネ\n\n"
      "Spacing and missing character test\n"
      "The quick b\trown fox jumps over\n"
      "the lazy, ta\tbulated dog.ᴇᴇ\n\n"
      "Iroha\n"
      "色はにほへど　散りぬるを\n"
      "我が世たれぞ　常ならむ・\n"
      "有為の奥山　　今日越えて\n"
      "浅き夢見じ　　酔ひもせず";

   char const **defFont = Lth_ContextResource(ctx, "Base.DefaultFont");
   Lth_Font *font = Lth_FontNew(*defFont);

   for(;;)
   {
      Lth_ContextRun(ctx);

      Lth_FontRunBegin();
      Lth_PrintString(test);
      Lth_FontRunPlain(ctx, font, 40, 20);

      ACS_Delay(1);
   }

#elif defined(Test_Windowing)

   Lth_WindowManager *wm = Lth_WMNew(ctx);

   Lth_Window *window[] = {
      Lth_WindowNew(ctx, "test window",             -1, -1, 50,  100),
      Lth_WindowNew(ctx, u8"テスト　ウィンドー　2", -1, -1, 100, 100),
      Lth_WindowNew(ctx, "test window 3",           -1, -1, 100, 30),
      Lth_WindowNew(ctx, "test window 4",           -1, -1, 100, 100)
   };

   for(int i = 0; i < 4; i++)
      Lth_WMMap(wm, window[i]);

   for(;;)
   {
      Lth_ContextRun(ctx);
      Lth_ControlRun(wm);
      ACS_Delay(1);
   }

#elif defined(Test_NoWM)

   Lth_Window *window = Lth_WindowNew(ctx, "test window", 20, 20, 100, 100);

   for(;;)
   {
      Lth_ContextRun(ctx);
      Lth_ControlRun(window);
      ACS_Delay(1);
   }

#endif

   Lth_ContextDestroy(ctx);
}

// EOF
