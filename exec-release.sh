target=build-release/src
[ "$1" == "nvidia" ] && optirunner=optirun
LD_LIBRARY_PATH=${target} $optirunner $target/cw
