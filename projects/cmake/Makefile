
help: ## show help
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sed -e 's/^GNUmakefile://' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'

#
# iOS
#

ios-clean: ## ios example clean
	rm -rf tmp/mac

ios: ios-example ## ios example & build
	cd tmp/ios && cmake --build ./

ios-simu: ios-example ## ios simulator example & build
	cd tmp/ios && xcodebuild -scheme "ALL_BUILD" BUILD_DIR="./tmp/ios/SimulatorBuildDir" -derivedDataPath "./SimulatorDerivedData" -configuration "Debug"  COMPILER_INDEX_STORE_ENABLE=NO -sdk iphonesimulator -arch x86_64 -project "iutest.xcodeproj"

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

mac-example: ## mac example
	mkdir -p tmp/mac && cd tmp/mac \
	&& cmake ../../../../projects/cmake -G "Xcode" -DCMAKE_XCODE_GENERATE_SCHEME=TRUE -Dbuild_use_gtest_configuration=OFF \
	&& xcodebuild -project iutest.xcodeproj -list
