{
  inputs = {
    nixpkgs.url = github:NixOS/nixpkgs/nixos-23.05;
    flake-utils.url = github:numtide/flake-utils;
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
    {
      packages.default = (import ./.) {
        nixpkgs = nixpkgs.legacyPackages.${system};
      };
    });
}
