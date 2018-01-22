@echo off
set PS3SDK=/c/PSDK3v2
set WIN_PS3SDK=C:/PSDK3v2
set PATH=%WIN_PS3SDK%/mingw/msys/1.0/bin;%WIN_PS3SDK%/mingw/bin;%WIN_PS3SDK%/ps3dev/bin;%WIN_PS3SDK%/ps3dev/ppu/bin;%WIN_PS3SDK%/ps3dev/spu/bin;%WIN_PS3SDK%/mingw/Python27;%PATH%;
set PSL1GHT=%PS3SDK%/psl1ght
set PS3DEV=%PS3SDK%/ps3dev


if exist Red-J_XMB_Customiser_v1.0.pkg del Red-J_XMB_Customiser_v1.0.pkg>nul

if exist Red-J_XMB_Customiser_v1.0.elf del Red-J_XMB_Customiser_v1.0.elf>nul
if exist Red-J_XMB_Customiser_v1.0.self del Red-J_XMB_Customiser_v1.0.self>nul
if exist build del /s/q build\*.*>nul

make pkg

ren build\pkg EP0001-REDJ00011_00-0000000000000000
param_sfo_editor.exe build\EP0001-REDJ00011_00-0000000000000000\PARAM.SFO "ATTRIBUTE" 133

if exist Red-J_XMB_Customiser_v1.0.elf del Red-J_XMB_Customiser_v1.0.elf>nul
if exist Red-J_XMB_Customiser_v1.0.self del Red-J_XMB_Customiser_v1.0.self>nul
if exist Red-J_XMB_Customiser_v1.0.pkg del Red-J_XMB_Customiser_v1.0.pkg>nul
if exist build del /q build\*.*>nul
if not exist build goto end

echo ContentID = EP0001-REDJ00011_00-0000000000000000>package.conf
echo Klicensee = 000000000000000000000000000000000000>>package.conf
echo PackageVersion = 01.00>>package.conf
echo DRMType = Free>>package.conf
echo ContentType = GameExec>>package.conf

psn_package_npdrm.exe -n package.conf build\EP0001-REDJ00011_00-0000000000000000

del package.conf

if exist Red-J_XMB_Customiser_v1.0 del Red-J_XMB_Customiser_v1.0.pkg>nul
move /y EP0001-REDJ00011_00-0000000000000000.pkg Red-J_XMB_Customiser_v1.0.pkg
pause

del /s/q build>nul
rd /q/s build

:end
