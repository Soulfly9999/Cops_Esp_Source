#include <list>
#include <vector>
#include <string>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "Unity/Vector2.h"
#include "Unity/Vector3.h"
#include "Unity/Rect.h"
#include "Unity/Color.h"
#include "Unity/Quaternion.h"
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "Includes/Chams.h"
#include "Includes/MonoString.h"
#include "Includes/Strings.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu.h"
#include "ESPDraw.h"
#include "hooks.h"
#include "ESPManager.h"
#include "Unity/ColorID.h"

#include <And64InlineHook/And64InlineHook.hpp>
#define targetLibName OBFUSCATE("libil2cpp.so")
#define unityLib OBFUSCATE("libunity.so")
ESPManager *espManager;
NepEsp es;
struct My_Patches {
    MemoryPatch Body1, Head1, Stw, EspR, Body,Spr,recoil, Bp, Bp1, Bp2, Bp3, Bp4, Bp5, Bp6, Bp7, Bp8, Bp9, Bp10, Bp11, Bp12, Bp13, Bp14, Bp15, Bp16, Bp17, Bp18, Bp19, Bp20, Bp21, Bp22, Bp23, Bp24, Bp25, Bp26, Bp27, Bp28, Bp29, Bp30, Bp31, Bp32, Bp33, Bp34, Bp35, Bp36, Bp37, Bp38, Bp39, Bp40, Bp41, Bp42, Bp43, Bp44, Bp45, Bp46, Bp47, Bp48, Bp49, Bp50;
 
} hexPatches;
bool Bypas,Body1,recoil,EspR,Gameplay,Head,Head1,Stw,Sp,Spr,ESPCrosshair,ESPHealth,ESPLine,ESPBox,HeadDot,ESP = false;
bool tutorial = false;
float fov,hb,bb,speed,fly;
float upval = 0.9f;
float upval2 = 0.9f;
float upval3 = 0.5f;
float upval4 = 0.5f;
float upval5 = 4.0f;
int HeadDotHeight = 0.5;
int LineFrom = 3;
int RedColor;
int GreenColor;
int BlueColor;
int Alpha;
int CrosshairSize;
int fillAlpha = 63;
void DrawESP(NepEsp esp, int screenWidth, int screenHeight) {
	
	
if(ESP) {
    if (espManager->enemies->empty()) {
        return;
    }
    for (int i = 0; i < espManager->enemies->size(); i++) {
        void *Player = (*espManager->enemies)[i]->object;
        if (PlayerAlive(Player)) {
            Color clr;
            clr.a = 255;
            Rect rect;
            Vector3 PlayerPos = GetPlayerLocation(Player);
            void *Cam = get_camera();
            Vector3 PosNew = {0.f, 0.f, 0.f};
            PosNew = WorldToScreenPoint(Cam, PlayerPos);
            if (PosNew.z < 1.f) continue;
            Vector3 Origin;
            Origin = PlayerPos;
            Origin.y += 0.7f;
            float posnum = upval; 
            float posnum2 = upval2;
            float posnum5 = upval5;
            float posnum3 = upval4;
            float posnum4 = HeadDotHeight;
            Origin.y += posnum;
            Vector3 BoxPosNew = {0.f, 0.f, 0.f};
            BoxPosNew = WorldToScreenPoint(Cam, Origin);
            float Hight =
                    abs(BoxPosNew.y - PosNew.y) * (posnum2 / posnum), Width = Hight * upval4;

            rect = Rect(BoxPosNew.x - Width / 2.f,
                        screenHeight - BoxPosNew.y,
                        Width, Hight
            );
            Vector2 DrawFromTop = Vector2(screenWidth / 2, 0);
            Vector2 DrawFromCrosshair = Vector2(screenWidth / 2, screenHeight / 2);
            Vector2 DrawFromBottom = Vector2(screenWidth / 2, screenHeight);
            Vector2 DrawToHead = Vector2(BoxPosNew.x, screenHeight - BoxPosNew.y + 15);
            Vector2 NamePOS = Vector2(BoxPosNew.x, screenHeight - BoxPosNew.y - 20);
            Vector2 DrawToBottom = Vector2(BoxPosNew.x, screenHeight - PosNew.y);
            Vector2 DrawToTop = Vector2(PosNew.x, screenHeight - BoxPosNew.y);
            Vector2 HealthPOS = Vector2((BoxPosNew.x - Width / 2.f), screenHeight - BoxPosNew.y - 5);
            Vector2 LeftSideDown = Vector2(BoxPosNew.x - Width / 2.f, screenHeight - PosNew.y);
                Vector2 RightSideUp = Vector2(Width, -Hight);
            Color Test(255,1,1,255);

            if (ESPLine) {
                if(LineFrom == 1){
                    esp.DrawLine(Color::Custom(), upval3, DrawFromBottom, DrawToBottom);
                }else if(LineFrom == 2){
                    esp.DrawLine(Color::Custom(), upval3, DrawFromCrosshair, DrawToBottom);
                }else if(LineFrom == 3){
                    esp.DrawLine(Color::Custom(), upval3, DrawFromTop, DrawToTop);
                }

            }
            
            if (ESPHealth) {
            	esp.DrawHorizontalHealthBar(HealthPOS,Width,100,GetPlayerHealth(Player));
}
            if (ESPBox) {
                    esp.DrawBox(Color::Custom(), 2, Rect((jfloat) rect.x, (jfloat) rect.y, (jfloat) rect.w, (jfloat) rect.h));
                    esp.DrawFilledRect(Color::Filled(),LeftSideDown,RightSideUp);

            }
            if (ESPCrosshair) {
            	esp.DrawCrosshair(Color::Custom(), DrawFromCrosshair, CrosshairSize);
            }
            if(HeadDot){
                esp.DrawFilledCircle(Color::Custom(), DrawToHead, upval5);
            }
            
            
                    R = RedColor;
                    G = GreenColor;
                    B = BlueColor;
                    A = 255;
                    
           
        } else {
            espManager->removeEnemyGivenObject(Player);
        }
    }

}
    
}

