
help: ## show help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sed -e 's/^GNUmakefile://' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

#
# iOS
#

ios-clean: ## ios example clean
	rm -rf tmp/mac

ios: ios-example ## ios example & cmake build
	cd tmp/ios && cmake --build ./

ios-xcodebuild: ios-example ## ios example & xcodebuild
	cd tmp/ios && xcodebuild -scheme "ALL_BUILD" clean archive -archivePath "./tmp/build.xcarchive" -derivedDataPath "./DerivedData" CODE_SIGN_IDENTITY="" CODE_SIGNING_REQUIRED=NO CODE_SIGNING_ALLOWED=NO COMPILER_INDEX_STORE_ENABLE=NO -project "iutest.xcodeproj"

ios-simu: ios-example ## ios simulator example & build
	cd tmp/ios && xcodebuild -scheme "ALL_BUILD" BUILD_DIR="./tmp/ios/SimulatorBuildDir" -derivedDataPath "./SimulatorDerivedData" -configuration "Debug" COMPILER_INDEX_STORE_ENABLE=NO  ONLY_ACTIVE_ARCH=NO -arch x86_64 -project "iutest.xcodeproj"
	# cd tmp/ios && xcodebuild -scheme "ALL_BUILD" BUILD_DIR="./tmp/ios/SimulatorBuildDir" -derivedDataPath "./SimulatorDerivedData" -configuration "Debug" COMPILER_INDEX_STORE_ENABLE=NO -sdk iphonesimulator -arch x86_64 -project "iutest.xcodeproj"

ios-cmake: tmp/ios-cmake
tmp/ios-cmake:
	mkdir -p tmp && cd tmp && git clone https://github.com/leetal/ios-cmake.git

ios-example: ios-cmake ## ios example
	mkdir -p tmp/ios && cd tmp/ios \
	&& cmake ../../../../projects/cmake -G "Xcode" -DCMAKE_XCODE_GENERATE_SCHEME=TRUE -Dbuild_use_gtest_configuration=OFF -DCMAKE_TOOLCHAIN_FILE=../ios-cmake/ios.toolchain.cmake -DPLATFORM=OS64COMBINED \
	&& xcodebuild -project iutest.xcodeproj -list

#
# Mac
#

mac-clean: ## mac example clean
	rm -rf tmp/mac

mac: mac-example ## mac example
	cd tmp/mac && cmake --build ./

mac-xcodebuild: mac-example ## mac example
	cd tmp/mac && xcodebuild -scheme "ALL_BUILD" BUILD_DIR="./tmp/ios/MacDerivedData" -derivedDataPath "./MacDerivedData" -configuration "Debug" COMPILER_INDEX_STORE_ENABLE=NO -arch x86_64 -project "iutest.xcodeproj"

mac-example: ## mac example
	mkdir -p tmp/mac && cd tmp/mac \
	&& cmake ../../../../projects/cmake -G "Xcode" -DCMAKE_XCODE_GENERATE_SCHEME=TRUE -Dbuild_use_gtest_configuration=OFF \
	&& xcodebuild -project iutest.xcodeproj -list

#
#
default: ## cmake default
	mkdir -p tmp/default && cd tmp/default \
	&& cmake ../../../../projects/cmake -Dbuild_use_gtest_configuration=OFF \
	&& cmake --build . \
	&& ctest -T Test .
