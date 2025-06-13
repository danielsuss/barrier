# Grave Modifier Setup for Barrier

## Overview
This implementation adds support for using the grave key (`) as a hotkey modifier in Barrier, similar to Control, Alt, and Shift.

## Required Setup

### 1. Code Changes
The following code changes have been implemented:

- **XWindowsUtil.cpp**: Added `case XK_grave: return kKeyModifierBitGrave;` to `getModifierBitForKeySym()`
- **XWindowsKeyState.cpp**: Added fallback mapping for grave modifier to Mod4 in `updateKeysymMapXKB()`
- **key_types.cpp**: Already included grave modifier in `kModifierNameMap`

### 2. X11 Modifier Mapping (REQUIRED)
The grave key must be mapped to an X11 modifier for hotkeys to work. Run this command:

```bash
xmodmap -e "add mod4 = grave"
```

### 3. Make it Permanent
To make the X11 mapping persistent across reboots, add this line to `~/.xsessionrc`:

```bash
echo 'xmodmap -e "add mod4 = grave"' >> ~/.xsessionrc
```

## Usage
Once setup is complete, you can use grave modifier hotkeys in your Barrier configuration:

```
keystroke(Grave+1) = switchToScreen(screen1,960,540)
keystroke(Grave+2) = switchToScreen(screen2,960,540)
```

## Verification
To verify the setup:

1. Check modifier mapping: `xmodmap -pm`
   - Should show `grave (0x31)` in the mod4 line
2. Test hotkeys: Press and hold grave, then press a number key
3. Check Barrier logs for successful hotkey registration

## Troubleshooting
- If hotkeys don't work, verify grave is mapped to mod4: `xmodmap -pm`
- If mapping is lost after reboot, ensure `~/.xsessionrc` contains the xmodmap command
- Restart Barrier server after making X11 mapping changes