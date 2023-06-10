{ nixpkgs ? import <nixpkgs> {} }:

nixpkgs.stdenv.mkDerivation {
  pname = "qtwave";
  version = "0.0.0";
  src = builtins.path {
    name = "qtwave";
    path = ./.;
    filter = path: type:
      let lib = nixpkgs.lib;
      in
        (baseNameOf path == ".git" -> type != "directory") &&
        (lib.strings.hasPrefix "build" (baseNameOf path) -> type != "directory") &&
        (baseNameOf path == "result" -> type != "symlink") &&
        !(lib.strings.hasSuffix ".nix" path) &&
        !(lib.strings.hasSuffix ".lock" path) &&
        !(lib.strings.hasSuffix ".user" path)
    ;
  };
  buildInputs = [ nixpkgs.qt6.qtbase ];
  nativeBuildInputs = [ nixpkgs.cmake nixpkgs.qt6.wrapQtAppsHook ];
}
