{pkgs}: {
  deps = [
    pkgs.gtk3
    pkgs.curl
    pkgs.expat
    pkgs.libGL
    pkgs.xorg.libXcursor
    pkgs.xorg.libXrandr
    pkgs.xorg.libXinerama
    pkgs.xorg.libXext
    pkgs.xorg.libX11
    pkgs.fontconfig
    pkgs.freetype
    pkgs.alsa-lib
    pkgs.pkg-config
    pkgs.cmake
  ];
}
