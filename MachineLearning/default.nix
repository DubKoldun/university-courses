with import <nixpkgs> {};
with pkgs.python3Packages;
buildPythonPackage rec {
  name = "mypackage";
  src = ./.;
  propagatedBuildInputs = [ matplotlib numpy ];
}
