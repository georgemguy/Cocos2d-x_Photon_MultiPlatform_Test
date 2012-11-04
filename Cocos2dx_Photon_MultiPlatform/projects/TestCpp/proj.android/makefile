all:
	./build_native.sh
	ant -Dsdk.dir=/Users/georgeguy/Documents/AndroidDevelopment/android-sdk-macosx debug
run:
	adb -d uninstall org.cocos2dx.TestCpp
	adb -d install bin/TestCpp-debug.apk
	adb -d logcat | grep cocos2d
clean:
	rm -rf libs/
	rm -rf obj/
	rm -rf bin/*
	rm -rf gen/
	rm -rf assets/*
