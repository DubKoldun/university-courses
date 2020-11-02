with import <nixpkgs> {};
with pkgs.python3Packages;
buildPythonPackage rec {
  name = "mypackage";
  src = ./.;
  propagatedBuildInputs = [ pip python37Packages.matplotlib python37Packages.ipykernel python37Packages.pandas python37Packages.numpy ];
}