let pkgs = import <nixpkgs> { };
in pkgs.haskellPackages.callPackage ./hw4.nix { }