extern "C"
JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_DrawOn(JNIEnv *env, jclass type, jobject espView, jobject canvas) {
                es = NepEsp(env, espView, canvas);
    if (es.isValid()){
        DrawESP(es, es.getWidth(), es.getHeight());
    }
    
 }

void *enemyPlayer = NULL;
void (*update)(void *player);
void _update(void *player) {
    if (player != NULL) {
        update(player);
        enemyPlayer = player;
    }
    if (ESP) {
        if (enemyPlayer) {
            espManager->tryAddEnemy(player);
        }
    }
}


bool (*old_get_BoolExampl)(void *instance);
bool get_BoolExampl(void *instance) {
    if (instance != NULL && Head) {
        return true;
    }
    return old_get_BoolExampl(instance);
}
bool (*old_get_BoolExamp)(void *instance);
bool get_BoolExamp(void *instance) {
    if (instance != NULL && Sp) {
        return true;
    }
    return old_get_BoolExamp(instance);
}
void *hack_thread(void *) {
    ProcMap il2cppMap;
    do {
        il2cppMap = KittyMemory::getLibraryMap("libil2cpp.so");
        sleep(1);
    } while (!isLibraryLoaded("libil2cpp.so") && mlovinit());
    espManager = new ESPManager();

    do {
        sleep(1);
    } while (!isLibraryLoaded (OBFUSCATE("libil2cpp.so")));
	hexPatches.Stw= MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x68AD64")), OBFUSCATE("00F020E3"));
	hexPatches.recoil = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0xD439DC ")), OBFUSCATE("0000A0E31EFF2FE1"));																
	hexPatches.Spr = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x74DC48")), OBFUSCATE("0000A0E31EFF2FE1"));
	hexPatches.Body1 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x68B534")), OBFUSCATE("0FCAB2EE"));				
	hexPatches.Head1= MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x68B540")), OBFUSCATE("0FCAB2EE"));				
    MSHookFunction((void *) getAbsoluteAddress("libil2cpp.so", 0x676200), (void *) &get_BoolExamp, (void **) &old_get_BoolExamp); //tutorial gameplay
    MSHookFunction((void *) getAbsoluteAddress("libil2cpp.so", 0x675730), (void *) &get_BoolExampl, (void **) &old_get_BoolExampl); //tutorial gameplayay
    MSHookFunction((void *) getAbsoluteAddress(targetLibName,string2Offset(OBFUSCATE_KEY("0x76C9BC", 'x'))), (void *) &_update, (void **) &update); // Character::Gameplay_Update

	hexPatches.Bp = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x53695C")), OBFUSCATE("0000A0E31EFF2FE1"));
	hexPatches.Bp1 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x536AA0")), OBFUSCATE("0000A0E31EFF2FE1"));
	hexPatches.Bp2 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x536BE4")), OBFUSCATE("0000A0E31EFF2FE1"));
	hexPatches.Bp3 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x536D28")), OBFUSCATE("0000A0E31EFF2FE1"));
	hexPatches.Bp4 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x536E6C")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp5 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x536FB0")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp6 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x5370F4")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp7 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x537238")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp8 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x53737C")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp9 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x5374AC")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp10 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x53682C")), OBFUSCATE("0000A0E31EFF2FE1"));			
    hexPatches.Bp11 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x6080FC")), OBFUSCATE("0000A0E31EFF2FE1"));	
    hexPatches.Bp12 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x6087B4")), OBFUSCATE("0000A0E31EFF2FE1"));;		
	hexPatches.Bp13 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x6081D0")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp14 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x537F5C")), OBFUSCATE("0000A0E31EFF2FE1"));				
    hexPatches.Bp15 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x53808C")), OBFUSCATE("0000A0E31EFF2FE1"));	
    hexPatches.Bp16 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x5381BC")), OBFUSCATE("0000A0E31EFF2FE1"));	
	hexPatches.Bp17 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x5382EC")), OBFUSCATE("0000A0E31EFF2FE1"));	
    hexPatches.Bp18 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x53841C")), OBFUSCATE("0000A0E31EFF2FE1"));	
	hexPatches.Bp19 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x53854C")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp20 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x53867C")), OBFUSCATE("0000A0E31EFF2FE1"));				
    hexPatches.Bp21 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x5387AC")), OBFUSCATE("0000A0E31EFF2FE1"));	
    hexPatches.Bp22 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x5388DC")), OBFUSCATE("0000A0E31EFF2FE1"));	
	hexPatches.Bp23 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x538A0C")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp24 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x538B3C")), OBFUSCATE("0000A0E31EFF2FE1"));
	hexPatches.Bp25 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x538C6C")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp26 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x538D9C")), OBFUSCATE("0000A0E31EFF2FE1"));			
    hexPatches.Bp27 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x538ECC ")), OBFUSCATE("0000A0E31EFF2FE1"));		
    hexPatches.Bp28 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x98930C")), OBFUSCATE("0000A0E31EFF2FE1"));
	hexPatches.Bp29 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x9891F0")), OBFUSCATE("0000A0E31EFF2FE1"));		
    hexPatches.Bp30 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x98953C")), OBFUSCATE("0000A0E31EFF2FE1"));	
	hexPatches.Bp31 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x98987C")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp32 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x9896DC")), OBFUSCATE("0000A0E31EFF2FE1"));
	hexPatches.Bp33 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x9896DC")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp34 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x989764")), OBFUSCATE("0000A0E31EFF2FE1"));				
    hexPatches.Bp35 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x988848")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp36 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x988950")), OBFUSCATE("0000A0E31EFF2FE1"));
	hexPatches.Bp37 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x9883DC")), OBFUSCATE("0000A0E31EFF2FE1"));	
    hexPatches.Bp38 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x9886AC")), OBFUSCATE("0000A0E31EFF2FE1"));	
	hexPatches.Bp39 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x98846C")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp40 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x988F5C")), OBFUSCATE("0000A0E31EFF2FE1"));				
    hexPatches.Bp41 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x988F50 ")), OBFUSCATE("0000A0E31EFF2FE1"));	
    hexPatches.Bp42 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x988BE4")), OBFUSCATE("0000A0E31EFF2FE1"));	
    hexPatches.Bp43 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x988D1C")), OBFUSCATE("0000A0E31EFF2FE1"));
	hexPatches.Bp44 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x929F44")), OBFUSCATE("0000A0E31EFF2FE1"));	
    hexPatches.Bp45 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x72FE88")), OBFUSCATE("0000A0E31EFF2FE1"));	
	hexPatches.Bp46 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0xA439D8")), OBFUSCATE("0000A0E31EFF2FE1"));
    hexPatches.Bp47 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x898804")), OBFUSCATE("0000A0E31EFF2FE1"));				
    hexPatches.Bp48 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0xC25F64 ")), OBFUSCATE("0000A0E31EFF2FE1"));	
    hexPatches.Bp49 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x93E698")), OBFUSCATE("0000A0E31EFF2FE1"));	
    hexPatches.Bp50 = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x93E584")), OBFUSCATE("0000A0E31EFF2FE1"));
	
	
	
    return NULL;
}

