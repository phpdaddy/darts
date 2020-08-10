#!/usr/bin/env sh
adb install -r bin/darts-debug.apk
adb shell am start -n org.oxygine.darts/org.oxygine.darts.MainActivity
