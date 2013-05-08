target=build-debug/src
[ "$1" == "nvidia" ] && optirunner=optirun
LD_LIBRARY_PATH=${target} $optirunner $target/cw