//JNI calls
extern "C" {


JNIEXPORT jobjectArray
JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_getFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    //Toasts added here so it's harder to remove it
    MakeToast(env, context, OBFUSCATE("Modded by Soulfly"), Toast::LENGTH_LONG);
  
	//please Update Gameplay offset or #hooks.h Offsets
	//Esp Is 32 Bit

    const char *features[] = {
////////////////////////////////////
 OBFUSCATE("Category_ESP"), 
OBFUSCATE("855_Toggle_Enable ESP"), 
OBFUSCATE("856_Toggle_ESP Line"),
OBFUSCATE("857_Toggle_ESP Box"),
OBFUSCATE("891_Toggle_ESP Health"),
OBFUSCATE("858_Toggle_Head Dot"),
OBFUSCATE("859_Toggle_Draw Crosshair"),
//////////////////////////////////////////////////////////////
OBFUSCATE("11111_Spinner_Draw Line From_Bottom,Crosshair,Top"),
OBFUSCATE("Category_Crosshair Settings"), 
OBFUSCATE("865_SeekBar_Size_0_200"), 
OBFUSCATE("Category_Drawing Colors"), 
OBFUSCATE("860_SeekBar_R_0_255"),  
OBFUSCATE("861_SeekBar_G_0_255"), 
OBFUSCATE("862_SeekBar_B_0_255"),  
OBFUSCATE("977_True_Toggle_Skip Gameplay Tutorial"),           
////////////////////////////////////////////////////////////



           
    };
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));
    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    pthread_t ptid;
    pthread_create(&ptid, NULL, antiLeech, NULL);
    return (ret);
}

JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_Preferences_Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint featNum, jstring featName, jint value,
                                        jboolean boolean, jstring str) {
    //Convert java string to c++
    const char *featureName = env->GetStringUTFChars(featName, 0);
    const char *TextInput;
    if (str != NULL)
        TextInput = env->GetStringUTFChars(str, 0);
    else
        TextInput = "Empty";

 switch (featNum) {
 
 case 977:
 Gameplay = boolean;
 break;
 case 978:
 Head = boolean;
 break;
 case 988:
 Sp = boolean;
 break;
 case 979:
 Head1 = boolean;
            if (Head1) {
                hexPatches.Head1 .Modify();
            } else {
                hexPatches.Head1 .Restore();
            }
break;
 case 989:
 Stw = boolean;
            if (Head1) {
                hexPatches.Stw .Modify();
            } else {
                hexPatches.Stw .Restore();
            }
break;
 case 998:
 Spr = boolean;
            if (Sp) {
                hexPatches.Spr .Modify();
            } else {
                hexPatches.Spr .Restore();
            }
break;
 case 996:
 recoil = boolean;
            if (recoil) {
                hexPatches.recoil .Modify();
            } else {
                hexPatches.recoil .Restore();
            }
break;
 case 995:
 Body1 = boolean;
            if (Body1) {
                hexPatches.Body1 .Modify();
            } else {
                hexPatches.Body1 .Restore();
            }
break;
 case 571:
 Bypas = boolean;
            if (Bypas) {
                hexPatches.Bp.Modify();
                hexPatches.Bp1.Modify();
                hexPatches.Bp2.Modify();
                hexPatches.Bp3.Modify();
                hexPatches.Bp4.Modify();
                hexPatches.Bp5.Modify();
				hexPatches.Bp6.Modify();
                hexPatches.Bp7.Modify();
                hexPatches.Bp8.Modify();
                hexPatches.Bp9.Modify();
                hexPatches.Bp11.Modify();
                hexPatches.Bp12.Modify();
				hexPatches.Bp13.Modify();
                hexPatches.Bp14.Modify();
                hexPatches.Bp15.Modify();
                hexPatches.Bp16.Modify();
				hexPatches.Bp17.Modify();
                hexPatches.Bp18.Modify();
				hexPatches.Bp19.Modify();
                hexPatches.Bp20.Modify();
                hexPatches.Bp21.Modify();
                hexPatches.Bp22.Modify();
				hexPatches.Bp23.Modify();
                hexPatches.Bp24.Modify();
				hexPatches.Bp25.Modify();
                hexPatches.Bp26.Modify();
                hexPatches.Bp27.Modify();
                hexPatches.Bp28.Modify();
				hexPatches.Bp29.Modify();
                hexPatches.Bp30.Modify();
				hexPatches.Bp31.Modify();
                hexPatches.Bp32.Modify();
                hexPatches.Bp33.Modify();
                hexPatches.Bp34.Modify();
				hexPatches.Bp35.Modify();
                hexPatches.Bp36.Modify();
				hexPatches.Bp37.Modify();
                hexPatches.Bp38.Modify();
                hexPatches.Bp39.Modify();
                hexPatches.Bp40.Modify();
				hexPatches.Bp41.Modify();
                hexPatches.Bp42.Modify();
                hexPatches.Bp43.Modify();
				hexPatches.Bp44.Modify();
                hexPatches.Bp45.Modify();
                hexPatches.Bp46.Modify();
                hexPatches.Bp47.Modify();
				hexPatches.Bp48.Modify();
                hexPatches.Bp49.Modify();
                hexPatches.Bp50.Modify();
            }else{
                hexPatches.Bp.Restore();
                hexPatches.Bp1.Restore();
                hexPatches.Bp2.Restore();
                hexPatches.Bp3.Restore();
                hexPatches.Bp4.Restore();
                hexPatches.Bp5.Restore();
				hexPatches.Bp6.Restore();
                hexPatches.Bp7.Restore();
                hexPatches.Bp8.Restore();
                hexPatches.Bp9.Restore();
                hexPatches.Bp11.Restore();
                hexPatches.Bp12.Restore();
				hexPatches.Bp13.Restore();
                hexPatches.Bp14.Restore();
                hexPatches.Bp15.Restore();
                hexPatches.Bp16.Restore();
				hexPatches.Bp17.Restore();
                hexPatches.Bp18.Restore();
				hexPatches.Bp19.Restore();
                hexPatches.Bp20.Restore();
                hexPatches.Bp21.Restore();
                hexPatches.Bp22.Restore();
				hexPatches.Bp23.Restore();
                hexPatches.Bp24.Restore();
				hexPatches.Bp25.Restore();
                hexPatches.Bp26.Restore();
                hexPatches.Bp27.Restore();
                hexPatches.Bp28.Restore();
				hexPatches.Bp29.Restore();
                hexPatches.Bp30.Restore();
				hexPatches.Bp31.Restore();
                hexPatches.Bp32.Restore();
                hexPatches.Bp33.Restore();
                hexPatches.Bp34.Restore();
				hexPatches.Bp35.Restore();
                hexPatches.Bp36.Restore();
				hexPatches.Bp37.Restore();
                hexPatches.Bp38.Restore();
                hexPatches.Bp39.Restore();
                hexPatches.Bp40.Restore();
				hexPatches.Bp41.Restore();
                hexPatches.Bp42.Restore();
                hexPatches.Bp43.Restore();
				hexPatches.Bp44.Restore();
                hexPatches.Bp45.Restore();
                hexPatches.Bp46.Restore();
                hexPatches.Bp47.Restore();
				hexPatches.Bp48.Restore();
                hexPatches.Bp49.Restore();
                hexPatches.Bp50.Restore();
            }
            break;
 case 865:
 CrosshairSize = value;
 break;
 
 case 860:
 RedColor = value;
 break;
 
 case 861:
 GreenColor = value;
 break;
 
 case 862:
 BlueColor = value;
 break;
 
 
 case 855:
            ESP = boolean;
            break;
            
            case 856:
            ESPLine = boolean;
            break;
            
            case 857:
            ESPBox = boolean;
            break;
            
        case 891:
ESPHealth = boolean;
break;

case 858:
HeadDot = boolean;
break;    

case 859:
ESPCrosshair = boolean;
break;

case 11111:
switch(value){
                    case 0:
                        LineFrom = 1;//bottom
                        break;
                    case 1:
                        LineFrom = 2;//crosshair
                        break;
                    case 2:
                        LineFrom = 3;//top
                        break;
                }
                break;
               
 }
}
}

//No need to use JNI_OnLoad, since we don't use JNIEnv
//We do this to hide OnLoad from disassembler
__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}
